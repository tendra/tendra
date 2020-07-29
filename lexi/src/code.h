/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEXI_CODE_H
#define LEXI_CODE_H

struct param;
struct arg;

enum code_kind {
	CODE_STRING,
	CODE_IDENT,
	CODE_REF
};

struct code {
	enum code_kind kind;
	char *name;
	struct code *next;
};

void code_append_ident(struct code **, char *);
void code_append_ref(struct code **, char *);
void code_append_string(struct code **, char *);
void code_destroy(struct code *);
void code_out(FILE *, struct code *,
	struct arg *rhs, struct param *in,
	struct arg *lhs, struct param *out,
	int);

#endif

