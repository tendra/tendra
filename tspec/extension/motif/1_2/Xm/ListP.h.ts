# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/List.h.ts";
+USE "motif/1_2", "Xm/PrimitiveP.h.ts";
+USE "motif/1_2", "Xm/ScrollBar.h.ts";
+USE "motif/1_2", "Xm/ScrolledW.h.ts";

+FIELD (struct) _XmListDragConvertStruct := {

   Widget 		w;
   XmString 		* strings;
   int 			num_strings;
};

+TYPEDEF _XmListDragConvertStruct XmListDragConvertStruct;

+FIELD (struct) _XmListClassPart := {

   XtPointer 		extension;
};

+TYPEDEF _XmListClassPart XmListClassPart;

+FIELD (struct)  _XmListClassRec := {

   CoreClassPart        core_class;
   XmPrimitiveClassPart primitive_class;
   XmListClassPart     list_class;
};

+TYPEDEF _XmListClassRec XmListClassRec;

+EXP lvalue XmListClassRec xmListClassRec;

+FIELD (struct) Element := {

	_XmString	name;
	Dimension	height;
	Dimension	width;
	Dimension	CumHeight;
	Boolean		selected;
	Boolean		last_selected;
	Boolean		LastTimeDrawn;
	unsigned short	NumLines;
	int		length;
};

+TYPEDEF Element *ElementPtr;

+FIELD (struct) _XmListPart := {

	Dimension	spacing;
	short           ItemSpacing;
	Dimension       margin_width;
	Dimension    	margin_height;
	XmFontList 	font;
	XmString	*items;
	int		itemCount;
	XmString	*selectedItems;
        int             *selectedIndices;
	int		selectedItemCount;
	int 		visibleItemCount;
	int 		LastSetVizCount;
	unsigned char	SelectionPolicy;
	unsigned char	ScrollBarDisplayPolicy;
	unsigned char	SizePolicy;
        XmStringDirection StrDir;

        Boolean		AutoSelect;
        Boolean		DidSelection;
        Boolean		FromSetSB;
        Boolean		FromSetNewSize;
        Boolean		AddMode;
	unsigned char	LeaveDir;
	unsigned char	HighlightThickness;
	int 		ClickInterval;
        XtIntervalId	DragID;
	XtCallbackList 	SingleCallback;
	XtCallbackList 	MultipleCallback;
	XtCallbackList 	ExtendCallback;
	XtCallbackList 	BrowseCallback;
	XtCallbackList 	DefaultCallback;


	GC		NormalGC;	
	GC		InverseGC;
	GC		HighlightGC;
        Pixmap          DashTile;
	ElementPtr	*InternalList;
	int		LastItem;
	int		FontHeight;
	int		top_position;
	char		Event;
	int		LastHLItem;
	int		StartItem;
	int		OldStartItem;
	int		EndItem;
	int		OldEndItem;
	Position	BaseX;
	Position	BaseY;
	Boolean		MouseMoved;
	Boolean		AppendInProgress;
	Boolean		Traversing;
	Boolean		KbdSelection;
	short		DownCount;
	Time		DownTime;
	int		CurrentKbdItem;
	unsigned char	SelectionType;
	GC		InsensitiveGC;

	int 		vmin;
	int 		vmax;
	int 		vOrigin;
	int 		vExtent;
	int 		hmin;
	int 		hmax;
	int 		hOrigin;
	int 		hExtent;

	Dimension	MaxWidth;
	Dimension	CharWidth;
	Position	XOrigin;
	
	XmScrollBarWidget   	hScrollBar;
	XmScrollBarWidget   	vScrollBar;
	XmScrolledWindowWidget  Mom;
	Dimension	MaxItemHeight;
	
};

+TYPEDEF _XmListPart XmListPart;

+FIELD (struct) _XmListRec := {
   CorePart	   core;
   XmPrimitivePart primitive;
   XmListPart	   list;
};

+TYPEDEF _XmListRec XmListRec;


