/* $Id$ */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA disk (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef READ_DEF_H_INCLUDED
#define READ_DEF_H_INCLUDED

#include <out/disk.h>

#include "type_ops.h"

/* Disk reading function declarations */

#ifndef READ_disk_list_ptr_type
#define READ_disk_list_ptr_type() READ_list_ptr_type()
#endif

#ifndef READ_list_ptr_type
static LIST(PTR(TYPE)) READ_list_ptr_type(void);
#endif

#ifndef READ_disk_string
#define READ_disk_string() READ_string()
#endif

#ifndef READ_disk_int
#define READ_disk_int() READ_int()
#endif

#ifndef READ_type
static TYPE READ_type(void);
#endif

#ifndef READ_zero_int
#define READ_zero_int() READ_int()
#endif

#ifndef READ_PRIMITIVE_P
#define READ_PRIMITIVE_P() READ_ptr_prim()
#endif

#ifndef READ_ptr_prim
static PTR(PRIMITIVE) READ_ptr_prim(void);
#endif

#ifndef READ_prim
static PRIMITIVE READ_prim(void);
#endif

#ifndef READ_CLASS_ID_P
#define READ_CLASS_ID_P() READ_ptr_cid()
#endif

#ifndef READ_ptr_cid
static PTR(CLASS_ID) READ_ptr_cid(void);
#endif

#ifndef READ_cid
static CLASS_ID READ_cid(void);
#endif

#ifndef READ_name_string
#define READ_name_string() READ_string()
#endif

#ifndef READ_IDENTITY_P
#define READ_IDENTITY_P() READ_ptr_ident()
#endif

#ifndef READ_ptr_ident
static PTR(IDENTITY) READ_ptr_ident(void);
#endif

#ifndef READ_ident
static IDENTITY READ_ident(void);
#endif

#ifndef READ_TYPE_P
#define READ_TYPE_P() READ_ptr_type()
#endif

#ifndef READ_ptr_type
static PTR(TYPE) READ_ptr_type(void);
#endif

#ifndef READ_ENUM_P
#define READ_ENUM_P() READ_ptr_en()
#endif

#ifndef READ_ptr_en
static PTR(ENUM) READ_ptr_en(void);
#endif

#ifndef READ_en
static ENUM READ_en(void);
#endif

#ifndef READ_list_ptr_ec
static LIST(PTR(ECONST)) READ_list_ptr_ec(void);
#endif

#ifndef READ_list_ECONST_P
#define READ_list_ECONST_P() READ_list_ptr_ec()
#endif

#ifndef READ_ECONST_P
#define READ_ECONST_P() READ_ptr_ec()
#endif

#ifndef READ_ptr_ec
static PTR(ECONST) READ_ptr_ec(void);
#endif

#ifndef READ_ec
static ECONST READ_ec(void);
#endif

#ifndef READ_STRUCTURE_P
#define READ_STRUCTURE_P() READ_ptr_str()
#endif

#ifndef READ_ptr_str
static PTR(STRUCTURE) READ_ptr_str(void);
#endif

#ifndef READ_str
static STRUCTURE READ_str(void);
#endif

#ifndef READ_list_ptr_cmp
static LIST(PTR(COMPONENT)) READ_list_ptr_cmp(void);
#endif

#ifndef READ_list_COMPONENT_P
#define READ_list_COMPONENT_P() READ_list_ptr_cmp()
#endif

#ifndef READ_COMPONENT_P
#define READ_COMPONENT_P() READ_ptr_cmp()
#endif

#ifndef READ_ptr_cmp
static PTR(COMPONENT) READ_ptr_cmp(void);
#endif

#ifndef READ_cmp
static COMPONENT READ_cmp(void);
#endif

#ifndef READ_UNION_P
#define READ_UNION_P() READ_ptr_un()
#endif

#ifndef READ_ptr_un
static PTR(UNION) READ_ptr_un(void);
#endif

#ifndef READ_un
static UNION READ_un(void);
#endif

#ifndef READ_list_ptr_fld
static LIST(PTR(FIELD)) READ_list_ptr_fld(void);
#endif

#ifndef READ_list_FIELD_P
#define READ_list_FIELD_P() READ_list_ptr_fld()
#endif

#ifndef READ_FIELD_P
#define READ_FIELD_P() READ_ptr_fld()
#endif

#ifndef READ_ptr_fld
static PTR(FIELD) READ_ptr_fld(void);
#endif

#ifndef READ_fld
static FIELD READ_fld(void);
#endif

#ifndef READ_list_ptr_map
static LIST(PTR(MAP)) READ_list_ptr_map(void);
#endif

#ifndef READ_list_MAP_P
#define READ_list_MAP_P() READ_list_ptr_map()
#endif

#ifndef READ_MAP_P
#define READ_MAP_P() READ_ptr_map()
#endif

#ifndef READ_ptr_map
static PTR(MAP) READ_ptr_map(void);
#endif

#ifndef READ_map
static MAP READ_map(void);
#endif

#ifndef READ_list_ptr_arg
static LIST(PTR(ARGUMENT)) READ_list_ptr_arg(void);
#endif

#ifndef READ_list_ARGUMENT_P
#define READ_list_ARGUMENT_P() READ_list_ptr_arg()
#endif

#ifndef READ_ARGUMENT_P
#define READ_ARGUMENT_P() READ_ptr_arg()
#endif

#ifndef READ_ptr_arg
static PTR(ARGUMENT) READ_ptr_arg(void);
#endif

#ifndef READ_arg
static ARGUMENT READ_arg(void);
#endif


/* Disk reading routine for LIST(PTR(TYPE)) */

#ifndef READ_list_ptr_type

static LIST(PTR(TYPE)) READ_list_ptr_type
(void)
{
    LIST(PTR(TYPE)) x_;
    x_ = NULL_list(PTR(TYPE));
    while (READ_BITS(1)) {
	PTR(TYPE) y_;
	LIST(PTR(TYPE)) z_;
	y_ = READ_ptr_type();
	CONS_ptr(y_, NULL_list(PTR(TYPE)), z_);
	x_ = APPEND_list(x_, z_);
    }
    return x_;
}

#endif


/* Disk reading routine for TYPE */

#ifndef READ_type

static TYPE READ_type
(void)
{
    TYPE x_;
    x_ = NULL_type;
    if (READ_BITS(1) == 1) {
	zero_int size;
	unsigned tag_ = READ_BITS(4);
	switch (tag_) {
	    case type_primitive_tag: {
		PRIMITIVE_P prim;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_primitive(alias_);
		    break;
		}
		NEW_ALIAS_type_primitive(x_, alias_);
		size = READ_zero_int();
		prim = READ_PRIMITIVE_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_primitive_prim(x_), prim);
		break;
	    }
	    case type_ident_tag: {
		IDENTITY_P id;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_ident(alias_);
		    break;
		}
		NEW_ALIAS_type_ident(x_, alias_);
		size = READ_zero_int();
		id = READ_IDENTITY_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_ident_id(x_), id);
		break;
	    }
	    case type_enumeration_tag: {
		ENUM_P en;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_enumeration(alias_);
		    break;
		}
		NEW_ALIAS_type_enumeration(x_, alias_);
		size = READ_zero_int();
		en = READ_ENUM_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_enumeration_en(x_), en);
		break;
	    }
	    case type_structure_tag: {
		STRUCTURE_P struc;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_structure(alias_);
		    break;
		}
		NEW_ALIAS_type_structure(x_, alias_);
		size = READ_zero_int();
		struc = READ_STRUCTURE_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_structure_struc(x_), struc);
		break;
	    }
	    case type_onion_tag: {
		UNION_P un;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_onion(alias_);
		    break;
		}
		NEW_ALIAS_type_onion(x_, alias_);
		size = READ_zero_int();
		un = READ_UNION_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_onion_un(x_), un);
		break;
	    }
	    case type_ptr_tag: {
		TYPE_P sub;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_ptr(alias_);
		    break;
		}
		NEW_ALIAS_type_ptr(x_, alias_);
		size = READ_zero_int();
		sub = READ_TYPE_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_ptr_sub(x_), sub);
		break;
	    }
	    case type_list_tag: {
		TYPE_P sub;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_list(alias_);
		    break;
		}
		NEW_ALIAS_type_list(x_, alias_);
		size = READ_zero_int();
		sub = READ_TYPE_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_list_sub(x_), sub);
		break;
	    }
	    case type_stack_tag: {
		TYPE_P sub;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_stack(alias_);
		    break;
		}
		NEW_ALIAS_type_stack(x_, alias_);
		size = READ_zero_int();
		sub = READ_TYPE_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_stack_sub(x_), sub);
		break;
	    }
	    case type_vec_tag: {
		TYPE_P sub;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_vec(alias_);
		    break;
		}
		NEW_ALIAS_type_vec(x_, alias_);
		size = READ_zero_int();
		sub = READ_TYPE_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_vec_sub(x_), sub);
		break;
	    }
	    case type_vec_ptr_tag: {
		TYPE_P sub;
		unsigned alias_ = READ_ALIAS();
		if (READ_BITS(1) == 0) {
		    x_ = FIND_ALIAS_type_vec_ptr(alias_);
		    break;
		}
		NEW_ALIAS_type_vec_ptr(x_, alias_);
		size = READ_zero_int();
		sub = READ_TYPE_P();
		COPY_int(type_size(x_), size);
		COPY_ptr(type_vec_ptr_sub(x_), sub);
		break;
	    }
	    case type_quote_tag: {
		string defn;
		size = READ_zero_int();
		defn = READ_string();
		MAKE_type_quote(size, defn, x_ );
		break;
	    }
	    case type_undef_tag: {
		string name;
		size = READ_zero_int();
		name = READ_string();
		MAKE_type_undef(size, name, x_ );
		break;
	    }
	}
    }
    return x_;
}

