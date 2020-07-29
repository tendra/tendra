# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+TYPEDEF void (*XmSearchProc)(Widget, XtPointer);
+TYPEDEF void (*XmQualifyProc)(Widget, XtPointer, XtPointer);

+EXP lvalue WidgetClass xmFileSelectionBoxWidgetClass;

+TYPE (struct) _XmFileSelectionBoxClassRec;
+TYPE (struct) _XmFileSelectionBoxRec;
+TYPEDEF _XmFileSelectionBoxClassRec * XmFileSelectionBoxWidgetClass;
+TYPEDEF _XmFileSelectionBoxRec * XmFileSelectionBoxWidget;

+FUNC Widget XmFileSelectionBoxGetChild( Widget widget, unsigned char child);
+FUNC void XmFileSelectionDoSearch( Widget widget, XmString dirmask) ;
+FUNC Widget XmCreateFileSelectionBox( Widget parent, String name, ArgList arglist, Cardinal argcount) ;
+FUNC Widget XmCreateFileSelectionDialog( Widget parent, String name,
                                         ArgList arglist, Cardinal argcount);

