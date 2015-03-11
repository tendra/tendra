/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TDF_CAPSULE_H
#define TDF_CAPSULE_H


/*
    CAPSULE VARIABLE TYPES

    These values correspond to the various types of linkable entity and
    entity groups within a TDF capsule.  They are used as arguments to
    capsule_id, unit_no etc.  VAR_label is a dummy value used for labels.
*/

enum {
	EQN_tld,
	EQN_versions,
	EQN_tokdec,
	EQN_tokdef,
	EQN_aldef,
	EQN_diagtype,
	EQN_tagdec,
	EQN_diagdef,
	EQN_dgcomp,
	EQN_tagdef,
	EQN_linkinfo,
	EQN_no,

	VAR_tag,
	VAR_token,
	VAR_alignment,
	VAR_diagtag,
	VAR_dgtag,
	VAR_no,

	VAR_label,
	VAR_total
};


/*
    USAGE INFORMATION

    These values are used to record the usage information for external
    identifiers.
*/

enum {
	USAGE_NONE   = 0x00U,
	USAGE_USE    = 0x01U,
	USAGE_DECL   = 0x02U,
	USAGE_DEFN   = 0x04U,
	USAGE_COMMON = 0x08U
};


#endif

