/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**** error.h --- Error reporting.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to an error message reporting facility.
 * This facility allows for named errors, with variables (called tags) inside
 * the error messages.  This allows the messages to be redefined (e.g.  in a
 * different language) with the variable components of the message in a
 * different order.
 *
 * In addition to the error mesage support, this facility also provides
 * support for named strings whose text may be redefined.  This is useful for
 * allowing the text of help messages to be redefined.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	EseverityT
 ** Type:	EseverityP
 ** Repr:	enum {ERROR_SEVERITY_INFORMATION, ERROR_SEVERITY_WARNING,
 *		      ERROR_SEVERITY_ERROR, ERROR_SEVERITY_FATAL,
 *		      ERROR_SEVERITY_INTERNAL}
 *
 * This is the error severity level type.  The lowest error severity is
 * ``ERROR_SEVERITY_INFORMATION'', which is used for information messages (not
 * normally printed out).  The highest severity of error is
 * ``ERROR_SEVERITY_INTERNAL'' which is used for internal program errors.
 *
 ** Type:	ETagT
 ** Type:	ETagP
 ** Repr:	<private>
 *
 * This is the error tag type.  A tag is used to represent a variable inside
 * an error message, such as the file name in which the error occured.  A
 * string of the form "${tag name}" inside an error message is replaced by the
 * tag of the same name.
 *
 ** Type:	ErrorListT
 ** Type:	ErrorListP
 ** Repr:	<private>
 *
 * This is used by the error type.
 *
 ** Type:	ErrorT
 ** Type:	ErrorP
 ** Repr:	<private>
 *
 * This is the error type.
 *
 ** Type:	EStringT
 ** Type:	EStringP
 ** Repr:	<private>
 *
 * This is the named string type.
 *
 ** Type:	ErrorProcP
 ** Repr:	void (*) PROTO_S ((OStreamP, ETagP, GenericP))
 *
 * This is the type of a procedure that is used to display the contents of a
 * tag when reporting an error.
 *
 ** Type:	ErrorInitProcP
 ** Repr:	void (*) PROTO_S ((void))
 *
 * This is the type of the procedure that will be called to define all of the
 * error messages for the current program.
 *
 ** Type:	ETagDataT
 ** Type:	ETagDataP
 ** Repr:	union {CStringP name; ETagP tag;}
 *
 * This is the type of an element in a vector of error tags to be passed to
 * the ``error_intern_tags'' function.  The vector should be initialised with
 * the tag names (surrounded by the ``UB'' and ``UE'' macros for union
 * initialisation), terminated by the ``ERROR_END_TAG_LIST'' macro, e.g.
 *
 *	static ETagDataT tags [] = {
 *	    UB "tag 1" UE,
 *	    UB "tag 2" UE,
 *	    ERROR_END_TAG_LIST
 *	};
 *
 * Once the ``error_intern_tags'' function has been called, the ``tag'' field
 * should be used to access the tag object.
 *
 ** Type:	ErrorDataT
 ** Type:	ErrorDataP
 ** Repr:	union {struct {CStringP name; EseverityP severity;
 *			       CStringP message; GenericP data;} s;
 *		       ErrorP error;}
 *
 * This is the type of an element in a vector of errors to be passed to the
 * ``error_intern_errors'' function.  The vector should be initialised with
 * the error names, severity levels, message text, and a pointer to a
 * non-function object (all surrounded by the ``UB'' and ``UE'' macros for
 * union initialisation).  The vector should be terminated by the
 * ``ERROR_END_ERROR_LIST'' macro, e.g.
 *
 *	static ErrorDataT errors [] = {
 *	    UB {
 *		"error 1", ERROR_SEVERITY_ERROR,
 *		"error 1 occured at line ${line}", NIL (GenericP)
 *	    } UE, ERROR_END_ERROR_LIST
 *	};
 *
 * Once the ``error_intern_errors'' function has been called, the ``error''
 * field should be used to access the error object.
 *
 *
 ** Type:	EStringDataT
 ** Type:	EStringDataP
 ** Repr:	union {struct {CStringP name; CStringP contents;} s;
 *		       EStringP estring;}
 *
 * This is the type of an element in a vector of named strings to be passed to
 * the ``error_intern_strings'' function.  The vector should be initialised
 * with the string names and contents (all surrounded by the ``UB'' and ``UE''
 * macros for union initialisation).  The vector should be terminated by the
 * ``ERROR_END_STRING_LIST'' macro, e.g.
 *
 *	static EStringDataT strings [] = {
 *	    UB {"string name", "string contents"} UE,
 *	    ERROR_END_STRING_LIST
 *	};
 *
 * Once the ``error_intern_strings'' function has been called, the ``estring''
 * field should be used to access the error string object.
 *
 ** Type:	ErrorStatusT
 ** Type:	ErrorStatusP
 ** Repr:	enum {ERROR_STATUS_BAD_MESSAGE, ERROR_STATUS_SUCCESS,
 *		      ERROR_STATUS_BAD_ERROR}
 *
 * This is the return type of the ``error_redefine_error'' function.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			error_init
 *			PROTO_S ((CStringP program, ErrorInitProcP proc))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the error reporting mechanism.  It should only be
 * called once, at the start of the program.  The basename of the program
 * string is used as the program name, for the "${program name}" tag. The
 * procedure is registered as the error initialisation procedure.  The error
 * initialisation procedure should be called once before attempting to report
 * errors.  The best way of doing this, is to call the
 * ``error_call_init_proc'' function which guarantees to only call the
 * function once.  Note that the error initialisation procedure is not
 * expected to be used to initialise named strings: these should be explicitly
 * initialised before they are used.
 *
 ** Function:	void			error_call_init_proc
 *			PROTO_S ((void))
 ** Exceptions:
 *
 * This calls the error initialisation procedure if it has not already been
 * called.  This function should be called before ``error_report'' (actually,
 * it should be called before the error value that will be passed to that
 * function is accessed).
 *
 ** Function:	ETagP			error_define_tag
 *			PROTO_S ((CStringP name))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function defines a tag with the specified name, and returns it.  The
 * name should not be modified or deallocated.  It is possible to define the
 * same tag more than once (but the same value will be returned each time).
 *
 ** Function:	ErrorP			error_define_error
 *			PROTO_S ((CStringP name, ESeverityT severity,
 *				  CStringP message, GenericP data))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function defines an error with the specified name, and returns it.
 * The name should not be modified or deallocated.  The severity level is used
 * to decide whether or not an error should be shown and whether or not the
 * program should abort, when the ``error_report'' function is called.  The
 * message is split up into a list of strings and tags, which will be printed
 * when the error is reported (the sequence "${tag name}" will be replaced by
 * the value of the tag when the error is reported).  The data is for use by
 * the program.
 *
 ** Function:	void			error_intern_tags
 *			PROTO_S ((ETagDataP vector))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the name entries in the specified vector into error
 * tags.  The vector should be terminated by the macro ``ERROR_END_TAG_LIST''.
 * This function should only be called once on any vector.
 *
 ** Function:	void			error_intern_errors
 *			PROTO_S ((ErrorDataP vector))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the name entries in the specified vector into errors.
 * The vector should be terminated by the macro ``ERROR_END_ERROR_LIST''.
 * This function should only be called once on any vector.
 *
 ** Function:	ErrorStatusT		error_redefine_error
 *			PROTO_S ((CStringP name, CStringP message))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the error message for the error with the specified
 * name.  If necessary, the error initialisation procedure will be called to
 * initialise the errors before they are redefined.  If the error does not
 * exist, the function will return ``ERROR_STATUS_BAD_ERROR''.  If the error
 * message contains an unterminated tag, the function will return
 * ``ERROR_STATUS_BAD_MESSAGE''.  If the function succeeds, it will return
 * ``ERROR_STATUS_SUCCESS''.
 *
 ** Function:	ErrorP			error_lookup_error
 *			PROTO_S ((CStringP name))
 ** Exceptions:
 *
 * This function returns the error with the specified name.  If the error does
 * not exist, it returns the null pointer.  If necessary, the error
 * initialisation procedure will be called to initialise the error messages
 * before they are looked up.
 *
 ** Function:	GenericP		error_data
 *			PROTO_S ((ErrorP error))
 ** Exceptions:
 *
 * This function returns the data associated with the specified error.
 *
 ** Function:	void			error_report
 *			PROTO_S ((ErrorP error, ErrorProcP proc,
 *				  GenericP closure))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function reports the specified error.  The procedure is used to print
 * out information for tags.  It is called with the output stream, the tag and
 * the specified closure.  If the procedure doesn't know about the tag, it
 * should ignore it.  The error message is only reported if the severity level
 * of the error is greater than or equal to the minimum severity level set by
 * the ``error_set_min_severity'' function.  The function will cause the
 * program to exit if the error's severity level is ``ERROR_SEVERITY_FATAL''
 * or higher.
 *
 ** Function:	void			error_set_min_report_severity
 *			PROTO_S ((ESeverityT severity))
 ** Exceptions:
 *
 * This function sets the minimum severity of error that should be reported.
 *
 ** Function:	ESeverityT		error_get_min_report_severity
 *			PROTO_S ((void))
 ** Exceptions:
 *
 * This function returns the minimum severity of error that will be reported.
 *
 ** Function:	ESeverityT		error_max_reported_severity
 *			PROTO_S ((void))
 ** Exceptions:
 *
 * This function returns the severity of the error with the highest severity
 * that has been passed to ``error_report''.
 *
 ** Function:	void			error_set_severity_message
 *			PROTO_S ((ESeverityT severity, CStringP message))
 ** Exceptions:
 *
 * This function sets the message to be displayed when the "${severity}" tag
 * is encountered for the specified severity.  Tags are not expanded in the
 * message. The message should not be modified or deallocated.
 *
 ** Function:	BoolT			error_set_prefix_message
 *			PROTO_S ((CStringP message))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function sets the error message prefix string.  This string is output
 * by ``error_display'' before outputting any actual error message.  Tags are
 * expanded, but only for the standard tags: "${program name}", "${severity}",
 * "${dollar}", "${this error name}", "${open brace}", and "${close brace}".
 * All other tags will be ignored.  The function returns true if the message
 * was valid, and false if there was an unterminated tag in the message.
 *
 ** Function:	EStringP		error_define_string
 *			PROTO_S ((CStringP name, CStringP contents))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function defines a named string with the specified name, and assigns
 * it the specified contents.  Neither the name nor the contents should be
 * modified or deallocated.  No tag splitting is performed on the contents.
 *
 ** Function:	void			error_intern_strings
 *			PROTO_S ((EStringDataP vector))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the name and contents entries in the specified vector
 * into named strings.  The vector should be terminated by the macro
 * ``ERROR_END_STRING_LIST''.  This function should only be called once on any
 * vector.
 *
 ** Function:	BoolT			error_redefine_string
 *			PROTO_S ((CStringP name, CStringP contents))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the contents of the named string with the specified
 * name.  If the name does not exist, the function returns false, otherwise it
 * returns true.
 *
 ** Function:	EStringP		error_lookup_string
 *			PROTO_S ((CStringP name))
 ** Exceptions:
 *
 * This function returns the named string with the specified name.  If the
 * named string does not exist, the function returns the null pointer.
 *
 ** Function:	CStringP		error_string_contents
 *			PROTO_S ((EStringP estring))
 ** Exceptions:
 *
 * This function returns the contents of the specified named string.  The
 * returned string should not be modified or deallocated.
 *
 ** Function:	void			write_error_file
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes out an error file (in the same format as parsed by the
 * functions in "error-file.[ch]") to the specified ostream.
 *
 ***=== MACROS ===============================================================
 *
 ** Macro:	ERROR_END_TAG_LIST
 ** Exceptions:
 *
 * This macro should form the last entry in a vector of ``ETagDataT'' objects.
 *
 ** Macro:	ERROR_END_ERROR_LIST
 ** Exceptions:
 *
 * This macro should form the last entry in a vector of ``ErrorDataT''
 * objects.
 *
 ** Macro:	ERROR_END_STRING_LIST
 ** Exceptions:
 *
 * This macro should form the last entry in a vector of ``EStringDataT''
 * objects.
 *
 **** Change log:
 * $Log: error.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:44:43  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:51  smf
 * Initial import of library shared files.
 *
