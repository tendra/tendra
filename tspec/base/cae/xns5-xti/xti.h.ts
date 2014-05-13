+USE "c/c89", "stddef.h.ts", "size_t" (!?);

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

# TODO: of equal size, and at least 32 bits
+TYPE (signed)   t_scalar_t;
+TYPE (unsigned) t_uscalar_t;

+DEFINE TBADADDR       1;
+DEFINE TBADOPT        2;
+DEFINE TACCES         3;
+DEFINE TBADF          4;
+DEFINE TNOADDR        5;
+DEFINE TOUTSTATE      6;
+DEFINE TBADSEQ        7;
+DEFINE TSYSERR        8;
+DEFINE TLOOK          9;
+DEFINE TBADDATA      10;
+DEFINE TBUFOVFLW     11;
+DEFINE TFLOW         12;
+DEFINE TNODATA       13;
+DEFINE TNODIS        14;
+DEFINE TNOUDERR      15;
+DEFINE TBADFLAG      16;
+DEFINE TNOREL        17;
+DEFINE TNOTSUPPORT   18;

+DEFINE TSTATECHNG    19;
+DEFINE TNOSTRUCTYPE  20;
+DEFINE TBADNAME      21;
+DEFINE TBADQLEN      22;
+DEFINE TADDRBUSY     23;
+DEFINE TINDOUT       24;
+DEFINE TPROVMISMATCH 25;
+DEFINE TRESQLEN      26;
+DEFINE TRESADDR      27;
+DEFINE TQFULL        28;
+DEFINE TPROTO        29;

+DEFINE T_LISTEN      %% 0x0001 %%;
+DEFINE T_CONNECT     %% 0x0002 %%;
+DEFINE T_DATA        %% 0x0004 %%;
+DEFINE T_EXDATA      %% 0x0008 %%;
+DEFINE T_DISCONNECT  %% 0x0010 %%;
+DEFINE T_UDERR       %% 0x0040 %%;
+DEFINE T_ORDREL      %% 0x0080 %%;
+DEFINE T_GODATA      %% 0x0100 %%;
+DEFINE T_GOEXDATA    %% 0x0200 %%;

+DEFINE T_MORE        %%  0x001 %%;
+DEFINE T_EXPEDITED   %%  0x002 %%;
+DEFINE T_PUSH        %%  0x004 %%;
+DEFINE T_NEGOTIATE   %%  0x004 %%;
+DEFINE T_CHECK       %%  0x008 %%;
+DEFINE T_DEFAULT     %%  0x010 %%;
+DEFINE T_SUCCESS     %%  0x020 %%;
+DEFINE T_FAILURE     %%  0x040 %%;
+DEFINE T_CURRENT     %%  0x080 %%;
+DEFINE T_PARTSUCCESS %%  0x100 %%;
+DEFINE T_READONLY    %%  0x200 %%;
+DEFINE T_NOTSUPPORT  %%  0x400 %%;

+EXP lvalue int t_errno;

+DEFMIN T_IOV_MAX 16;

+FIELD struct t_iovec {
	void *iov_base;
	size_t iov_len;
};

+FIELD struct t_info {
	t_scalar_t addr;
	t_scalar_t options;
	t_scalar_t tsdu;
	t_scalar_t etsdu;
	t_scalar_t connect;
	t_scalar_t discon;
	t_scalar_t servtype;
	t_scalar_t flags;
};

+DEFINE T_COTS     01;
+DEFINE T_COTS_ORD 02;
+DEFINE T_CLTS     03;

+DEFINE T_SENDZERO   %% 0x001 %%;
+DEFINE T_ORDRELDATA %% 0x002 %%;

+FIELD struct netbuf {
	unsigned int maxlen;
	unsigned int len;
	void *buf;
};

+FIELD struct t_opthdr {
	t_uscalar_t len;
	t_uscalar_t level;
	t_uscalar_t name;
	t_uscalar_t status;
};

+FIELD struct t_bind | "struct_t_bind" {
	struct netbuf addr;
	unsigned int qlen;
};

+FIELD struct t_optmgmt | "struct_t_optmgmt" {
	struct netbuf opt;
	t_scalar_t flags;
};

+FIELD struct t_discon {
	struct netbuf udata;
	int reason;
	int sequence;
};

+FIELD struct t_call {
	struct netbuf addr;
	struct netbuf opt;
	struct netbuf udata;
	int sequence;
};

+FIELD struct t_unitdata {
	struct netbuf addr;
	struct netbuf opt;
	struct netbuf udata;
};

+FIELD struct t_uderr {
	struct netbuf addr;
	struct netbuf opt;
	t_scalar_t error;
};

