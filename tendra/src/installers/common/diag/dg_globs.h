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
$Log: dg_globs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/12/04  19:36:31  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.2  1997/10/23  09:21:09  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.1  1997/08/23  13:26:53  pwe
 * initial ANDF-DE
 *
***********************************************************************/

#ifndef dg_glob_key
#define dg_glob_key

extern dg_filename all_files;
extern dg_compilation all_comp_units;
extern int doing_inlining;
extern dg_info current_dg_info;
extern exp current_dg_exp;
extern short_sourcepos no_short_sourcepos;

#endif
