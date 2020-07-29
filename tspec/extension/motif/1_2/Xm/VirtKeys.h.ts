# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


#+USE "motif/1_2","Xm/Xm.h.ts";

+USE "x5/t", "X11/Intrinsic.h.ts";

+EXP unsigned long osfXK_BackSpace ;
+EXP unsigned long osfXK_Insert ;
+EXP unsigned long osfXK_Delete ;
+EXP unsigned long osfXK_Copy ;
+EXP unsigned long osfXK_Cut ;
+EXP unsigned long osfXK_Paste ;

+EXP unsigned long osfXK_AddMode ;
+EXP unsigned long osfXK_PrimaryPaste ;
+EXP unsigned long osfXK_QuickPaste ;

+EXP unsigned long osfXK_PageUp ;
+EXP unsigned long osfXK_PageDown ;

+EXP unsigned long osfXK_EndLine ;
+EXP unsigned long osfXK_BeginLine ;

+EXP unsigned long osfXK_Activate ;

+EXP unsigned long osfXK_MenuBar ;

+EXP unsigned long osfXK_Clear ;
+EXP unsigned long osfXK_Cancel ;
+EXP unsigned long osfXK_Help ;
+EXP unsigned long osfXK_Menu ;
+EXP unsigned long osfXK_Select ;
+EXP unsigned long osfXK_Undo ;

+EXP unsigned long osfXK_Left ;
+EXP unsigned long osfXK_Up ;
+EXP unsigned long osfXK_Right ;
+EXP unsigned long osfXK_Down ;


+EXP String XmVosfBackSpace ;
+EXP String XmVosfInsert ;
+EXP String XmVosfDelete ;
+EXP String XmVosfCopy ;
+EXP String XmVosfCut ;
+EXP String XmVosfPaste; 

+EXP String XmVosfAddMode; 
+EXP String XmVosfPrimaryPaste ;
+EXP String XmVosfQuickPaste ;

+EXP String XmVosfPageUp ;
+EXP String XmVosfPageDown; 

+EXP String XmVosfEndLine ;
+EXP String XmVosfBeginLine; 

+EXP String XmVosfActivate ;

+EXP String XmVosfMenuBar ;

+EXP String XmVosfClear ;
+EXP String XmVosfCancel ;
+EXP String XmVosfHelp ;
+EXP String XmVosfMenu ;
+EXP String XmVosfSelect; 
+EXP String XmVosfUndo ;

+EXP String XmVosfLeft ;
+EXP String XmVosfUp ;
+EXP String XmVosfRight ; 
+EXP String XmVosfDown ;

+FUNC void XmTranslateKey(Display *, KeyCode, Modifiers, Modifiers *, KeySym *);

+FUNC void _XmVirtKeysInitialize (Widget shell);





