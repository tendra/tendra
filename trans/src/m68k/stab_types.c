/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

#include <construct/shape.h>

#include <reader/code.h>
#include <reader/externs.h>

#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "utility.h"
#include "xdb_output.h"
#include "stab_types.h"

/*
    CREATE A STABS INSTRUCTION
*/

void
make_stabs(char *s, int a, long b, mach_op *op)
{
	mach_op *p = make_extern_data(s, 0);
	p->of = make_int_data((long)a);
	p->of->of = make_int_data(0);
	p->of->of->of = make_int_data(b);
	p->of->of->of->of = (op ? op : make_int_data(0));
	make_instr(m_stabs, p, NULL, 0);
}


/*
    CREATE A STABN INSTRUCTION
*/

void
make_stabn(int a, long lab)
{
	mach_op *p = make_int_data((long)a);
	p->of = make_int_data(0);
	p->of->of = make_int_data(0);
	p->of->of->of = make_lab_data(lab, 0);
	make_instr(m_stabn, p, NULL, 0);
}


/*
    TYPE USED FOR BUILDING STAB TYPES
*/

#define TSIZE 100

typedef struct page_tag {
	int index;
	char text[TSIZE];
	struct page_tag *next;
} page;


/*
    LIST OF FREE PAGES
*/

static page *free_pages = NULL;


/*
    CREATE A NEW PAGE
*/

static page *
new_page(void)
{
	page *p = free_pages;
	if (p == NULL) {
		p = alloc_nof(page, 1);
	} else {
		free_pages = p->next;
	}
	p->index = 0;
	p->next = NULL;
	return p;
}


/*
    ADD A STRING TO A PAGE
*/

static page *
sprint_string(page *p, char *s)
{
	int i = p->index;
	for (; *s; s++) {
		if (i >= TSIZE) {
			p->index = TSIZE;
			p->next = new_page();
			p = p->next;
			i = 0;
		}
		p->text[i] = *s;
		i++;
	}
	p->index = i;
	return p;
}


/*
    ADD A NUMBER TO A PAGE
*/

static page *
sprint_number(page *p, long n)
{
	char buff[100];
	IGNORE sprintf(buff, "%ld", n);
	return sprint_string(p, buff);
}


/*
    CREATE A NEW STAB TYPE
*/

static char *
new_stab_type(diag_type dt)
{
	static long next_stab_type = 16;
	char *res = alloc_nof(char, 8);
	sprintf(res, "%ld", next_stab_type++);
	if (dt) {
		dt->been_outed = res;
	}
	return res;
}


/*
    SIZE OF LAST TYPE ANALYSED
*/

static long last_type_sz = 0;


/*
    INDEX TO SIMPLE STAB TYPES
*/

#define STAB_SCHAR	0
#define STAB_UCHAR	1
#define STAB_SWORD	2
#define STAB_UWORD	3
#define STAB_SLONG	4
#define STAB_ULONG	5
#define STAB_FLOAT	6
#define STAB_DOUBLE	7
#define STAB_LDOUBLE	8
#define STAB_VOID	9
#define STAB_PTR	10
#define STAB_COMPLEX	-1


/*
    TABLE OF SIMPLE STAB TYPES
*/

