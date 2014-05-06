# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;

+IF %% __SYSV_TERMINAL_INTERFACE %%

+TYPE TERMINAL ;

+CONST int auto_left_margin, auto_right_margin, back_color_erase, can_change ;
+CONST int ceol_standout_glitch, col_addr_glitch, cpi_changes_res ;
+CONST int cr_cancels_micro_mode, dest_tabs_magic_smso, eat_newline_glitch ;
+CONST int erase_overstrike, generic_type, hard_copy, hard_cursor ;
+CONST int has_meta_key, has_print_wheel, has_status_line ;
+CONST int hue_lightness_saturation, insert_null_glitch, lpi_changes_res ;
+CONST int memory_above, memory_below, move_insert_mode, move_standout_mode ;
+CONST int needs_xon_xoff, no_esc_ctlc, no_pad_char, non_rev_rmcup ;
+CONST int over_strike, prtr_silent, row_addr_glitch, semi_auto_right_margin ;
+CONST int status_line_esc_ok, tilde_glitch, transparent_underline, xon_xoff ;

+CONST int buffer_capacity, columns, dot_horz_spacing, dot_vert_spacing ;
+CONST int init_tabs, label_height, label_width, lines, lines_of_memory ;
+CONST int magic_cookie_glitch, max_colors, max_micro_address, max_micro_jump ;
+CONST int max_pairs, micro_char_size, micro_line_size, no_color_video ;
+CONST int num_labels, number_of_pins, output_res_char, output_res_horz_inch ;
+CONST int output_res_line, output_res_vert_inch, padding_baud_rate ;
+CONST int virtual_terminal, wide_char_size, width_status_line ;

#
# Commented out
#
# +CONST int bit_image_entwining, bit_image_type, buttons, create_window ;
# +CONST int dial_phone, display_clock, fixed_pause, flash_hook, get_mouse ;
# +CONST int goto_window, hangup, key_mouse, label_format, max_attributes ;
# +CONST int maximum_windows, mouse_info, non_dest_scroll_region, print_rate ;
# +CONST int pulse, quick_dial, remove_clock, req_mouse_pos, set_clock ;
# +CONST int set_pglen_inch, tone, user0, user1, user2, user3, user4, user5 ;
# +CONST int user6, user7, user8, user9, wait_tone ;
#

