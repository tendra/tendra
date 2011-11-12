# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# CAE, X/Open Curses, Issue 4

+TYPE TERMINAL ;

+EXP (extern) TERMINAL *cur_term ;


# Boolean capabilities

+EXP int auto_left_margin, auto_right_margin, back_color_erase, can_change ;
+EXP int ceol_standout_glitch, col_addr_glitch, cpi_changes_res ;
+EXP int cr_cancels_micro_mode, dest_tabs_magic_smso, eat_newline_glitch ;
+EXP int erase_overstrike, generic_type, get_mouse, hard_copy, hard_cursor ;
+EXP int has_meta_key, has_print_wheel, has_status_line ;
+EXP int hue_lightness_saturation, insert_null_glitch, lpi_changes_res ;
+EXP int memory_above, memory_below, move_insert_mode, move_standout_mode ;
+EXP int needs_xon_xoff, no_esc_ctlc, no_pad_char ;
+EXP int non_dest_scroll_region, non_rev_rmcup ;
+EXP int over_strike, prtr_silent, row_addr_glitch, semi_auto_right_margin ;
+EXP int status_line_esc_ok, tilde_glitch, transparent_underline, xon_xoff ;


# Number capabilities

+EXP int bit_image_entwining, bit_image_type, buffer_capacity, buttons ;
+EXP int columns, dot_horz_spacing, dot_vert_spacing ;
+EXP int init_tabs, label_height, label_width, lines, lines_of_memory ;
+EXP int magic_cookie_glitch ;
+EXP int max_attributes, max_colors, max_micro_address, max_micro_jump ;
+EXP int max_pairs, maximum_windows ;
+EXP int micro_char_size, micro_line_size, no_color_video ;
+EXP int num_labels, number_of_pins, output_res_char, output_res_horz_inch ;
+EXP int output_res_line, output_res_vert_inch, padding_baud_rate ;
+EXP int virtual_terminal, wide_char_size, width_status_line ;


# String capabilities

