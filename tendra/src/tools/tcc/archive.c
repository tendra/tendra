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


#include "config.h"
#include "external.h"
#include "filename.h"
#include "list.h"
#include "archive.h"
#include "flags.h"
#include "options.h"
#include "utility.h"


/*
 * READ A GIVEN FILE FROM A STREAM
 *
 * This routine reads n characters from the file f into a new file named nm. It
 * returns a nonzero value if an error occurs.
 */
static int
read_file(char *nm, char *w, long n, FILE *f)
{
	FILE *g = NULL;
	int ret = 0;
	size_t m = (size_t)n;

	if (dry_run) {
		if (fseek(f, n, SEEK_CUR)) {
			error(SERIOUS, "Error when stepping over '%s'", nm);
			ret = 1;
		}

		goto out;
	}

	if ((g == fopen(nm, w)) == NULL) {
		error(SERIOUS, "Can't open copy destination file, '%s'", nm);
		ret = 1;
		goto out;
	}

	while (m) {
		size_t r = m;
		size_t s;
		void  *p = buffer;

		if (r > buffer_size)
			r = buffer_size;

		s = fread(p, sizeof(char), r, f);
		if (s != r) {
			error(SERIOUS, "Reading error when creating '%s'", nm);
			ret = 1;
			goto out;
		}

		s = fwrite(p, sizeof(char), r, g);
		if (s != r) {
			error(SERIOUS, "Writing error when creating '%s'", nm);
			ret = 1;
			goto out;
		}

		m = (size_t)(m - r);
	}

out:
	if (g)
		(void) fclose(g);

	return (ret);
}


/*
 * WRITE A GIVEN FILE TO A STREAM
 *
 * This routine copies the file named nm into the file f. It returns a nonzero
 * value if an error occurs.
 */
static int
write_file(char *nm, char *rd, FILE *f)
{
	FILE *g;
	size_t n;
	void *p = buffer;

	if (dry_run)
		return (0);

	if ((g = fopen(nm, rd)) == NULL) {
		error(SERIOUS, "Can't open copy source file, '%s'", nm);
		return (1);
	}

	while ((n = fread(p, sizeof(char), buffer_size, g)) != 0) {
		if (fwrite(p, sizeof(char), n, f) != n) {
			error(SERIOUS, "Writing error when copying '%s'", nm);
			(void) fclose(g);
			return (1);
		}
	}

	(void) fclose(g);

	return (0);
}


/*
 * CAT A FILE
 *
 * This routine copies the file named nm to the standard output. It returns a
 * nonzero value if an error occurs.
 */

int
cat_file(char *nm)
{
	return (write_file(nm, "r", stdout));
}


/*
 * CREATE A DIRECTORY
 *
 * This routine creates a directory called nm, returning zero if it is
 * successful. Two alternative versions of the routine are provided. The first
 * is POSIX compliant and uses mkdir and various mode constants from
 * sys/stat.h. The second raises an error - in this case the mkdir function
 * should be implemented by an external call.
 */

int
make_dir(char *nm)
{
	if (dry_run) {
		return (0);
	}
	{
		mode_t m = (mode_t)(S_IRWXU | S_IRWXG | S_IRWXO);
		int e = mkdir(nm, m);
		return (e);
	}
}


/*
 * MOVE A FILE
 *
 * This routine moves the file named from to the file named to, returning zero
 * if it is successful. Normally the files will be on different filesystems, so
 * we can't always use rename.
 */

int
move_file(char *from, char *to)
{
	int e;
	FILE *f;
	if (dry_run) {
		return (0);
	}
	if (streq(from, to)) {
		return (0);
	}
	if (rename(from, to) == 0) {
		return (0);
	}
	if (errno != EXDEV) {
		error(SERIOUS, "Can't rename '%s' to '%s'", from, to);
		return (1);
	}
	f = fopen(to, "wb");
	if (f == NULL) {
		error(SERIOUS, "Can't open copy destination file, '%s'", to);
		return (1);
	}
	e = write_file(from, "rb", f);
	IGNORE fclose(f);
	if (e) {
		return (e);
	}
	if (remove(from)) {
		error(SERIOUS, "Can't remove source file, '%s'", from);
		return (1);
	}
	return (0);
}


/*
 * REMOVE A FILE
 *
 * This routine removes the file or directory named nm, returning zero if it is
 * successful. Two alternative versions of the routine are provided. The first
 * is POSIX compliant and uses stuff from sys/stat.h and dirent.h. The second
 * raises an error - in this case the remove function should be implemented by
 * an external call.
 */

