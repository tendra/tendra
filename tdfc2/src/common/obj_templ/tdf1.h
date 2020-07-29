/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

#define ENS_%SN(A, B)	%48tENC_BITS(A, %SB, B)
@if sort.extends
#define ENX_%SN(A, B)	%48tENC_EXTN(A, %SB, B)
@endif
@loop sort.cons
@if cons.edge
@if cons.extends
#define ENC_%27CN(A, B)%48t{ ENX_%SN(A, %CE); ENC_INT(A, B); }
@else
#define ENC_%27CN(A, B)%48t{ ENS_%SN(A, %CE); ENC_INT(A, B); }
@endif
@else
@if cons.extends
#define ENC_%27CN(A)	%48tENX_%SN(A, %CE)
@else
#define ENC_%27CN(A)	%48tENS_%SN(A, %CE)
@endif
@endif
@end
@endif
@end
