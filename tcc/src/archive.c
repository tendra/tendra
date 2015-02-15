/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#define _POSIX_SOURCE

#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include "config.h"
#include "external.h"
#include "filename.h"
#include "list.h"
#include "archive.h"
#include "flags.h"
#include "options.h"
#include "utility.h"
#include "environ.h"


/*
 * ARCHIVE HEADER
 *
 * A TDF archive always starts with ARCHIVE_HEADER, and the main part of the
 * archive ends with ARCHIVE_TRAILER.
 */
#define ARCHIVE_HEADER		"!TDF\n"
#define ARCHIVE_TRAILER		"-\n"


/*
 * ARCHIVE FLAGS
 *
 * These flags control the output of the file names and options in the output
 * TDF archive.
 */
enum filetype archive_type = TDF_ARCHIVE; /* XXX: global */
static bool archive_full = 1;
static bool archive_links = 0;
static bool archive_names = 1;
static bool archive_options = 1;


/*
 * READ A GIVEN FILE FROM A STREAM
 *
 * This routine reads n characters from the file f into a new file named nm. It
 * returns a nonzero value if an error occurs.
 */
static int
read_file(const char *nm, const char *w, size_t n, FILE *f)
{
	int ret;
	FILE *g;
	size_t m;

	ret = 0;
	g   = NULL;
	m   = n;

	if (dry_run) {
		if (fseek(f, n, SEEK_CUR)) {
			error(ERR_SERIOUS, "Error when stepping over '%s'", nm);
			ret = 1;
		}

		goto out;
	}

	if ((g = fopen(nm, w)) == NULL) {
		error(ERR_SERIOUS, "Can't open copy destination file, '%s'", nm);
		ret = 1;
		goto out;
	}

	while (m) {
		size_t r = m;
		size_t s;
		void  *p;

		p = buffer;

		if (r > buffer_size) {
			r = buffer_size;
		}

		s = fread(p, sizeof(char), r, f);
		if (s != r) {
			error(ERR_SERIOUS, "Reading error when creating '%s'", nm);
			ret = 1;
			goto out;
		}

		s = fwrite(p, sizeof(char), r, g);
		if (s != r) {
			error(ERR_SERIOUS, "Writing error when creating '%s'", nm);
			ret = 1;
			goto out;
		}

		m = (size_t)(m - r);
	}

out:
	if (g)
		IGNORE fclose(g);

	return ret;
}


/*
 * WRITE A GIVEN FILE TO A STREAM
 *
 * This routine copies the file named nm into the file f. It returns a nonzero
 * value if an error occurs.
 */
static int
write_file(const char *nm, const char *rd, FILE *f)
{
	FILE *g;
	size_t n;
	void *p = buffer;

	if (dry_run)
		return 0;

	if ((g = fopen(nm, rd)) == NULL) {
		error(ERR_SERIOUS, "Can't open copy source file, '%s'", nm);
		return 1;
	}

	while ((n = fread(p, sizeof(char), buffer_size, g)) != 0) {
		if (fwrite(p, sizeof(char), n, f) != n) {
			error(ERR_SERIOUS, "Writing error when copying '%s'", nm);
			IGNORE fclose(g);
			return 1;
		}
	}

	IGNORE fclose(g);

	return 0;
}

/*
 * Wrapper around remove(3), to ease debugging.
 */
static int
remove_file(const char *nm)
{
#if 0
	fprintf(stderr, "tcc: trying to remove file '%s'\n", nm);
#endif
	return remove(nm);
}



/*
 * MOVE A FILE
 *
 * This routine moves the file named from to the file named to, returning zero
 * if it is successful. Normally the files will be on different filesystems, so
 * we can't always use rename.
 */
static int
move_file(const char *from, const char *to)
{
	int e;
	FILE *f;

	if (dry_run)
		return 0;

	if (strcmp(from, to) == 0)
		return 0;

	if (rename(from, to) == 0)
		return 0;

	if (errno != EXDEV) {
		error(ERR_SERIOUS, "Can't rename '%s' to '%s'", from, to);
		return 1;
	}

	if ((f = fopen(to, "w")) == NULL) {
		error(ERR_SERIOUS, "Can't open copy destination file, '%s'", to);
		return 1;
	}

	e = write_file(from, "r", f);
	IGNORE fclose(f);

	if (e)
		return e;

	if (remove_file(from) != 0) {
		error(ERR_SERIOUS, "Can't remove source file, '%s'", from);
		return 1;
	}

	return 0;
}

/*
 * FIND THE SIZE OF A FILE
 *
 * This routine calculates the length of a file, returning zero for
 * non-existant or empty files.
 */
long
file_size(const char *nm)
{
	struct stat st;

	if (stat(nm, &st) == -1)
		return 0;

	return (long)st.st_size;
}



/*
 * FIND THE DATE STAMP OF A FILE
 *
 * This routine calculates the date stamp of a file.
 * If this is a dry run or an error occured, zero is returned.
 */
