# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_REMOTE_SERVICES %%

+USE "svid/svid3", "sys/types.h.ts" ;
+USE "svid/svid3", "rpc/types.h.ts" ;
+USE "svid/svid3", "tiuser.h.ts" ;
+USE "svid/svid3", "rpc/key_prot.h.ts" ;
+USE "svid/svid3", "rpc/xdr.h.ts" ;
+USE "svid/svid3", "sys/time.h.ts" ;
+USE "svid/svid3", "netconfig.h.ts" (!?) ;

+ENUM enum clnt_stat := {
    RPC_SUCCESS = 0,
    RPC_CANTENCODEARGS = 1,
    RPC_CANTENCODERES = 2,
    RPC_CANTSEND = 3,
    RPC_CANTRECV = 4,
    RPC_TIMEDOUT = 5,
    RPC_INTR = 18,
    RPC_VERSMISMATCH = 6,
    RPC_AUTHERROR = 7,
    RPC_PROGUNAVAIL = 8,
    RPC_PROGVERSMISMATCH = 9,
    RPC_PROCUNAVAIL = 10,
    RPC_CANTDECODEARGS = 11,
    RPC_SYSTEMERROR = 12,
    RPC_UNKNOWNHOST = 13,
    RPC_UNKNOWNPROTO = 17,
    RPC_UNKNOWNADDR = 19,
    RPC_NOBROADCAST = 21,
    RPC_RPCBFAILURE = 14,
    RPC_PROGNOTREGISTERED = 15,
    RPC_N2AXLATEFAILURE = 22,
    RPC_TLIERROR = 20,
    RPC_FAILED = 16
} ;

+ENUM enum auth_stat := {
    AUTH_OK = 0,
    AUTH_BADCRED = 1,
    AUTH_REJECTEDCRED = 2,
    AUTH_BADVERF = 3,
    AUTH_REJECTEDVERF = 4,
    AUTH_TOOWEAK = 5,
    AUTH_INVALIDRESP = 6,
    AUTH_FAILED = 7
} ;

+ENUM enum xprt_stat := {
    XPRT_DIED,
    XPRT_MOREREQS,
    XPRT_IDLE
} ;

+TYPE fd_set, des_block ;

+FIELD struct opaque_auth {
    enum_t oa_flavor ;
    caddr_t oa_base ;
    unsigned int oa_length ;
} ;

+FIELD struct auth_ops {
    void ( *ah_nextverf ) () ;
    int ( *ah_marshal ) () ;
    int ( *ah_validate ) () ;
    int ( *ah_refresh ) () ;
    void ( *ah_destroy ) () ;
} ;

+FIELD ( struct ) AUTH {
    struct opaque_auth ah_cred ;
    struct opaque_auth ah_verf ;
    des_block ah_key ;
    struct auth_ops *ah_ops ;
    caddr_t ah_private ;
} ;

+FIELD struct clnt_ops {
    enum clnt_stat ( *cl_call ) () ;
    void ( *cl_abort ) () ;
    void ( *cl_geterr ) () ;
    bool_t ( *cl_freeres ) () ;
    void ( *cl_destroy ) () ;
    bool_t ( *cl_control ) () ;
} ;

+FIELD ( struct ) CLIENT {
    AUTH *cl_auth ;
    struct clnt_ops *cl_ops ;
    caddr_t cl_private ;
    char *cl_netid ;
    char *cl_tp ;
} ;

+FIELD struct xp_ops {
    bool_t ( *xp_recv ) () ;
    enum xprt_stat ( *xp_stat ) () ;
    bool_t ( *xp_getargs ) () ;
    bool_t ( *xp_reply ) () ;
    bool_t ( *xp_freeargs ) () ;
    void ( *xp_destroy ) () ;
} ;

+FIELD ( struct ) SVCXPRT {
    int xp_fd ;
    struct xp_ops *xp_ops ;
    char *xp_tp ;
    char *xp_netid ;
    struct netbuf xp_ltaddr ;
    struct netbuf xp_rtaddr ;
    struct opaque_auth xp_verf ;
    caddr_t xp_p1 ;
    caddr_t xp_p2 ;
    caddr_t xp_p3 ;
} ;

