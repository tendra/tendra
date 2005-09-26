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

  $TenDRA$
*/


#ifndef __INT64_h
#define __INT64_h

extern INT64	make_INT64	(INT32, UINT32);
extern UINT64	make_UINT64	(UINT32, UINT32);

extern INT64	__TDFUs_plus	(INT64, INT64);
extern UINT64	__TDFUu_plus	(UINT64, UINT64);
extern INT64	__TDFUs_minus	(INT64, INT64);
extern UINT64	__TDFUu_minus	(UINT64, UINT64);
extern INT64	__TDFUs_mult	(INT64, INT64);
extern UINT64	__TDFUu_mult	(UINT64, UINT64);
extern INT64	__TDFUs_div1	(INT64, INT64);
extern INT64	__TDFUs_div2	(INT64, INT64);
extern UINT64	__TDFUu_div2	(UINT64, UINT64);
extern INT64	__TDFUs_rem1	(INT64, INT64);
extern INT64	__TDFUs_rem2	(INT64, INT64);
extern UINT64	__TDFUu_rem2	(UINT64, UINT64);
extern INT64	__TDFUneg	(INT64);
extern UINT64	__TDFUu_shl	(UINT64, UINT32);
extern UINT64	__TDFUu_shr	(UINT64, UINT32);
extern INT64	__TDFUabs	(INT64);
extern INT64	__TDFUsswiden	(INT32);
extern UINT64	__TDFUsuwiden	(INT32);
extern UINT64	__TDFUuuwiden	(UINT32);
extern INT64	__TDFUuswiden	(UINT32);
extern INT32	__TDFUssshorten	(INT64);
extern UINT32	__TDFUsushorten	(INT64);
extern UINT32	__TDFUuushorten	(UINT64);
extern INT32	__TDFUusshorten	(UINT64);
extern INT64	__TDFUu642s64	(UINT64);
extern UINT64	__TDFUs642u64	(INT64);
extern INT64	__TDFUs_max	(INT64, INT64);
extern UINT64	__TDFUu_max	(UINT64, UINT64);
extern INT64	__TDFUs_min	(INT64, INT64);
extern UINT64	__TDFUu_min	(UINT64, UINT64);
extern int	__TDFUs_test	(INT64, INT64);
extern int	__TDFUu_test	(UINT64, UINT64);
extern UINT64	__TDFUand	(UINT64, UINT64);
extern UINT64	__TDFUor	(UINT64, UINT64);
extern UINT64	__TDFUxor	(UINT64, UINT64);
extern UINT64	__TDFUnot	(UINT64);

extern INT64 const_0;
extern UINT64 const_u0;
extern INT64 const_1;
extern UINT64 const_u1;

extern void INT64_print  (char *,  INT64, char *);
extern void UINT64_print (char *, UINT64, char *);

#endif  /* ndef __INT64_h */
