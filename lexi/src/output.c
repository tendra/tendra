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

#include "error.h"
#include "xalloc.h"

#include "char.h"
#include "lex.h"
#include "output.h"
#include "options.h"

/*
	OUTPUT FILE

	This variable gives the main output file.  out is used within this file
	as a shorthand for lex_output.
*/

FILE *lex_output;


/*
	OUTPUT INDENTATION

	This routine outputs an indentation of d.
*/

static void
output_indent(int d)
{
	while(d --> 0)
		fputc('\t', lex_output);
}


/*
	FIND A CHARACTER LITERAL

	This routine finds the character literal corresponding to c.
*/

static char *
char_lit(letter_translation* ctrans)
{
	static char buff [10];
	if (ctrans->type == eof_letter) return("LEX_EOF");
	if (ctrans->type == char_letter) {
	switch (ctrans->u.ch) {
		case '\n': return("'\\n'");
		case '\r': return("'\\r'");
		case '\t': return("'\\t'");
		case '\v': return("'\\v'");
		case '\f': return("'\\f'");
		case '\\': return("'\\\\'");
		case '\'': return("'\\''");
	}
	if (ctrans->u.ch > 127) return("'?'");
	sprintf(buff, "'%c'", (char)ctrans->u.ch);
	return(buff);
	}
	else
		return("'?'");	  
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

static	void 
output_actions( zone* z, instructions_list* ret, int n, int d)
{
  instruction* instr;
  for(instr=ret->head; instr; instr=instr->next) {
    switch(instr->type) {
    case return_token :
      /* assert(!instr->next);*/
      output_indent(d);
      fprintf(lex_output, "return(%s);\n", instr->u.name);
      break;
    case apply_function:
      output_indent(d);
      if(!(instr->next))
	fprintf(lex_output, "return(");
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
      fputs(")", lex_output);
      if(!(instr->next))
	fputs(")", lex_output);
      fputs(";\n", lex_output);
      break;
    case push_zone:
      output_indent(d);
      fprintf(lex_output, "state->zone_function=&%s_%s;\n",read_token_name,
	      instr->u.z->zone_name);
      if(instr->u.z->entering_instructions->head) 
	output_actions(NULL,instr->u.z->entering_instructions,n,d);
      else {
	output_indent(d);
	fprintf(lex_output,"return(%s(state));\n",read_token_name);
      }
      break;
    case pop_zone:
      output_indent(d);
      if(instr->u.z==instr->u.z->top_level->global_zone)
	fprintf(lex_output, "state->zone_function=&%s;\n",read_token_name);	
      else
	fprintf(lex_output, "state->zone_function=&%s_%s;\n",read_token_name,
		instr->u.z->zone_name);
      if(z->leaving_instructions->head) 
	output_actions(NULL,z->leaving_instructions,n,d);
      else {
	output_indent(d);
	fprintf(lex_output,"return(%s(state));\n",read_token_name);
      }
      break;
    case do_nothing:
      if(instr->next) 
	error(ERROR_SERIOUS, "$$ should only appear at the end of an instruction list");
/*Should be caught during parsing*/
  /* assert(!instr->next);*/
      output_indent(d);
      if(z) /* if z==NULL, we are in a push or pop zone action and can't go to start*/
	fputs("goto start;\n",lex_output);	  	
      else /*We're outputting entering and leaving actions.*/
	fprintf(lex_output,"return(%s(state));\n",read_token_name);	  
      break;
    }
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
		output_indent(d);
		if(!in_pre_pass && z->zone_pre_pass->next)
		  fprintf(lex_output, "int c%d = %s_aux_%s()", 
			  n, read_token_name, z->zone_name);
		else
		    fprintf(lex_output, "int c%d = lexi_readchar()", n);
		fputs(";\n", lex_output);
		if (w1) {
			output_indent(d);
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
			output_indent(d);
			fputs("restart: {\n", lex_output);
			d++;
		}

		if (cases > 4) {
			/* Small number of cases */
			output_indent(d);
			fprintf(lex_output, "switch (c%d) {\n", n);
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				ctrans=letters_table_get_translation(c,top_level->letters_table);
				if (ctrans->type == char_letter||ctrans->type==eof_letter) {
					output_indent(d + 1);
					fprintf(lex_output, "case %s: {\n", char_lit(ctrans));
					if (output_pass(z, q, in_pre_pass, n + 1, d + 2) == 0) {
						output_indent(d + 2);
						fputs("break;\n", lex_output);
					}
					output_indent(d + 1);
					fputs("}\n", lex_output);
				}
			}
			output_indent(d);
			fputs("}\n", lex_output);
		} else {
			/* Large number of cases */
			int started = 0;
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				ctrans=letters_table_get_translation(c,top_level->letters_table);
				if (ctrans->type==char_letter||ctrans->type==eof_letter) {
					output_indent(d);
					if (started)
						fputs("} else ", lex_output);
					fprintf(lex_output, "if (c%d == %s) {\n",
								n, char_lit(ctrans));
					output_pass(z, q, in_pre_pass, n + 1, d + 1);
					started = 1;
				}
			}
			if (started) {
				output_indent(d);
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
					output_indent(d);
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
			output_indent(d);
			fputs("}\n", lex_output);
		}
		if (w2) {
			d--;
			output_indent(d);
			fputs("}\n", lex_output);
		}
		if (n) {
			output_indent(d);
			fprintf(lex_output, "%spush(c%d);\n", lexi_prefix,n);
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
					output_indent(d);
					fprintf(lex_output, "if (%s) {\n", cond);
					output_indent(d + 1);
					fprintf(lex_output, "c0 = %s;\n", str);
					output_indent(d + 1);
					fputs("goto restart;\n", lex_output);
					output_indent(d);
					fputs("}\n", lex_output);
				} else {
					output_indent(d);
					fprintf(lex_output, "c0 = %s;\n", str);
					output_indent(d);
					fputs("goto restart;\n", lex_output);
				}
			} else {
				output_indent(d);
				if (cond)
					fprintf(lex_output, "if (%s) ", cond);
				fputs("goto start;\n", lex_output);
			}
		} else {
			if (cond) {
			output_indent(d);
				fprintf(lex_output, "if (%s) {", cond);
				d++;
			}
			output_actions(z,ret,n,d);
			if (cond) {
			  d--;
			  fprintf(lex_output, "}", cond);
			}
       		}
	}
	return(((ret||retmap) && (cond == NULL))? 1 : 0);
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
      fprintf(lex_output,"static int %s_aux_%s(void)\n", read_token_name,
	    p->zone_name);
      fputs("{\n", lex_output);
      fputs("\tstart: {\n", lex_output);
      output_pass(p, p->zone_pre_pass, in_pre_pass, 0, 2);
      fputs("\treturn(c0);\n", lex_output);
      fputs("\t}\n", lex_output);
      fputs("}\n\n\n", lex_output);
    }
    return;
}

