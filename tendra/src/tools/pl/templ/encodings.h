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


#ifndef ENCODING_INCLUDED
#define ENCODING_INCLUDED


@use all
@loop sort
@if sort.simple
/* CONSTRUCTS FOR %ST */
@loop sort.cons

@if cons.params
#define o_%CN(%
@loop cons.param
 p%PE,%
@end
%b )\
@else
#define o_%CN\
@endif
@if cons.token
    TOK_APP (\
@if cons.extends
	out_extendable_int ( ( unsigned long ) e_%CN, ( unsigned ) %SB ),\
@else
	out_basic_int ( ( unsigned long ) e_%CN, ( unsigned ) %SB ),\
@endif
	s_%SN, p0, p1 )
@else
@if cons.cond
    TDF_COND (\
@if cons.extends
	out_extendable_int ( ( unsigned long ) e_%CN, ( unsigned ) %SB ),\
@else
	out_basic_int ( ( unsigned long ) e_%CN, ( unsigned ) %SB ),\
@endif
	s_%SN, p0, p1, p2 )
@else
    {\
@if sort.basic
@if cons.extends
	out_extendable_int ( ( unsigned long ) e_%CN, ( unsigned ) %SB ) ;\
@else
	out_basic_int ( ( unsigned long ) e_%CN, ( unsigned ) %SB ) ;\
@endif
@endif
@loop cons.param
@if param.sort.compound
	o_%PSN ( p%PE ) ;\
@else
	p%PE ; ASSERT_SORT ( s_%PSN ) ;\
@endif
@end
	SET_RSORT ( s_%SN ) ;\
    }
@endif
@endif
@end


@endif
@end
/* CONSTRUCTS FOR COMPOUND SORTS */

@loop sort
@if sort.option
#define o_%SN( p )	%40tTDF_OPTION ( p, s_%SSN )
@else
@if sort.list
#define o_%SN( p )	%40tTDF_LIST ( p, s_%SSN )
@else
@if sort.slist
#define o_%SN( p )	%40tTDF_SLIST ( p, s_%SSN )
@endif
@endif
@endif
@end


#endif