#endif


/* Disk reading routine for PTR(PRIMITIVE) */

#ifndef READ_ptr_prim

static PTR(PRIMITIVE) READ_ptr_prim
(void)
{
    PTR(PRIMITIVE) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(PRIMITIVE);
    } else {
	x_ = MAKE_ptr(SIZE_prim);
	COPY_prim(x_, READ_prim());
    }
    return x_;
}

#endif


/* Disk reading routine for PRIMITIVE */

#ifndef READ_prim

static PRIMITIVE READ_prim
(void)
{
    PRIMITIVE x_;
    x_.id = READ_CLASS_ID_P();
    x_.defn = READ_string();
    return x_;
}

#endif


/* Disk reading routine for PTR(CLASS_ID) */

#ifndef READ_ptr_cid

static PTR(CLASS_ID) READ_ptr_cid
(void)
{
    PTR(CLASS_ID) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(CLASS_ID);
    } else {
	x_ = MAKE_ptr(SIZE_cid);
	COPY_cid(x_, READ_cid());
    }
    return x_;
}

#endif


/* Disk reading routine for CLASS_ID */

#ifndef READ_cid

static CLASS_ID READ_cid
(void)
{
    CLASS_ID x_;
    x_.name = READ_string();
    x_.name_aux = READ_string();
    x_.flag = READ_int();
    x_.file = READ_name_string();
    x_.line = READ_int();
    return x_;
}