int
remove_file(char *nm)
{
	int e;
	struct stat st;

	if (dry_run)
		return (0);

	e = stat(nm, &st);
	if (e != -1) {
		mode_t m = (mode_t)st.st_mode;
		if (S_ISDIR(m)) {
			DIR *d = opendir(nm);
			if (d == NULL) {
				e = 1;
			} else {
				char *p;
				struct dirent *t;
				char buff [1000];
				IGNORE sprintf(buff, "%s/", nm);
				p = buff + strlen(buff);
				while (t = readdir(d), t != NULL) {
					char *dnm = t->d_name;
					if (!streq(dnm, ".") &&
					    !streq(dnm, "..")) {
						IGNORE strcpy(p, dnm);
						if (remove_file(buff)) {
							e = 1;
						}
					}
				}
				IGNORE closedir(d);
				if (rmdir(nm)) {
					e = 1;
				}
			}
		} else {
			e = remove(nm);
		}
	} else {
		/* If the file didn't exist, don't worry */
		if (errno == ENOENT) {
			return (0);
		}
	}
	if (e) {
		error(SERIOUS, "Can't remove '%s'", nm);
		return (1);
	}
	return (0);
}


/*
 * TOUCH A FILE
 *
 * This routine touches the file called nm. It returns 0 if it is successful.
 */

int
touch_file(char *nm, char *opt)
{
	if (!dry_run) {
		FILE *f = fopen(nm, "w");
		if (f == NULL) {
			error(SERIOUS, "Can't touch file, '%s'", nm);
		}
		if (opt && streq(opt, "-k")) {
			/* This is an empty C spec file */
			static unsigned char cs[] = {
				0x80
			};
			size_t s1 = sizeof(cs[0]);
			size_t sn = (size_t)(sizeof(cs) / s1);
			IGNORE fwrite(cs, s1, sn, f);
		} else {
			IGNORE fputs("EMPTY\n", f);
		}
		IGNORE fclose(f);
	}
	return (0);
}


/*
 * FIND THE SIZE OF A FILE
 *
 * This routine calculates the length of a file, returning zero for
 * non-existant files. Two versions of the routine are provided. The first is
 * POSIX compliant and uses stat from sys/stat.h to access the length directly.
 * The second just reads the file and counts the number of characters.
 */

long
file_size(char *nm)
{
	struct stat st;
	int e = stat(nm, &st);
	if (e == -1) {
		return (0);
	}
	return ((long)st.st_size);
}



/*
 * FIND THE DATE STAMP OF A FILE
 *
 * This routine calculates the date stamp of a file. If the target machine
 * does not support stat, or this is a dry run, zero is always returned.
 */

static long
file_time(char *nm)
{
	int e;
	struct stat st;
	if (dry_run) {
		return (0);
	}
	e = stat(nm, &st);
	if (e == -1) {
		error(SERIOUS, "Can't access file '%s'", nm);
		return (0);
	}
	return ((long)st.st_mtime);
}


/*
 * ARCHIVE HEADER
 *
 * A TDF archive always starts with ARCHIVE_HEADER, and the main part of the
 * archive ends with ARCHIVE_TRAILER.
 */

#define ARCHIVE_HEADER		"!TDF\n"
#define ARCHIVE_TRAILER		"-\n"


/*
 * IS A FILE AN ARCHIVE?
 *
 * Returns 1 if the file starts with ARCHIVE_HEADER, 0 otherwise.
 */
int
is_archive(char *nm)
{
	FILE *f;
	int archive = 0;
	char buf[sizeof(ARCHIVE_HEADER)];

	/* XXX: no distinction between not an archive and fopen error */
	if ((f = fopen(nm, "r"))  == NULL)
		return (archive);

	if (fgets(buf, (int)sizeof(buf), f) != NULL)
		if (strcmp(buf, ARCHIVE_HEADER) == 0)
			archive = 1;

	(void) fclose(f);
	return (archive);
}


/*
 * ARCHIVE FLAGS
 *
 * These flags control the output of the file names and options in the output
 * TDF archive.
 */

int archive_type = TDF_ARCHIVE;
static boolean archive_full = 1;
static boolean archive_links = 0;
static boolean archive_names = 1;
static boolean archive_options = 1;


/*
 * PROCESS ARCHIVE OPTIONS
 *
 * This routine processes any outstanding archive options.
 */

void
process_archive_opt(void)
{
	list *p;
	for (p = opt_joiner; p != NULL; p = p->next) {
		char *opt = p->item;
		if (streq(opt, "-copy") || streq(opt, "-c")) {
			archive_links = 0;
			link_specs = 0;
		} else if (streq(opt, "-full") || streq(opt, "-f")) {
			archive_full = 1;
		} else if (streq(opt, "-link") || streq(opt, "-l")) {
			archive_links = 1;
			link_specs = 1;
		} else if (streq(opt, "-names") || streq(opt, "-n")) {
			archive_names = 1;
		} else if (streq(opt, "-no_names") || streq(opt, "-nn")) {
			archive_names = 0;
		} else if (streq(opt, "-no_options") || streq(opt, "-no")) {
			archive_options = 0;
		} else if (streq(opt, "-options") || streq(opt, "-o")) {
			archive_options = 1;
		} else if (streq(opt, "-short") || streq(opt, "-s")) {
			archive_full = 0;
		} else {
			error(WARNING, "Unknown archiver option, '%s'", opt);
		}
	}
	opt_joiner = NULL;
	return;
}


