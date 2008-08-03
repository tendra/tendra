/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
					 Crown Copyright (c) 1997

	This TenDRA(r) Computer Program is subject to Copyright
	owned by the United Kingdom Secretary of State for Defence
	acting through the Defence Evaluation and Research Agency
	(DERA).  It is made available to Recipients with a
	royalty-free licence for its use, reproduction, transfer
	to other parties and amendment for any purpose not excluding
	product development provided that any such use et cetera
	shall be deemed to be acceptance of the following conditions:-

		(1) Its Recipients shall ensure that this Notice is
		reproduced upon any copies or amended versions of it;

		(2) Any amended version of it shall be clearly marked to
		show both the nature of and the organisation responsible
		for the relevant amendment or amendments;

		(3) Its onward transfer from a recipient to another
		party shall be deemed to be that party's acceptance of
		these conditions;

		(4) DERA gives no warranty or assurance as to its
		quality or suitability for any purpose and DERA accepts
		no liability whatsoever in relation to any use to which
		it may be put.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "exds/common.h"
#include "exds/exception.h"
#include "exds/dalloc.h"
#include "exds/dstring.h"

#include "error/error.h"
#include "xalloc/xalloc.h"

#include "char.h"
#include "localnames.h"
#include "lex.h"
#include "lctlex.h"
#include "c-output.h"
#include "options.h"
#include "output.h"

/*
 * This is populated by the selected output language, set from opt->language.
 * It may be inspected for language-specific regions of the generated code.
 */
enum { C90, C99 } language;

static void
output_keywords(lexer_parse_tree* top_level, FILE *output, FILE *output_h);

/*
	OUTPUT FILE

	This variable gives the main output file.  out is used within this file
	as a shorthand for lex_output. Likewise lex_output_h is a convenience
	for the output header.

	These correspond to options.outputfile[0].file and [1] respectively.
*/

FILE *lex_output;
FILE *lex_output_h;


/*
	FIND A CHARACTER LITERAL

	This routine finds the character literal corresponding to c.
*/

static char *
char_lit(letter_translation* ctrans)
{
	static char buff [10];
	if (ctrans->type == eof_letter) return "LEXI_EOF";
	if (ctrans->type == char_letter) {
	switch (ctrans->u.ch) {
		case '\n': return "'\\n'";
		case '\r': return "'\\r'";
		case '\t': return "'\\t'";
		case '\v': return "'\\v'";
		case '\f': return "'\\f'";
		case '\\': return "'\\\\'";
		case '\'': return "'\\''";
	}
	if (ctrans->u.ch > 127) return "'?'";
	sprintf(buff, "'%c'", (char)ctrans->u.ch);
	return buff;
	}
	else
		return "'?'";
}


/*
	OUTPUT OPTIONS

	The flag in_pre_pass is used to indicate the preliminary pass to
	output_pass.  read_name gives the name of the character reading
	function used in the output routines.
*/

/*static int in_pre_pass = 0;*/
/*static char *read_name = "lexi_readchar";*/
static const char *read_token_name;
static const char *lexi_prefix;


static void 
output_locals(LocalNamesT* locals, int d, FILE* lex_output )
{
	const char* prefixvar = "ZV";
	const char* prefixtype = "ZT";
	char* st;
	char* s = xmalloc_nof(char, locals->max_depth+1);
	LocalNamesIteratorT it ;
	for( localnames_begin(&it, locals); 
	    it.p; 
	    localnamesiterator_next(&it)) {
		EntryT* t;
		LocalNamesEntryT* p= it.p;
		int i;
		s[it.depth]=0;
		for( i = it.depth-1 ; i>=0; --i) {
			/* TODO assert(p) */
			s[i]=p->c;
			p=p->up;
		}
		output_indent(lex_output,d);
		/* TODO assert(entry_is_type(t)); */
		if(t->u.type->mapped) {
			prefixtype="";
			st=nstring_to_cstring(&t->u.type->mapping);
		} else {
			st=nstring_to_cstring(entry_key(t));
		}
	       	fprintf(lex_output,"%s%s %s%s;\n", prefixtype, st, prefixvar, s);
		DEALLOCATE(st);
	}
	xfree(s);
}

