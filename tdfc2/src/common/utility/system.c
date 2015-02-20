/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#define _POSIX_SOURCE

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/system.h>
#include <utility/error.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <parse/file.h>


/*
    The flag good_fseek is true if a simple fseek on the byte count has
    the desired effect, and false otherwise (for example on DOS machines).
    Similarly binary_mode is true if there are separate text and binary
    file modes.  The flag good_stat is true if the st_dev and st_ino
    fields of struct stat are sufficient to uniquely identify a file
    (this may not be true for machines with small ino_t types and
    file systems mounted from machines with large ino_t types).
*/

int good_fseek = 1;
int good_stat = 0;
int text_mode = 0;
int binary_mode = 0;
int file_sep = '/';
int drive_sep = 0;


/*
    This routine seeks a position n bytes from the start of the file f.
    It returns 0 if good_fseek is false, otherwise it returns 1 for
    successful seeks and -1 otherwise.
*/

int
file_seek(FILE *f, long n)
{
	if (n == 0) {
		/* Can always rewind a file */
		rewind(f);
		return 1;
	}
	if (good_fseek) {
		/* Use fseek if it works */
		int s = fseek(f, n, SEEK_SET);
		if (s == -1) {
			return -1;
		}
		return 1;
	}
	return 0;
}


/*
    This macro converts the time_t value A to an unsigned long.  Since
    time_t may be any arithmetic type, this may not be totally portable.
*/

#define time_value(A)		((unsigned long)(A))


/*
    These variables are used to hold the current time as a struct tm.
    The date is also used to form a string which is unique for each
    translation unit.
*/

char uniq_string[50];
unsigned long crt_time = 0;
static int have_crt_time = 0;
static struct tm crt_time_str;


/*
    This routine assigns the current time to the variables above, returning
    a pointer to crt_time_str.  Note that the actual time is taken only the
    first time the function is called.
*/

static struct tm *
get_crt_time(void)
{
	if (!have_crt_time) {
		const char *s1, *s2;
		time_t t = time(NIL(time_t));
		if (t == (time_t) -1) {
			/* Use a (seemingly) random date if time fails */
			struct tm *st = &crt_time_str;
			st->tm_mday = 24;
			st->tm_mon = 6 /* July */ ;
			st->tm_year = 62;
			st->tm_hour = 23;
			st->tm_min = 30;
			st->tm_sec = 0;
			error(ERR_INTERNAL, "Can't find current date");
		} else {
			struct tm *st = localtime(&t);
			crt_time_str = *st;
			crt_time = time_value(t);
		}
		have_crt_time = 1;
		s1 = find_time("%.2d%.2d%.2d");
		s2 = find_date("%s%.2d_%d");
		sprintf_v(uniq_string, "%s_%s", s1, s2);
	}
	return &crt_time_str;
}


/*
    This routine returns a string giving the current date in the form
    given by fmt.  This is used in the __DATE__ built-in macro.
*/

const char *
find_date(const char *fmt)
{
	static char buff[20];
	static const char *month_name[12] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	struct tm *st = get_crt_time();
	int day = st->tm_mday;
	const char *month = month_name[st->tm_mon];
	int year = 1900 + st->tm_year;
	sprintf_v(buff, fmt, month, day, year);
	return buff;
}


/*
    This routine returns a string giving the current time in the form
    given by fmt.  This is used in the __TIME__ built-in macro.
*/

const char *
find_time(const char *fmt)
{
	static char buff[20];
	struct tm *st = get_crt_time();
	int hour = st->tm_hour;
	int min = st->tm_min;
	int sec = st->tm_sec;
	sprintf_v(buff, fmt, hour, min, sec);
	return buff;
}


/*
    This routine finds the file statistics for the file with pathname nm
    and assigns them into fs.  It returns fs if this is successful and the
    null pointer otherwise.
*/

STAT_TYPE *
stat_func(char *nm, STAT_TYPE *fs)
{
#if FS_POSIX
	int s = stat(nm, fs);
	if (s != -1) {
		return fs;
	}
#endif
	UNUSED(nm);
	UNUSED(fs);
	return NULL;
}


/*
    This routine converts the date from the file statistics fs to an
    unsigned long.
*/

unsigned long
stat_date(STAT_TYPE *fs)
{
	unsigned long date = 0;
	if (fs) {
		date = time_value(fs->st_mtime);
	}
	return date;
}


/*
    This routine checks whether the files given by the statistics fs and
    gs represent the same file.  Two files are the same if their device
    and inode numbers are equal (except on machines where good_stat is
    false).
*/

int
stat_equal(STAT_TYPE *fs, STAT_TYPE *gs)
{
	if (fs && gs) {
		if (fs->st_dev == gs->st_dev && fs->st_ino == gs->st_ino) {
			return good_stat;
		}
	}
	return 0;
}


/*
    This routine finds the current working directory, returning '.' if
    this cannot be found.
*/

const char *
find_cwd(void)
{
	static const char *crt_directory = NULL;
	if (crt_directory == NULL) {
#if FS_POSIX
		char buff[1024];
		char *nm = getcwd(buff, 1024);
		if (nm) {
			/* Copy result */
			string dir = xustrcpy(ustrlit(nm));
			dir = make_pathname(dir);
			crt_directory = strlit(dir);
		} else {
			crt_directory = ".";
		}
#else
		crt_directory = ".";
#endif
	}
	return crt_directory;
}


/*
    This routine finds the name of the machine on which the program is
    running, returning the empty string if this cannot be found.
*/

const char *
find_machine(void)
{
	static const char *machine_name = NULL;
	if (machine_name == NULL) {
#if FS_UTSNAME
		struct utsname un;
		if (uname(&un) != -1) {
			string s = ustrlit(un.nodename);
			s = xustrcpy(s);
			machine_name = strlit(s);
			return machine_name;
		}
#endif
		machine_name = "";
	}
	return machine_name;
}