static void
output_zone_pass(zone *p) 
{
    zone *z;
    int in_pre_pass=0;
    int is_p_global_zone=(p==p->top_level->global_zone);
    int has_zones=(p->top_level->global_zone->next!=NULL);
    for(z=p->next;z!=NULL;z=z->opt) {
        output_zone_pass(z);
    }
    fprintf(lex_output,"/* MAIN PASS ANALYSER for zone %s*/\n\n",p->zone_name);
    if(is_p_global_zone) {
       	fprintf(lex_output,"int\n%s(struct %sstate *state)\n",
		read_token_name, lexi_prefix);
	fputs("{\n", lex_output);
	if(p->top_level->global_zone->next!=NULL) {
	  fprintf(lex_output,"\tif(state->zone_function!=&%s)\n",read_token_name);
	  fprintf(lex_output, "\t\treturn ((*state->zone_function)(state));\n");
	}
    }
    else {
        fprintf(lex_output,"static int\n%s_%s(struct %sstate *state)\n",
	read_token_name,p->zone_name, lexi_prefix);
	fputs("{\n", lex_output);
    }
    fputs("\tstart: {\n", lex_output);
    output_pass(p, p->zone_main_pass, in_pre_pass, 0, 2);
    if(p->default_actions) {
        int dd=2;
	if(p->default_cond) {
	    fprintf(lex_output,"\tif(%s) {\n\t",p->default_cond);
	    dd=4;
        }
        output_actions(p,p->default_actions,1,dd);
        if(p->default_cond) 
	    fprintf(lex_output,"}\n",p->default_cond);
    } 
    else 
        fputs("\t\treturn(unknown_token(c0));\n", lex_output);
    fputs("\t}\n", lex_output);
    fputs("}\n", lex_output);
    return;
}