static void 
output_action(FILE* lex_output, lexer_parse_tree* top_level, EntryT* action, args_list* lhs, args_list* rhs, int d)
{
	/* TODO assert(entry_is_action(action)) */
	NameTransT trans;
	/* Semi Inefficient : we will recreate the translator stack each time we output the same action:
	    this will never be the same translator stack, however the sort will always give the same permutation:
	    an optimization should be possible here. I don't see it as necessary for the moment.*/
	nametrans_init(&trans, typetuple_length(&action->u.action->inputs)+typetuple_length(&action->u.action->outputs));
	nametrans_append_tuple(&trans,&action->u.action->inputs,rhs);
	nametrans_append_tuple(&trans,&action->u.action->outputs,lhs);
	nametrans_sort(&trans);

	output_indent(lex_output, d);
	fputs("{\n", lex_output);
	++d;
	if(lhs->nb_return_terminal) {
		char* st;
		EntryT* t = lexer_terminal_type(top_level);
		char* prefixtype = "ZT";
		/* TODO assert(entry_is_type(t)); */
		output_indent(lex_output, d);
		if(t->u.type->mapped) {
			prefixtype="";
			st=nstring_to_cstring(&t->u.type->mapping);
		} else {
			st=nstring_to_cstring(entry_key(t));
		}
	       	fprintf(lex_output,"%s%s ZT1;\n", prefixtype, st);
	}
	/* End Semi Inefficient*/
	if(action_is_defined(action->u.action)) {
		ccode_output(lex_output, &action->u.action->code, &trans, d );
		if(lhs->nb_return_terminal) {
			/*TODO assert(lhs->nb_return_terminal==1)*/
			output_indent(lex_output, d);
			fputs("return ZT1;\n",lex_output);
		}
	} else {
		/*TODO We should catch this error before beginning output */
		char* pe=nstring_to_cstring(entry_key(action));
		error(ERROR_SERIOUS, "Action \%s is used but undefined", pe);
		DEALLOCATE(pe);
	}
	--d;
	output_indent(lex_output, d);
	fputs("}\n", lex_output);
}


