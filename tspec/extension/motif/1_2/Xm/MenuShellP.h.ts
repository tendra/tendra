# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/MenuShell.h.ts";
+USE "motif/1_2", "Xm/XmP.h.ts";
+USE "x5/t", "X11/ShellP.h.ts";

+FIELD (struct) XmMenuShellPart := {

	unsigned char	focus_policy;
	XmFocusData	focus_data;
	Boolean		private_shell;
	XmFontList	default_font_list;
	XmFontList	button_font_list;
	XmFontList	label_font_list;
};


+FIELD (struct) _XmMenuShellRec := {

	CorePart		core;
	CompositePart		composite;
	ShellPart		shell;
	OverrideShellPart	override;
	XmMenuShellPart		menu_shell;
};

+TYPEDEF _XmMenuShellRec XmMenuShellRec;

/* OBSOLETE for combatability only */
+FIELD (struct) _XmMenuShellWidgetRec := {

	CorePart		core;
	CompositePart		composite;
	ShellPart		shell;
	OverrideShellPart	override;
	XmMenuShellPart		menu_shell;
};

+TYPEDEF _XmMenuShellWidgetRec XmMenuShellWidgetRec;


+FIELD (struct) XmMenuShellClassPart := { 

	XtActionProc		popdownOne;
	XtActionProc		popdownEveryone;
	XtActionProc		popdownDone;
	XmMenuPopupProc		popupSharedMenupane;

	XtPointer		extension;
};


+FIELD (struct) _XmMenuShellClassRec := {

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ShellClassPart		shell_class;
	OverrideShellClassPart	override_shell_class;
	XmMenuShellClassPart	menu_shell_class;
};

+TYPEDEF _XmMenuShellClassRec XmMenuShellClassRec;

+EXP lvalue XmMenuShellClassRec xmMenuShellClassRec;

+MACRO unsigned char MS_FocusPolicy(Widget);

+FUNC void _XmEnterRowColumn(Widget, XtPointer, XEvent *, Boolean *);
+FUNC void _XmClearTraversal(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmSetLastManagedMenuTime(Widget, Time);




