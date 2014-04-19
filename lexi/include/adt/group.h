/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_GROUP_H
#define LEXI_GROUP_H

struct zone;

/*
 * TYPE REPRESENTING A CHARACTER GROUP
 *
 * A character group is a named unordered set of letters.
 */

struct group {
	/*
	 * The set of characters present in a group, expressed as a bitmap. Each
	 * element is true if the index is a character in the group, and false
	 * otherwise. Since EOF is not a character, it may not be present in groups.
	 */
	int defn[256];

	/*
	 * Groups definition are maintained in a global list. This is
	 * used for numbering group definitions at output.
	 */
	struct group *next;
};

struct group_name {
	char *name;

	/*
	 * The zone within which this group is defined.
	 */
	struct zone *z;

	/*
	 * A pointer to the group definition. Several groups can point to the same definition.
	 */
	struct group *g;

	/*
	 * group_name elements appear in a list of group within one zone in the tree of zones
	 */
	struct group_name *next;
};

struct group_name *make_group(struct zone *, char *, char *);
int in_group(struct group *, char);
int is_group_empty(struct group *);
int is_group_equal(struct group *a, struct group *b);
struct group_name *find_group(const struct zone *z, const char *name);

#endif

