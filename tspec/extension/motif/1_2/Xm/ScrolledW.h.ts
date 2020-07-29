# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmScrolledWindowWidgetClass;

+TYPE (struct) _XmScrolledWindowClassRec;
+TYPE (struct) _XmScrolledWindowRec;
+TYPEDEF _XmScrolledWindowClassRec * XmScrolledWindowWidgetClass;
+TYPEDEF _XmScrolledWindowRec      * XmScrolledWindowWidget;

+FUNC void XmScrolledWindowSetAreas (Widget sw, Widget hscroll,
                                      Widget vscroll, Widget wregion);
+FUNC Widget XmCreateScrolledWindow (Widget parent,  String name,
                                      ArgList args, Cardinal argCount);

+FUNC void XmScrollVisible(Widget scrollw_widget, Widget widget, Dimension left_right_margin, Dimension top_bottom_margin);