static void 
output_instructions( zone* z, instructions_list* ret, int n, int d)
{
  instruction* instr;
  int changezone = 0;
  LocalNamesT* locals = instructionslist_localnames(ret);
  if(locals->top) {
    output_indent(lex_output,d);
    fputs("{\n", lex_output);
    ++d;
    output_locals(locals, d, lex_output );
  }
    
  for(instr=ret->head; instr; instr=instr->next) {
    switch(instr->type) {
    case return_terminal :
      /* assert(!instr->next);*/
      output_indent(lex_output, d);
      fprintf(lex_output, "return %s;\n", instr->u.name);
      break;
    case action_call :
      output_action(lex_output, z->top_level, instr->u.act.called_act, instr->u.act.lhs, instr->u.act.rhs, d);
      break;
    case terminal_apply_function:
    case pure_apply_function:
      output_indent(lex_output, d);
      if(instr->type == terminal_apply_function)
	fprintf(lex_output, "return "); 
      fprintf(lex_output, "%s(", instr->u.fun->name);
      {
	arg* fun_args;
	for(fun_args=instr->u.fun->args->head;fun_args;fun_args=fun_args->next) {
	  int i;
	  if(fun_args!=instr->u.fun->args->head) 
	    fputs(", ", lex_output);
	  switch(fun_args->type) {
	  case arg_chars_list:
	    fputs("c0", lex_output);
	    for (i = 1; i < n ; i++)
	      fprintf(lex_output, ", c%d", i);
	    break;
	    
	  case arg_charP:
	    error(ERROR_SERIOUS, "#* Not implemented yet in output.c");
	    break;
	    
	  case arg_litteral:
	    fprintf(lex_output, "%s", fun_args->u.litteral);
	  break;
	  
	  case arg_char_nb:
	    if(fun_args->u.digit <n)
	      fprintf(lex_output, "c%d", fun_args->u.digit);
	    else
	      error(ERROR_SERIOUS, "In #[0-9]* arg, the digit must be smaller than the number of chars in a token");
	    /*Should be caught during parsing*/
	    break;
	  case arg_nb_of_chars:
	    fprintf(lex_output, "%d", n);	  
	  }
	}
      }
      fputs(");\n", lex_output);
      break;
    case push_zone:
      changezone=1;
      if(instr->u.s.z->type == typezone_general_zone) {
	output_indent(lex_output, d);
	fprintf(lex_output, "state->zone_function = %s_%s;\n",
		read_token_name, instr->u.s.z->zone_name);
      }
      if(instr->u.s.z->entering_instructions->head) {
	output_instructions(NULL,instr->u.s.z->entering_instructions,n,d);
      }
      if(instr->u.s.z->entering_instructions->nb_return_terminal == 0) {
	output_indent(lex_output, d);
	switch(instr->u.s.z->type) {
	case typezone_general_zone:
	  fprintf(lex_output,"return %s(state);\n",read_token_name);
	  break;
	case typezone_pseudo_token:
	  fputs("return ", lex_output);
	  /* FALL THROUGH VOLUNTARY*/
	case typezone_pure_function:
	  fprintf(lex_output, "%s_%s(state);\n", read_token_name, instr->u.s.z->zone_name);
	  output_indent(lex_output, d);
	  fputs("goto start;\n", lex_output);
	  break;
	}
      }
      break;
    case pop_zone:
      changezone=1;
      if(z->type == typezone_general_zone) { 
	output_indent(lex_output, d);
	if(instr->u.s.z==instr->u.s.z->top_level->global_zone) {
	  fprintf(lex_output, "state->zone_function = %s;\n",read_token_name);
	} else {
	  fprintf(lex_output, "state->zone_function = %s_%s;\n",read_token_name,
		  instr->u.s.z->zone_name);
	}
      }
      if(!instr->u.s.is_beginendmarker_in_zone) {
	int i;
	for (i = n-1;i>=0;--i) {
	  output_indent(lex_output, d);
	  fprintf(lex_output, "%spush(state, c%d);\n", lexi_prefix, i);
	}
      }
      if(z->leaving_instructions->head) 
	output_instructions(NULL,z->leaving_instructions,n,d);
      if(z->leaving_instructions->nb_return_terminal ==0 ) {
	output_indent(lex_output, d);
	switch(z->type) {
	case typezone_general_zone:
	  fprintf(lex_output,"return %s(state);\n",read_token_name);
	  break;
	case typezone_pure_function:
	  fputs("return;\n", lex_output);
	  break;
	case typezone_pseudo_token:
	  break;
	  /*UNREACHABLE*/ /*TODO assert*/
	}
      }
      break;
    case do_nothing:
      if(instr->next) 
	error(ERROR_SERIOUS, "$$ should only appear at the end of an instruction list"); /*TODO Should be caught during parsing*/
      break;
    }
  }
  if(ret->nb_return_terminal == 0 && !changezone) {
    if(z) {/* if z==NULL, we are in a push or pop zone instruction and can't go to start*/
      output_indent(lex_output, d);
      fputs("goto start;\n",lex_output);
    } 
  }
  if(locals->top) {
    d--;
    output_indent(lex_output,d);
    fputs("}\n", lex_output);
  }

}

/*
  OUTPUT PASS INFORMATION

	This routine outputs code for the lexical pass indicated by p.  n
	gives the depth of recursion and d gives the indentation.
*/

