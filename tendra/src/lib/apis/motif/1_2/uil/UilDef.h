/*
    COPYRIGHT NOTICE

    This program is the proprietary property of IXI Ltd, a subsidiary
    of the Santa Cruz Operation (SCO). Use, reproduction, production
    of amended versions and/or transfer of this program is permitted
    PROVIDED THAT:

    (a)  This legend be preserved on any such reproduction and amended
         version.

    (b)  Any recipient of such reproduction or amended version accept
         the conditions set out in this legend.

    IXI accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Copyright (c) 1995, 1996

*/

/*
    Copyright (c) 1996 Open Software Foundation, Inc.

    All Rights Reserved

    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, provided
    that the above copyright notice appears in all copies and that both the
    copyright notice and this permission notice appear in supporting
    documentation.

    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
    INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
    CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/


+USE "x5/t","X11/Intrinsic.h";

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
