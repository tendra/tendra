/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "config.h"
#include "filename.h"
#include "list.h"
#include "environ.h"
#include "flags.h"
#include "options.h"
#include "suffix.h"
#include "utility.h"


/*
 *  THE CURRENT ENVIRONMENTS PATH
 *
 *  The environment path is a colon-separated list of directories which
 *  are searched for tcc environments.
 */

static char *envpath = ".";


/*
 *  UPDATE THE ENVIRONMENTS PATH
 *
 *  This routine initialises and updates the environments path.  This is
 *  given by the contents of the system variable TCCENV, plus the default
 *  directory (environ_dir), plus the current directory.
 */

void
find_envpath(void)
{
	char *p = buffer;
	char *tcc_env = getenv (TCCENV_VAR);
	if (tcc_env) {
		IGNORE sprintf (p, "%s:", tcc_env);
		p += strlen (p);
	}
	IGNORE sprintf (p, "%s:.", environ_dir);
	if (!streq (buffer, envpath))
		envpath = string_copy (buffer);
	return;
}


/*
 *  PRINT THE ENVIRONMENTS PATH
 *
 *  This routine prints the environment path.
 */

void
show_envpath(void)
{
	find_envpath ();
	error (INFO, "Environment path is '%s'", envpath);
	return;
}


/*
 *  READ AN ENVIRONMENT - AUXILIARY ROUTINE
 *
 *  This routine reads the environment named nm, returning zero if it
 *  is successful.  A return value of 1 indicates that the environment
 *  could not be found, otherwise 2 is returned.
 *
 *  In the revision to this function, the strategy is to minimize
 *  copying chars.  This routine opens the file, and examines each env
 *  file a line at a time.  Line analysis scans past the key, until
 *  the first whitespace is found.  Then, the routine scans forward to
 *  the start of the value, and cut the line buffer in half by making
 *  the whitespace a '\0' character.  The routine continues scanning
 *  the value, performing appropriate substitutions for <vars>.
 *
 *  TODO: The two resulting strings in the buffer (key and value) must
 *  be strdup'd.  A future revision to this function may just read
 *  entire file into memory, and convert key whitespace to NULL
 *  characters, thereby breaking up the lines into appropriate tokens,
 *  and avoiding copying strings around in memory.
 */