+DEFINE T_BIND     1;
+DEFINE T_OPTMGMT  2;
+DEFINE T_CALL     3;
+DEFINE T_DIS      4;
+DEFINE T_UNITDATA 5;
+DEFINE T_UDERROR  6;
+DEFINE T_INFO     7;

+DEFINE T_ADDR  %% 0x01   %%;
+DEFINE T_OPT   %% 0x02   %%;
+DEFINE T_UDATA %% 0x04   %%;
+DEFINE T_ALL   %% 0xffff %%;

+DEFINE T_UNBND    1;
+DEFINE T_IDLE     2;
+DEFINE T_OUTCON   3;
+DEFINE T_INCON    4;
+DEFINE T_DATAXFER 5;
+DEFINE T_OUTREL   6;
+DEFINE T_INREL    7;

+DEFINE T_YES              1;
+DEFINE T_NO               0;
+DEFINE T_NULL             0;
+DEFINE T_ABSREQ   %% 0x8000 %%;
+DEFINE T_INFINITE %%   (-1) %%;
+DEFINE T_INVALID  %%   (-2) %%;

+CONST int _SC_T_IOV_MAX;

+DEFINE T_UNSPEC %% (~0 − 2) %%;
+DEFINE T_ALLOPT 0;
+DEFINE T_ALIGN(p) %% (((t_uscalar_t) (p) + (sizeof (t_scalar_t) − 1)) & ~sizeof (t_scalar_t) − 1)) %%;
+MACRO unsigned char *T_OPT_DATA(struct t_opthdr *); # "definition to be added"
+MACRO struct t_opthdr *T_OPT_NEXTHDR(struct netbuf *, size_t, struct t_opthdr *);
+MACRO struct t_opthdr *T_OPT_FIRSTHDR(struct netbuf *); # "definition to be added"

+CONST int XTI_GENERIC;

+CONST int XTI_DEBUG, XTI_LINGER, XTI_RCVBUF, XTI_RCVLOWAT, XTI_SNDBUF, XTI_SNDLOWAT;

+FIELD struct t_linger {
	t_scalar_t l_onoff;
	t_scalar_t l_linger;
};

+DEFINE T_CLASS0  0;
+DEFINE T_CLASS1  1;
+DEFINE T_CLASS2  2;
+DEFINE T_CLASS3  3;
+DEFINE T_CLASS4  4;

+DEFINE T_PRITOP  0;
+DEFINE T_PRIHIGH 1;
+DEFINE T_PRIMID  2;
+DEFINE T_PRILOW  3;
+DEFINE T_PRIDFLT 4;

+DEFINE T_NOPROTECT      1;
+DEFINE T_PASSIVEPROTECT 2;
+DEFINE T_ACTIVEPROTECT  4;

+DEFINE T_LTPDUDFLT 128;

+FIELD struct rate {
	t_scalar_t targetvalue;
	t_scalar_t minacceptvalue;
};

+FIELD struct reqvalue {
	struct rate called;
	struct rate calling;
};

+FIELD struct thrpt {
	struct reqvalue maxthrpt;
	struct reqvalue avgthrpt;
};

+FIELD struct transdel {
	struct reqvalue maxdel;
	struct reqvalue avgdel;
};

+CONST int T_ISO_TP;
+CONST int ISO_TP;

+CONST int
	T_TCO_THROUGHPUT,     TCO_THROUGHPUT,
	T_TCO_TRANSDEL,       TCO_TRANSDEL,
	T_TCO_RESERRORRATE,   TCO_RESERRORRATE,
	T_TCO_TRANSFFAILPROB, TCO_TRANSFFAILPROB,
	T_TCO_ESTFAILPROB,    TCO_ESTFAILPROB,
	T_TCO_RELFAILPROB,    TCO_RELFAILPROB,
	T_TCO_ESTDELAY,       TCO_ESTDELAY,
	T_TCO_RELDELAY,       TCO_RELDELAY,
	T_TCO_CONNRESIL,      TCO_CONNRESIL,
	T_TCO_PROTECTION,     TCO_PROTECTION,
	T_TCO_PRIORITY,       TCO_PRIORITY,
	T_TCO_EXPD,           TCO_EXPD;

+CONST int
	T_TCL_TRANSDEL, TCL_TRANSDEL,
	T_TCL_RESERRORRATE, TCL_RESERRORRATE,
	T_TCL_PROTECTION, TCL_PROTECTION,
	T_TCL_PRIORITY, TCL_PRIORITY;