/*
  Check if input copyright file contains only comments.
  Return 0 if successful, 1 if the file contains things that are not comments
  and 2 if the file finish while in a comment.

  TODO: we should use lexi to generate this.
*/
static int 
check_if_file_is_comment(FILE* input)
{
	int state = 0;
	int c;
	while((c=fgetc(input))!=EOF) {
		switch(state) {
		case 0:
			while(isspace(c))
				c=fgetc(input);
			if(c==EOF)
				ungetc(c, input);
			else if ( c == '/' && fgetc(input)=='*') {
				state=1;
			} else
				return 1; /*Contains a non space character outside of a comment*/
			break;
		case 1:
			while((c=fgetc(input))!=EOF && c!='*')
		  		;
			if(c==EOF)
				return 2; /*EOF while in a comment */
			else if (fgetc(input)=='/')
				state=0;
			break;
		}
		
	}
	return 0; /*Only contains comments*/
}

/* 
   COMMENT FILE

   cat input into output, commenting as appropiate.
   Returns false if the input file was found to have
   contained an illegal comment.
*/
static int
comment_file(FILE* output, FILE* input, const char *start, const char *middle, const char *end) {
    char buf[BUFSIZ];

    fprintf(output, "%s \n%s ", start, middle);
    while(1) {
        buf[BUFSIZ - 1] = 'x';

        if(!fgets(buf, sizeof buf, input)) {
            break;
        }

        if(strstr(buf, end)) {
            return 0;
        }

        fputs(buf, output);

        if(!(buf[BUFSIZ - 1] == '\0' && buf[BUFSIZ - 2] != '\n')) {
            fprintf(output, "%s ", middle);
        }
    }
    fprintf(output, "\n %s\n", end);

    return 1;
}

/*
	OUTPUT COPYRIGHT

	This routine outputs the copyright statement
*/
static void
output_copyright(lexer_parse_tree* top_level, cmd_line_options* opt)
{
	if(opt->copyright_file_cmd_line || top_level->copyright_file) {
		FILE* copyright_file= opt->copyright_file_cmd_line ? opt->copyright_file_cmd_line : top_level->copyright_file;

		if(!comment_file(opt->lex_output, copyright_file, "/*", " *", "*/")) {
			error(ERROR_SERIOUS,"Copyright file contains comment characters");
		}

		rewind(copyright_file);
		if(!comment_file(opt->lex_output_h, copyright_file, "/*", " *", "*/")) {
			error(ERROR_SERIOUS,"Copyright file contains comment characters");
		}
	}
	if(opt->copyright_file_cmd_line)
		fclose(opt->copyright_file_cmd_line);
	if(top_level->copyright_file)
		fclose(top_level->copyright_file);
	return;
}

/* 
   OUTPUT GENERATED BY LEXI Version

   This routine outputs a statement stating that the file is automatically
   generated.

*/

static void 
output_generated_by_lexi(FILE* out) 
{
	fputs("/*\n *  AUTOMATICALLY GENERATED", out);
	fprintf(out, " BY %s VERSION %s", progname, progvers);
	fputs("\n */\n", out);
}

/*
  OUTPUT THE MACROS NEEDED TO ACCESS THE LOOKUP TABLE
*/

