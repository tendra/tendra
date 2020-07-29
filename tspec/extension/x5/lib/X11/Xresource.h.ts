# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Resource manager facilities

+USE "x5/lib", "X11/X.h.ts" ;
+USE "x5/lib", "X11/Xlib.h.ts", "types" ;

+TYPE ~XrmDatabaseRec ;
+TYPEDEF ~XrmDatabaseRec *XrmDatabase ;		# see 15.4 (it's a pointer)
+TYPE XrmHashTable ;				# RCA : never specified


# Quarks (15.3)

+IFNDEF __STRICT_MIT_XLIB
# XrmQuark is typedef to int on page 286, but this may well be an
# unintended overspecifiaction.  On DEC Alpha OSF/1 it is a long,
# to be the same size as String, which is assumed by Xt.
+TYPE (int) XrmQuark ;
+ELSE
+TYPEDEF int XrmQuark.1 ;
+ENDIF

+TYPEDEF XrmQuark XrmName ;
+TYPEDEF XrmQuark XrmClass ;
+TYPEDEF XrmQuark XrmRepresentation ;
+DEFINE NULLQUARK	%% ((XrmQuark)0) %% ;

+FUNC XrmQuark XrmUniqueQuark ( void ) ;

+TYPEDEF XrmQuark *XrmQuarkList ;
+TYPEDEF XrmQuarkList XrmNameList ;
+TYPEDEF XrmQuarkList XrmClassList ;

+FUNC XrmQuark XrmStringToQuark ( char * ) ;
+FUNC XrmQuark XrmPermStringToQuark ( char * ) ;
+DEFINE XrmStringToName(string)		%% XrmStringToQuark(string) %% ;
+DEFINE XrmStringToClass(string)	%% XrmStringToQuark(string) %% ;
+DEFINE XrmStringToRepresentation(string) %% XrmStringToQuark(string) %% ;

+FUNC char *XrmQuarkToString ( XrmQuark ) ;
+DEFINE XrmNameToString(name)		%% XrmQuarkToString(name) %% ;
+DEFINE XrmClassToString(class)		%% XrmQuarkToString(class) %% ;
+DEFINE XrmRepresentationToString(type)	%% XrmQuarkToString(type) %% ;

+FUNC void XrmStringToQuarkList ( char *, XrmQuarkList ) ;
+DEFINE XrmStringToNameList(str,name)	%% XrmStringToQuarkList((str),(name)) %% ;
+DEFINE XrmStringToClassList(str,class)	%% XrmStringToQuarkList((str),(class)) %% ;

+ENUM XrmBinding := { XrmBindTightly, XrmBindLoosely } ;
+TYPEDEF XrmBinding *XrmBindingList ;

+FUNC void XrmStringToBindingQuarkList ( char *, XrmBindingList,
    XrmQuarkList ) ;


# Creating and Storing Databases (15.4)

+FIELD ( struct ) XrmValue := {
    unsigned int size ;
    XPointer addr ;
} ;
+TYPEDEF XrmValue *XrmValuePtr ;

+FUNC void XrmInitialize ( void ) ;
+FUNC XrmDatabase XrmGetFileDatabase ( char * ) ;
+FUNC void XrmPutFileDatabase ( XrmDatabase, char * ) ;
+FUNC char *XResourceManagerString ( Display * ) ;
+FUNC char *XScreenResourceString ( Screen * ) ;
+FUNC XrmDatabase XrmGetStringDatabase ( char * ) ;
+FUNC char *XrmLocaleOfDatabase ( XrmDatabase ) ;
+FUNC void XrmDestroyDatabase ( XrmDatabase ) ;
+FUNC void XrmSetDatabase ( Display *, XrmDatabase ) ;
+FUNC XrmDatabase XrmGetDatabase ( Display * ) ;


# Merging Resource Databases (15.5) - first is misprint in spec

+FUNC Status XrmCombineFileDatabase ( char *, XrmDatabase *, Bool ) ; # RCA
+FUNC void XrmCombineDatabase ( XrmDatabase, XrmDatabase *, Bool ) ;
+FUNC void XrmMergeDatabases ( XrmDatabase, XrmDatabase * ) ;


# Looking Up Resources (15.6)

+FUNC Bool XrmGetResource ( XrmDatabase, char *, char *, char **,
    XrmValue * ) ; 
+FUNC Bool XrmQGetResource ( XrmDatabase, XrmNameList, XrmClassList,
    XrmRepresentation *, XrmValue * ) ;

+TYPEDEF XrmHashTable *XrmSearchList ;

+FUNC Bool XrmQGetSearchList ( XrmDatabase, XrmNameList, XrmClassList,
    XrmSearchList, int ) ;
+FUNC Bool XrmQGetSearchResource ( XrmSearchList, XrmName, XrmClass,
    XrmRepresentation *, XrmValue * ) ;


# Storing into a Resource Database (15.7)

+FUNC void XrmPutResource ( XrmDatabase *, char *, char *, XrmValue * ) ;
+FUNC void XrmQPutResource ( XrmDatabase *, XrmBindingList, XrmQuarkList,
    XrmRepresentation, XrmValue * ) ;
+FUNC void XrmPutStringResource ( XrmDatabase *, char *, char * ) ;
+FUNC void XrmQPutStringResource ( XrmDatabase *, XrmBindingList,
    XrmQuarkList, char * ) ;
+FUNC void XrmPutLineResource ( XrmDatabase *, char * ) ;


# Enumerating Database Entries (15.8)

+DEFINE XrmEnumAllLevels	%% 0 %% ;
+DEFINE XrmEnumOneLevel		%% 1 %% ;

+FUNC Bool XrmEnumerateDatabase ( XrmDatabase, XrmNameList, XrmClassList,
    int, Bool (*) (), XPointer ) ;


# Parsing Command line Options (15.9)

+ENUM XrmOptionKind := {
    XrmoptionNoArg,
    XrmoptionIsArg,
    XrmoptionStickyArg,
    XrmoptionSepArg,
    XrmoptionResArg,
    XrmoptionSkipArg,
    XrmoptionSkipLine,
    XrmoptionSkipNArgs
} ;

+FIELD ( struct ) XrmOptionDescRec := {
    char *option ;
    char *specifier ;
    XrmOptionKind argKind ;
    XPointer value ;
} ;

+TYPEDEF XrmOptionDescRec *XrmOptionDescList ;

+FUNC void XrmParseCommand ( XrmDatabase *, XrmOptionDescList, int,
    char *, int *, char ** ) ;
