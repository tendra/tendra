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

#include "error.h"

#include "char.h"
#include "lex.h"
#include "output.h"


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
	int n = 4 * d;
	for (; n >= 8; n -= 8)
		fputc('\t', lex_output);
	for (; n; n--)
		fputc(' ', lex_output);
	return;
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
	switch (ctrans->ch) {
		case '\n': return("'\\n'");
		case '\r': return("'\\r'");
		case '\t': return("'\\t'");
		case '\v': return("'\\v'");
		case '\f': return("'\\f'");
		case '\\': return("'\\\\'");
		case '\'': return("'\\''");
	}
	if (ctrans->ch > 127) return("'?'");
	sprintf(buff, "'%c'", (char)ctrans->ch);
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



static	void 
output_actions( zone* z, instructions_list* ret, int n, int d)
{
  instruction* instr;
  for(instr=ret->head; instr; instr=instr->next) {
    switch(instr->type) {
    case return_token :
      /* assert(!instr->next);*/
      output_indent(d);
      fprintf(lex_output, "return(%s);\n", instr->name);
      break;
    case apply_function:
      output_indent(d);
      if(!(instr->next))
	fprintf(lex_output, "return(");
      fprintf(lex_output, "%s(", instr->fun->name);
      {
      arg* fun_args;
      for(fun_args=instr->fun->args->head;fun_args;fun_args=fun_args->next) {
	int i;
	if(fun_args!=instr->fun->args->head) 
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
	case arg_char_nb:
	  if(fun_args->digit <n)
	    fprintf(lex_output, "c%d", fun_args->digit);
	  else
	    error(ERROR_SERIOUS, "In #[0-9]* arg, the digit must be smaller than the number of chas in a token");
	  /*Should be caught during parsing*/
	  break;
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
      fprintf(lex_output, "state->zone_function=&read_token_zone_%s;\n",
	      instr->z->zone_name);
      if(instr->z->entering_instructions->head) 
	output_actions(NULL,instr->z->entering_instructions,n,d);
      else {
	output_indent(d);
	fputs("return(read_token(state));\n",lex_output);
      }
      break;
    case pop_zone:
      output_indent(d);
      fprintf(lex_output, "state->zone_function=&read_token_zone_%s;\n",
	      instr->z->zone_name);
      if(z->leaving_instructions->head) 
	output_actions(NULL,z->leaving_instructions,n,d);
      else {
	output_indent(d);
	fputs("return(read_token(state));\n",lex_output);
      }
      break;
    case do_nothing:
      if(instr->next) 
	error(ERROR_SERIOUS, "$$ should only appear at the end of an instruction list");
/*Should be caught during parsing*/
  /* assert(!instr->next);*/
      output_indent(d);
      if(z)
	fputs("goto start;\n",lex_output);	  	
      else /*We're outputting entering and leaving actions.*/
	fputs("return(read_token(state));\n",lex_output);	  
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
	int cases = 0;
	int classes = 0;
	instructions_list *ret = NULL;
	char* retmap= NULL ;
	char *cond = NULL;
	letter_translation* ctrans;

	/* First pass */
	for (q = p->next; q != NULL; q = q->opt) {
	    letter c = q->ch;
	    ctrans=letters_table_get_translation(c,lxi_parse_tree.letters_table);
		if (ctrans->type==last_letter) {
			if(in_pre_pass)
				retmap = q->map;
			else
				ret = q->definition;
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
		  fprintf(lex_output, "int c%d = read_token_aux_zone_%s()", 
			  n, z->zone_name);
		else
		    fprintf(lex_output, "int c%d = lexi_readchar()", n);
		if (classes || w1)
			fprintf(lex_output, ", t%d", n);
		fputs(";\n", lex_output);
		if (w1) {
			output_indent(d);
			fputs("t0 = lookup_char(c0);\n", lex_output);
			output_indent(d);
			fputs("if (is_white(t0)) goto start;\n", lex_output);
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
				ctrans=letters_table_get_translation(c,lxi_parse_tree.letters_table);
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
				ctrans=letters_table_get_translation(c,lxi_parse_tree.letters_table);
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
			if (!w1) {
				output_indent(d);
				fprintf(lex_output, "t%d = lookup_char(c%d);\n", n, n);
			}
			for (q = p->next; q != NULL; q = q->opt) {
				letter c = q->ch;
				ctrans=letters_table_get_translation(c,lxi_parse_tree.letters_table);
				if (ctrans->type==group_letter) {
					char *gnm=ctrans->grp->name;
					output_indent(d);
					if (started)
						fputs("} else ", lex_output);
					fprintf(lex_output, "if (is_%s(t%d)) {\n", gnm, n);
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
			fprintf(lex_output, "lexi_push(c%d);\n", n);
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
				        letter ca=find_escape((map)[1]);
					ctrans=letters_table_get_translation(ca,lxi_parse_tree.letters_table);
				        str = char_lit(ctrans);
					m = (map) [2];
				} else {
				  ctrans=letters_table_get_translation((letter)m,lxi_parse_tree.letters_table);
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
  fprintf(lex_output,"int\nread_token_zone_%s(struct lexer_state_tag* state);\n",p->zone_name);
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
      fprintf(lex_output,"static int read_token_aux_zone_%s(void)\n",
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
    for(z=p->next;z!=NULL;z=z->opt) {
      output_zone_pass(z);
    }
    fprintf(lex_output,"/* MAIN PASS ANALYSER for zone %s*/\n\n",p->zone_name);
    fprintf(lex_output,"int\nread_token_zone_%s(struct lexer_state_tag* state)\n",p->zone_name);
    fputs("{\n", lex_output);
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
        fputs("\treturn(unknown_token(c0));\n", lex_output);
    fputs("\t}\n", lex_output);
    fputs("}\n", lex_output);
    return;
}

/*
	OUTPUT INITIAL COMMENT

	This routine outputs a comment stating that the file is automatically
	generated.
*/

static void
output_comment(void)
{
	if (first_comment) {
		/* Print copyright comment, if present */
		fprintf(lex_output, "%s\n\n", first_comment);
	}
	fputs("/*\n *  AUTOMATICALLY GENERATED", lex_output);
	fprintf(lex_output, " BY %s VERSION %s", progname, progvers);
	fputs("\n */\n\n\n", lex_output);
	return;
}


/*
	MAIN OUTPUT ROUTINE

	This routine is the entry point for the main output routine.
*/

void
output_all(FILE *output, bool generate_asserts)
{
	int c, n;
	size_t groupwidth;
	int in_pre_pass; /*boolean*/
	const char *grouptype;
	const char *grouphex;

	lex_output = output;

	if (lxi_parse_tree.no_groups >= 16) {
		grouptype = "uint32_t";
		grouphex = "0x%08lxUL";
		groupwidth = 2;
	} else if (lxi_parse_tree.no_groups >= 8) {
		grouptype = "uint16_t";
		grouphex = "0x%04lx";
		groupwidth = 4;
	} else {
		grouptype = "uint8_t";
		grouphex = "0x%02lx";
		groupwidth = 8;
	}


	/* Initial comment */
	output_comment();

	if(generate_asserts) {
		fputs("#include <assert.h>\n", lex_output);
	}
	fputs("#include <stdint.h>\n\n", lex_output);

	/* Character look-up table */
	fputs("/* LOOKUP TABLE */\n\n", lex_output);
	fprintf(lex_output, "typedef %s lexi_lookup_type;\n", grouptype);
	fputs("static lexi_lookup_type lookup_tab[257] = {\n", lex_output);
	for (c = 0; c <= 256; c++) {
		unsigned long m = 0;
		letter a = (c == 256 ? lxi_parse_tree.eof_letter_code : (letter)c);
		m = 0;
		for (n = 0; n < lxi_parse_tree.no_groups; n++) {
			if (in_group(lxi_parse_tree.groups [n].defn, a)) {
				m |= (unsigned long)(1 << n);
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
	fputs("\n};\n\n", lex_output);

	fputs("#ifndef LEX_EOF\n", lex_output);
	fputs("#define LEX_EOF\t\t256\n", lex_output);
	fputs("#endif\n\n", lex_output);


	/* Buffer operations */
	fputs("/*\n", lex_output);
	fputs(" * Lexi's buffer is a simple stack. The size is calculated as\n", lex_output); 
	fputs(" * max(mapping) - 1 + max(token) - 1\n", lex_output);
	fputs(" */\n", lex_output);
	if(lxi_parse_tree.global_zone->zone_pre_pass->next) {
		fprintf(lex_output, "static int lexi_buffer[%u - 1 + %u - 1];\n",
			char_maxlength(lxi_parse_tree.global_zone->zone_pre_pass), char_maxlength(lxi_parse_tree.global_zone->zone_main_pass));
	} else {
		fprintf(lex_output, "static int lexi_buffer[%u - 1];\n",
			char_maxlength(lxi_parse_tree.global_zone->zone_main_pass));
	}
	fputs("static int lexi_buffer_index;\n\n", lex_output);

	fputs("/* Push a character to lexi's buffer */\n", lex_output);
	fputs("static void lexi_push(const int c) {\n", lex_output);
	if(generate_asserts) {
		fputs("\tassert(lexi_buffer_index < sizeof lexi_buffer / sizeof *lexi_buffer);\n", lex_output);
	}
	fputs("\tlexi_buffer[lexi_buffer_index++] = c;\n", lex_output);
	fputs("}\n\n", lex_output);

	fputs("/* Pop a character from lexi's buffer */\n", lex_output);
	fputs("static int lexi_pop(void) {\n", lex_output);
	if(generate_asserts) {
		fputs("\tassert(lexi_buffer_index > 0);\n", lex_output);
	}
	fputs("\treturn lexi_buffer[--lexi_buffer_index];\n", lex_output);
	fputs("}\n\n", lex_output);

	fputs("/* Flush lexi's buffer */\n", lex_output);
	fputs("static void lexi_flush(void) {\n", lex_output);
	fputs("\tlexi_buffer_index = 0;\n", lex_output);
	fputs("}\n\n", lex_output);

	/* TODO nice thing: we can abstract away 'aux() here, too. */
	fputs("/* Read a character */\n", lex_output);
	fputs("static int lexi_readchar(void) {\n", lex_output);
	fputs("\tif(lexi_buffer_index) {\n", lex_output);
	fputs("\t\treturn lexi_pop();\n", lex_output);
	fputs("\t}\n\n", lex_output);
	fputs("\treturn read_char();\n", lex_output);
	fputs("}\n\n", lex_output);


	/* Macros for accessing table */
	fputs("#define lookup_char(C)\t", lex_output);
	fputs("((int)lookup_tab[(C)])\n", lex_output);
	for (n = 0; n < lxi_parse_tree.no_groups; n++) {
		const char *gnm;
		unsigned long m = (unsigned long)(1 << n);
		gnm = lxi_parse_tree.groups[n].name;
		fprintf(lex_output, "#define is_%s(T)\t((T) & ", gnm);
		fprintf(lex_output, grouphex, m);
		fputs(")\n", lex_output);
	}

	fputs("\n\n", lex_output);
	/* Lexical pre-pass */
	in_pre_pass=1;
	fputs( "/* PRE-PASS ANALYSERS */\n\n", lex_output);
	output_zone_prepass(lxi_parse_tree.global_zone);

	/* Main pass */

	in_pre_pass = 0;
	if(lxi_parse_tree.global_zone->next) {
	  fputs("\n", lex_output);
	  
	  fputs("/* lexer_state_definition */\n\n", lex_output);
	  
	  fputs("typedef struct lexer_state_tag {\n"
		"\tint (*zone_function)(struct lexer_state_tag*);\n"
		"\t} lexer_state;\n",
		lex_output);
	  
	  fputs("\n\nint read_token(lexer_state*);\n\n", lex_output);

	  fputs("\n/* ZONES PASS ANALYSER PROTOTYPES*/\n\n", lex_output);
	  output_zone_pass_prototypes(lxi_parse_tree.global_zone);
	  fputs("\n\n/* ZONES PASS ANALYSER */\n\n", lex_output);
	  output_zone_pass(lxi_parse_tree.global_zone);
	  fputs("lexer_state current_lexer_state_v="
		"{&read_token_zone_global};\n",
		lex_output);
	  fputs("lexer_state* current_lexer_state=&current_lexer_state_v;",
		lex_output);
	  fputs("\n\nread_token(lexer_state* state)\n"
		"{\n\treturn((*(state->zone_function))(state));\n}\n",
		lex_output);
	  
	}
	else {
	  fputs("/* MAIN PASS ANALYSER */\n\n",lex_output);
	  fputs("int\nread_token(void)\n",lex_output);
	  fputs("{\n", lex_output);
	  fputs("\tstart: {\n", lex_output);
	  output_pass(lxi_parse_tree.global_zone,lxi_parse_tree.global_zone->zone_main_pass, in_pre_pass, 0, 2);
	  if(lxi_parse_tree.global_zone->default_actions) {
	    int dd=2;
	    if(lxi_parse_tree.global_zone->default_cond) {
	      fprintf(lex_output,"\tif(%s) {\n\t",lxi_parse_tree.global_zone->default_cond);
	      dd=4;
	    }
	    output_actions(lxi_parse_tree.global_zone,lxi_parse_tree.global_zone->default_actions,1,dd);
	    if(lxi_parse_tree.global_zone->default_cond) 
	      fprintf(lex_output,"}\n\t",lxi_parse_tree.global_zone->default_cond);	    
	  }
	  else 
	    fputs("\treturn(unknown_token(c0));\n", lex_output);
	  fputs("\t}\n", lex_output);
	  fputs("}\n", lex_output);}
	    
	return;
}


/*
	OUTPUT CODE FOR A SINGLE KEYWORD

	This routine outputs code for the keyword p.
*/

static void
output_word(keyword *p)
{
  fprintf(lex_output, "MAKE_KEYWORD(\"%s\", ",p->name);
  switch(p->instr->type) {
  case apply_function:
    /* No args are possible for functions in keyword instructions*/
    fprintf(lex_output,"%s());\n",p->instr->fun->name);
    break;
  case return_token:
    fprintf(lex_output,"%s);\n",p->instr->name);    
    break;
  }
  p->done = 1;
  return;
}

/*
	KEYWORD OUTPUT ROUTINE

	This routine outputs code to generate all keywords.
*/

void
output_keyword(FILE *output)
{
	keyword *p, *q;

		lex_output = output;

	output_comment();
	fputs("/* KEYWORDS */\n\n", lex_output);
	for (p = lxi_parse_tree.global_zone->keywords; p != NULL; p = p->next) {
		if (p->done == 0) {
			char *cond = p->cond;
			if (cond) {
				fprintf(lex_output, "if (%s) {\n\t", cond);
				output_word(p);
				for (q = p->next; q != NULL; q = q->next) {
					if (q->cond && !strcmp(q->cond, cond)) {
						fputs("\t", lex_output);
						output_word(q);
					}
				}
				fputs("}\n", lex_output);
			} else {
				output_word(p);
				for (q = p->next; q != NULL; q = q->next) {
					if (q->cond == NULL)
						output_word(q);
				}
			}
		}
	}
	return;
}