static int
output_pass(zone* z, character* p, int in_pre_pass, int n, int d)
{
	character *q;
	lexer_parse_tree* top_level=z->top_level;
	int cases = 0;
	int classes = 0;
	instructions_list *ret = NULL;
	char* retmap= NULL ;
	char *cond = NULL;
	letter_translation* ctrans;
	zone* scope;

	/* First pass */
	for (q = p->next; q != NULL; q = q->opt) {
	    letter c = q->ch;
	    ctrans=letters_table_get_translation(c,top_level->letters_table);
		if (ctrans->type==last_letter) {
			if(in_pre_pass)
				retmap = q->u.map;
			else
				ret = q->u.definition;
			cond = q->cond;
		} else if (ctrans->type==char_letter || ctrans->type==eof_letter) {
			cases++;
		} else {
			classes++;
		}
	}

	/* Deal with cases */
	if (cases || classes) {
		int w1 = (n == 0 && !in_pre_pass);
		int w2 = (n == 0 && in_pre_pass);
		output_indent(lex_output, d);
		if(!in_pre_pass && z->zone_pre_pass->next)
		  fprintf(lex_output, "int c%d = %s_aux_%s(state)",
			  n, read_token_name, z->zone_name);
		else
		  fprintf(lex_output, "int c%d = %sreadchar(state)", n, lexi_prefix);
		fputs(";\n", lex_output);
		if (w1) {
			output_indent(lex_output, d);
			for(scope=z; scope != NULL; scope=scope->up) {
				if(scope->white_space) {
					if(scope==scope->top_level->global_zone)
						fprintf(lex_output, "if (%sgroup(%sgroup_white, c0)) goto start;\n",
							lexi_prefix, lexi_prefix);
					else 
						fprintf(lex_output,"if (%sgroup(%sgroup_%s_%s, c0)) goto start;\n",
							lexi_prefix, lexi_prefix, scope->zone_name, scope->white_space->name);
					break;
				}
			}
		}
		if (w2) {
			output_indent(lex_output, d);
			fputs("restart: {\n", lex_output);
			d++;
		}

		if (cases > 4) {
			/* Small number of cases */
			output_indent(lex_output, d);
			fprintf(lex_output, "switch (c%d) {\n", n);
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				ctrans=letters_table_get_translation(c,top_level->letters_table);
				if (ctrans->type == char_letter||ctrans->type==eof_letter) {
					output_indent(lex_output, d + 1);
					fprintf(lex_output, "case %s: {\n", char_lit(ctrans));
					if (output_pass(z, q, in_pre_pass, n + 1, d + 2) == 0) {
						output_indent(lex_output, d + 2);
						fputs("break;\n", lex_output);
					}
					output_indent(lex_output, d + 1);
					fputs("}\n", lex_output);
				}
			}
			output_indent(lex_output, d);
			fputs("}\n", lex_output);
		} else {
			/* Large number of cases */
			int started = 0;
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				ctrans=letters_table_get_translation(c,top_level->letters_table);
				if (ctrans->type==char_letter||ctrans->type==eof_letter) {
					output_indent(lex_output, d);
					if (started)
						fputs("} else ", lex_output);
					fprintf(lex_output, "if (c%d == %s) {\n",
								n, char_lit(ctrans));
					output_pass(z, q, in_pre_pass, n + 1, d + 1);
					started = 1;
				}
			}
			if (started) {
				output_indent(lex_output, d);
				fputs("}\n", lex_output);
			}
		}

		if (classes) {
			/* Complex cases */
			int started = 0;
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				ctrans=letters_table_get_translation(c,top_level->letters_table);
				if (ctrans->type==group_letter||ctrans->type==notin_group_letter) {
					char* reverse_match=(ctrans->type==notin_group_letter) ? "!": "";
					char_group *grp=ctrans->u.grp;
					output_indent(lex_output, d);
					if (started)
						fputs("} else ", lex_output);
					if(grp->z==grp->z->top_level->global_zone)
						fprintf(lex_output, "if (%s%sgroup(%sgroup_%s, c%d)) {\n",
							reverse_match, lexi_prefix, lexi_prefix, grp->name, n);
					else
						fprintf(lex_output, "if (%s%sgroup(%s%s_%s, c%d)) {\n",
							reverse_match, lexi_prefix, lexi_prefix, grp->z->zone_name, grp->name, n);
					output_pass(z, q, in_pre_pass, n + 1, d + 1);
					started = 1;
				}
			}
			output_indent(lex_output, d);
			fputs("}\n", lex_output);
		}
		if (w2) {
			d--;
			output_indent(lex_output, d);
			fputs("}\n", lex_output);
		}
		if (n) {
			output_indent(lex_output, d);
			fprintf(lex_output, "%spush(state, c%d);\n", lexi_prefix,n);
		}
	}

	/* Deal with return */
	if (ret||retmap) {
		if (in_pre_pass) {
			char*map=retmap;
		        int m = *(map);
			if (m) {
				char *str;
				if (m == '\\') {
				  letter ca=find_escape((map)[1],top_level->eof_letter_code);
				  ctrans=letters_table_get_translation(ca,top_level->letters_table);
				        str = char_lit(ctrans);
					m = (map) [2];
				} else {
				  ctrans=letters_table_get_translation((letter)m,top_level->letters_table);
					str = char_lit(ctrans);
					m = (map) [1];
				}
				if (m) {
					error(ERROR_SERIOUS, "Bad mapping string, '%s'", map);
				}
				if (cond) {
					output_indent(lex_output, d);
					fprintf(lex_output, "if (%s) {\n", cond);
					output_indent(lex_output, d + 1);
					fprintf(lex_output, "c0 = %s;\n", str);
					output_indent(lex_output, d + 1);
					fputs("goto restart;\n", lex_output);
					output_indent(lex_output, d);
					fputs("}\n", lex_output);
				} else {
					output_indent(lex_output, d);
					fprintf(lex_output, "c0 = %s;\n", str);
					output_indent(lex_output, d);
					fputs("goto restart;\n", lex_output);
				}
			} else {
				output_indent(lex_output, d);
				if (cond)
					fprintf(lex_output, "if (%s) ", cond);
				fputs("goto start;\n", lex_output);
			}
		} else {
			if (cond) {
			output_indent(lex_output, d);
				fprintf(lex_output, "if (%s) {", cond);
				d++;
			}
			output_instructions(z,ret,n,d);
			if (cond) {
			  d--;
			  fprintf(lex_output, "}");
			}
       		}
	}
	return (ret || retmap) && (cond == NULL);
}

