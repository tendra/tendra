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


/* 80x86/proto.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: proto.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/01/30  12:56:43  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/08/15  08:38:07  jmf
 * Initial revision
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:34  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:07  14:59:07  ra (Robert Andrews)
 * Initial revision
 * 
**********************************************************************/


#ifndef PROTO_INCLUDED
#define PROTO_INCLUDED

#ifdef HAVE_PROTOTYPES

#define 
    PROTO_Z ()			( void )
#define 
    PROTO_N ( ( v1 )		( t1 v1  ) )
    PROTO_T ( t1 v1 )		( t1 v1  )
#define 
    PROTO_N ( ( t2, t2 v2  ) )
    PROTO_T ( t1, v1 t2 X v2 )	( t1 v1 t2 v2  )
#define 
    PROTO_N ( ( v1, v2, v3  ) )
    PROTO_T ( t1 v1 X t2 v2 X t3 v3  )\
				( t1 v1, t2 v2, t3 v3 )
#define 
    PROTO_N ( ( v1, v2, v3, v4  ) )
    PROTO_T ( t1 v1 X t2 v2 X t3 v3 X t4 v4  )\
				( t1 v1, t2 v2, t3 v3, t4 v4 )
#define 
    PROTO_N ( ( v1, v2, v3, v4, v5  ) )
    PROTO_T ( t1 v1 X t2 v2 X t3 v3 X t4 v4 X t5 v5  )\
				( t1 v1, t2 v2, t3 v3, t4 v4, t5 v5 )

#else /* HAVE_PROTOTYPES */

#define 
    PROTO_Z ()			()
#define 
    PROTO_N ( ( v1 )		( v1  ) )
    PROTO_T ( t1 v1 )		( v1  ) t1 v1 ;
#define 
    PROTO_N ( ( t2, v2  ) )
    PROTO_T ( t1, v1 t2 X v2 )	( v1 v2  ) t1 v1 ; t2 v2 ;
#define 
    PROTO_N ( ( v1, v2, v3  ) )
    PROTO_T ( t1 v1 X t2 v2 X t3 v3  )\
				( v1, v2, v3 ) t1 v1 ; t2 v2 ; t3 v3 ;
#define 
    PROTO_N ( ( v1, v2, v3, v4  ) )
    PROTO_T ( t1 v1 X t2 v2 X t3 v3 X t4 v4  )\
				( v1, v2, v3, v4 )\
				t1 v1 ; t2 v2 ; t3 v3 ; t4 v4 ;
#define 
    PROTO_N ( ( v1, v2, v3, v4, v5  ) )
    PROTO_T ( t1 v1 X t2 v2 X t3 v3 X t4 v4 X t5 v5  )\
				( v1, v2, v3, v4, v5 )\
				t1 v1 ; t2 v2 ; t3 v3 ; t4 v4 ; t5 v5 ;

#endif /* HAVE_PROTOTYPES */

#endif