**/

/****************************************************************************/

#ifndef H_ERROR
#define H_ERROR

#include "os-interface.h"
#include "cstring.h"
#include "dstring.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int ESeverityT, *ESeverityP;
#define ERROR_SEVERITY_INFORMATION	(0)
#define ERROR_SEVERITY_WARNING		(1)
#define ERROR_SEVERITY_ERROR		(2)
#define ERROR_SEVERITY_FATAL		(3)
#define ERROR_SEVERITY_INTERNAL		(4)
#else
typedef enum {
    ERROR_SEVERITY_INFORMATION,
    ERROR_SEVERITY_WARNING,
    ERROR_SEVERITY_ERROR,
    ERROR_SEVERITY_FATAL,
    ERROR_SEVERITY_INTERNAL
} ESeverityT, *ESeverityP;    
#endif /* defined (FS_NO_ENUM) */

typedef struct ETagT {
    struct ETagT	       *next;
    CStringP			name;
} ETagT, *ETagP;

typedef struct ErrorListT {
    struct ErrorListT	       *next;
#ifdef FS_NO_ENUM
    int				tag;
#define ERROR_TAG_STRING	(0)
#define ERROR_TAG_TAG		(1)
#else
    enum {
	ERROR_TAG_STRING,
	ERROR_TAG_TAG
    }				tag;
#endif /* defined (FS_NO_ENUM) */
    union {
	NStringT		string;
	ETagP			tag;
    } u;
} ErrorListT, *ErrorListP;