static char *stab_tab[] = {
	"2", "11", "6", "8", "1", "4", "12", "13", "14", "15",
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


/*
    TEST IF A TYPE IS SIMPLE
*/

static int
test_type(diag_type dt)
{
	switch (dt->key) {
	case DIAG_TYPE_FLOAT: {
		shape sha = f_floating(dt->data.f_var);
		last_type_sz = shape_size(sha);
		if (name(sha) == shrealhd) {
			return STAB_FLOAT;
		}
		if (name(sha) == realhd) {
			return STAB_DOUBLE;
		}
		return STAB_LDOUBLE;
	}
	case DIAG_TYPE_VARIETY: {
		shape sha = f_integer(dt->data.var);
		last_type_sz = shape_size(sha);
		switch (name(sha)) {
		case scharhd:
			return STAB_SCHAR;
		case swordhd:
			return STAB_SWORD;
		case slonghd:
			return STAB_SLONG;
		case ucharhd:
			return STAB_UCHAR;
		case uwordhd:
			return STAB_UWORD;
		case ulonghd:
			return STAB_ULONG;
		}
		break;
	}
	case DIAG_TYPE_NULL:
		last_type_sz = 0;
		return STAB_VOID;
	default:
		break;
	}
	return STAB_COMPLEX;
}


/*
    BUILD UP A STAB TYPE IN A BUFFER
*/

static page *
build_stab_type(diag_type dt, page *ptr)
{
	switch (dt->key) {
	case DIAG_TYPE_FLOAT:
	case DIAG_TYPE_NULL:
	case DIAG_TYPE_VARIETY: {
		/* Simple types */
		int t = test_type(dt);
		ptr = sprint_string(ptr, stab_tab[t]);
		break;
	}
	case DIAG_TYPE_ARRAY: {
		diag_type dtl = dt->data.array.element_type;
		long lo = no(dt->data.array.lower_b);
		long hi = no(dt->data.array.upper_b);
		char *stl = analyse_stab_type(dtl, NULL, NULL);
		ptr = sprint_string(ptr, new_stab_type(dt));
		ptr = sprint_string(ptr, "=ar1;");
		ptr = sprint_number(ptr, lo);
		ptr = sprint_string(ptr, ";");
		ptr = sprint_number(ptr, hi);
		ptr = sprint_string(ptr, ";");
		ptr = sprint_string(ptr, stl);
		last_type_sz *= (hi - lo + 1);
		break;
	}
	case DIAG_TYPE_BITFIELD: {
		long sz = dt->data.bitfield.no_of_bits.nat_val.small_nat;
		ptr = sprint_string(ptr, "1");
		last_type_sz = sz;
		break;
	}
	case DIAG_TYPE_ENUM:
		/* Not yet supported */
		ptr = sprint_string(ptr, "1");
		last_type_sz = 32;
		break;
	case DIAG_TYPE_LOC: {
		diag_type dtl = dt->data.loc.object;
		ptr = build_stab_type(dtl, ptr);
		break;
	}
	case DIAG_TYPE_PROC: {
		diag_type dtl = dt->data.proc.result_type;
		char *stl = analyse_stab_type(dtl, NULL, NULL);
		ptr = sprint_string(ptr, new_stab_type(dt));
		ptr = sprint_string(ptr, "=*");
		ptr = sprint_string(ptr, new_stab_type(NULL));
		ptr = sprint_string(ptr, "=f");
		ptr = sprint_string(ptr, stl);
		last_type_sz = 32;
		break;
	}
	case DIAG_TYPE_PTR: {
		diag_type dtl = dt->data.ptr.object;
		int t = test_type(dtl);
		if (t != STAB_COMPLEX) {
			char *st = stab_tab[STAB_PTR + t];
			if (st) {
				ptr = sprint_string(ptr, st);
			} else {
				st = new_stab_type(NULL);
				stab_tab[STAB_PTR + t] = st;
				ptr = sprint_string(ptr, st);
				ptr = sprint_string(ptr, "=*");
				ptr = sprint_string(ptr, stab_tab[t]);
			}
		} else {
			char *stl = analyse_stab_type(dtl, NULL, NULL);
			ptr = sprint_string(ptr, new_stab_type(dt));
			ptr = sprint_string(ptr, "=*");
			ptr = sprint_string(ptr, stl);
		}
		last_type_sz = 32;
		break;
	}
	case DIAG_TYPE_STRUCT: {
		char *nm = dt->data.t_struct.nme.ints.chars;
		if (*nm) {
			char *res;
			dt->data.t_struct.nme.ints.chars = "";
			res = analyse_stab_type(dt, nm, "T");
			dt->data.t_struct.nme.ints.chars = nm;
			make_stabs(res, 128, 0L, NULL);
			res = (char *)dt->been_outed;
			ptr = sprint_string(ptr, res);
		} else {
			shape sha = dt->data.t_struct.tdf_shape;
			long sz = shape_size(sha);
#if 0
			struct_fields *fld = dt->data.t_struct.fields->array;
#else
			diag_field *fld = dt->data.t_struct.fields->array;
#endif
			long i, n = (long)dt->data.t_struct.fields->lastused;

			ptr = sprint_string(ptr, new_stab_type(dt));
			ptr = sprint_string(ptr, "=s");
			ptr = sprint_number(ptr, sz / 8);

			/* Deal with structure fields */
			for (i = n - 1; i >= 0; i--) {
				char *fnm = fld[i] ->field_name.ints.chars;
				long off = no(fld[i] ->where);
				diag_type dtl = fld[i] ->field_type;
				char *q = analyse_stab_type(dtl, NULL, NULL);
				ptr = sprint_string(ptr, fnm);
				ptr = sprint_string(ptr, ":");
				ptr = sprint_string(ptr, q);
				ptr = sprint_string(ptr, ",");
				ptr = sprint_number(ptr, off);
				ptr = sprint_string(ptr, ",");
				ptr = sprint_number(ptr, last_type_sz);
				ptr = sprint_string(ptr, ";");
			}
			ptr = sprint_string(ptr, ";");
			last_type_sz = sz;
		}
		break;
	}
	case DIAG_TYPE_UNION: {
		char *nm = dt->data.t_union.nme.ints.chars;
		if (*nm) {
			char *res;
			dt->data.t_struct.nme.ints.chars = "";
			res = analyse_stab_type(dt, nm, "T");
			dt->data.t_struct.nme.ints.chars = nm;
			make_stabs(res, 128, 0L, NULL);
			res = (char *)dt->been_outed;
			ptr = sprint_string(ptr, res);
		} else {
			shape sha = dt->data.t_union.tdf_shape;
			long sz = shape_size(sha);
#if 0
			union_fields *fld = dt->data.t_union.fields->array;
#else
			diag_field *fld = dt->data.t_union.fields->array;
#endif
			long i, n = (long)dt->data.t_union.fields->lastused;

			ptr = sprint_string(ptr, new_stab_type(dt));
			ptr = sprint_string(ptr, "=u");
			ptr = sprint_number(ptr, sz / 8);

			/* Deal with union fields */
			for (i = n - 1; i >= 0; i--) {
				char *fnm = fld[i] ->field_name.ints.chars;
				diag_type dtl = fld[i] ->field_type;
				char *q = analyse_stab_type(dtl, NULL, NULL);
				ptr = sprint_string(ptr, fnm);
				ptr = sprint_string(ptr, ":");
				ptr = sprint_string(ptr, q);
				ptr = sprint_string(ptr, ",0,");
				ptr = sprint_number(ptr, last_type_sz);
				ptr = sprint_string(ptr, ";");
			}
			ptr = sprint_string(ptr, ";");
			last_type_sz = sz;
		}
		break;
	}
	default:
		ptr = sprint_string(ptr, "15");
		last_type_sz = 0;
		break;
	}
	return ptr;
}


/*
    FIND A STAB TYPE
*/

char *
analyse_stab_type(diag_type dt, char *nm, char *cl)
{
	int n = 0;
	page *ptr, *p;
	char *res = (char *)dt->been_outed;
	if (res && nm == NULL && cl == NULL) {
		return res;
	}
	p = ptr = new_page();
	if (nm) {
		p = sprint_string(p, "\"");
		p = sprint_string(p, nm);
	}
	if (cl) {
		p = sprint_string(p, ":");
		p = sprint_string(p, cl);
	}
	if (res) {
		p = sprint_string(p, res);
	} else {
		p = build_stab_type(dt, p);
	}
	if (nm) {
		p = sprint_string(p, "\"");
	}

	/* Copy accumulated string */
	for (p = ptr; p; p = p->next) {
		n += p->index;
	}
	res = alloc_nof(char, n + 1);
	n = 0;
	for (p = ptr; p; p = p->next) {
		strncpy(res + n, p->text, p->index);
		n += p->index;
	}
	res[n] = 0;

	/* Free pages */
	p =  ptr;
	while (p->next) {
		p = p->next;
	}
	p->next = free_pages;
	free_pages = ptr;
	return res;
}


/*
    INITIALIZE BASIC STAB TYPES
*/

void
init_stab_types(void)
{
	static char *stab_types[] = {
		"\"int:t1=r1;-2147483648;2147483647;\"",
		"\"char:t2=r2;0;127;\"",
		"\"long int:t3=r1;-2147483648;2147483647;\"",
		"\"unsigned int:t4=r1;0;-1;\"",
		"\"long unsigned int:t5=r1;0;-1;\"",
		"\"short int:t6=r1;-32768;32767;\"",
		"\"long long int:t7=r1;0;-1;\"",
		"\"short unsigned int:t8=r1;0;65535;\"",
		"\"long long unsigned int:t9=r1;0;-1;\"",
		"\"signed char:t10=r1;-128;127;\"",
		"\"unsigned char:t11=r1;0;255;\"",
		"\"float:t12=r1;4;0;\"",
		"\"double:t13=r1;8;0;\"",
		"\"long double:t14=r1;8;0;\"",
		"\"void:t15=15\""
	};
	int i;
	for (i = 0; i < 15; i++) {
		make_stabs(stab_types[i], 128, 0L, NULL);
	}
}
