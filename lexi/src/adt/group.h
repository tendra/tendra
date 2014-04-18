/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_GROUP_H
#define LEXI_GROUP_H

struct zone_tag;

/*
 * TYPE REPRESENTING A CHARACTER GROUP
 *
 * A character group is a named unordered set of letters.
 */
typedef struct char_group_name_tag char_group_name;
typedef struct char_group_defn_tag char_group_defn;

struct char_group_defn_tag {
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
	char_group_defn *next_in_groups_list;
};

struct char_group_name_tag {
	char *name;

	/*
	 * The zone within which this group is defined.
	 */
	struct zone_tag *z;

	/*
	 * A pointer to the group definition. Several groups can point to the same definition.
	 */

	char_group_defn* def;
	/*
	 * char_group_name elements appear in a list of group within one zone in the tree of zones
	 */
	char_group_name *next;
};

char_group_name *make_group(struct zone_tag *, char *, char *);
int in_group(char_group_defn *, char);
int is_group_empty(char_group_defn *);
int is_group_equal(char_group_defn *a, char_group_defn *b);
char_group_name *find_group(const struct zone_tag *z, const char *name);

#endif