static void
output_zone_pass_prototypes(zone *p) 
{
  zone *z;
  for(z=p->next;z!=NULL;z=z->opt) {
    output_zone_pass_prototypes(z);
  }
  if(!(p==p->top_level->global_zone))
    fprintf(lex_output,"static int %s_%s(struct %sstate *state);\n",
		read_token_name,p->zone_name, lexi_prefix);
}

static void
output_zone_prepass(zone *p) 
{
    zone *z;
    int in_pre_pass=1;
    for(z=p->next;z!=NULL;z=z->opt) {
      output_zone_prepass(z);
    }
    if(p->zone_pre_pass->next) {
      fprintf(lex_output,"/* PRE PASS ANALYSER for zone %s*/\n\n",p->zone_name);
      fprintf(lex_output,"static int %s_aux_%s(struct %sstate *state)\n", read_token_name,
	      p->zone_name, lexi_prefix);
      fputs("{\n", lex_output);
      fputs("\tstart: {\n", lex_output);
      output_pass(p, p->zone_pre_pass, in_pre_pass, 0, 2);
      fputs("\treturn c0;\n", lex_output);
      fputs("\t}\n", lex_output);
      fputs("}\n\n\n", lex_output);
    }
    return;
}

static void
output_zone_pass(cmd_line_options *opt, zone *p) 
{
    zone *z;
    int in_pre_pass=0;
    int is_p_global_zone=(p==p->top_level->global_zone);
    for(z=p->next;z!=NULL;z=z->opt) {
        output_zone_pass(opt, z);
    }
    fprintf(lex_output,"/* MAIN PASS ANALYSER for zone %s*/\n\n",p->zone_name);
    if(is_p_global_zone) {
       	fprintf(lex_output,"int\n%s(struct %sstate *state)\n",
		read_token_name, lexi_prefix);
	fputs("{\n", lex_output);
	if(p->top_level->global_zone->next!=NULL) {
	  fprintf(lex_output, "\tif(state->zone_function != %s)\n", read_token_name);
	  fprintf(lex_output, "\t\treturn (*state->zone_function)(state);\n");
	}
    }
    else {
        fprintf(lex_output,"static int\n%s_%s(struct %sstate *state)\n",
	read_token_name, p->zone_name, lexi_prefix);
	fputs("{\n", lex_output);
    }
    fputs("\tstart: {\n", lex_output);
    output_pass(p, p->zone_main_pass, in_pre_pass, 0, 2);
    if(p->default_instructions) {
        int dd=2;
	if(p->default_cond) {
	    fprintf(lex_output,"\tif(%s) {\n\t",p->default_cond);
	    dd=4;
        }
        output_instructions(p,p->default_instructions,1,dd);
        if(p->default_cond) 
	    fprintf(lex_output,"}\n");
    } 
    else 
        fprintf(lex_output, "\t\treturn %sunknown_token;\n",
			opt->interface_prefix);
    fputs("\t}\n", lex_output);
    fputs("}\n", lex_output);
    return;
}

/*
	OUTPUT COPYRIGHT

	This routine outputs the copyright statement and closes opt->copyright_file.
*/
static void
output_copyright(lexer_parse_tree* top_level, cmd_line_options* opt)
{
	if(!opt->copyright_file) {
		return;
	}

	if(!output_comment_file(OUTPUT_COMMENT_C90, lex_output, opt->copyright_file)) {
		error(ERROR_SERIOUS,"Copyright file contains comment characters");
	}

	rewind(opt->copyright_file);
	if(!output_comment_file(OUTPUT_COMMENT_C90, lex_output_h, opt->copyright_file)) {
		error(ERROR_SERIOUS,"Copyright file contains comment characters");
	}

	return;
}