static long
file_time(const char *nm)
{
	struct stat st;

	if (dry_run)
		return 0;

	if (stat(nm, &st) == -1) {
		error(ERR_SERIOUS, "Can't access file '%s'", nm);
		return 0;
	}

	return (long)st.st_mtime;
}


/*
 * IS A FILE AN ARCHIVE?
 *
 * Returns 1 if the file starts with ARCHIVE_HEADER, 0 otherwise.
 */
int
is_archive(const char *nm)
{
	FILE *f;
	int archive = 0;
	char buf[sizeof(ARCHIVE_HEADER)];

	/* XXX: no distinction between not an archive and fopen error */
	if ((f = fopen(nm, "r"))  == NULL)
		return archive;

	if (fgets(buf, (int)sizeof(buf), f) != NULL)
		if (strcmp(buf, ARCHIVE_HEADER) == 0)
			archive = 1;

	IGNORE fclose(f);
	return archive;
}


/*
 * PROCESS ARCHIVE OPTIONS
 *
 * This routine processes any outstanding archive options.
 */
void
process_archive_opt(void)
{
	const char *opt;
	const char *opt_joiner;
	char *s;

	opt_joiner = envvar_get(envvars, "FLAG_ARCHIVER");
	if (opt_joiner == NULL) {
		return;
	}

	s = xstrdup(opt_joiner);

	/* TODO: getopt */
	for (opt = strtok(s, " "); opt != NULL; opt = strtok(NULL, " ")) {
		if (strcmp(opt, "-copy") == 0 || strcmp(opt, "-c") == 0) {
			archive_links = 0;
			link_specs = 0;
		} else if (strcmp(opt, "-full") == 0 || strcmp(opt, "-f") == 0) {
			archive_full = 1;
		} else if (strcmp(opt, "-link") == 0 || strcmp(opt, "-l") == 0) {
			archive_links = 1;
			link_specs = 1;
		} else if (strcmp(opt, "-names") == 0 || strcmp(opt, "-n") == 0) {
			archive_names = 1;
		} else if (strcmp(opt, "-no_names") == 0 || strcmp(opt, "-nn") == 0) {
			archive_names = 0;
		} else if (strcmp(opt, "-no_options") == 0 || strcmp(opt, "-no") == 0) {
			archive_options = 0;
		} else if (strcmp(opt, "-options") == 0 || strcmp(opt, "-o") == 0) {
			archive_options = 1;
		} else if (strcmp(opt, "-short") == 0 || strcmp(opt, "-s") == 0) {
			archive_full = 0;
		} else {
			error(ERR_WARN, "Unknown archiver option, '%s'", opt);
		}
	}
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
build_archive(const char *arch, const char **input)
{
    FILE *f;
    const char **s;
    bool end = 0;
    if (dry_run) {
	    return 0;
    }
    f = fopen(arch, "wb");
    if (f == NULL) {
	error(ERR_SERIOUS, "Can't open output archive, '%s'", arch);
	return 1;
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
	    const char *ln = *s;
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
	    const char *n = find_basename(*s);
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
		error(ERR_SERIOUS, "Can't open '%s' for archiving", *s);
		IGNORE fclose(f);
		return 1;
	    } else {
		void *p = buffer;
		size_t m = fread(p, sizeof(char), buffer_size, g);
		IGNORE fprintf(f, "+ %ld %s\n",(long)m, n);
		while (m) {
		    if (fwrite(p, sizeof(char), m, f)!= m) {
			error(ERR_SERIOUS, "Write error in archive '%s'", arch);
			IGNORE fclose(f);
			return 1;
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
    return 0;
}


/*
 * SPLIT AN ARCHIVE
 *
 * This routine splits the TDF archive named arch into it consistuent
 * components. Any files from the archive are stored in the location indicated
 * by ret. The routine returns zero if it is successful.
 */

int
split_archive(const char *arch, filename **ret)
{
    bool go = 1;
    char *emsg = NULL;
    filename *q = NULL;
    filename *output = NULL;
    bool need_moves = 0;

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
		    p = xstrdup(p);
		    q = find_filename(p, UNKNOWN_TYPE);
		    q = make_filename(no_filename, q->type, where(q->type));
		} else {
		    /* Unhidden names */
		    p = xstrdup(p);
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
	    q = find_filename(xstrdup(p), UNKNOWN_TYPE);
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
		error(ERR_WARN, "Date stamp on file '%s' has changed",
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
		p = xstrdup(buffer);
		if (verbose) {
			comment(1, "... extract option %s\n", p);
		}
		envvar_set(&envvars, "FLAG_INSTALL", p, HASH_APPEND, HASH_CLI);
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
	    error(ERR_SERIOUS, emsg, arch);
    }
    IGNORE fclose(f);
    if (need_moves) {
	    for (q = output; q != NULL; q = q->next) {
		    if (q->aux && filetype_table[archive_type].keep_aux) {
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
    if (emsg) {
	    return 1;
    }
    return 0;
}