/*
 * BUILD AN ARCHIVE
 *
 * This routine creates a TDF archive called arch from the null-terminated list
 * of files and options, input. The string ARCHIVE_OPTION_START is uses to
 * indicate the end of the files and the beginning of the options. The routine
 * returns zero if it is successful.
 */

int
build_archive(char *arch, char **input)
{
    FILE *f;
    char **s;
    boolean end = 0;
    if (dry_run) {
	    return (0);
    }
    f = fopen(arch, "wb");
    if (f == NULL) {
	error(SERIOUS, "Can't open output archive, '%s'", arch);
	return (1);
    }
    IGNORE fputs(ARCHIVE_HEADER, f);
    for (s = input; *s; s++) {
	if (end) {
	    /* Archive options */
	    if (archive_options) {
		if (verbose) {
		    comment(1, "... archive option %s\n", *s);
		}
		IGNORE fprintf(f, "%s\n", *s);
	    }
	} else if (streq(*s, ARCHIVE_OPTION_START)) {
	    /* Start of archive options */
	    IGNORE fputs(ARCHIVE_TRAILER, f);
	    end = 1;
	} else if (archive_links && archive_type != TDF_ARCHIVE) {
	    /* Archive file - link */
	    char *ln = *s;
	    if (verbose) {
		comment(1, "... archive file %s (link)\n", ln);
	    }
	    if (archive_full) {
		    ln = find_fullname(ln);
	    }
	    IGNORE fprintf(f, "> %ld %s\n", file_time(ln), ln);
	} else {
	    /* Archive file - copy */
	    FILE *g;
	    char *n = find_basename(*s);
	    if (!archive_names) {
		int i, m = (int)strlen(n);
		buffer [0] = '*';
		buffer [1] = 0;
		for (i = m - 1; i >= 0; i--) {
		    if (n [i] == '.') {
			IGNORE strcpy(buffer + 1, n + i);
			break;
		    }
		}
		n = buffer;
	    }
	    if (verbose) {
		    comment(1, "... archive file %s\n", *s);
	    }
	    g = fopen(*s, "rb");
	    if (g == NULL) {
		error(SERIOUS, "Can't open '%s' for archiving", *s);
		IGNORE fclose(f);
		return (1);
	    } else {
		void *p = buffer;
		size_t m = fread(p, sizeof(char), buffer_size, g);
		IGNORE fprintf(f, "+ %ld %s\n",(long)m, n);
		while (m) {
		    if (fwrite(p, sizeof(char), m, f)!= m) {
			error(SERIOUS, "Write error in archive '%s'", arch);
			IGNORE fclose(f);
			return (1);
		    }
		    m = fread(p, sizeof(char), buffer_size, g);
		    if (m) {
			    IGNORE fprintf(f, "+ %ld +\n", (long)m);
		    }
		}
		IGNORE fclose(g);
	    }
	}
    }
    if (!end) {
	    IGNORE fputs(ARCHIVE_TRAILER, f);
    }
    IGNORE fclose(f);
    return (0);
}


/*
 * SPLIT AN ARCHIVE
 *
 * This routine splits the TDF archive named arch into it consistuent
 * components. Any files from the archive are stored in the location indicated
 * by ret. The routine returns zero if it is successful.
 */

