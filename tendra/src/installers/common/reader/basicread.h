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
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: basicread.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
#ifndef basicrd_key
#define basicrd_key 1



extern char initreader PROTO_S ((char *n));
     /* start the input stream reading from the file called n */

extern void endreader PROTO_S ((void));

extern int getcode PROTO_S ((int n));
     /* read n bits from the input stream */

extern int get_big_code PROTO_S ((int n));
     /* read construct encoding number (n bit pieces)
        from the input stream */

extern place keep_place PROTO_S ((void));
     /* deliver the current place in the input stream */

extern place add_place PROTO_S ((place pl, int n));
     /* form a place n bits further on in the input stream than pl */

extern void set_place PROTO_S ((place pl));
     /* start reading from pl in the input stream */

extern place new_place PROTO_S ((int bn));
     /* records bn bits from the input stream in a new place.
        The input stream is stepped on over these bits */

extern void failer PROTO_S ((char *s));
     /* records the failure message s and sets good_trans to false */

extern int  small_dtdfint PROTO_S ((void));
     

extern void to_boundary PROTO_S ((void));
     /* step the input stream on to the next byte boundary */

extern bitstream d_bitstream PROTO_S ((void));
     /* delivers a new place for the bitstream in the input stream and
        steps over it */

extern void start_bytestream PROTO_S ((void));
     /* records in bytestream_pickup the end of a bytestream */

extern bytestream d_bytestream PROTO_S ((void));
     /* returns bytestream_pickup */

extern void ignore_bytestream PROTO_S ((void));
     /* steps over a bytestream */

extern void end_bytestream PROTO_S ((void));
     /* resets the input stream from bytestream_pickup */

extern tdfstring d_tdfstring PROTO_S ((void));
     /* reads a tdfstring from the input stream */

extern tdfstring d_tdfident PROTO_S ((void));
     /* reads a tdfident from the input stream */

extern tdfbool d_tdfbool PROTO_S ((void));
     /* reads a tdfbool from the input stream */

extern tdfint d_tdfint PROTO_S ((void));
     /* reads a tdfint from the input stream */

extern int crt_lno;

extern char * crt_flnm;

extern int crt_charno;

extern void add_capsule_frees PROTO_S ((void * vp));



#endif
