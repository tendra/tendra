/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: diagtypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1998/01/11  18:45:10  pwe
 * consistent new/old diags
 *
 * Revision 1.3  1997/12/04  19:36:45  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.2  1997/08/23  13:27:17  pwe
 * initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/
#ifndef diagtypes_key
#define diagtypes_key 1


#ifdef NEWDIAGS

typedef dg_name diag_descriptor;
typedef dg_name_list diag_descriptor_list;
typedef dg_name_list diag_unit;
typedef dg_tag diag_tag;
typedef dgtag_struct diag_tagdef;
typedef int diag_tagdef_list;
typedef dg_type diag_type;
typedef dg_type_list diag_type_list;
typedef dg_enum enum_values;
typedef dg_enum_list enum_values_list;
typedef dg_classmem diag_field;
typedef dg_classmem_list diag_field_list;
typedef int diag_tq;
typedef dg_filename filename;
typedef dg_sourcepos sourcemark;
typedef int diag_type_unit;


#else

				/* temp hacsk to check syntax */

				/* end hacks */
				/* dummy defs of lists */

				/* end dummy defs */
				/* forward defns for compiler pacification */

#include "diagtypes1.h"


				/* end forward defns */

struct filename_t 
{
  nat		date;
  tdfstring	machine;
  tdfstring	file;
};

typedef	struct sourcemark_t
{
  filename	file;
  nat		line_no;
  nat		char_off;
} sourcemark;

struct enum_values_t
{
  exp		val;
  tdfstring	nme;
};

typedef struct enum_values_t *	enum_values;

struct enum_values_list_t 
{
  int		len;
  int		lastused;
  enum_values *		array;
};

typedef struct enum_values_list_t *	enum_values_list;

struct diag_field_t
{
  tdfstring	field_name;
  exp		where;
  diag_type	field_type;
};

typedef struct diag_field_t *diag_field;

struct diag_field_list_t 
{
  int		len;
  int		lastused;
  diag_field *	array;
};

typedef struct diag_field_list_t *	diag_field_list;

struct diag_type_list_t
{
  int		len;
  int		lastused;
  diag_type 		*array;
};

typedef struct diag_type_list_t *diag_type_list;

typedef struct 
{	 	
  unsigned	is_const:1;
  unsigned	is_volatile:1;
} diag_tq;


typedef tdfint diag_tag;

struct diag_tagdef_t
{
  diag_tag	d_tag;
  char        *	ext_name;
  diag_type	d_type;
};

typedef struct diag_tagdef_t diag_tagdef;

typedef enum 
{
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

struct diag_type_t 
{
  diag_type_key	key;
  OUTPUT_REC been_outed;
  union
  {
    struct
    {
      diag_type		element_type;
      exp		stride;
      exp		lower_b;
      exp		upper_b;
      diag_type		index_type;
    } array;
    struct
    {
      diag_type		result_type;
      nat		no_of_bits;
    } bitfield;
    struct
    {
      diag_type		base_type;
      tdfstring		nme;
      enum_values_list	values;
    } t_enum;
    floating_variety	f_var;
    struct
    {
      diag_type		object;
      diag_tq		qualifier;
    } loc;
    struct
    {
      diag_type_list	params;
      bool 		opt_args;
      diag_type		result_type;
    } proc;
    struct
    {
      diag_type		object;
      diag_tq		qualifier;
    } ptr;
    struct
    {
      shape		tdf_shape;
      tdfstring		nme;
      diag_field_list fields;
    } t_struct;
    struct
    {
      shape		tdf_shape;
      tdfstring		nme;
      diag_field_list fields;
    } t_union;
    variety		var;
  } data;
};

typedef enum 
{
  DIAG_UNINIT,
  DIAG_ID_KEY,
  DIAG_STRUCT_KEY,
  DIAG_TYPEDEF_KEY
} diag_desc_key;

typedef struct diagdef_t
{
  diag_desc_key 	key;
  char * 		ext_name;
  union	
  {
    struct 
    {
      tdfstring 	nme;
      diag_type 	new_type;
      sourcemark 	whence;
      exp		access;
    } id;
    struct
    {
      tdfstring 	nme;
      diag_type		new_type;
      sourcemark 	whence;
    } struc;
    struct
    {
      tdfstring		nme;
      diag_type		new_type;
      sourcemark 	whence;
    } typ;
  } data;
} diagdef;
				/* diag_descriptor is in diagtypes1.h */

typedef struct diag_unit_t
{
  int		len;
  int		lastused;
  diag_descriptor *	array;
} diag_unit;

typedef diag_unit diag_descriptor_list;

typedef int diag_type_unit;
typedef diag_type_unit diag_tagdef_list;

#include "diaginfo.h"

#endif
#endif

