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
+IMPLEMENT "ansi", "stddef.h", "null" (!?) ;
+IMPLEMENT "ansi", "stddef.h", "size_t" (!?) ;

+FUNC char *strcat ( char *, const char * ) ;
+FUNC int strcmp ( const char *, const char * ) ;
+FUNC char *strcpy ( char *, const char * ) ;
+FUNC size_t strcspn ( const char *, const char * ) ;
+FUNC size_t strlen ( const char * ) ;
+FUNC char *strncat ( char *, const char *, size_t ) ;
+FUNC int strncmp ( const char *, const char *, size_t ) ;
+FUNC char *strncpy ( char *, const char *, size_t ) ;
+FUNC size_t strspn ( const char *, const char * ) ;
+FUNC char *strtok ( char *, const char * ) ;

+IFNDEF ~protect ( "cpp", "cstring" )
# These are overloaded in C++
+FUNC char *strchr ( const char *, int ) ;
+FUNC char *strrchr ( const char *, int ) ;
+FUNC char *strpbrk ( const char *, const char * ) ;
+FUNC char *strstr ( const char *, const char * ) ;
+IFNDEF __JUST_POSIX
+FUNC void *memchr ( const void *, int, size_t ) ;
+ENDIF
+ENDIF

+IFNDEF __JUST_POSIX
+FUNC int memcmp ( const void *, const void *, size_t ) ;
+FUNC void *memcpy ( void *, const void *, size_t ) ;
+FUNC void *memset ( void *, int, size_t ) ;
+FUNC int strcoll ( const char *, const char * ) ;
+FUNC char *strerror ( int ) ;
+FUNC size_t strxfrm ( char *, const char *, size_t ) ;
+IFNDEF __JUST_XPG3
+FUNC void *memmove ( void *, const void *, size_t ) ;
+ENDIF
+ENDIF
