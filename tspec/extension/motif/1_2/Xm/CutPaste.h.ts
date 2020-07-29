# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts" ;

+CONST int XmClipboardFail;
+CONST int XmClipboardSuccess;
+CONST int XmClipboardTruncate;
+CONST int XmClipboardLocked;
+CONST int XmClipboardBadFormat;
+CONST int XmClipboardNoData;

/* pre 1.2 definitions */
+CONST int ClipboardFail;
+CONST int ClipboardSuccess;
+CONST int ClipboardTruncate;
+CONST int ClipboardLocked;
+CONST int ClipboardBadFormat;
+CONST int ClipboardNoData;

+FIELD (struct) XmClipboardPendingRec := { 

	long	DataId;
	long	PrivateId;
};

+TYPEDEF XmClipboardPendingRec *XmClipboardPendingList;


+TYPEDEF void (*XmCutPasteProc)(Widget, long *, long *, int *);
+TYPEDEF void (*VoidProc)(Widget, int *, int *, int *);


+FUNC int XmClipboardBeginCopy(
                        Display *display,
                        Window window,
                        XmString label,
                        Widget widget,
                        VoidProc callback,
                        long *itemid) ;
+FUNC int XmClipboardStartCopy(
                        Display *display,
                        Window window,
                        XmString label,
                        Time timestamp,
                        Widget widget,
                        XmCutPasteProc callback,
                        long *itemid) ;
+FUNC int XmClipboardCopy(
                        Display *display,
                        Window window,
                        long itemid,
                        char *format,
                        XtPointer buffer,
                        unsigned long length,
                        long private_id,
                        long *dataid) ;
+FUNC int XmClipboardEndCopy(
                        Display *display,
                        Window window,
                        long itemid) ;
+FUNC int XmClipboardCancelCopy(
                        Display *display,
                        Window window,
                        long itemid) ;
+FUNC int XmClipboardWithdrawFormat(
                        Display *display,
                        Window window,
                        long data) ;
+FUNC int XmClipboardCopyByName(
                        Display *display,
                        Window window,
                        long data,
                        XtPointer buffer,
                        unsigned long length,
                        long private_id) ;
+FUNC int XmClipboardUndoCopy(
                        Display *display,
                        Window window) ;
+FUNC int XmClipboardLock(
                        Display *display,
                        Window window) ;
+FUNC int XmClipboardUnlock(
                        Display *display,
                        Window window,
                        Boolean all_levels) ;
+FUNC int XmClipboardStartRetrieve(
                        Display *display,
                        Window window,
                        Time timestamp) ;
+FUNC int XmClipboardEndRetrieve(
                        Display *display,
                        Window window) ;
+FUNC int XmClipboardRetrieve(
                        Display *display,
                        Window window,
                        char *format,
                        XtPointer buffer,
                        unsigned long length,
                        unsigned long *outlength,
                        long *private_id) ;
+FUNC int XmClipboardInquireCount(
                        Display *display,
                        Window window,
                        int *count,
                        unsigned long *maxlength) ;
+FUNC int XmClipboardInquireFormat(
                        Display *display,
                        Window window,
                        int n,
                        XtPointer buffer,
                        unsigned long bufferlength,
                        unsigned long *outlength) ;
+FUNC int XmClipboardInquireLength(
                        Display *display,
                        Window window,
                        char *format,
                        unsigned long *length) ;
+FUNC int XmClipboardInquirePendingItems(
                        Display *display,
                        Window window,
                        char *format,
                        XmClipboardPendingList *list,
                        unsigned long *count) ;
+FUNC int XmClipboardRegisterFormat(
                        Display *display,
                        char *format_name,
                        int format_length) ;


