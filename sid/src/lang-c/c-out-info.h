/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-out-info.h - Output control ADT.
 *
 * See the file "c-out-info.c" for more information.
 */

#ifndef H_C_OUT_INFO
#define H_C_OUT_INFO

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include <exds/ostream.h>
#include "../output.h"
#include "persistent.h"

/*To avoid circularity:*/
struct CCodeT;

typedef enum {
    CPFX_TYPE,
    CPFX_FN,
    CPFX_IN,
    CPFX_OUT,
    CPFX_LABEL,
    CPFX_TERMINAL,
    CPFX_PERSISTENTS,
    CPFX_NUM_PREFIXES
} CPrefixT;

typedef struct COutputInfoT {
    OutputInfoT *       info;
    struct CCodeT      *header1;
    struct CCodeT      *header2;
    struct CCodeT      *trailer1;
    struct CCodeT      *trailer2;
    NStringT		prefixes[CPFX_NUM_PREFIXES];
    PersistentListT    persistents;
    bool		prototypes;
    bool		numeric_ids;
    bool		numeric_terminals;
    bool		casts;
    bool		unreachable;
    bool		lines;
    bool		terminals;
    unsigned		split;
} COutputInfoT;

void		 c_out_info_init(COutputInfoT *, OutputInfoT *);
OutputInfoT *	 c_out_info_info(COutputInfoT *);
OStreamT *		 c_out_info_ostream(COutputInfoT *);
char *		 c_out_info_program_name(COutputInfoT *);
char *		 c_out_info_source_name(COutputInfoT *);
char *		 c_out_info_c_source_name(COutputInfoT *);
struct CCodeT	*c_out_info_get_header1(COutputInfoT *);
void		 c_out_info_set_header1(COutputInfoT *, struct CCodeT *);
struct CCodeT	*c_out_info_get_header2(COutputInfoT *);
void		 c_out_info_set_header2(COutputInfoT *, struct CCodeT *);
struct CCodeT	*c_out_info_get_trailer1(COutputInfoT *);
void		 c_out_info_set_trailer1(COutputInfoT *, struct CCodeT *);
struct CCodeT	*c_out_info_get_trailer2(COutputInfoT *);
void		 c_out_info_set_trailer2(COutputInfoT *, struct CCodeT *);
NStringT *		 c_out_info_type_prefix(COutputInfoT *);
NStringT *		 c_out_info_fn_prefix(COutputInfoT *);
NStringT *		 c_out_info_in_prefix(COutputInfoT *);
NStringT *		 c_out_info_out_prefix(COutputInfoT *);
NStringT *		 c_out_info_label_prefix(COutputInfoT *);
NStringT *		 c_out_info_terminal_prefix(COutputInfoT *);
NStringT * 	 c_out_info_persistents_prefix(COutputInfoT * info);
NStringT *	 c_out_info_prefix(COutputInfoT *, CPrefixT);
PersistentListT * 	c_out_info_persistents(COutputInfoT* info);
bool		 c_out_info_get_prototypes(COutputInfoT *);
void		 c_out_info_set_prototypes(COutputInfoT *, bool);
bool		 c_out_info_get_numeric_ids(COutputInfoT *);
void		 c_out_info_set_numeric_ids(COutputInfoT *, bool);
bool		 c_out_info_get_numeric_terminals(COutputInfoT *);
void		 c_out_info_set_numeric_terminals(COutputInfoT *, bool);
bool		 c_out_info_get_casts(COutputInfoT *);
void		 c_out_info_set_casts(COutputInfoT *, bool);
bool		 c_out_info_get_unreachable(COutputInfoT *);
void		 c_out_info_set_unreachable(COutputInfoT *, bool);
bool		 c_out_info_get_lines(COutputInfoT *);
void		 c_out_info_set_lines(COutputInfoT *, bool);
bool		 c_out_info_get_terminals(COutputInfoT *);
void		 c_out_info_set_terminals(COutputInfoT *, bool);
unsigned		 c_out_info_get_split(COutputInfoT *);
void		 c_out_info_set_split(COutputInfoT *, unsigned);

#endif /* !defined (H_C_OUT_INFO) */
