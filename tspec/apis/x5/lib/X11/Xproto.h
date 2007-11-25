#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
# Basic X protocol

+USE "x5/lib", "X11/Xprotostr.h" ;		# see 1.3


# Exposure Events (10.9)
+TYPE ( struct ) xEvent, ( struct ) xGenericReply, ( union ) xReply ;
+TYPE ( struct ) xReq, ( struct ) xResourceReq ;


# Protocol Request Numbers (Appendix A)

+CONST int X_AllocColor ;
+CONST int X_AllocColorCells ;
+CONST int X_AllocColorPlanes ;
+CONST int X_AllocNamedColor ;
+CONST int X_AllowEvents ;
+CONST int X_Bell ;
+CONST int X_ChangeActivePointerGrab ;
+CONST int X_ChangeGC ;
+CONST int X_ChangeHosts ;
+CONST int X_ChangeKeyboardControl ;
+CONST int X_ChangeKeyboardMapping ;
+CONST int X_ChangePointerControl ;
+CONST int X_ChangeProperty ;
+CONST int X_ChangeSaveSet ;
+CONST int X_ChangeWindowAttributes ;
+CONST int X_CirculateWindow ;
+CONST int X_ClearArea ;
+CONST int X_CloseFont ;
+CONST int X_ConfigureWindow ;
+CONST int X_ConvertSelection ;
+CONST int X_CopyArea ;
+CONST int X_CopyColormapAndFree ;
+CONST int X_CopyGC ;
+CONST int X_CopyPlane ;
+CONST int X_CreateColormap ;
+CONST int X_CreateCursor ;
+CONST int X_CreateGC ;
+CONST int X_CreateGlyphCursor ;
+CONST int X_CreatePixmap ;
+CONST int X_CreateWindow ;
+CONST int X_DeleteProperty ;
+CONST int X_DestroySubwindows ;
+CONST int X_DestroyWindow ;
+CONST int X_FillPoly ;
+CONST int X_ForceScreenSaver ;
+CONST int X_FreeColormap ;
+CONST int X_FreeColors ;
+CONST int X_FreeCursor ;
+CONST int X_FreeGC ;
+CONST int X_FreePixmap ;
+CONST int X_GetAtomName ;
+CONST int X_GetFontPath ;
+CONST int X_GetGeometry ;
+CONST int X_GetImage ;
+CONST int X_GetInputFocus ;
+CONST int X_GetKeyboardControl ;
+CONST int X_GetKeyboardMapping ;
+CONST int X_GetModifierMapping ;
+CONST int X_GetMotionEvents ;
+CONST int X_GetPointerControl ;
+CONST int X_GetPointerMapping ;
+CONST int X_GetProperty ;
+CONST int X_GetScreenSaver ;
+CONST int X_GetSelectionOwner ;
+CONST int X_GetWindowAttributes ;
+CONST int X_GrabButton ;
+CONST int X_GrabKey ;
+CONST int X_GrabKeyboard ;
+CONST int X_GrabPointer ;
+CONST int X_GrabServer ;
+CONST int X_ImageText16 ;
+CONST int X_ImageText8 ;
+CONST int X_InstallColormap ;
+CONST int X_InternAtom ;
+CONST int X_KillClient ;
+CONST int X_ListExtensions ;
+CONST int X_ListFonts ;
+CONST int X_ListFontsWithInfo ;
+CONST int X_ListHosts ;
+CONST int X_ListInstalledColormaps ;
+CONST int X_ListProperties ;
+CONST int X_LookupColor ;
+CONST int X_MapSubwindows ;
+CONST int X_MapWindow ;
+CONST int X_NoOperation ;
+CONST int X_OpenFont ;
+CONST int X_PolyArc ;
+CONST int X_PolyFillArc ;
+CONST int X_PolyFillRectangle ;
+CONST int X_PolyLine ;
+CONST int X_PolyPoint ;
+CONST int X_PolyRectangle ;
+CONST int X_PolySegment ;
+CONST int X_PolyText16 ;
+CONST int X_PolyText8 ;
+CONST int X_PutImage ;
+CONST int X_QueryBestSize ;
+CONST int X_QueryColors ;
+CONST int X_QueryExtension ;
+CONST int X_QueryFont ;
+CONST int X_QueryKeymap ;
+CONST int X_QueryPointer ;
+CONST int X_QueryTextExtents ;
+CONST int X_QueryTree ;
+CONST int X_RecolorCursor ;
+CONST int X_ReparentWindow ;
+CONST int X_RotateProperties ;
+CONST int X_SendEvent ;
+CONST int X_SetAccessControl ;
+CONST int X_SetClipRectangles ;
+CONST int X_SetCloseDownMode ;
+CONST int X_SetDashes ;
+CONST int X_SetFontPath ;
+CONST int X_SetInputFocus ;
+CONST int X_SetModifierMapping ;
+CONST int X_SetPointerMapping ;
+CONST int X_SetScreenSaver ;
+CONST int X_SetSelectionOwner ;
+CONST int X_StoreColors ;
+CONST int X_StoreNamedColor ;
+CONST int X_TranslateCoords ;
+CONST int X_UngrabButton ;
+CONST int X_UngrabKey ;
+CONST int X_UngrabKeyboard ;
+CONST int X_UngrabPointer ;
+CONST int X_UngrabServer ;
+CONST int X_UninstallColormap ;
+CONST int X_UnmapSubwindows ;
+CONST int X_UnmapWindow ;
+CONST int X_WarpPointer ;
