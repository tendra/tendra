/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diagtypes_key
#define diagtypes_key 1

#include "diagtypes1.h"

#ifdef DIAG3_DWARF1
#include <dwarf1/dw1_types.h>
#endif

struct filename_t {
	nat		date;
	tdfstring	machine;
	tdfstring	file;
};

typedef	struct sourcemark_t {
	filename	file;
	nat		line_no;
	nat		char_off;
} sourcemark;

struct enum_values_t {
	exp		val;
	tdfstring	name;
};

typedef struct enum_values_t *enum_values;

struct enum_values_list_t {
	int		len;
	int		lastused;
	enum_values	*array;
};

typedef struct enum_values_list_t *enum_values_list;

struct diag_field_t {
	tdfstring	field_name;
	exp		where;
	diag_type	field_type;
};

typedef struct diag_field_t *diag_field;

struct diag_field_list_t {
	int		len;
	int		lastused;
	diag_field	*array;
};

typedef struct diag_field_list_t *diag_field_list;

struct diag_type_list_t {
	int		len;
	int		lastused;
	diag_type 		*array;
};

typedef struct diag_type_list_t *diag_type_list;

typedef struct {
	bool	is_const:1;
	bool	is_volatile:1;
} diag_tq;


typedef tdfint diag_tag;

struct diag_tagdef_t {
	diag_tag	d_tag;
	char        	*ext_name;
	diag_type	d_type;
};

typedef struct diag_tagdef_t diag_tagdef;

typedef enum {
	DIAG_TYPE_UNINIT,
	DIAG_TYPE_ARRAY,
	DIAG_TYPE_BITFIELD,
	DIAG_TYPE_ENUM,
	DIAG_TYPE_FLOAT,
	DIAG_TYPE_LOC,
	DIAG_TYPE_PROC,
	DIAG_TYPE_PTR,
	DIAG_TYPE_STRUCT,
	DIAG_TYPE_NULL,
	DIAG_TYPE_UNION,
	DIAG_TYPE_VARIETY,
	DIAG_TYPE_INITED
} diag_type_key;

struct diag_type_t {
	diag_type_key	key;
#ifdef DIAG3_DWARF1
	dwarf_type_label *dw1_been_outed;
#endif
#if defined(TRANS_X86) || defined(TRANS_HPPA) || defined(TRANS_SPARC)
	long been_outed;
#else
	void *been_outed;
#endif
	union {
		struct {
			diag_type		element_type;
			exp			stride;
			exp			lower_b;
			exp			upper_b;
			diag_type		index_type;
		} array;
		struct {
			diag_type		result_type;
			nat			no_of_bits;
		} bitfield;
		struct {
			diag_type		base_type;
			tdfstring		name;
			enum_values_list	values;
		} t_enum;
		floating_variety		f_var;
		struct {
			diag_type		object;
			diag_tq			qualifier;
		} loc;
		struct {
			diag_type_list		params;
			bool 			opt_args;
			diag_type		result_type;
		} proc;
		struct {
			diag_type		object;
			diag_tq			qualifier;
		} ptr;
		struct {
			shape			tdf_shape;
			tdfstring		name;
			diag_field_list 	fields;
		} t_struct;
		struct {
			shape			tdf_shape;
			tdfstring		name;
			diag_field_list 	fields;
		} t_union;
		variety		var;
	} data;
};

typedef enum {
	DIAG_UNINIT,
	DIAG_ID_KEY,
	DIAG_STRUCT_KEY,
	DIAG_TYPEDEF_KEY
} diag_desc_key;

typedef struct diagdef_t {
	diag_desc_key 	key;
	char		*ext_name;
#ifdef DIAG3_DWARF1
	dwarf_label lab;
#endif
	union {
		struct {
			tdfstring 	name;
			diag_type 	new_type;
			sourcemark 	whence;
			exp		access;
		} id;
		struct {
			tdfstring 	name;
			diag_type	new_type;
			sourcemark 	whence;
		} struc;
		struct {
			tdfstring	name;
			diag_type	new_type;
			sourcemark 	whence;
		} type;
	} data;
} diagdef;
				/* diag_descriptor is in diagtypes1.h */

typedef struct diag_unit_t {
	int		len;
	int		lastused;
	diag_descriptor *array;
} diag_unit;

typedef diag_unit diag_descriptor_list;

typedef int diag_type_unit;
typedef diag_type_unit diag_tagdef_list;

#include "diaginfo.h"

#endif