int
split_archive(char *arch, filename **ret)
{
    boolean go = 1;
    char *emsg = NULL;
    list *opts = NULL;
    filename *q = NULL;
    filename *output = NULL;
    boolean need_moves = 0;

    /* Open archive file */
    FILE *f = fopen(arch, "rb");
    if (f == NULL) {
	emsg = "Can't open input archive, '%s'";
	goto archive_error;
    }

    /* Check for archive header */
    if (fgets(buffer, buffer_size, f) == NULL ||
	 !streq(buffer, ARCHIVE_HEADER)) {
	emsg = "Illegal input archive, '%s'";
	goto archive_error;
    }

    /* Extract archived files */
    do {
	if (fgets(buffer, buffer_size, f) == NULL) {
	    emsg = "Premature end of archive '%s'";
	    goto archive_error;
	}
	if (buffer [0] == '+' && buffer [1] == ' ') {
	    /* Archived file - copy */
	    char c;
	    long n = 0;
	    char *w = "wb";
	    char *p = buffer + 2;
	    int m = (int)strlen(buffer) - 1;
	    if (buffer [m] == '\n') {
		    buffer [m] = 0;
	    }
	    while (c = *(p++), c != ' ') {
		if (c < '0' || c > '9') {
		    emsg = "Illegal file length specifier in archive '%s'";
		    goto archive_error;
		}
		n = 10 * n + (c - '0');
	    }
	    if (streq(p, "+")) {
		/* File continuations */
		if (q == NULL) {
		    emsg = "Illegal file continuation in archive '%s'";
		    goto archive_error;
		}
		w = "ab";
	    } else {
		filename *qo = q;
		if (streq(p, "*")) {
		    /* Old form hidden names */
		    int k = where(INDEP_TDF);
		    q = make_filename(no_filename, INDEP_TDF, k);
		} else if (strneq(p, "*.", 2)) {
		    /* New form hidden names */
		    int t;
		    p = string_copy(p);
		    q = find_filename(p, UNKNOWN_TYPE);
		    t = q->type;
		    q = make_filename(no_filename, t, where(t));
		} else {
		    /* Unhidden names */
		    p = string_copy(p);
		    q = find_filename(p, UNKNOWN_TYPE);
		    q = make_filename(q, q->type, where(q->type));
		}
		if (archive_type != TDF_ARCHIVE && qo) {
			q->uniq = qo->uniq;
		}
		if (q->type == archive_type && q->storage != TEMP_FILE) {
		    filename *qn = make_filename(q, q->type, TEMP_FILE);
		    qn->aux = q;
		    qn->uniq = q->uniq;
		    q = qn;
		    need_moves = 1;
		}
		output = add_filename(output, q);
		if (verbose) {
		    comment(1, "... extract file %s\n", q->name);
		}
	    }
	    if (read_file(q->name, w, n, f)) {
		emsg = "Read error in archive '%s'";
		goto archive_error;
	    }
	} else if (buffer [0] == '>' && buffer [1] == ' ') {
	    /* Archived file - link */
	    char c;
	    long ad = 0, fd;
	    filename *qo = q;
	    char *p = buffer + 2;
	    int m = (int)strlen(buffer) - 1;
	    if (buffer [m] == '\n') {
		    buffer [m] = 0;
	    }
	    while (c = *(p++), c != ' ') {
		if (c < '0' || c > '9') {
		    emsg = "Illegal link information in archive '%s'";
		    goto archive_error;
		}
		ad = 10 * ad + (c - '0');
	    }
	    q = find_filename(string_copy(p), UNKNOWN_TYPE);
	    q->storage = PRESERVED_FILE;
	    if (archive_type != TDF_ARCHIVE && qo) {
		    q->uniq = qo->uniq;
	    }
	    output = add_filename(output, q);
	    if (verbose) {
		comment(1, "... extract file %s (link)\n", q->name);
	    }
	    fd = file_time(q->name);
	    if (ad && fd && ad != fd) {
		error(WARNING, "Date stamp on file '%s' has changed",
			q->name);
	    }
	} else if (streq(buffer, ARCHIVE_TRAILER)) {
	    /* Archived options */
	    char *p;
	    int c, m;
	    while (c = getc(f), c != EOF) {
		buffer [0] = (char)c;
		if (fgets(buffer + 1, buffer_size - 1, f) == NULL) {
		    emsg = "Premature end of archive '%s'";
		    goto archive_error;
		}
		m = (int)strlen(buffer) - 1;
		if (buffer [m] == '\n') {
			buffer [m] = 0;
		}
		p = string_copy(buffer);
		if (verbose) {
			comment(1, "... extract option %s\n", p);
		}
		opts = add_item(opts, p);
	    }
	    go = 0;
	} else {
	    emsg = "Illegal file description in archive '%s'";
	    goto archive_error;
	}
    } while (go);

    /* Return */
archive_error:
    if (emsg) {
	    error(SERIOUS, emsg, arch);
    }
    IGNORE fclose(f);
    if (need_moves) {
	    for (q = output; q != NULL; q = q->next) {
		    if (q->aux && keeps_aux [ archive_type ]) {
			    if (verbose) {
				    comment(1, "... rename %s to %s\n",
					    q->name, q->aux->name);
			    }
			    if (move_file(q->name, q->aux->name)) {
				    emsg = "rhubarb";
			    } else {
				    q->name = q->aux->name;
				    q->storage = q->aux->storage;
			    }
		    }
		    q->aux = NULL;
	    }
    }
    *ret = output;
    if (opts) {
	    process_options(opts, main_optmap, 0);
	    opt_archive = add_list(opt_archive, opts);
    }
    if (emsg) {
	    return (1);
    }
    return (0);
}
