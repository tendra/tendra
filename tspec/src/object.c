/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <time.h>
#include <string.h>

#include "config.h"
#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"
#include "variable.h"

/*
 * CREATE A NEW OBJECT
 *
 * This routine creates a new object, with name nm and type t.
 */
object *
make_object(char *nm, int t)
{
	object *p;

	p = xmalloc(sizeof *p);
	p->name = nm;
	p->objtype = t;
	p->next = NULL;
	p->filename = filename;
	p->line_no = crt_line_no;

	return p;
}

/*
 * JOIN TWO LISTS OF OBJECTS
 *
 * This routine joins two lists of objects, returning the result.
 */
object *
join_object(object *p, object *q)
{
	object *r;

	if (p == NULL) {
		return q;
	}

	if (q == NULL) {
		return p;
	}

	for (r = p; r->next != NULL; r = r->next)
		;

	r->next = q;

	return p;
}

/*
 * FIND A SUBSET
 *
 * This routine looks up the subset named nm.  The operation for splitting
 * nm into its components (which should only be called with preprocessed
 * input) needs to be kept in step with subset_name.
 */
object *
make_subset(char *nm)
{
	object *p;
	char *api;
	char *file;
	char *subset;
	char *s;

	p = search_hash(subsets, nm, no_version);
	if (p != NULL) {
		return p;
	}

	api = xstrdup(nm);
	file = NULL;
	subset = NULL;

	s = strchr(api, ':');
	if (s != NULL) {
		*s = 0;
		file = s + 1;
		s = strchr(file, ':');
		if (s) {
			*s = 0;
			subset = s + 1;
		}

		if (*file == 0) {
			file = NULL;
		}
	}

	p = make_object(nm, OBJ_SUBSET);
	p->u.u_info = make_info(api, file, subset);
	p->u.u_info->age = (time_t)0;
	IGNORE add_hash(subsets, p, no_version);

	return p;
}

/*
 * CREATE SUBSET INFORMATION
 *
 * This routine creates the subset information for the subset
 * api:file:subset.
 */
info *
make_info(char *api, char *file, char *subset)
{
	info *p;

	p = xmalloc(sizeof *p);

	p->api    = api;
	p->file   = file;
	p->subset = subset;

	p->age   = date_stamp(filename);
	p->incl  = include_name(output_incl_dir, api, file, subset);
	p->src   = src_name(output_src_dir, api, file, subset);
	p->block = block_name(api, file, subset);
	p->linkage = "C";
	p->nspace = NULL;
	p->method = NULL;
	p->prefix = token_prefix(api, file, subset);
	p->protect = macro_name(PROTECT_PREFIX, api, file, subset);
	p->version = NULL;
	p->tokens  = 0;
	p->implemented = 0;
	p->elements = NULL;

	return p;
}

/*
 * UPDATE A SUBSET DATESTAMP
 *
 * This routine updates the datestamp on the subset p from that on the
 * subset q.
 */
void
update_time(object *p, object *q)
{
	if (p != NULL && q != NULL) {
		time_t tp = p->u.u_info->age;
		time_t tq = q->u.u_info->age;
		if (tp && tq > tp) {
			p->u.u_info->age = tq;
		}
	}
}

/*
 * CREATE A TOKEN
 *
 * This routine creates a token called nm (version vers) describing the
 * object p.  If this is a real token then the tokens field of the
 * current subset is set.
 */
object *
make_token(char *nm, int vers, object *p, int objtype)
{
	object *r = make_object(nm, OBJ_TOKEN);
	r->u.u_obj = p;
	IGNORE add_hash(tokens, r, vers);

	if (!crt_object) {
		return r;
	}

	switch (objtype) {
	case OBJ_EXTERN:
	case OBJ_WEAK:
		break;

	default:
		crt_object->u.u_info->tokens = 1;
		break;
	}

	return r;
}

/*
 * CREATE AN EXPRESSION
 *
 * This routine creates and expression object of type t called nm (version
 * vers).
 */
object *
make_exp(char *nm, int vers, int t)
{
	object *r = make_object(nm, t);

	IGNORE add_hash(exps, r, vers);
	r->u.u_type = NULL ;

	return r;
}

