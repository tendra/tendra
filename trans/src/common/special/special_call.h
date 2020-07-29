/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPECIAL_CALL_H
#define SPECIAL_CALL_H

struct special_call {
	const char *name;
	int mask;
	bool (*f)(dec *dp);
};

bool
special_call(const struct special_call a[], size_t count,
	dec *dp);

extern const struct special_call special_calls[];
extern size_t special_calls_count;

#endif