typedef struct ErrorT {
    struct ErrorT	       *next;
    CStringP 			name;
    ESeverityT			severity;
    ErrorListP			error_list;
    GenericP			data;
} ErrorT, *ErrorP;

typedef struct EStringT {
    struct EStringT	       *next;
    CStringP			name;
    CStringP			contents;
} EStringT, *EStringP;

typedef void (*ErrorProcP) PROTO_S ((OStreamP, ETagP, GenericP));
typedef void (*ErrorInitProcP) PROTO_S ((void));
typedef UNION ETagDataT {
    CStringP			name;
    ETagP			tag;
} ETagDataT, *ETagDataP;
typedef UNION ErrorDataT {
    struct {
	CStringP		name;
	ESeverityT		severity;
	CStringP		message;
	GenericP		data;
    } s;
    ErrorP			error;
} ErrorDataT, *ErrorDataP;
typedef UNION EStringDataT {
    struct {
	CStringP		name;
	CStringP		contents;
    } s;
    EStringP			estring;
} EStringDataT, *EStringDataP;

#ifdef FS_NO_ENUM
typedef int ErrorStatusT, *ErrorStatusP;
#define ERROR_STATUS_BAD_MESSAGE	(0)
#define ERROR_STATUS_SUCCESS		(1)
#define ERROR_STATUS_BAD_ERROR		(2)
#else
typedef enum {
    ERROR_STATUS_BAD_MESSAGE,
    ERROR_STATUS_SUCCESS,
    ERROR_STATUS_BAD_ERROR
} ErrorStatusT, *ErrorStatusP;
#endif /* defined (FS_NO_ENUM) */