+EXP char *acs_chars, *alt_scancode_esc, *back_tab, *bell ;
+EXP char *bit_image_carriage_return, *bit_image_newline, *bit_image_repeat ;
+EXP char *carriage_return, *change_char_pitch, *change_line_pitch ;
+EXP char *change_res_horz, *change_res_vert, *change_scroll_region ;
+EXP char *char_padding, *char_set_names, *clear_all_tabs, *clear_margins ;
+EXP char *clear_screen, *clr_bol, *clr_eol, *clr_eos, *code_set_init ;
+EXP char *color_names, *column_address, *command_character, *create_window ;
+EXP char *cursor_address ;
+EXP char *cursor_down, *cursor_home, *cursor_invisible, *cursor_left ;
+EXP char *cursor_mem_address, *cursor_normal, *cursor_right, *cursor_to_ll ;
+EXP char *cursor_up, *cursor_visible, *define_bit_image_region ;
+EXP char *define_char, *delete_character, *delete_line, *device_type ;
+EXP char *dis_status_line ;
+EXP char *display_clock, *display_pc_char, *down_half_line, *ena_acs ;
+EXP char *end_bit_image_region, *enter_alt_charset_mode, *enter_am_mode ;
+EXP char *enter_blink_mode, *enter_bold_mode, *enter_ca_mode ;
+EXP char *enter_delete_mode, *enter_dim_mode, *enter_doublewide_mode ;
+EXP char *enter_draft_quality, *enter_insert_mode, *enter_italics_mode ;
+EXP char *enter_left_hl_mode, *enter_leftward_mode, *enter_low_hl_mode ;
+EXP char *enter_micro_mode ;
+EXP char *enter_near_letter_quality, *enter_normal_quality ;
+EXP char *enter_pc_charset_mode, *enter_protected_mode, *enter_reverse_mode ;
+EXP char *enter_right_hl_mode ;
+EXP char *enter_scancode_mode, *enter_secure_mode, *enter_shadow_mode ;
+EXP char *enter_standout_mode, *enter_subscript_mode ;
+EXP char *enter_superscript_mode, *enter_top_hl_mode ;
+EXP char *enter_underline_mode, *enter_upward_mode, *enter_vertical_hl_mode ;
+EXP char *enter_xon_mode, *erase_chars, *exit_alt_charset_mode ;
+EXP char *exit_am_mode, *exit_attribute_mode, *exit_ca_mode ;
+EXP char *exit_delete_mode, *exit_doublewide_mode, *exit_insert_mode ;
+EXP char *exit_italics_mode, *exit_leftward_mode, *exit_micro_mode ;
+EXP char *exit_pc_charset_mode, *exit_scancode_mode, *exit_shadow_mode ;
+EXP char *exit_standout_mode, *exit_subscript_mode, *exit_superscript_mode ;
+EXP char *exit_underline_mode, *exit_upward_mode, *exit_xon_mode ;
+EXP char *fixed_pause, *flash_hook ;
+EXP char *flash_screen, *form_feed, *from_status_line ;
+EXP char *goto_window, *hangup ;
+EXP char *init_1string, *init_2string, *init_3string, *init_file, *init_prog ;
+EXP char *initialize_color, *initialize_pair, *insert_character ;
+EXP char *insert_line, *insert_padding, *key_a1, *key_a3, *key_b2 ;
+EXP char *key_backspace, *key_beg, *key_btab, *key_c1, *key_c3, *key_cancel ;
+EXP char *key_catab, *key_clear, *key_close, *key_command, *key_copy ;
+EXP char *key_create, *key_ctab, *key_dc, *key_dl, *key_down, *key_eic ;
+EXP char *key_end, *key_enter, *key_eol, *key_eos, *key_exit, *key_f0 ;
+EXP char *key_f1, *key_f10, *key_f11, *key_f12, *key_f13, *key_f14 ;
+EXP char *key_f15, *key_f16, *key_f17, *key_f18, *key_f19, *key_f2 ;
+EXP char *key_f20, *key_f21, *key_f22, *key_f23, *key_f24, *key_f25 ;
+EXP char *key_f26, *key_f27, *key_f28, *key_f29, *key_f3, *key_f30 ;
+EXP char *key_f31, *key_f32, *key_f33, *key_f34, *key_f35, *key_f36 ;
+EXP char *key_f37, *key_f38, *key_f39, *key_f4, *key_f40, *key_f41 ;
+EXP char *key_f42, *key_f43, *key_f44, *key_f45, *key_f46, *key_f47 ;
+EXP char *key_f48, *key_f49, *key_f5, *key_f50, *key_f51, *key_f52 ;
+EXP char *key_f53, *key_f54, *key_f55, *key_f56, *key_f57, *key_f58 ;
+EXP char *key_f59, *key_f6, *key_f60, *key_f61, *key_f62, *key_f63 ;
+EXP char *key_f7, *key_f8, *key_f9, *key_find, *key_help, *key_home ;
+EXP char *key_ic, *key_il, *key_left, *key_ll, *key_mark, *key_message ;
+EXP char *key_mouse ;
+EXP char *key_move, *key_next, *key_npage, *key_open, *key_options ;
+EXP char *key_ppage, *key_previous, *key_print, *key_redo, *key_reference ;
+EXP char *key_refresh, *key_replace, *key_restart, *key_resume, *key_right ;
+EXP char *key_save, *key_sbeg, *key_scancel, *key_scommand, *key_scopy ;
+EXP char *key_screate, *key_sdc, *key_sdl, *key_select, *key_send, *key_seol ;
+EXP char *key_sexit, *key_sf, *key_sfind, *key_shelp, *key_shome, *key_sic ;
+EXP char *key_sleft, *key_smessage, *key_smove, *key_snext, *key_soptions ;
+EXP char *key_sprevious, *key_sprint, *key_sr, *key_sredo, *key_sreplace ;
+EXP char *key_sright, *key_srsume, *key_ssave, *key_ssuspend, *key_stab ;
+EXP char *key_sundo, *key_suspend, *key_undo, *key_up, *keypad_local ;
+EXP char *keypad_xmit, *lab_f0, *lab_f1, *lab_f10, *lab_f2, *lab_f3 ;
+EXP char *lab_f4, *lab_f5, *lab_f6, *lab_f7, *lab_f8, *lab_f9 ;
+EXP char *label_format, *label_off ;
+EXP char *label_on, *meta_off, *meta_on, *micro_column_address, *micro_down ;
+EXP char *micro_left, *micro_right, *micro_row_address, *micro_up ;
+EXP char *mouse_info, *newline ;
+EXP char *order_of_pins, *orig_colors, *orig_pair, *pad_char, *parm_dch ;
+EXP char *parm_delete_line, *parm_down_cursor, *parm_down_micro, *parm_ich ;
+EXP char *parm_index, *parm_insert_line, *parm_left_cursor, *parm_left_micro ;
+EXP char *parm_right_cursor, *parm_right_micro, *parm_rindex ;
+EXP char *parm_up_cursor, *parm_up_micro, *pc_term_options, *pkey_key ;
+EXP char *pkey_local, *pkey_plab, *pkey_xmit, *plab_norm, *print_screen ;
+EXP char *prtr_non, *prtr_off, *prtr_on, *pulse ;
+EXP char *quick_dial, *remove_clock, *repeat_char, *req_for_input ;
+EXP char *reset_1string, *reset_2string, *reset_3string, *reset_file ;
+EXP char *restore_cursor, *row_address, *save_cursor, *scancode_escape ;
+EXP char *scroll_forward, *scroll_reverse, *select_char_set, *set0_des_seq ;
+EXP char *set1_des_seq, *set2_des_seq, *set3_des_seq ;
+EXP char *set_a_attributes, *set_a_background ;
+EXP char *set_a_foreground, *set_attributes, *set_background ;
+EXP char *set_bottom_margin, *set_bottom_margin_parm, *set_clock ;
+EXP char *set_color_band ;
+EXP char *set_color_pair, *set_foreground, *set_left_margin ;
+EXP char *set_left_margin_parm, *set_lr_margin ;
+EXP char *set_pglen_inch, *set_page_length ;
+EXP char *set_right_margin, *set_right_margin_parm, *set_tab, *set_tb_margin ;
+EXP char *set_top_margin, *set_top_margin_parm, *set_window ;
+EXP char *start_bit_image, *start_char_set_def, *stop_bit_image ;
+EXP char *stop_char_set_def, *subscript_characters, *superscript_characters ;
+EXP char *tab, *these_cause_cr, *to_status_line, *tone ;
+EXP char *user0, *user1, *user2, *user3, *user4 ;
+EXP char *user5, *user6, *user7, *user8, *user9 ;
+EXP char *underline_char, *up_half_line, *wait_tone ;
+EXP char *xoff_character, *xon_character, *zero_motion ;


+SUBSET "curs" := {
    # also in unix95:curses.h

    +FUNC int putp ( char * const ) ;
    +FUNC int tigetflag ( char * ) ;
    +FUNC int tigetnum ( char * ) ;
    +FUNC char *tigetstr ( char * ) ;
    +FUNC char *tparm ( char *, long, long, long, long, long,
	long, long, long, long ) ;
} ;


+FUNC int del_curterm ( TERMINAL * ) ;
+FUNC int restartterm ( char *, int, int * ) ;
+FUNC TERMINAL *set_curterm ( TERMINAL * ) ;
+FUNC int setupterm ( char *, int, int * ) ;
+FUNC int tgetent ( char *, char * const ) ;
+FUNC int tgetflag ( char [2] ) ;
+FUNC int tgetnum ( char [2] ) ;
+FUNC char *tgetstr ( char [2], char ** ) ;
+FUNC char *tgoto ( char * const, int, int ) ;
+FUNC int tputs ( char * const, int, int (*) ( int ) ) ;
