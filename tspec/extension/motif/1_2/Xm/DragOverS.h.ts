# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2", "Xm/Xm.h.ts";
+USE "motif/1_2", "Xm/DragC.h.ts";
+USE "motif/1_2", "Xm/DragIcon.h.ts";

+TYPE (struct) _XmDragOverShellRec;
+TYPE (struct) _XmDragOverShellClassRec;
+TYPEDEF _XmDragOverShellRec *XmDragOverShellWidget;
+TYPEDEF _XmDragOverShellClassRec *XmDragOverShellWidgetClass;

+EXP lvalue WidgetClass xmDragOverShellWidgetClass;


