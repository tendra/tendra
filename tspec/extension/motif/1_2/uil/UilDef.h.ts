# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1996, Open Software Foundation, Inc.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t","X11/Intrinsic.h.ts";

+TYPE (int) Uil_status_type;
+TYPE (int) Uil_continue_type;

+CONST int Uil_k_terminate;
+CONST int Uil_k_continue;

+CONST int Uil_k_success_status;
+CONST int Uil_k_info_status;
+CONST int Uil_k_warning_status;
+CONST int Uil_k_error_status;
+CONST int Uil_k_severe_status;
+CONST int Uil_k_max_status;

+FIELD struct _Uil_command_type := {
    char	    *source_file;
    char	    *resource_file;
    char	    *listing_file;
    unsigned int    include_dir_count;
    char	    **include_dir;
    unsigned	    listing_file_flag : 1;
    unsigned	    resource_file_flag : 1;
    unsigned	    machine_code_flag : 1;
    unsigned	    report_info_msg_flag : 1;
    unsigned	    report_warn_msg_flag : 1;
    unsigned	    parse_tree_flag : 1;
    unsigned        issue_summary : 1;
    unsigned int    status_update_delay;
    char	    *database;
    unsigned	    database_flag : 1;
    unsigned	    use_setlocale_flag : 1;
};

+TYPEDEF struct _Uil_command_type Uil_command_type;

+FIELD struct _Uil_compile_desc_type := {
    unsigned int	compiler_version;
    unsigned int	data_version;
    char		*parse_tree_root;
    unsigned int	message_count[5];    
};

+TYPEDEF struct _Uil_compile_desc_type Uil_compile_desc_type;

+FUNC Uil_status_type Uil(Uil_command_type *, Uil_compile_desc_type *,
			  Uil_continue_type (*)(),
			  char *,
			  Uil_continue_type (*)(),
			  char *);

/*
 *	MISSING: UilDumpSymbolTable
 */