/*
  OUTPUT THE MACROS NEEDED TO ACCESS THE LOOKUP TABLE
*/

static void
output_macros(cmd_line_options* opt, lexer_parse_tree* top_level, const char *grouptype, 
		    const char *grouphex,size_t groupwidth) 
{
	char_group* grp;

	fprintf(lex_output_h, "enum %sgroups {\n", opt->lexi_prefix);

	/* Group interface */
	for( grp=top_level->groups_list.head; grp!=NULL; grp=grp->next_in_groups_list) {
		unsigned long m = (unsigned long)(1 << grp->group_code);
		if(grp->z==grp->z->top_level->global_zone) {
			fprintf(lex_output_h, "\t%sgroup_%s = ",
				opt->lexi_prefix, grp->name);
		} else {
			fprintf(lex_output_h, "\t%sgroup_%s_%s = ",
				opt->lexi_prefix, grp->z->zone_name, grp->name);
		}
		fprintf(lex_output_h, grouphex, m);

		if(grp->next_in_groups_list) {
			fputs(",", lex_output_h);
		}

		fputs("\n", lex_output_h);
	}

	fputs("};\n", lex_output_h);

	fputs("\n/* true if the given character is present in the given group */\n",
		lex_output_h);
	fprintf(lex_output_h, "%s %sgroup(enum %sgroups group, int c);\n",
		language == C90 ? "int" : "bool", opt->lexi_prefix, opt->lexi_prefix);

	/*
	 * I'm presenting an int here for multibyte character literals, although
	 * the lookup-table behind them is not that wide. Furthermore, it helps set
	 * my mind at ease for lexers generated on machines with different signedness
	 * for char than the machine upon which the generated lexer is compiled.
	 */
	fprintf(lex_output, "%s %sgroup(enum %sgroups group, int c) {\n",
		language == C90 ? "int" : "bool", opt->lexi_prefix, opt->lexi_prefix);
	fputs("\treturn lookup_tab[c] & group;\n", lex_output);
	fputs("}\n", lex_output);
}

/*
  OUTPUT THE LOOKUP TABLE
*/

static void
output_lookup_table(cmd_line_options* opt, lexer_parse_tree* top_level, const char *grouptype, 
		    const char *grouphex, size_t groupwidth) 
{
	int c;
	char_group* grp;
	/* Character look-up table */
	fputs("/* LOOKUP TABLE */\n\n", lex_output);
	fprintf(lex_output, "typedef %s lookup_type;\n", grouptype);
	fputs("static lookup_type lookup_tab[257] = {\n", lex_output);
	for (c = 0; c <= 256; c++) {
		unsigned long m = 0;
		letter a = (c == 256 ? top_level->eof_letter_code : (letter)c);
		m = 0;
		for( grp=top_level->groups_list.head; grp!=NULL; grp=grp->next_in_groups_list) {
			if (in_group(grp, a)) {
				m |= (unsigned long)(1 << grp->group_code);
			}
		}
		if ((c % groupwidth) == 0)
			fputs("\t", lex_output);
		fprintf(lex_output, grouphex, m);
		if (c != 256) {
			if ((c % groupwidth) == groupwidth - 1) {
				fputs(",\n", lex_output);
			} else {
				fputs(", ", lex_output);
			}
		}
	}
	fputs("\n};",lex_output);
}

/* 
   OUTPUT LEXI AUTOMATED DEFINED OPERATIONS 

*/