/* I have no idea about these */
+TYPE struct accepted_reply, struct authsys_parms ;
+TYPE struct rpc_msg, struct rejected_reply, struct rpcblist ;
+TYPE struct authdes_cred, struct rpc_err ;

/* USL addendum */
+TYPEDEF bool_t ( *resultproc_t ) () ;

+CONST int CLSET_TIMEOUT, CLGET_TIMEOUT, CLGET_FD, CLGET_SVC_ADDR ;
+CONST int CLSET_FD_CLOSE, CLSET_FD_NCLOSE, CLSET_RETRY_TIMEOUT ;
+CONST int CLGET_RETRY_TIMEOUT ;

+FUNC void auth_destroy ( AUTH * ) ;
+FUNC AUTH *authnone_create ( void ) ;
+FUNC AUTH *authsys_create ( const char *, const uid_t, const gid_t,
     const int, const gid_t * ) ;
+FUNC AUTH *authsys_create_default ( void ) ;

+FUNC enum clnt_stat clnt_call ( CLIENT *, const unsigned long,
    const xdrproc_t, caddr_t, const xdrproc_t, caddr_t,
    const struct timeval ) ;
+FUNC int clnt_freeres ( CLIENT *, const xdrproc_t, caddr_t ) ;
+FUNC void clnt_geterr ( const CLIENT *, struct rpc_err * ) ;
+FUNC void clnt_perrno ( const enum clnt_stat ) ;
+FUNC void clnt_perror ( const CLIENT *, const char * ) ;
+FUNC char *clnt_sperrno ( const enum clnt_stat ) ;
+FUNC char *clnt_sperror ( const CLIENT *, const char * ) ;
+FUNC enum clnt_stat rpc_broadcast ( const unsigned long, const unsigned long,
    const unsigned long, const xdrproc_t, caddr_t, const xdrproc_t, caddr_t,
    const resultproc_t, const char * ) ;
+FUNC enum clnt_stat rpc_call ( const char *, const unsigned long,
    const unsigned long, const xdrproc_t, const xdrproc_t, const char *,
    char *, const char * ) ;

+FUNC bool_t clnt_control ( CLIENT *, const unsigned int, char * ) ;
+FUNC CLIENT *clnt_create ( const char *, const unsigned long,
    const unsigned long, const char * ) ;
+FUNC void clnt_destroy ( CLIENT * ) ;
+FUNC CLIENT *clnt_dg_create ( const int, const struct netbuf *,
    const unsigned long, const unsigned long, const unsigned int,
    const unsigned int ) ;
+FUNC void clnt_pcreateerror ( const char * ) ;
+FUNC CLIENT *clnt_raw_create ( const unsigned long, const unsigned long ) ;
+FUNC char *clnt_spcreateerror ( const char * ) ;
+FUNC CLIENT *clnt_tli_create ( const int, const struct netconfig *,
    const struct netbuf *, const unsigned long, const unsigned long,
    const unsigned int, const unsigned int ) ;
+FUNC CLIENT *clnt_tp_create ( const char *, const unsigned long,
    const unsigned long, const struct netconfig * ) ;
+FUNC CLIENT *clnt_vc_create ( const int, const struct netbuf *,
    const unsigned long, const unsigned long, const unsigned int,
    const unsigned int ) ;

+FUNC int rpc_reg ( const unsigned long, const unsigned long,
    const unsigned long, const char *(*) (), const xdrproc_t,
    const xdrproc_t, const char * ) ;
+FUNC int svc_reg ( const SVCXPRT *, const unsigned long,
    const unsigned long, void (*) (), const struct netconfig * ) ;
+FUNC void svc_unreg ( const unsigned long, const unsigned long ) ;
+FUNC void xprt_register ( const SVCXPRT * ) ;
+FUNC void xprt_unregister ( const SVCXPRT * ) ;

+FUNC int svc_create ( void (*) (), const unsigned long,
    const unsigned long, const char * ) ;
+FUNC void svc_destroy ( SVCXPRT * ) ;
+FUNC SVCXPRT *svc_dg_create ( const int, const unsigned int,
    const unsigned int ) ;