/*--------------------------------------------------------------------------*/

extern void			error_init
	PROTO_S ((CStringP, ErrorInitProcP));
extern void			error_call_init_proc
	PROTO_S ((void));
extern ETagP			error_define_tag
	PROTO_S ((CStringP));
extern ErrorP			error_define_error
	PROTO_S ((CStringP, ESeverityT, CStringP, GenericP));
extern void			error_intern_tags
	PROTO_S ((ETagDataP));
extern void			error_intern_errors
	PROTO_S ((ErrorDataP));
extern ErrorStatusT		error_redefine_error
	PROTO_S ((CStringP, CStringP));
extern ErrorP			error_lookup_error
	PROTO_S ((CStringP));
extern GenericP			error_data
	PROTO_S ((ErrorP));
extern void			error_report
	PROTO_S ((ErrorP, ErrorProcP, GenericP));
extern void			error_set_min_report_severity
	PROTO_S ((ESeverityT));
extern ESeverityT		error_get_min_report_severity
	PROTO_S ((void));
extern ESeverityT		error_max_reported_severity
	PROTO_S ((void));
extern void			error_set_severity_message
	PROTO_S ((ESeverityT, CStringP));
extern BoolT			error_set_prefix_message
	PROTO_S ((CStringP));
extern EStringP			error_define_string
	PROTO_S ((CStringP, CStringP));
extern void			error_intern_strings
	PROTO_S ((EStringDataP));
extern BoolT			error_redefine_string
	PROTO_S ((CStringP, CStringP));
extern EStringP			error_lookup_string
	PROTO_S ((CStringP));
extern CStringP			error_string_contents
	PROTO_S ((EStringP));

extern void			write_error_file
	PROTO_S ((OStreamP));

/*--------------------------------------------------------------------------*/

#define ERROR_END_TAG_LIST UB NIL (CStringP) UE
#define ERROR_END_ERROR_LIST \
UB {NIL (CStringP), (ESeverityT) 0, NIL (CStringP), NIL (GenericP)} UE
#define ERROR_END_STRING_LIST UB {NIL (CStringP), NIL (CStringP)} UE

#endif /* !defined (H_ERROR) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
