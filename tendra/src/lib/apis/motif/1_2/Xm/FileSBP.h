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



/* SCO CID (IXI) FileSBP.h,v 1.1 1996/08/08 14:12:49 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/SelectioBP.h";
+USE "motif/1_2", "Xm/FileSB.h";

+CONST int XmFSB_MAX_WIDGETS_VERT;

+CONST int XmFS_NO_MATCH;
+CONST int XmFS_IN_FILE_SEARCH;
+CONST int XmFS_DIR_SEARCH_PROC;

+FIELD (struct) _XmFileSelectionBoxConstraintPart := {

	char	unused;
};

+TYPEDEF _XmFileSelectionBoxConstraintPart XmFileSelectionBoxConstraintPart;
+TYPEDEF _XmFileSelectionBoxConstraintPart * XmFileSelectionBoxConstraint;

+FIELD (struct) XmFileSelectionBoxClassPart := { 

	XtPointer		extension;
};

+FIELD (struct) _XmFileSelectionBoxClassRec := { 

	CoreClassPart			core_class;
	CompositeClassPart		composite_class;
	ConstraintClassPart		constraint_class;
	XmManagerClassPart		manager_class;
	XmBulletinBoardClassPart	bulletin_board_class;
	XmSelectionBoxClassPart		selection_box_class;
	XmFileSelectionBoxClassPart	file_selection_box_class;
};

+TYPEDEF _XmFileSelectionBoxClassRec XmFileSelectionBoxClassRec;

+EXP lvalue XmFileSelectionBoxClassRec xmFileSelectionBoxClassRec;

+FIELD (struct) XmFileSelectionBoxPart := {

	XmString			directory;
	XmString			pattern;
	Widget				dir_list_label;
	XmString        		dir_list_label_string;
	Widget				dir_list;
	XmString			*dir_list_items;
	int				dir_list_item_count;
	int				dir_list_selected_item_position;
	Widget				filter_label;
	XmString			filter_label_string;
	Widget				filter_text;
	XmString			dir_mask;
	XmString			no_match_string;
	XmQualifyProc			qualify_search_data_proc;
	XmSearchProc			dir_search_proc;
	XmSearchProc			file_search_proc;
	unsigned char			file_type_mask;
	Boolean				list_updated;
	Boolean				directory_valid;
	unsigned char			state_flags;
};


+FIELD (struct) _XmFileSelectionBoxRec := { 

	CorePart			core;
	CompositePart			composite;
	ConstraintPart			constraint;
	XmManagerPart			manager;
	XmBulletinBoardPart		bulletin_board;
	XmSelectionBoxPart		selection_box;
	XmFileSelectionBoxPart		file_selection_box;
};

+TYPEDEF _XmFileSelectionBoxRec XmFileSelectionBoxRec;

+MACRO XmString FS_Directory(Widget);
+MACRO XmString FS_DirMask(Widget);
+MACRO Widget FS_DirListLabel(Widget);
+MACRO XmString FS_DirListLabelString(Widget);
+MACRO Widget FS_DirList(Widget);
+MACRO XmString *FS_DirListItems(Widget);
+MACRO int FS_DirListItemCount(Widget);
+MACRO Widget FS_FilterLabel(Widget);
+MACRO XmString FS_FilterLabelString(Widget);
+MACRO Widget FS_FilterText(Widget);
+MACRO XmString FS_Pattern(Widget);
+MACRO XmString FS_NoMatchString(Widget);
+MACRO XmQualifyProc FS_QualifySearchDataProc(Widget);
+MACRO XmSearchProc FS_DirSearchProc(Widget);
+MACRO XmSearchProc FS_FileSearchProc(Widget);
+MACRO unsigned char FS_FileTypeMask(Widget);
+MACRO Boolean FS_ListUpdated(Widget);
+MACRO Boolean FS_DirectoryValid(Widget);
+MACRO unsigned char FS_StateFlags(Widget);
+MACRO int FS_DirListSelectedItemPosition(Widget);