int
read_env_aux(char *nm, hashtable *ht)
{
	/* Find the environment */
	FILE *f;
	char *p, *q, *s;
	char *tmp;
	int  count;
	int  line_num;
	int  line_len;
	
	if (*nm == 0) {
		return (1);
	} else if (*nm == '/') {
		f = fopen (nm, "r");
	} else {
		p = envpath;
		do {
			q = buffer;
			while (*p && *p != ':') {
				*(q++) = *(p++);
			}
			*(q++) = '/';
			IGNORE strcpy (q, nm);
			f = fopen (buffer, "r");
		} while (f == null && *(p++));
	}
	if (f == null)
		return (1);
	/*
	 *  Parse each line of the env file
	 */
	line_num = 0;
	while (fgets (buffer, buffer_size, f) != null)
	{
		char   c;          /* current character */
		int    count = 0;  /* track number of characters consumed */
		list   dummy;      /* find command */
		int    space_max;  /* spaces to shift over in final command */
		int    cnt;        /* counter */
		int    cnt_max;    /* counter max */
		htnode *hn;        /* temp hashtable node */
			
		line_len = strlen(buffer);
		line_num++;
		c = *buffer;
		
		/*  Env lines may only start with these characters.  */
		if (c == '<' || c == '>' || c == '+' || c == '?') {
			char *key;       /* start of key */
			char *key_term;  /* end of key */
			char *val;       /* start of value associated with key */
			p = buffer+1;
			key = buffer;
			while (c = *(p++), is_alphanum (c))
			{
				count++;
			}
			key_term = p; /* remember where key ended */
			if (!is_whitespace(c))
			{
				error (WARNING,
					   "Illegal environmental variable, '%s' in %s, line %d",
					   key, nm, line_num);
			}
			space_max = 0;
			while (c = *(p++), is_whitespace(c))
			{
				count++;
				space_max++;
			}
            /* remember start of value associated with key */			
			val = p;
			
            /* cut line buffer into strings with key/value halves */
			*(key_term-1) = '\0';  

			/* All env values should be quoted */
			if (!is_quote (c)) {
				error (WARNING,
					   "Illegal environmental value for '%s' in %s, line %d",
					   val, nm, line_num);
			}

            /* remove quote */
			*(p-1)=' ';
			
			while (c = *(p++), !is_quote (c))
			{
				count++;
				if (c == '\\') {
					c = *(p++);
					count++;
				}
				if (c == 0 || is_newline (c))
				{
					error (WARNING,
						   "Illegal environmental value for '%s' in %s,"
						   " line %d",
						   val, nm, line_num);
					break;
				}

                /* Check for variable substitution */
				if (c == '<')
				{
					int esc_len; /* length of escaped <variable> */
					int sub_len; /* length of replacement */
					int offset;  /* difference between esc and sub
									lengths */
					char prev;
					char *esc_start = p;
					char *esc_end;
					char *tmp = NULL;

					char *pivot;   /* where to start shifting */
					int shift_max; /* no. chars needing shift */
					int delta;     /* which direction to iterate */
					
					hn = NULL;

					/* scan to matching close '>' */
					while ((c = *(p++)) != '>')
					{
						count++;
						if (count == line_len)
							error (FATAL,
								   "Missing closing '>' in %s line %d\n",
								   nm, line_num);
					}
					
					/* Temporarily overwrite the '>' with '\0' to
					   facilitate string lookup using the buffer */
					esc_end = p-1;
					prev = *esc_end;
					*esc_end = '\0';
					esc_len = strlen(esc_start);
					
					/*   Attempt to match TENDRA_* env arguments,
						 which are most likely to occur. */
					if (!strncmp ("TENDRA", esc_start, 6)) {
						tmp = find_path_subst(esc_start);
					}

					/* If we fail to find a TENDRA_* env match, look
					   up in hashtable */
					if (!tmp)
					{
						hn = lookup_table(ht, esc_start);
						if (hn == NULL)
						{
							error (FATAL,
								   "Undefined variable <%s> in %s line %d\n",
								   esc_start, nm, line_num);
						}
						tmp = hn->val;						
					}

					/* restore the '>' character */
					*esc_end = prev;

					if (tmp == NULL)
						error (FATAL,
							   "Undefined variable %s in %s line %d\n",
							   esc_start, nm, line_num);

					sub_len = strlen(tmp);
						
					/* verify the line buffer has enough space */
					if (line_len + sub_len >= buffer_size)
					{
						error (FATAL,
							   "Line %d too  long in env file %s\n",
							   line_num,  nm);
					}
					offset  = sub_len - esc_len;
					shift_max = strlen(esc_end);
					if (esc_len > sub_len) /* shrink */
					{
						delta = 1;
						pivot = esc_end;
					}
					else /* grow */
					{  
						delta = -1;
						pivot = buffer + line_len;
					}
						
					/* shift line buffer to accomodate
					   substitution */
					for (cnt = 0; cnt < shift_max; cnt++)
						*(pivot + (cnt * delta) + offset - 2) =
							*(pivot + (cnt * delta));
					/* perform subsitution on resized line */
					for (cnt = 0; cnt < sub_len; cnt++)
						*(esc_start - 1 + cnt) = tmp[cnt];
						
					/* because of the substitution, we must
					   advance our pointer in the outer scope,
					   adjust the length of the line, and truncate
					   the new line. */
					p = esc_end + offset - 1;
					line_len += offset - 2;  /* -2 for <> pair */
					buffer[line_len] = '\0';
					
				} /* if '<' escape started */
				
			} /* while reading env value */

			/* truncate extra quote at end */
			*(p-1) = '\0';

			/* backup the key, preserving the leading +, ?, >, < tccenv
			   command */
			key = string_copy(key);

			/* restore line to whole buffer and execute cmd update */
			*(key_term-1) = ' ';

			/* shift the key forward, consuming extra white space */
			cnt_max = strlen(key) + 1;
			for (cnt = 1; cnt <= cnt_max; cnt++)
				*(key_term - cnt + space_max) =  *(key_term - cnt - 1);

			/* if the key/value pair is a tccenv variable, it's
			   a finished command, and should be executed */
			hn = lookup_table(ht, key);
			if (hn && (hn->flag & TCCENV))
			{
				/* copy over the shortened buffer */
				dummy.item = string_copy (buffer + space_max + 1);
				dummy.next = null;
				process_options (&dummy, environ_optmap, 1);
			}

			/* update hashtable with new key/value pair*/
			hn = update_table(ht, key, val, USR, nm, line_num);
			
		} /* if valid tccenv line */

	} /* while reading lines in tcc file */

	IGNORE fclose (f);
	return (0);	
}

void
reconcile_envopts(void)
{
	int i;
	htnode *hn;
	for (i = 0; i < TCC_TBLSZE; i++)
	{
		hn = environ_hashtable->node[i];
		if (hn &&  (hn->flag & USR)  &&
			!(hn->flag & READ))
			error (WARNING, "%s, line %d: environment option %s declared"
				   " but never used", hn->file, hn->line_num, hn->key);
	}
}


/*
 *  READ AN ENVIRONMENT
 *
 *  This routine reads the environment named nm, reporting an error if
 *  it is unsuccessful.
 */



void
read_env(char *nm)
{
	int e;
	static hashtable *ht;
	if (ht == NULL)
	{
		ht = init_table (TCC_TBLSZE, TCC_KEYSZE, &hash);
		environ_hashtable = ht; /* hack */
	}
	e = read_env_aux(nm, ht);
	if (e == 1)
		error (WARNING, "Can't find environment, '%s'", nm);
	return;
}
