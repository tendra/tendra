/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef reform_diagtypes_key
#define reform_diagtypes_key 1

/*
 * This header provides a shallow copy of the old diag/ types, all prefixed reform_.
 * These are included as .reform_suchandsuch fields to provide emulation of the
 * previous diag/ datastructured, implmented as single fields within the current
 * newdiag/ structs.
 *
 * The purpose here is twofold; firstly to allow existing diag/-consuming code to
 * keep building, with a straightforward modification to refer to the stop-gap
 * .reform_ fields. Secondly, to make each use of those fields obvious.
 *
 * As consumers are transitioned over to the newdiag/ struct reform_layout, each
 * .reform_ field may be removed from the newdiag/ structs, and therefore their
 * associated diag/ types here may also be removed. This scheme allows for code
 * to be tranditioned gradually to the new scheme, rather than all at once.
 *
 * TODO: eventually this entire header can go
 */

#include <construct/installtypes.h>
#include <reader/code.h>

#include "diag_reform.h"

struct reform_filename_t {
	nat		date;
	tdfstring	machine;
	tdfstring	file;
};

typedef	struct reform_sourcemark_t {
	reform_filename	file;
	nat		line_no;
	nat		char_off;
} reform_sourcemark;

struct reform_enum_values_t {
	exp		val;
	tdfstring	nme;
};

typedef struct reform_enum_values_t *reform_enum_values;

struct reform_enum_values_list_t {
	int		len;
	int		lastused;
	reform_enum_values	*array;
};

typedef struct reform_enum_values_list_t *reform_enum_values_list;

struct reform_diag_field_t {
	tdfstring	field_name;
	exp		where;
	reform_diag_type	field_type;
};

typedef struct reform_diag_field_t *reform_diag_field;

struct reform_diag_field_list_t {
	int		len;
	int		lastused;
	reform_diag_field	*array;
};

typedef struct reform_diag_field_list_t *reform_diag_field_list;

struct reform_diag_type_list_t {
	int		len;
	int		lastused;
	reform_diag_type 		*array;
};

typedef struct reform_diag_type_list_t *reform_diag_type_list;

typedef struct {
	unsigned	is_const:1;
	unsigned	is_volatile:1;
} reform_diag_tq;


typedef tdfint reform_diag_tag;

struct reform_diag_tagdef_t {
	reform_diag_tag	d_tag;
	char        	*ext_name;
	reform_diag_type	d_type;
};

typedef struct reform_diag_tagdef_t reform_diag_tagdef;

typedef enum {
	reform_DIAG_TYPE_UNINIT,
	reform_DIAG_TYPE_ARRAY,
	reform_DIAG_TYPE_BITFIELD,
	reform_DIAG_TYPE_ENUM,
	reform_DIAG_TYPE_FLOAT,
	reform_DIAG_TYPE_LOC,
	reform_DIAG_TYPE_PROC,
	reform_DIAG_TYPE_PTR,
	reform_DIAG_TYPE_STRUCT,
	reform_DIAG_TYPE_NULL,
	reform_DIAG_TYPE_UNION,
	reform_DIAG_TYPE_VARIETY,
	reform_DIAG_TYPE_INITED
} reform_diag_type_key;

struct reform_diag_type_t {
	reform_diag_type_key	key;
	reform_OUTPUT_REC been_outed;
	union {
		struct {
			reform_diag_type		element_type;
			exp			stride;
			exp			lower_b;
			exp			upper_b;
			reform_diag_type		index_type;
		} array;
		struct {
			reform_diag_type		result_type;
			nat			no_of_bits;
		} bitfield;
		struct {
			reform_diag_type		base_type;
			tdfstring		nme;
			reform_enum_values_list	values;
		} t_enum;
		floating_variety		f_var;
		struct {
			reform_diag_type		object;
			reform_diag_tq			qualifier;
		} loc;
		struct {
			reform_diag_type_list		params;
			bool 			opt_args;
			reform_diag_type		result_type;
		} proc;
		struct {
			reform_diag_type		object;
			reform_diag_tq			qualifier;
		} ptr;
		struct {
			shape			tdf_shape;
			tdfstring		nme;
			reform_diag_field_list 	fields;
		} t_struct;
		struct {
			shape			tdf_shape;
			tdfstring		nme;
			reform_diag_field_list 	fields;
		} t_union;
		variety		var;
	} data;
};

typedef enum {
	reform_DIAG_UNINIT,
	reform_DIAG_ID_KEY,
	reform_DIAG_STRUCT_KEY,
	reform_DIAG_TYPEDEF_KEY
} reform_diag_desc_key;

typedef struct reform_diagdef_t {
	reform_diag_desc_key 	key;
	char		*ext_name;
	union {
		struct {
			tdfstring 	nme;
			reform_diag_type 	new_type;
			reform_sourcemark 	whence;
			exp		access;
		} id;
		struct {
			tdfstring 	nme;
			reform_diag_type	new_type;
			reform_sourcemark 	whence;
		} struc;
		struct {
			tdfstring	nme;
			reform_diag_type	new_type;
			reform_sourcemark 	whence;
		} typ;
	} data;
} reform_diagdef;
				/* diag_descriptor is in diagtypes1.h */

typedef struct reform_diag_unit_t {
	int		len;
	int		lastused;
	reform_diag_descriptor *array;
} reform_diag_unit;

typedef reform_diag_unit reform_diag_descriptor_list;

typedef int reform_diag_type_unit;
typedef reform_diag_type_unit reform_diag_tagdef_list;

#include "reform_diaginfo.h"

#endif