static void
output_buffer(cmd_line_options* opt) 
{
	/* Buffer operations */
	fputs("/* Push a character to lexi's buffer */\n", lex_output_h);
	fprintf(lex_output_h, "void %spush(struct %sstate *state, const int c);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_output, "void %spush(struct %sstate *state, const int c) {\n",
		lexi_prefix, lexi_prefix);
	if(opt->generate_asserts) {
		fputs("\tassert(state);\n", lex_output);
		fputs("\tassert(state->buffer_index < sizeof state->buffer / sizeof *state->buffer);\n", lex_output);
	}
	fputs("\tstate->buffer[state->buffer_index++] = c;\n", lex_output);
	fputs("}\n\n", lex_output);

	fputs("/* Pop a character from lexi's buffer */\n", lex_output_h);
	fprintf(lex_output_h, "int %spop(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_output, "int %spop(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);
	if(opt->generate_asserts) {
		fputs("\tassert(state);\n", lex_output);
		fputs("\tassert(state->buffer_index > 0);\n", lex_output);
	}
	fputs("\treturn state->buffer[--state->buffer_index];\n", lex_output);
	fputs("}\n\n", lex_output);

	fputs("/* Flush lexi's buffer */\n", lex_output_h);
	fprintf(lex_output_h, "void %sflush(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_output, "void %sflush(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);
	fputs("\tstate->buffer_index = 0;\n", lex_output);
	fputs("}\n\n", lex_output);

	/* TODO nice thing: we can abstract away 'aux() here, too. */
	fputs("/* Read a character */\n", lex_output_h);
	fprintf(lex_output_h, "int %sreadchar(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_output,"int %sreadchar(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);
	fputs("\tif(state->buffer_index) {\n", lex_output);
	fprintf(lex_output,"\t\treturn %spop(state);\n", lexi_prefix);
	fputs("\t}\n\n", lex_output);
	/* TODO pass opaque here */
	fprintf(lex_output, "\treturn %sgetchar();\n", opt->interface_prefix);
	fputs("}\n", lex_output);
}

void 
output_headers()
{
	ccode_output(lex_output_h, &(global_lct_parse_tree.hfileheader), NULL, 0);
	ccode_output(lex_output, &(global_lct_parse_tree.cfileheader), NULL, 0);
}

void 
output_trailers()
{
	ccode_output(lex_output_h, &(global_lct_parse_tree.hfiletrailer),NULL,0);
	ccode_output(lex_output, &(global_lct_parse_tree.cfiletrailer),NULL,0);
}

void
c_output_all(cmd_line_options *opt, lexer_parse_tree* top_level)
{
	int in_pre_pass; /*boolean*/
	size_t groupwidth;
	const char *grouptype;
	const char *grouphex;

	assert(!strcmp(opt->language, "C90") || !strcmp(opt->language, "C99"));
	language = !strcmp(opt->language, "C90") ? C90 : C99;

	lex_output = opt->outputfile[0].file;
	lex_output_h = opt->outputfile[1].file;

	read_token_name = xstrcat(opt->lexi_prefix, "read_token");
	lexi_prefix = opt->lexi_prefix;

	/*
	 * Here we ouput exact-width types from stdint.h for C99, and appropiate
	 * types based on their respective minimum maxiums otherwise. These types
	 * may be larger than required on some systems, but that's ok.
	 */
	if (top_level->no_total_groups >= 16) {
		grouptype = language == C99 ? "uint32_t" : "unsigned long";
		grouphex = "0x%08lxUL";
		groupwidth = 2;
	} else if (top_level->no_total_groups >= 8) {
		grouptype = language == C99 ? "uint16_t" : "unsigned short";
		grouphex = "0x%04lx";
		groupwidth = 4;
	} else {
		grouptype = language == C99 ? "uint8_t" : "unsigned char";
		grouphex = "0x%02lx";
		groupwidth = 8;
	}



	output_copyright(top_level,opt);

	output_generated_by_lexi(OUTPUT_COMMENT_C90, lex_output);

	output_generated_by_lexi(OUTPUT_COMMENT_C90, lex_output_h);
	fprintf(lex_output_h, "#ifndef LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fprintf(lex_output_h, "#define LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fputs("\n", lex_output_h);

	if(opt->outputfile[1].name) {
		fprintf(lex_output, "#include \"%s\"\n\n", opt->outputfile[1].name);
	}

	output_headers() ;

	if(opt->generate_asserts) {
		fputs("#include <assert.h>\n", lex_output);
	}
	if(language == C99) {
		fputs("#include <stdbool.h>\n", lex_output);
		fputs("#include <stdbool.h>\n\n", lex_output_h);
		fputs("#include <stdint.h>\n\n", lex_output);
	}

	fputs("/*\n"
		" * This struct holds state for the lexer; its representation is\n"
		" * private, but present here for ease of allocation.\n"
		" */\n", lex_output_h);
	fprintf(lex_output_h, "struct %sstate {\n"
	      "\tint (*zone_function)(struct %sstate *);\n",
		opt->lexi_prefix, opt->lexi_prefix);

	/* Buffer storage */
	fputs("\n", lex_output_h);
	fputs("\t/*\n", lex_output_h);
	fputs("\t * Lexi's buffer is a simple stack. The size is calculated as\n", lex_output_h);
	fputs("\t * max(mapping) - 1 + max(token) - 1\n", lex_output_h);
	fputs("\t */\n", lex_output_h);
	if(top_level->global_zone->zone_pre_pass->next) {
		fprintf(lex_output_h, "\tint buffer[%u - 1 + %u - 1];\n",
			zone_maxlength(top_level->global_zone, 1), 
			zone_maxlength(top_level->global_zone, 0));
	} else {
		fprintf(lex_output_h, "\tint buffer[%u - 1];\n",
			zone_maxlength(top_level->global_zone, 0));
	}
	fputs("\tint buffer_index;\n", lex_output_h);
	fputs("};\n\n", lex_output_h);

	output_lookup_table(opt,top_level,grouptype,grouphex,groupwidth);
	fputs("\n\n", lex_output);

	fputs("#ifndef LEXI_EOF\n", lex_output_h);
	fprintf(lex_output_h, "#define LEXI_EOF %u\n", top_level->eof_letter_code);
	fputs("#endif\n\n", lex_output_h);

	output_buffer(opt);
	fputs("\n", lex_output);

	output_macros(opt,top_level,grouptype,grouphex,groupwidth);
	fputs("\n\n", lex_output);


	/* Keywords */
	output_keywords(top_level, lex_output, lex_output_h);


	/* Lexical pre-pass */
	in_pre_pass=1;
	fputs("/* PRE-PASS ANALYSERS */\n\n", lex_output);
	output_zone_prepass(top_level->global_zone);

	/* Main pass */

	in_pre_pass = 0;

	fputs("\n/* Identify a token */\n", lex_output_h);
	fprintf(lex_output_h, "int %s(struct %sstate *state);\n\n",
		read_token_name, lexi_prefix);

	/* lexi_init() */
	/* TODO assert() state */
	fprintf(lex_output_h, "/* Initialise a %sstate structure */\n",
		opt->lexi_prefix);
	fprintf(lex_output_h, "void %sinit(struct %sstate *state);\n\n",
		opt->lexi_prefix, opt->lexi_prefix);
	fprintf(lex_output,"void %sinit(struct %sstate *state) {\n"
		"\tstate->zone_function = %s;\n"
		"\tstate->buffer_index = 0;\n"
		"}\n",
		opt->lexi_prefix, opt->lexi_prefix,
		read_token_name);

	fputs("/* ZONES PASS ANALYSER PROTOTYPES*/\n\n", lex_output);
	output_zone_pass_prototypes(top_level->global_zone);

	fputs("/* MAIN PASS ANALYSERS */\n\n", lex_output);
  	output_zone_pass(opt, top_level->global_zone);

	fputs("#endif\n", lex_output_h);
	output_trailers() ;
	fputs("\n", lex_output);
	fputs("\n", lex_output_h);

  	return;
}

/*
	KEYWORDS GENERATION

	This routine outputs a type-agnostic keyword interface.

	TODO at some point (where the code is clearer), this can
	be rewritten to generate and output a trie in its own right.
	For the moment, we just need the interface in place to set
	the generated API.
*/
static void
output_keywords(lexer_parse_tree* top_level, FILE *output, FILE *output_h)
{
	keyword *p;

	fputs("\n/* Identify a keyword */\n", output_h);
	fprintf(output_h, "int %skeyword(const char *identifier, int notfound);\n",
		lexi_prefix);

	fprintf(output, "#include <string.h>\n");
	fprintf(output, "int %skeyword(const char *identifier, int notfound) {\n",
		lexi_prefix);

	for (p = top_level->global_zone->keywords; p; p = p->next) {
		fprintf(output, "\tif(");

		if(p->cond) {
			fprintf(output, "%s && ", p->cond);
		}

		fprintf(output, "!strcmp(identifier, \"%s\")) return ",
			p->name);

		switch(p->instr->type) {
		case pure_apply_function:
			/*
			 * Arguments are not permitted for functions in
			 * keyword instructions.
			 */
			fprintf(output, "%s()", p->instr->u.fun->name);
			break;

		case return_terminal:
			fprintf(output, "%s", p->instr->u.name);
			break;

		default:
			assert(!"unrecognised instruction type for keyword");
		}

		fprintf(output, ";\n");
	}

	fprintf(output, "\treturn notfound;\n}\n");

	return;
}

