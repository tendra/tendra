# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;

+IF %% __SYSV_REMOTE_SERVICES %%

+USE "svid3", "stdio.h.ts" ;
+USE "svid3", "sys/types.h.ts" ;
+USE "svid3", "rpc/types.h.ts" ;

+ENUM enum xdr_op := {
    XDR_ENCODE = 0,
    XDR_DECODE = 1,
    XDR_FREE = 2
} ;

+TYPE xdrproc_t ;

+FIELD struct xdr_ops {
    bool_t ( *x_getlong ) () ;
    bool_t ( *x_putlong ) () ;
    bool_t ( *x_getbytes ) () ;
    bool_t ( *x_putbytes ) () ;
    unsigned int ( *x_getpostn ) () ;
    bool_t ( *x_setpostn ) () ;
    long *( *x_inline ) () ;
    void ( *x_destroy ) () ;
} ;

+TYPE struct xdr_discrim ;

+FIELD ( struct ) XDR {
    enum xdr_op x_op ;
    struct xdr_ops *x_ops ;
    caddr_t x_public ;
    caddr_t x_private ;
    caddr_t x_base ;
    int x_handy ;
} ;

+FUNC unsigned int xdr_getpos ( const XDR * ) ;
+FUNC long *xdr_inline (  XDR *, const int ) ;
+FUNC bool_t xdrrec_eof (  XDR * ) ;
+FUNC bool_t xdr_setpos (  XDR *, const unsigned int ) ;

+FUNC bool_t xdr_array ( XDR *, caddr_t *, unsigned int *,
    const unsigned int, const unsigned int, const xdrproc_t ) ;
+FUNC bool_t xdr_bytes ( XDR *, char **, unsigned int *, const unsigned int ) ;
+FUNC bool_t xdr_opaque ( XDR *, caddr_t, const unsigned int ) ;
+FUNC bool_t xdr_pointer ( XDR *, char **, unsigned int, const xdrproc_t ) ;
+FUNC bool_t xdr_reference ( XDR *, caddr_t *, unsigned int, const xdrproc_t ) ;
+FUNC bool_t xdr_string ( XDR *, char **, const unsigned int ) ;
+FUNC bool_t xdr_union ( XDR *, enum_t *, char *, const struct xdr_discrim *,
    const bool_t (*) () ) ;
+FUNC bool_t xdr_vector ( XDR *, char *, const unsigned int,
    const unsigned int, const xdrproc_t ) ;
+FUNC bool_t xdr_wrapstring ( XDR *, char ** ) ;

+FUNC void xdr_destroy ( XDR * ) ;
+FUNC void xdrmem_create ( XDR *, const caddr_t, const unsigned int,
    const enum xdr_op ) ;
+FUNC void xdrrec_create ( XDR *, const unsigned int, const unsigned int,
    const caddr_t, const int (*) (), const int (*) () ) ;
+FUNC void xdrstdio_create ( XDR *, FILE *, const enum xdr_op ) ;

+FUNC bool_t xdr_bool ( XDR *, bool_t * ) ;
+FUNC bool_t xdr_char ( XDR *, char * ) ;
+FUNC bool_t xdr_double ( XDR *, double * ) ;
+FUNC bool_t xdr_enum ( XDR *, enum_t * ) ;
+FUNC void xdr_free ( xdrproc_t, char * ) ;
+FUNC bool_t xdr_float ( XDR *, float * ) ;
+FUNC bool_t xdr_int ( XDR *, int * ) ;
+FUNC bool_t xdr_long ( XDR *, long * ) ;
+FUNC bool_t xdr_short ( XDR *, short * ) ;
+FUNC bool_t xdr_u_char ( XDR *, char * ) ;
+FUNC bool_t xdr_u_long ( XDR *, unsigned long * ) ;
+FUNC bool_t xdr_u_short ( XDR *, unsigned short * ) ;
+FUNC bool_t xdr_void ( void ) ;

+ENDIF