#endif


/* Disk reading routine for PTR(IDENTITY) */

#ifndef READ_ptr_ident

static PTR(IDENTITY) READ_ptr_ident
(void)
{
    PTR(IDENTITY) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(IDENTITY);
    } else {
	x_ = MAKE_ptr(SIZE_ident);
	COPY_ident(x_, READ_ident());
    }
    return x_;
}

#endif


/* Disk reading routine for IDENTITY */

#ifndef READ_ident

static IDENTITY READ_ident
(void)
{
    IDENTITY x_;
    x_.id = READ_CLASS_ID_P();
    x_.defn = READ_TYPE_P();
    return x_;
}

#endif


/* Disk reading routine for PTR(TYPE) */

#ifndef READ_ptr_type

static PTR(TYPE) READ_ptr_type
(void)
{
    PTR(TYPE) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(TYPE);
    } else {
	x_ = MAKE_ptr(SIZE_type);
	COPY_type(x_, READ_type());
    }
    return x_;
}

#endif


/* Disk reading routine for PTR(ENUM) */

#ifndef READ_ptr_en

static PTR(ENUM) READ_ptr_en
(void)
{
    PTR(ENUM) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(ENUM);
    } else {
	x_ = MAKE_ptr(SIZE_en);
	COPY_en(x_, READ_en());
    }
    return x_;
}

