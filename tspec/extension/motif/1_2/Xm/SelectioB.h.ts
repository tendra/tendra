# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmSelectionBoxWidgetClass;

+TYPE (struct) _XmSelectionBoxClassRec;
+TYPE (struct) _XmSelectionBoxRec;
+TYPEDEF _XmSelectionBoxClassRec * XmSelectionBoxWidgetClass;
+TYPEDEF _XmSelectionBoxRec * XmSelectionBoxWidget;


+FUNC Widget XmSelectionBoxGetChild( Widget sb, unsigned char child);
+FUNC Widget XmCreateSelectionBox( Widget p, String name, ArgList args,
                                                                  Cardinal n) ;
+FUNC Widget XmCreateSelectionDialog( Widget ds_p, String name,
                                              ArgList sb_args, Cardinal sb_n) ;
+FUNC Widget XmCreatePromptDialog( Widget parent, String name, ArgList arglist,
                                                            Cardinal argcount);