static void
output_macros(cmd_line_options* opt, lexer_parse_tree* top_level, const char *grouptype, 
		    const char *grouphex,size_t groupwidth) 
{
	int n;
	char_group* grp;

	fprintf(opt->lex_output_h, "enum %sgroups {\n", opt->lexi_prefix);

	/* Group interface */
	for( grp=top_level->groups_list.head; grp!=NULL; grp=grp->next_in_groups_list) {
		char *gnm;
		unsigned long m = (unsigned long)(1 << grp->group_code);
		if(grp->z==grp->z->top_level->global_zone) {
			fprintf(opt->lex_output_h, "\t%sgroup_%s = ",
				opt->lexi_prefix, grp->name, opt->lexi_prefix);
		} else {
			fprintf(opt->lex_output_h, "\t%sgroup_%s_%s = ",
				opt->lexi_prefix, grp->z->zone_name, grp->name, opt->lexi_prefix);
		}
		fprintf(opt->lex_output_h, grouphex, m);

		if(grp->next_in_groups_list) {
			fputs(",", opt->lex_output_h);
		}

		fputs("\n", opt->lex_output_h);
	}

	fputs("};\n", opt->lex_output_h);

	fputs("\n/* true if the given character is present in the given group */\n",
		opt->lex_output_h);
	fprintf(opt->lex_output_h, "extern int %sgroup(enum %sgroups group, int c);\n",
		opt->lexi_prefix, opt->lexi_prefix);

	/*
	 * I'm presenting an int here for multibyte character literals, although
	 * the lookup-table behind them is not that wide. Furthermore, it helps set
	 * my mind at ease for lexers generated on machines with different signedness
	 * for char than the machine upon which the generated lexer is compiled.
	 */
	fprintf(opt->lex_output, "int %sgroup(enum %sgroups group, int c) {\n",
		opt->lexi_prefix, opt->lexi_prefix);
	fputs("\treturn lookup_tab[c] & group;\n", opt->lex_output);
	fputs("}\n", opt->lex_output);
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
	fprintf(opt->lex_output, "typedef %s lookup_type;\n", grouptype);
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
output_buffer(cmd_line_options* opt, lexer_parse_tree* top_level) 
{
	/* Buffer operations */
	fputs("/*\n", lex_output);
	fputs(" * Lexi's buffer is a simple stack. The size is calculated as\n", lex_output); 
	fputs(" * max(mapping) - 1 + max(token) - 1\n", lex_output);
	fputs(" */\n", lex_output);
	if(top_level->global_zone->zone_pre_pass->next) {
		fprintf(lex_output, "static int buffer[%u - 1 + %u - 1];\n",
			char_maxlength(top_level->global_zone,top_level->global_zone->zone_pre_pass), 
			char_maxlength(top_level->global_zone,top_level->global_zone->zone_main_pass));
	} else {
		fprintf(lex_output, "static int buffer[%u - 1];\n",
			char_maxlength(top_level->global_zone,top_level->global_zone->zone_main_pass));
	}
	fputs("static int buffer_index;\n\n", lex_output);

	fputs("/* Push a character to lexi's buffer */\n", lex_output);
	fprintf(opt->lex_output_h, "extern void %spush(const int c);\n", lexi_prefix);
	fprintf(lex_output, "void %spush(const int c) {\n", lexi_prefix);
	if(opt->generate_asserts) {
		fputs("\tassert(buffer_index < sizeof buffer / sizeof *buffer);\n", lex_output);
	}
	fputs("\tbuffer[buffer_index++] = c;\n", lex_output);
	fputs("}\n\n", lex_output);

	fputs("/* Pop a character from lexi's buffer */\n", lex_output);
	fprintf(opt->lex_output_h, "extern int %spop(void);\n", lexi_prefix);
	fprintf(lex_output, "int %spop(void) {\n", lexi_prefix);
	if(opt->generate_asserts) {
		fputs("\tassert(buffer_index > 0);\n", lex_output);
	}
	fputs("\treturn buffer[--buffer_index];\n", lex_output);
	fputs("}\n\n", lex_output);

	fputs("/* Flush lexi's buffer */\n", lex_output);
	fprintf(opt->lex_output_h, "extern void %sflush(void);\n", lexi_prefix);
	fprintf(lex_output, "void %sflush(void) {\n", lexi_prefix);
	fputs("\tbuffer_index = 0;\n", lex_output);
	fputs("}\n\n", lex_output);

	/* TODO nice thing: we can abstract away 'aux() here, too. */
	fputs("/* Read a character */\n", lex_output);
	fprintf(opt->lex_output_h, "extern int %sreadchar(void);\n", lexi_prefix);
	fprintf(lex_output,"int %sreadchar(void) {\n", lexi_prefix);
	fputs("\tif(buffer_index) {\n", lex_output);
	fprintf(lex_output,"\t\treturn %spop();\n", lexi_prefix);
	fputs("\t}\n\n", lex_output);
	fputs("\treturn read_char();\n", lex_output);
	fputs("}\n", lex_output);
}

/*
	MAIN OUTPUT ROUTINE

	This routine is the entry point for the main output routine.
*/

void
output_all(cmd_line_options *opt, lexer_parse_tree* top_level)
{
	int c, n;
	int in_pre_pass; /*boolean*/
	size_t groupwidth;
	const char *grouptype;
	const char *grouphex;

	lex_output=opt->lex_output;
	read_token_name = xstrcat(opt->lexi_prefix, "read_token");
	lexi_prefix = opt->lexi_prefix;

	FILE* lex_state_output= opt->lex_output_h;

	if (top_level->no_total_groups >= 16) {
		grouptype = "uint32_t";
		grouphex = "0x%08lxUL";
		groupwidth = 2;
	} else if (top_level->no_total_groups >= 8) {
		grouptype = "uint16_t";
		grouphex = "0x%04lx";
		groupwidth = 4;
	} else {
		grouptype = "uint8_t";
		grouphex = "0x%02lx";
		groupwidth = 8;
	}



	output_copyright(top_level,opt);
	fputs("\n",opt->lex_output);

	output_generated_by_lexi(opt->lex_output);
	fputs("\n",opt->lex_output);

	output_generated_by_lexi(opt->lex_output_h);
	fputs("\n",opt->lex_output_h);
	fprintf(opt->lex_output_h,"#ifndef LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fprintf(opt->lex_output_h,"#define LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fputs("\n",opt->lex_output_h);
	fprintf(opt->lex_output,"#include \"%s\"\n\n",opt->lex_output_h_filename);

	if(opt->generate_asserts) {
		fputs("#include <assert.h>\n", lex_output);
	}
	fputs("#include <stdint.h>\n\n", opt->lex_output);
	fputs("/*\n"
		" * This struct holds state for the lexer; its representation is\n"
		" * private, but present here for ease of allocation.\n"
		" */\n", opt->lex_output_h);
	fprintf(opt->lex_output_h,"struct %sstate {\n"
	      "\tint (*zone_function)(struct %sstate *);\n"
		"};\n", opt->lexi_prefix, opt->lexi_prefix);

	output_lookup_table(opt,top_level,grouptype,grouphex,groupwidth);
	fputs("\n\n", lex_output);	

	fputs("#ifndef LEX_EOF\n", lex_state_output);
	fprintf(lex_state_output,"#define LEX_EOF\t\t%u\n", top_level->eof_letter_code);
	fputs("#endif\n\n", lex_state_output);

	output_buffer(opt, top_level);
	fputs("\n", lex_output);

	output_macros(opt,top_level,grouptype,grouphex,groupwidth);
	fputs("\n\n", lex_output);


	/* Keywords */
	output_keywords(top_level, opt->lex_output, opt->lex_output_h);


	/* Lexical pre-pass */
	in_pre_pass=1;
	fputs( "/* PRE-PASS ANALYSERS */\n\n", lex_output);
	output_zone_prepass(top_level->global_zone);

	/* Main pass */

	in_pre_pass = 0;

	bool has_zones=(top_level->global_zone->next!=NULL);

	fprintf(opt->lex_output_h,"\nextern int %s(struct %sstate *state);\n",
		read_token_name, lexi_prefix);

	/* lexi_init() */
	/* TODO assert() state */
	fprintf(opt->lex_output_h,"void %sinit(struct %sstate *state);\n",
		opt->lexi_prefix, opt->lexi_prefix);
	fprintf(lex_output,"void %sinit(struct %sstate *state) {\n"
		"\tstate->zone_function = &%s;\n"
		"}\n",
		opt->lexi_prefix, opt->lexi_prefix,
		read_token_name);

	fputs("/* ZONES PASS ANALYSER PROTOTYPES*/\n\n", lex_output);
	output_zone_pass_prototypes(top_level->global_zone);

	fputs("/* MAIN PASS ANALYSERS */\n\n", lex_output);
  	output_zone_pass(top_level->global_zone);

	fputs("#endif\n",opt->lex_output_h);

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
extern void
output_keywords(lexer_parse_tree* top_level, FILE *output, FILE *output_h)
{
	keyword *p;

	fputs("\n/* KEYWORDS */\n", output);

	fprintf(output_h, "extern int %skeyword(const char *identifier, int notfound);\n",
		lexi_prefix);

	fprintf(output, "#include <string.h>\n");
	fprintf(output, "int %skeyword(const char *identifier, int notfound) {\n",
		lexi_prefix);

	/* TODO remove ->done */

	for (p = top_level->global_zone->keywords; p; p = p->next) {
		fprintf(output, "\tif(");

		if(p->cond) {
			fprintf(output, "%s && ", p->cond);
		}

		fprintf(output, "!strcmp(identifier, \"%s\")) return ",
			p->name);

		switch(p->instr->type) {
		case apply_function:
			/*
			 * Arguments are not permitted for functions in
			 * keyword instructions.
			 */
			fprintf(output, "%s()", p->instr->u.fun->name);
			break;

		case return_token:
			fprintf(output, "%s", p->instr->u.name);
			break;
		}

		fprintf(output, ";\n");
	}

	fprintf(output, "\treturn notfound;\n}\n");

	return;
}

