/*
 * tcc/startup.c acceptance tests.
 * These are output to newly-created files, whos names are are listed on stdout.
 * $Id$
 */

#include <stddef.h>
#include <stdio.h>

#include "../startup.h"

/*
 * Hacks. These are mostly to circumvent things we don't use here.
 * These are a sign that tcc's internal interfaces suck.
 */
#include "../config.h"
#include "../filename.h"
filename *execute(filename *input, filename *output) { }
#include "../list.h"
const char *temporary_dir = "tempdir";
const char *name_h_file = "name_h_file";
const char *name_E_file = "name_E_file";
const char *name_p_file = "name_p_file";
boolean warnings = 1;
boolean checker = 1;
list *exec_move = NULL;
list *exec_remove = NULL;
boolean keeps[100];
#include <unistd.h>
#include <stdlib.h>
void main_end(void) { exit(EXIT_FAILURE); }
#include "../options.h"
char **env_paths;
optmap environ_optmap[3];
void cmd_list(const list *l) { }
static void add_to_tokdef(void) { }

/* Things we do use */
boolean dry_run = 0;
const char *test_output;

char const *nv[] = {
	"",
	"a=b",
	"=",
	"x=",
	"=y",
	"==",
	"a==",
	"=b=",
	"==c",
	"a=b=",
	"=b=c",
	"a=b=c",
	"a==c",
	"xyz abc",
	"xyz=abc",
	"xyz =abc",
	"xyz= abc",
	"xyz = abc",
	"xyz == abc",
	"xyz = = abc"
};

void cmd_string(const char *s) {
	printf("%s\n", s);
}

static void test_pragma(void) {
	size_t i;

	for (i = 0; i < sizeof nv / sizeof *nv; i++) {
		add_pragma(nv[i]);
	}
}

static void test_token(void) {
	size_t i;

	for (i = 0; i < sizeof nv / sizeof *nv; i++) {
		add_token(nv[i]);
	}
}

int main(void) {
	add_to_startup("STARTUP:\n");
	add_to_endup("ENDUP:\n");

	test_token();
	test_pragma();
	close_startup();
	remove_startup();

	/* TODO test other things, too */

	return 0;
}