+FUNC SVCXPRT *svc_fd_create ( const int, const unsigned int,
    const unsigned int ) ;
+FUNC SVCXPRT *svc_raw_create ( void ) ;
+FUNC SVCXPRT *svc_tli_create ( int, const struct netconfig *,
    const struct t_bind *, const unsigned int, const unsigned int ) ;
+FUNC SVCXPRT *svc_tp_create ( void (*) (), const unsigned long,
    const unsigned long, const struct netconfig * ) ;
+FUNC SVCXPRT *svc_vc_create ( int, const unsigned int, const unsigned int ) ;

+FUNC void svcerr_auth ( const SVCXPRT *, const enum auth_stat ) ;
+FUNC void svcerr_decode ( const SVCXPRT * ) ;
+FUNC void svcerr_noproc ( const SVCXPRT * ) ;
+FUNC void svcerr_noprog ( const SVCXPRT * ) ;
+FUNC void svcerr_progvers ( const SVCXPRT * ) ;
+FUNC void svcerr_systemerr ( const SVCXPRT * ) ;
+FUNC void svcerr_weakauth ( const SVCXPRT * ) ;

+FUNC int svc_freeargs ( const SVCXPRT *, const xdrproc_t, char * ) ;
+FUNC int svc_getargs ( const SVCXPRT *, const xdrproc_t, caddr_t * ) ;
+FUNC void svc_getreqset ( fd_set * ) ;
+FUNC struct netbuf *svc_getrpccaller ( const SVCXPRT * ) ;
+FUNC void svc_run ( void ) ;
+FUNC int svc_sendreply ( const SVCXPRT *, const xdrproc_t, const caddr_t * ) ;

+FUNC bool_t xdr_accepted_reply ( XDR *, const struct accepted_reply * ) ;
+FUNC bool_t xdr_authsys_parms ( XDR *, const struct authsys_parms * ) ;
/* Error in book? */
+FUNC bool_t xdr_callhdr ( XDR *, const struct rpc_msg * ) ;
+FUNC bool_t xdr_callmsg ( XDR *, const struct rpc_msg * ) ;
+FUNC bool_t xdr_opaque_auth ( XDR *, const struct opaque_auth * ) ;
+FUNC bool_t xdr_rejected_reply ( XDR *, const struct rejected_reply * ) ;
+FUNC bool_t xdr_replymsg ( XDR *, const struct rpc_msg * ) ;

+FUNC struct rpcblist *rpcb_getmaps ( const struct netconfig *, const char * ) ;
+FUNC bool_t rpcb_getaddr ( const unsigned long, const unsigned long,
    const struct netconfig *, const struct netbuf *, const char * ) ;
+FUNC bool_t rpcb_gettime ( const char *, time_t * ) ;
/* Errata */
+FUNC enum clnt_stat rpcb_rmtcall ( const struct netconfig *, const char *,
    const unsigned long, const unsigned long, const unsigned long,
    xdrproc_t, caddr_t, const xdrproc_t, caddr_t, const struct timeval,
    const struct netbuf * ) ;
+FUNC bool_t rpcb_set ( const unsigned long, const unsigned long,
    const struct netconfig *, const struct netbuf * ) ;
+FUNC bool_t rpcb_unset ( const unsigned long, const unsigned long,
    const struct netconfig * ) ;

+FUNC int authdes_getucred ( const struct authdes_cred *, uid_t *,
    gid_t *, short *, int * ) ;
+FUNC AUTH *authdes_seccreate ( const char *, const unsigned int,
    struct netbuf *, const des_block * ) ;
+FUNC int getnetname ( char [] ) ;
+FUNC int host2netname ( char [], const char *, const char * ) ;
+FUNC int key_decryptsession ( const char *, des_block * ) ;
+FUNC int key_encryptsession ( const char *, des_block * ) ;
+FUNC int key_gendes ( des_block * ) ;
+FUNC int key_setsecret ( const char * ) ;
+FUNC int netname2host ( const char *, char *, const int ) ;
+FUNC int netname2user ( const char *, uid_t *, gid_t *, int *, gid_t [] ) ;
+FUNC int user2netname ( char [], const uid_t, const char * ) ;

+ENDIF
