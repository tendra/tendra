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


/**** type.c --- Type ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the type ADT manipulation routines.
 *
 **** Change Log:
 * $Log: type.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:59:09  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:44  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "type.h"

/*--------------------------------------------------------------------------*/

TypeP
type_create PROTO_Z ()
{
    TypeP type = ALLOCATE (TypeT);

    type->assign_code        = NIL (GenericP);
    type->param_assign_code  = NIL (GenericP);
    type->result_assign_code = NIL (GenericP);
    return (type);
}

#ifdef FS_FAST
#undef type_get_assign_code
#endif /* defined (FS_FAST) */
GenericP
type_get_assign_code PROTO_N ((type))
		     PROTO_T (TypeP type)
{
    return (type->assign_code);
}
#ifdef FS_FAST
#define type_get_assign_code(t) ((t)->assign_code)
#endif /* defined(FS_FAST) */

#ifdef FS_FAST
#undef type_set_assign_code
#endif /* defined (FS_FAST) */
void
type_set_assign_code PROTO_N ((type, code))
		     PROTO_T (TypeP    type X
			      GenericP code)
{
    ASSERT (type->assign_code == NIL (GenericP));
    type->assign_code = code;
}
#ifdef FS_FAST
#define type_set_assign_code(t, c) ((t)->assign_code = (c))
#endif /* defined(FS_FAST) */

#ifdef FS_FAST
#undef type_get_param_assign_code
#endif /* defined (FS_FAST) */
GenericP
type_get_param_assign_code PROTO_N ((type))
			   PROTO_T (TypeP type)
{
    return (type->param_assign_code);
}
#ifdef FS_FAST
#define type_get_param_assign_code(t) ((t)->param_assign_code)
#endif /* defined(FS_FAST) */

#ifdef FS_FAST
#undef type_set_param_assign_code
#endif /* defined (FS_FAST) */
void
type_set_param_assign_code PROTO_N ((type, code))
			   PROTO_T (TypeP    type X
				    GenericP code)
{
    ASSERT (type->param_assign_code == NIL (GenericP));
    type->param_assign_code = code;
}
#ifdef FS_FAST
#define type_set_param_assign_code(t, c) ((t)->param_assign_code = (c))
#endif /* defined(FS_FAST) */

#ifdef FS_FAST
#undef type_get_result_assign_code
#endif /* defined (FS_FAST) */
GenericP
type_get_result_assign_code PROTO_N ((type))
			    PROTO_T (TypeP type)
{
    return (type->result_assign_code);
}
#ifdef FS_FAST
#define type_get_result_assign_code(t) ((t)->result_assign_code)
#endif /* defined(FS_FAST) */

#ifdef FS_FAST
#undef type_set_result_assign_code
#endif /* defined (FS_FAST) */
void
type_set_result_assign_code PROTO_N ((type, code))
			    PROTO_T (TypeP    type X
				     GenericP code)
{
    ASSERT (type->result_assign_code == NIL (GenericP));
    type->result_assign_code = code;
}
#ifdef FS_FAST
#define type_set_result_assign_code(t, c) ((t)->result_assign_code = (c))
#endif /* defined(FS_FAST) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