#endif


/* Disk reading routine for ENUM */

#ifndef READ_en

static ENUM READ_en
(void)
{
    ENUM x_;
    x_.id = READ_CLASS_ID_P();
    x_.consts = READ_list_ECONST_P();
    x_.order = READ_number();
    x_.lists = READ_int();
    return x_;
}

#endif


/* Disk reading routine for LIST(PTR(ECONST)) */

#ifndef READ_list_ptr_ec

static LIST(PTR(ECONST)) READ_list_ptr_ec
(void)
{
    LIST(PTR(ECONST)) x_;
    x_ = NULL_list(PTR(ECONST));
    while (READ_BITS(1)) {
	PTR(ECONST) y_;
	LIST(PTR(ECONST)) z_;
	y_ = READ_ptr_ec();
	CONS_ptr(y_, NULL_list(PTR(ECONST)), z_);
	x_ = APPEND_list(x_, z_);
    }
    return x_;
}

#endif


/* Disk reading routine for PTR(ECONST) */

#ifndef READ_ptr_ec

static PTR(ECONST) READ_ptr_ec
(void)
{
    PTR(ECONST) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(ECONST);
    } else {
	x_ = MAKE_ptr(SIZE_ec);
	COPY_ec(x_, READ_ec());
    }
    return x_;
}

#endif


/* Disk reading routine for ECONST */

#ifndef READ_ec

static ECONST READ_ec
(void)
{
    ECONST x_;
    x_.name = READ_string();
    x_.value = READ_number();
    return x_;
}

#endif


/* Disk reading routine for PTR(STRUCTURE) */

#ifndef READ_ptr_str

static PTR(STRUCTURE) READ_ptr_str
(void)
{
    PTR(STRUCTURE) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(STRUCTURE);
    } else {
	x_ = MAKE_ptr(SIZE_str);
	COPY_str(x_, READ_str());
    }
    return x_;
}

#endif


/* Disk reading routine for STRUCTURE */

#ifndef READ_str

static STRUCTURE READ_str
(void)
{
    STRUCTURE x_;
    x_.id = READ_CLASS_ID_P();
    x_.base = READ_STRUCTURE_P();
    x_.defn = READ_list_COMPONENT_P();
    x_.output = READ_zero_int();
    return x_;
}

#endif


/* Disk reading routine for LIST(PTR(COMPONENT)) */

#ifndef READ_list_ptr_cmp

static LIST(PTR(COMPONENT)) READ_list_ptr_cmp
(void)
{
    LIST(PTR(COMPONENT)) x_;
    x_ = NULL_list(PTR(COMPONENT));
    while (READ_BITS(1)) {
	PTR(COMPONENT) y_;
	LIST(PTR(COMPONENT)) z_;
	y_ = READ_ptr_cmp();
	CONS_ptr(y_, NULL_list(PTR(COMPONENT)), z_);
	x_ = APPEND_list(x_, z_);
    }
    return x_;
}

#endif


/* Disk reading routine for PTR(COMPONENT) */

#ifndef READ_ptr_cmp

static PTR(COMPONENT) READ_ptr_cmp
(void)
{
    PTR(COMPONENT) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(COMPONENT);
    } else {
	x_ = MAKE_ptr(SIZE_cmp);
	COPY_cmp(x_, READ_cmp());
    }
    return x_;
}

#endif


/* Disk reading routine for COMPONENT */

#ifndef READ_cmp

static COMPONENT READ_cmp
(void)
{
    COMPONENT x_;
    x_.name = READ_string();
    x_.type = READ_TYPE_P();
    x_.value = READ_string();
    return x_;
}

#endif


/* Disk reading routine for PTR(UNION) */

#ifndef READ_ptr_un

static PTR(UNION) READ_ptr_un
(void)
{
    PTR(UNION) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(UNION);
    } else {
	x_ = MAKE_ptr(SIZE_un);
	COPY_un(x_, READ_un());
    }
    return x_;
}

#endif


/* Disk reading routine for UNION */

#ifndef READ_un