+CONST int
	T_TCO_LTPDU,      TCO_LTPDU,
	T_TCO_ACKTIME,    TCO_ACKTIME,
	T_TCO_REASTIME,   TCO_REASTIME,
	T_TCO_EXTFORM,    TCO_EXTFORM,
	T_TCO_FLOWCTRL,   TCO_FLOWCTRL,
	T_TCO_CHECKSUM,   TCO_CHECKSUM,
	T_TCO_NETEXP,     TCO_NETEXP,
	T_TCO_NETRECPTCF, TCO_NETRECPTCF,
	T_TCO_PREFCLASS,  TCO_PREFCLASS,
	T_TCO_ALTCLASS1,  TCO_ALTCLASS1,
	T_TCO_ALTCLASS2,  TCO_ALTCLASS2,
	T_TCO_ALTCLASS3,  TCO_ALTCLASS3,
	T_TCO_ALTCLASS4,  TCO_ALTCLASS4;

+CONST int
	T_TCL_CHECKSUM, TCL_CHECKSUM;

+CONST int
	T_INET_TCP, INET_TCP;

+CONST int
	T_TCP_NODELAY,   TCP_NODELAY,
	T_TCP_MAXSEG,    TCP_MAXSEG,
	T_TCP_KEEPALIVE, TCP_KEEPALIVE;

+FIELD struct t_kpalive {
	t_scalar_t kp_onoff;
	t_scalar_t kp_timeout;
};

+DEFINE T_GARBAGE %% 0x02 %%;

+CONST int
	T_INET_UDP, INET_UDP;

+CONST int
	T_UDP_CHECKSUM, UDP_CHECKSUM;

+CONST int
	T_INET_IP, INET_IP;

+CONST int
	T_IP_OPTIONS, IP_OPTIONS,
	T_IP_TOS,     IP_TOS,
	T_IP_TTL,     IP_TTL;

+CONST int
	T_IP_REUSEADDR, IP_REUSEADDR,
	T_IP_DONTROUTE, IP_DONTROUTE,
	T_IP_BROADCAST, IP_BROADCAST;

+DEFINE T_ROUTINE       0;
+DEFINE T_PRIORITY      1;
+DEFINE T_IMMEDIATE     2;
+DEFINE T_FLASH         3;
+DEFINE T_OVERRIDEFLASH 4;
+DEFINE T_CRITIC_ECP    5;
+DEFINE T_INETCONTROL   6;
+DEFINE T_NETCONTROL    7;

+DEFINE T_NOTOS   0;
+DEFINE T_LDELAY  %% (1 << 4) %%;
+DEFINE T_HITHRPT %% (1 << 3) %%;
+DEFINE T_HIREL   %% (1 << 2) %%;
+DEFINE T_LOCOST  %% (1 << 1) %%;

#define SET_TOS(prec, tos) %% ((0x7 & (prec)) << 5 | (0x1c & (tos))) %%;

+FUNC int t_accept(int, int, const struct t_call *);
+FUNC void *t_alloc(int, int, int);
+FUNC int t_bind(int, const struct t_bind *, struct t_bind *);
+FUNC int t_close(int);
+FUNC int t_connect(int, const struct t_call *, struct t_call *);
+FUNC int t_error(const char *);
+FUNC int t_free(void *, int);
+FUNC int t_getinfo(int, struct t_info *);
+FUNC int t_getprotaddr(int, struct t_bind *, struct t_bind *);
+FUNC int t_getstate(int);
+FUNC int t_listen(int, struct t_call *);
+FUNC int t_look(int);
+FUNC int t_open(const char *, int, struct t_info *);
+FUNC int t_optmgmt(int, const struct t_optmgmt *, struct t_optmgmt *);
+FUNC int t_rcv(int, void *, unsigned int, int *);
+FUNC int t_rcvconnect(int, struct t_call *);
+FUNC int t_rcvdis(int, struct t_discon *);
+FUNC int t_rcvrel(int);
+FUNC int t_rcvreldata(int, struct t_discon *discon);
+FUNC int t_rcvudata(int, struct t_unitdata *, int *);
+FUNC int t_rcvuderr(int, struct t_uderr *);
+FUNC int t_rcvv(int, struct t_iovec *, unsigned int, int *);
+FUNC int t_rcvvudata(int, struct t_unitdata *, struct t_iovec *, unsigned int, int *);
+FUNC int t_snd(int, void *, unsigned int, int);
+FUNC int t_snddis(int, const struct t_call *);
+FUNC int t_sndrel(int);
+FUNC int t_sndreldata(int, struct t_discon *);
+FUNC int t_sndudata(int, const struct t_unitdata *);
+FUNC int t_sndv(int, const struct t_iovec *, unsigned int iovcount, int);
+FUNC int t_sndvudata(int, struct t_unitdata *, struct t_iovec *, unsigned int);
+FUNC const char *t_strerror(int);
+FUNC int t_sync(int);
+FUNC int t_sysconf(int);
+FUNC int t_unbind(int);

