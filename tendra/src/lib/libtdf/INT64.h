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


#ifndef __INT64_h
#define __INT64_h

extern INT64	make_INT64	PROTO_S ((INT32, UINT32));
extern UINT64	make_UINT64	PROTO_S ((UINT32, UINT32));

extern INT64	__TDFUs_plus	PROTO_S ((INT64, INT64));
extern UINT64	__TDFUu_plus	PROTO_S ((UINT64, UINT64));
extern INT64	__TDFUs_minus	PROTO_S ((INT64, INT64));
extern UINT64	__TDFUu_minus	PROTO_S ((UINT64, UINT64));
extern INT64	__TDFUs_mult	PROTO_S ((INT64, INT64));
extern UINT64	__TDFUu_mult	PROTO_S ((UINT64, UINT64));
extern INT64	__TDFUs_div1	PROTO_S ((INT64, INT64));
extern INT64	__TDFUs_div2	PROTO_S ((INT64, INT64));
extern UINT64	__TDFUu_div2	PROTO_S ((UINT64, UINT64));
extern INT64	__TDFUs_rem1	PROTO_S ((INT64, INT64));
extern INT64	__TDFUs_rem2	PROTO_S ((INT64, INT64));
extern UINT64	__TDFUu_rem2	PROTO_S ((UINT64, UINT64));
extern INT64	__TDFUneg	PROTO_S ((INT64));
extern UINT64	__TDFUu_shl	PROTO_S ((UINT64, UINT32));
extern UINT64	__TDFUu_shr	PROTO_S ((UINT64, UINT32));
extern INT64	__TDFUabs	PROTO_S ((INT64));
extern INT64	__TDFUsswiden	PROTO_S ((INT32));
extern UINT64	__TDFUsuwiden	PROTO_S ((INT32));
extern UINT64	__TDFUuuwiden	PROTO_S ((UINT32));
extern INT64	__TDFUuswiden	PROTO_S ((UINT32));
extern INT32	__TDFUssshorten	PROTO_S ((INT64));
extern UINT32	__TDFUsushorten	PROTO_S ((INT64));
extern UINT32	__TDFUuushorten	PROTO_S ((UINT64));
extern INT32	__TDFUusshorten	PROTO_S ((UINT64));
extern INT64	__TDFUu642s64	PROTO_S ((UINT64));
extern UINT64	__TDFUs642u64	PROTO_S ((INT64));
extern INT64	__TDFUs_max	PROTO_S ((INT64, INT64));
extern UINT64	__TDFUu_max	PROTO_S ((UINT64, UINT64));
extern INT64	__TDFUs_min	PROTO_S ((INT64, INT64));
extern UINT64	__TDFUu_min	PROTO_S ((UINT64, UINT64));
extern int	__TDFUs_test	PROTO_S ((INT64, INT64));
extern int	__TDFUu_test	PROTO_S ((UINT64, UINT64));
extern UINT64	__TDFUand	PROTO_S ((UINT64, UINT64));
extern UINT64	__TDFUor	PROTO_S ((UINT64, UINT64));
extern UINT64	__TDFUxor	PROTO_S ((UINT64, UINT64));
extern UINT64	__TDFUnot	PROTO_S ((UINT64));

extern INT64 const_0;
extern UINT64 const_u0;
extern INT64 const_1;
extern UINT64 const_u1;

extern void INT64_print  PROTO_S ((char *,  INT64, char *));
extern void UINT64_print PROTO_S ((char *, UINT64, char *));

#endif  /* ndef __INT64_h */
