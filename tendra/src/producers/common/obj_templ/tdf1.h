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


/*
    AUTOMATICALLY GENERATED FROM TDF %VA.%VB
    BY %ZX (VERSION %ZV), DO NOT EDIT
*/

#define TDF_major	%48t%VA
#define TDF_minor	%48t%VB

@use all
@loop sort
@if sort.unit
#define LINK_%SN	%48t"%SU"
@endif
@end
#define LINK_tld_props	%48t"tld"

@loop sort
@if sort.link
#define LINK_%SN	%48t"%SL"
@endif
@end
#define LINK_label	%48t"label"

@loop sort
@if sort.name.foreign
#define LINK_%SN	%48t"%SCN"
@endif
@end
@loop sort
@if sort.basic

#define ENS_%SN( A, B )	%48tENC_BITS ( A, %SB, B )
@if sort.extends
#define ENX_%SN( A, B )	%48tENC_EXTN ( A, %SB, B )
@endif
@loop sort.cons
@if cons.edge
@if cons.extends
#define ENC_%27CN( A, B )%48t{ ENX_%SN ( A, %CE ) ; ENC_INT ( A, B ) ; }
@else
#define ENC_%27CN( A, B )%48t{ ENS_%SN ( A, %CE ) ; ENC_INT ( A, B ) ; }
@endif
@else
@if cons.extends
#define ENC_%27CN( A )	%48tENX_%SN ( A, %CE )
@else
#define ENC_%27CN( A )	%48tENS_%SN ( A, %CE )
@endif
@endif
@end
@endif
@end
