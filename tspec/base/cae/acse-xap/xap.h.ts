# $Id: xap.h.ts 3121 2014-05-03 15:20:48Z kate $

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+DEFINE AP_ASN1_ID 11;
+DEFINE AP_ID       8;
+DEFINE AP_ACSE_ID  7;
+DEFINE AP_PRES_ID  6;
+DEFINE AP_SESS_ID  5;
+DEFINE AP_TRAN_ID  4;
+DEFINE AP_OS_ID    0;

+DEFINE AP_MAXOBJBUF 12;
+DEFINE AP_CK_OBJ_NULL(O)  %% ((O)->length ? 0 : 1) %%;
+DEFINE AP_SET_OBJ_NULL(O) %% ((O)->length = 0)     %%;

+NAT ~ap_maxobjbuf; /* TODO: relate to AP_MAXOBJBUF */
+FIELD struct ~ap_objid {
	long length;
#	union {
#		unsigned char short_buf[~ap_maxobjbuf];
#		unsigned char *long_buf;
#	} b;
};
+TYPEDEF struct ~ap_objid ap_objid_t; /* TODO: how to make ~ap_objid anonymous? */

+FIELD struct ~ap_cdl_elt {
	long pci;
	ap_objid_t *a_sytx;
	int size_t_sytx;
	ap_objid_t **m_t_sytx;
};
+TYPEDEF struct ~ap_cdl_elt ap_cdl_elt_t;

+FIELD struct ~ap_cdl {
	int size;
	ap_cdl_elt_t *m_ap_cdl;
};
+TYPEDEF struct ~ap_cdl ap_cdl_t;

+FIELD struct ~ap_dcn {
	ap_objid_t *a_sytx;
	ap_objid_t *t_sytx;
};
+TYPEDEF struct ~ap_dcn ap_dcn_t;

+DEFINE AP_ACCEPT   0;
+DEFINE AP_USER_REJ 1;
+DEFINE AP_PROV_REJ 2;

+DEFINE AP_RSN_NSPEC            0;
+DEFINE AP_A_SYTX_NSUP          1;
+DEFINE AP_PROP_T_SYTX_NSUP     2;
+DEFINE AP_LCL_LMT_DCS_EXCEEDED 3;

+FIELD struct ~ap_cdrl_elt {
	long res;
	ap_objid_t *t_sytx;
	long prov_rsn;
};
+TYPEDEF struct ~ap_cdrl_elt ap_cdrl_elt_t;

+FIELD struct ~ap_cdrl {
	int size;
	ap_cdrl_elt_t *m_ap_cdl;
};
+TYPEDEF struct ~ap_cdrl ap_cdrl_t;

+FIELD struct ~ap_aeq {
	int size;
	unsigned char *udata;
};
+TYPEDEF struct ~ap_aeq ap_aeq_t;

+FIELD struct ~ap_apt {
	int size;
	unsigned char *udata;
};
+TYPEDEF struct ~ap_apt ap_apt_t;

+FIELD struct ~ap_aei_api_id {
	int size;
	unsigned char *udata;
};
+TYPEDEF struct ~ap_aei_api_id ap_aei_api_id_t;

+FIELD struct ~ap_octet_string {
	long length;
	unsigned char* data;
};
+TYPEDEF struct ~ap_octet_string ap_octet_string_t;

+DEFINE AP_UNKNOWN 0;
+DEFINE AP_CLNS    1;
+DEFINE AP_CONS    2;
+DEFINE AP_RFC1006 3;

+FIELD struct ~ap_nsap {
	ap_octet_string_t nsap;
	int nsap_type;
};
+TYPEDEF struct ~ap_nsap ap_nsap_t;

+FIELD struct ~ap_paddr {
	ap_octet_string_t *p_selector;
	ap_octet_string_t *s_selector;
	ap_octet_string_t *t_selector;
	int n_nsaps;
	ap_nsap_t *nsaps;
};
+TYPEDEF struct ~ap_paddr ap_paddr_t;

+FIELD struct ~ap_dcs_elt {
	long pci;
	ap_objid_t *a_sytx;
	ap_objid_t *t_sytx;
};
+TYPEDEF struct ~ap_dcs_elt ap_dcs_elt_t;

+FIELD struct ~ap_dcs {
	int size;
	ap_dcs_elt_t *dcs;
};
+TYPEDEF struct ~ap_dcs ap_dcs_t;

+FIELD struct ~ap_conn_id {
	ap_octet_string_t *user_ref;
	ap_octet_string_t *comm_ref;
	ap_octet_string_t *addtl_ref;
};
+TYPEDEF struct ~ap_conn_id ap_conn_id_t;