+CONST char *acs_chars, *alt_scancode_esc, *back_tab, *bell ;
+CONST char *bit_image_carriage_return, *bit_image_newline, *bit_image_repeat ;
+CONST char *carriage_return, *change_char_pitch, *change_line_pitch ;
+CONST char *change_res_horz, *change_res_vert, *change_scroll_region ;
+CONST char *char_padding, *char_set_names, *clear_all_tabs, *clear_margins ;
+CONST char *clear_screen, *clr_bol, *clr_eol, *clr_eos, *code_set_init ;
+CONST char *color_names, *column_address, *command_character, *cursor_address ;
+CONST char *cursor_down, *cursor_home, *cursor_invisible, *cursor_left ;
+CONST char *cursor_mem_address, *cursor_normal, *cursor_right, *cursor_to_ll ;
+CONST char *cursor_up, *cursor_visible, *define_bit_image_region ;
+CONST char *define_char, *delete_character, *delete_line, *device_type ;
+CONST char *dis_status_line, *display_pc_char, *down_half_line, *ena_acs ;
+CONST char *end_bit_image_region, *enter_alt_charset_mode, *enter_am_mode ;
+CONST char *enter_blink_mode, *enter_bold_mode, *enter_ca_mode ;
+CONST char *enter_delete_mode, *enter_dim_mode, *enter_doublewide_mode ;
+CONST char *enter_draft_quality, *enter_insert_mode, *enter_italics_mode ;
+CONST char *enter_leftward_mode, *enter_micro_mode ;
+CONST char *enter_near_letter_quality, *enter_normal_quality ;
+CONST char *enter_pc_charset_mode, *enter_protected_mode, *enter_reverse_mode ;
+CONST char *enter_scancode_mode, *enter_secure_mode, *enter_shadow_mode ;
+CONST char *enter_standout_mode, *enter_subscript_mode ;
+CONST char *enter_superscript_mode, *enter_underline_mode, *enter_upward_mode ;
+CONST char *enter_xon_mode, *erase_chars, *exit_alt_charset_mode ;
+CONST char *exit_am_mode, *exit_attribute_mode, *exit_ca_mode ;
+CONST char *exit_delete_mode, *exit_doublewide_mode, *exit_insert_mode ;
+CONST char *exit_italics_mode, *exit_leftward_mode, *exit_micro_mode ;
+CONST char *exit_pc_charset_mode, *exit_scancode_mode, *exit_shadow_mode ;
+CONST char *exit_standout_mode, *exit_subscript_mode, *exit_superscript_mode ;
+CONST char *exit_underline_mode, *exit_upward_mode, *exit_xon_mode ;
+CONST char *flash_screen, *form_feed, *from_status_line, *init_1string ;
+CONST char *init_2string, *init_3string, *init_file, *init_prog ;
+CONST char *initialize_color, *initialize_pair, *insert_character ;
+CONST char *insert_line, *insert_padding, *key_a1, *key_a3, *key_b2 ;
+CONST char *key_backspace, *key_beg, *key_btab, *key_c1, *key_c3, *key_cancel ;
+CONST char *key_catab, *key_clear, *key_close, *key_command, *key_copy ;
+CONST char *key_create, *key_ctab, *key_dc, *key_dl, *key_down, *key_eic ;
+CONST char *key_end, *key_enter, *key_eol, *key_eos, *key_exit, *key_f0 ;
+CONST char *key_f1, *key_f10, *key_f11, *key_f12, *key_f13, *key_f14 ;
+CONST char *key_f15, *key_f16, *key_f17, *key_f18, *key_f19, *key_f2 ;
+CONST char *key_f20, *key_f21, *key_f22, *key_f23, *key_f24, *key_f25 ;
+CONST char *key_f26, *key_f27, *key_f28, *key_f29, *key_f3, *key_f30 ;
+CONST char *key_f31, *key_f32, *key_f33, *key_f34, *key_f35, *key_f36 ;
+CONST char *key_f37, *key_f38, *key_f39, *key_f4, *key_f40, *key_f41 ;
+CONST char *key_f42, *key_f43, *key_f44, *key_f45, *key_f46, *key_f47 ;
+CONST char *key_f48, *key_f49, *key_f5, *key_f50, *key_f51, *key_f52 ;
+CONST char *key_f53, *key_f54, *key_f55, *key_f56, *key_f57, *key_f58 ;
+CONST char *key_f59, *key_f6, *key_f60, *key_f61, *key_f62, *key_f63 ;
+CONST char *key_f7, *key_f8, *key_f9, *key_find, *key_help, *key_home ;
+CONST char *key_ic, *key_il, *key_left, *key_ll, *key_mark, *key_message ;
+CONST char *key_move, *key_next, *key_npage, *key_open, *key_options ;
+CONST char *key_ppage, *key_previous, *key_print, *key_redo, *key_reference ;
+CONST char *key_refresh, *key_replace, *key_restart, *key_resume, *key_right ;
+CONST char *key_save, *key_sbeg, *key_scancel, *key_scommand, *key_scopy ;
+CONST char *key_screate, *key_sdc, *key_sdl, *key_select, *key_send, *key_seol ;
+CONST char *key_sexit, *key_sf, *key_sfind, *key_shelp, *key_shome, *key_sic ;
+CONST char *key_sleft, *key_smessage, *key_smove, *key_snext, *key_soptions ;
+CONST char *key_sprevious, *key_sprint, *key_sr, *key_sredo, *key_sreplace ;
+CONST char *key_sright, *key_srsume, *key_ssave, *key_ssuspend, *key_stab ;
+CONST char *key_sundo, *key_suspend, *key_undo, *key_up, *keypad_local ;
+CONST char *keypad_xmit, *lab_f0, *lab_f1, *lab_f10, *lab_f2, *lab_f3 ;
+CONST char *lab_f4, *lab_f5, *lab_f6, *lab_f7, *lab_f8, *lab_f9, *label_off ;
+CONST char *label_on, *meta_off, *meta_on, *micro_column_address, *micro_down ;
+CONST char *micro_left, *micro_right, *micro_row_address, *micro_up, *newline ;
+CONST char *order_of_pins, *orig_colors, *orig_pair, *pad_char, *parm_dch ;
+CONST char *parm_delete_line, *parm_down_cursor, *parm_down_micro, *parm_ich ;
+CONST char *parm_index, *parm_insert_line, *parm_left_cursor, *parm_left_micro ;
+CONST char *parm_right_cursor, *parm_right_micro, *parm_rindex ;
+CONST char *parm_up_cursor, *parm_up_micro, *pc_term_options, *pkey_key ;
+CONST char *pkey_local, *pkey_plab, *pkey_xmit, *plab_norm, *print_screen ;
+CONST char *prtr_non, *prtr_off, *prtr_on, *repeat_char, *req_for_input ;
+CONST char *reset_1string, *reset_2string, *reset_3string, *reset_file ;
+CONST char *restore_cursor, *row_address, *save_cursor, *scancode_escape ;
+CONST char *scroll_forward, *scroll_reverse, *select_char_set, *set0_des_seq ;
+CONST char *set1_des_seq, *set2_des_seq, *set3_des_seq, *set_a_background ;
+CONST char *set_a_foreground, *set_attributes, *set_background ;
+CONST char *set_bottom_margin, *set_bottom_margin_parm, *set_color_band ;
+CONST char *set_color_pair, *set_foreground, *set_left_margin ;
+CONST char *set_left_margin_parm, *set_lr_margin, *set_page_length ;
+CONST char *set_right_margin, *set_right_margin_parm, *set_tab, *set_tb_margin ;
+CONST char *set_top_margin, *set_top_margin_parm, *set_window ;
+CONST char *start_bit_image, *start_char_set_def, *stop_bit_image ;
+CONST char *stop_char_set_def, *subscript_characters, *superscript_characters ;
+CONST char *tab, *these_cause_cr, *to_status_line, *underline_char ;
+CONST char *up_half_line, *xoff_character, *xon_character, *zero_motion ;

+EXP lvalue char *boolnames [] ;
+EXP lvalue char *boolcodes [] ;
+EXP lvalue char *boolfnames [] ;
+EXP lvalue char *numnames [] ;
+EXP lvalue char *numcodes [] ;
+EXP lvalue char *numfnames [] ;
+EXP lvalue char *strnames [] ;
+EXP lvalue char *strcodes [] ;
+EXP lvalue char *strfnames [] ;

+ENDIF