static UNION READ_un
(void)
{
    UNION x_;
    x_.id = READ_CLASS_ID_P();
    x_.base = READ_UNION_P();
    x_.s_defn = READ_list_COMPONENT_P();
    x_.u_defn = READ_list_FIELD_P();
    x_.map = READ_list_MAP_P();
    x_.no_fields = READ_int();
    return x_;
}

#endif


/* Disk reading routine for LIST(PTR(FIELD)) */

#ifndef READ_list_ptr_fld

static LIST(PTR(FIELD)) READ_list_ptr_fld
(void)
{
    LIST(PTR(FIELD)) x_;
    x_ = NULL_list(PTR(FIELD));
    while (READ_BITS(1)) {
	PTR(FIELD) y_;
	LIST(PTR(FIELD)) z_;
	y_ = READ_ptr_fld();
	CONS_ptr(y_, NULL_list(PTR(FIELD)), z_);
	x_ = APPEND_list(x_, z_);
    }
    return x_;
}

#endif


/* Disk reading routine for PTR(FIELD) */

#ifndef READ_ptr_fld

static PTR(FIELD) READ_ptr_fld
(void)
{
    PTR(FIELD) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(FIELD);
    } else {
	x_ = MAKE_ptr(SIZE_fld);
	COPY_fld(x_, READ_fld());
    }
    return x_;
}

#endif


/* Disk reading routine for FIELD */

#ifndef READ_fld

static FIELD READ_fld
(void)
{
    FIELD x_;
    x_.name = READ_string();
    x_.tag = READ_int();
    x_.flag = READ_int();
    x_.set = READ_int();
    x_.base = READ_FIELD_P();
    x_.defn = READ_list_COMPONENT_P();
    return x_;
}

#endif


/* Disk reading routine for LIST(PTR(MAP)) */

#ifndef READ_list_ptr_map

static LIST(PTR(MAP)) READ_list_ptr_map
(void)
{
    LIST(PTR(MAP)) x_;
    x_ = NULL_list(PTR(MAP));
    while (READ_BITS(1)) {
	PTR(MAP) y_;
	LIST(PTR(MAP)) z_;
	y_ = READ_ptr_map();
	CONS_ptr(y_, NULL_list(PTR(MAP)), z_);
	x_ = APPEND_list(x_, z_);
    }
    return x_;
}

#endif


/* Disk reading routine for PTR(MAP) */

#ifndef READ_ptr_map

static PTR(MAP) READ_ptr_map
(void)
{
    PTR(MAP) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(MAP);
    } else {
	x_ = MAKE_ptr(SIZE_map);
	COPY_map(x_, READ_map());
    }
    return x_;
}

#endif


/* Disk reading routine for MAP */

#ifndef READ_map

static MAP READ_map
(void)
{
    MAP x_;
    x_.name = READ_string();
    x_.flag = READ_int();
    x_.ret_type = READ_TYPE_P();
    x_.args = READ_list_ARGUMENT_P();
    return x_;
}

#endif


/* Disk reading routine for LIST(PTR(ARGUMENT)) */

#ifndef READ_list_ptr_arg

static LIST(PTR(ARGUMENT)) READ_list_ptr_arg
(void)
{
    LIST(PTR(ARGUMENT)) x_;
    x_ = NULL_list(PTR(ARGUMENT));
    while (READ_BITS(1)) {
	PTR(ARGUMENT) y_;
	LIST(PTR(ARGUMENT)) z_;
	y_ = READ_ptr_arg();
	CONS_ptr(y_, NULL_list(PTR(ARGUMENT)), z_);
	x_ = APPEND_list(x_, z_);
    }
    return x_;
}

#endif


/* Disk reading routine for PTR(ARGUMENT) */

#ifndef READ_ptr_arg

static PTR(ARGUMENT) READ_ptr_arg
(void)
{
    PTR(ARGUMENT) x_;
    if (READ_BITS(1) == 0) {
	x_ = NULL_ptr(ARGUMENT);
    } else {
	x_ = MAKE_ptr(SIZE_arg);
	COPY_arg(x_, READ_arg());
    }
    return x_;
}

#endif


/* Disk reading routine for ARGUMENT */

#ifndef READ_arg

static ARGUMENT READ_arg
(void)
{
    ARGUMENT x_;
    x_.name = READ_string();
    x_.type = READ_TYPE_P();
    return x_;
}

#endif


#endif