+FIELD struct ~ap_old_conn_id {
	ap_octet_string_t *clg_user_ref;
	ap_octet_string_t *cld_user_ref;
	ap_octet_string_t *comm_ref;
	ap_octet_string_t *addtl_ref;
};
+TYPEDEF struct ~ap_old_conn_id ap_old_conn_id_t;

+DEFINE AP_NO      0;
+DEFINE AP_YES     1;
+DEFINE AP_PRITOP  0;
+DEFINE AP_PRIHIGH 1;
+DEFINE AP_PRIMID  2;
+DEFINE AP_PRILOW  3;
+DEFINE AP_PRIDFLT 4;

+FIELD struct ~ap_rate {
	long targetvalue;
	long minacceptvalue;
};
+TYPEDEF struct ~ap_rate ap_rate_t;

+FIELD struct ~ap_reqvalue {
	ap_rate_t called;
	ap_rate_t calling;
};
+TYPEDEF struct ~ap_reqvalue ap_reqvalue_t;

+FIELD struct ~ap_thrpt {
	ap_reqvalue_t maxthrpt;
	ap_reqvalue_t avgthrpt;
};
+TYPEDEF struct ~ap_thrpt ap_thrpt_t;

+FIELD struct ~ap_transdel {
	ap_reqvalue_t maxdel;
	ap_reqvalue_t avgdel;
};
+TYPEDEF struct ~ap_transdel ap_transdel_t;

+FIELD struct ~ap_qos {
	ap_thrpt_t throughput;
	ap_transdel_t transdel;
	ap_rate_t reserrorrate;
	ap_rate_t transffailprob;
	ap_rate_t estfailprob;
	ap_rate_t relfailprob;
	ap_rate_t estdelay;
	ap_rate_t reldelay;
	ap_rate_t connresil;
	unsigned int protection;
	int priority;
	char optimizedtrans;
	char extcntl;
};
+TYPEDEF struct ~ap_qos ap_qos_t;

+FIELD struct ~ap_diag {
	long rsn;
	long evt;
	long src;
	char *error;
};
+TYPEDEF struct ~ap_diag ap_diag_t;

+FIELD struct ~ap_pollfd {
	int fd;
	short events;
	short revents;
};
+TYPEDEF struct ~ap_pollfd ap_pollfd_t;

+FIELD struct ~ap_osi_dbuf {
	unsigned char *db_base;
	unsigned char *db_lim;
	unsigned char db_ref;
};
+TYPEDEF struct ~ap_osi_dbuf ap_osi_dbuf_t;

+TYPE struct ap_osi_vbuf;
+TYPEDEF struct ap_osi_vbuf ap_osi_vbuf_t;
+FIELD struct ap_osi_vbuf {
	ap_osi_vbuf_t *b_cont;
	unsigned char *b_rptr;
	unsigned char *b_wptr;
	ap_osi_dbuf_t *b_datap;
};

+FIELD struct ~ap_a_assoc_env {
	unsigned long mask;
	unsigned long mode_sel;
	ap_objid_t cntx_name;
	ap_aei_api_id_t clg_aeid;
	ap_aeq_t clg_aeq;
	ap_aei_api_id_t clg_apid;
	ap_apt_t clg_apt;
	ap_aei_api_id_t cld_aeid;
	ap_aeq_t cld_aeq;
	ap_aei_api_id_t cld_apid;
	ap_apt_t cld_apt;
	ap_paddr_t rem_paddr;
	ap_cdl_t pcdl;
	ap_dcn_t dpcn;
	ap_qos_t qos;
	unsigned long a_version_sel;
	unsigned long p_version_sel;
	unsigned long s_version_sel;
	unsigned long afu_sel;
	unsigned long pfu_sel;
	unsigned long sfu_sel;
	ap_conn_id_t *clg_conn_id;
	ap_conn_id_t *cld_conn_id;
	unsigned long init_sync_pt;
	unsigned long init_tokens;
	ap_aei_api_id_t rsp_aeid;
	ap_aeq_t rsp_aeq;
	ap_aei_api_id_t rsp_apid;
	ap_apt_t rsp_apt;
	ap_cdrl_t pcdrl;
	long dpcr;
};
+TYPEDEF struct ~ap_a_assoc_env ap_a_assoc_env_t;

+FIELD struct ~ap_cdata {
	long udata_length;
	long rsn;

	long evt;
	long sync_p_sn;

	long sync_type;
	long resync_type;
	long src;
	long res;

	long res_src;
	long diag;

	unsigned long tokens;

	ap_a_assoc_env_t *env;

	ap_octet_string_t act_id;
	ap_octet_string_t old_act_id;
	ap_old_conn_id_t *old_conn_id;
};
+TYPEDEF struct ~ap_cdata ap_cdata_t;

+FIELD union ~ap_val {
	long l;
	void *v;
};
+TYPEDEF union ~ap_val ap_val_t;

