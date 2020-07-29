/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * error.h - Error reporting.
 *
 * This file specifies the interface to an error message reporting facility.
 * This facility allows for named errors, with variables (called tags) inside
 * the error messages.  This allows the messages to be redefined (e.g.  in a
 * different language) with the variable components of the message in a
 * different order.
 *
 *
 * In addition to the error mesage support, this facility also provides
 * support for named strings whose text may be redefined.  This is useful for
 * allowing the text of help messages to be redefined.
 */

#ifndef H_ERROR
#define H_ERROR

#include <exds/common.h>
#include <exds/ostream.h>
#include <exds/dstring.h>


/*
 * This is used by the error type.
 */
typedef struct ErrorListT ErrorListT;

/*
 * This is the error severity level type.  The lowest error severity is
 * "ERROR_SEVERITY_INFORMATION", which is used for information messages (not
 * normally printed out).  The highest severity of error is
 * "ERROR_SEVERITY_INTERNAL" which is used for internal program errors.
 */
typedef enum {
	ERROR_SEVERITY_INFORMATION,
	ERROR_SEVERITY_WARNING,
	ERROR_SEVERITY_ERROR,
	ERROR_SEVERITY_FATAL,
	ERROR_SEVERITY_INTERNAL
} ESeverityT;

/*
 * This is the error tag type.  A tag is used to represent a variable inside
 * an error message, such as the file name in which the error occured.  A
 * string of the form "${tag name}" inside an error message is replaced by the
 * tag of the same name.
 */
typedef struct ETagT ETagT;
struct ETagT {
	ETagT *next;
	const char *name;
};

/*
 * This is the error type.
 */
typedef struct ErrorT ErrorT;
struct ErrorT {
	ErrorT *next;
	const char *name;
	ESeverityT severity;
	ErrorListT *error_list;
	void *data;
};

/*
 * This is the named string type.
 */
typedef struct EStringT EStringT;
struct EStringT {
	EStringT *next;
	const char *name;
	const char *contents;
};

/*
 * This is the type of a procedure that is used to display the contents of a
 * tag when reporting an error.
 */
typedef void(*ErrorprocP)(OStreamT *, ETagT *, void *);

/*
 * This is the type of the procedure that will be called to define all of the
 * error messages for the current program.
 */
typedef void(*ErrorInitProcP)(void);

/*
 * This is the type of an element in a vector of error tags to be passed to
 * the ``error_intern_tags'' function.  The vector should be initialised with
 * the tag names (surrounded by braces for union
 * initialisation), terminated by the ``ERROR_END_TAG_LIST'' macro, e.g.
 *
 *	static ETagDataT tags [] = {
 *		{ "tag 1" },
 *		{ "tag 2" },
 *		ERROR_END_TAG_LIST
 *	};
 *
 * Once the ``error_intern_tags'' function has been called, the ``tag'' field
 * should be used to access the tag object.
 */
typedef union ETagDataT {
	const char *name;
	ETagT *tag;
} ETagDataT;

/*
 * This is the type of an element in a vector of errors to be passed to the
 * ``error_intern_errors'' function.  The vector should be initialised with
 * the error names, severity levels, message text, and a pointer to a
 * non-function object (all surrounded by braces for
 * union initialisation).  The vector should be terminated by the
 * ``ERROR_END_ERROR_LIST'' macro, e.g.
 *
 *	static ErrorDataT errors [] = {
 *	    { {
 *		"error 1", ERROR_SEVERITY_ERROR,
 *		"error 1 occured at line ${line}", NULL
 *	    } }, ERROR_END_ERROR_LIST
 *	};
 *
 * Once the ``error_intern_errors'' function has been called, the ``error''
 * field should be used to access the error object.
 */
typedef union ErrorDataT {
	struct {
		const char *name;
		ESeverityT severity;
		char *message;
		void *data;
	} s;
	ErrorT *error;
} ErrorDataT;

/*
 * This is the type of an element in a vector of named strings to be passed to
 * the ``error_intern_strings'' function.  The vector should be initialised
 * with the string names and contents (all surrounded by braces
 * macros for union initialisation).  The vector should be terminated by the
 * ``ERROR_END_STRING_LIST'' macro, e.g.
 *
 *	static EStringDataT strings [] = {
 *		{ {"string name", "string contents"} },
 *		ERROR_END_STRING_LIST
 *	};
 *
 * Once the ``error_intern_strings'' function has been called, the ``estring''
 * field should be used to access the error string object.
 */
typedef union EStringDataT {
	struct {
		const char *name;
		const char *contents;
	} s;
	EStringT *estring;
} EStringDataT;

/*
 * This is the return type of the ``error_redefine_error'' function.
 */
typedef enum {
	ERROR_STATUS_BAD_MESSAGE,
	ERROR_STATUS_SUCCESS,
	ERROR_STATUS_BAD_ERROR
} ErrorStatusT;

/*
 * Exceptions:	XX_dalloc_no_memory
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
 */
void
error_init(const char *, ErrorInitProcP);

/*
 * This calls the error initialisation procedure if it has not already been
 * called.  This function should be called before ``error_report'' (actually,
 * it should be called before the error value that will be passed to that
 * function is accessed).
 */
void
error_call_init_proc(void);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function defines a tag with the specified name, and returns it.  The
 * name should not be modified or deallocated.  It is possible to define the
 * same tag more than once (but the same value will be returned each time).
 */
ETagT *
error_define_tag(const char *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function defines an error with the specified name, and returns it.
 * The name should not be modified or deallocated.  The severity level is used
 * to decide whether or not an error should be shown and whether or not the
 * program should abort, when the ``error_report'' function is called.  The
 * message is split up into a list of strings and tags, which will be printed
 * when the error is reported (the sequence "${tag name}" will be replaced by
 * the value of the tag when the error is reported).  The data is for use by
 * the program.
 */
ErrorT *
error_define_error(const char *, ESeverityT, const char *, void *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the name entries in the specified vector into error
 * tags.  The vector should be terminated by the macro ``ERROR_END_TAG_LIST''.
 * This function should only be called once on any vector.
 */
void
error_intern_tags(ETagDataT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the name entries in the specified vector into errors.
 * The vector should be terminated by the macro ``ERROR_END_ERROR_LIST''.
 * This function should only be called once on any vector.
 */
void
error_intern_errors(ErrorDataT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the error message for the error with the specified
 * name.  If necessary, the error initialisation procedure will be called to
 * initialise the errors before they are redefined.  If the error does not
 * exist, the function will return ``ERROR_STATUS_BAD_ERROR''.  If the error
 * message contains an unterminated tag, the function will return
 * ``ERROR_STATUS_BAD_MESSAGE''.  If the function succeeds, it will return
 * ``ERROR_STATUS_SUCCESS''.
 */
ErrorStatusT
error_redefine_error(const char *, const char *);

/*
 * This function returns the error with the specified name.  If the error does
 * not exist, it returns the null pointer.  If necessary, the error
 * initialisation procedure will be called to initialise the error messages
 * before they are looked up.
 */
ErrorT *
error_lookup_error(const char *);

/*
 * This function returns the data associated with the specified error.
 */
void *
error_data(ErrorT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function reports the specified error.  The procedure is used to print
 * out information for tags.  It is called with the output stream, the tag and
 * the specified closure.  If the procedure doesn't know about the tag, it
 * should ignore it.  The error message is only reported if the severity level
 * of the error is greater than or equal to the minimum severity level set by
 * the ``error_set_min_severity'' function.  The function will cause the
 * program to exit if the error's severity level is ``ERROR_SEVERITY_FATAL''
 * or higher.
 */
void
error_report(ErrorT *, ErrorprocP, void *);

void
error_set_min_report_severity(ESeverityT);

ESeverityT
error_get_min_report_severity(void);

/*
 * This function returns the severity of the error with the highest severity
 * that has been passed to ``error_report''.
 */
ESeverityT
error_max_reported_severity(void);

/*
 * This function sets the message to be displayed when the "${severity}" tag
 * is encountered for the specified severity.  Tags are not expanded in the
 * message. The message should not be modified or deallocated.
 */
void
error_set_severity_message(ESeverityT, const char *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function sets the error message prefix string.  This string is output
 * by ``error_display'' before outputting any actual error message.  Tags are
 * expanded, but only for the standard tags: "${program name}", "${severity}",
 * "${dollar}", "${this error name}", "${open brace}", and "${close brace}".
 * All other tags will be ignored.  The function returns true if the message
 * was valid, and false if there was an unterminated tag in the message.
 */
bool
error_set_prefix_message(const char *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function defines a named string with the specified name, and assigns
 * it the specified contents.  Neither the name nor the contents should be
 * modified or deallocated.  No tag splitting is performed on the contents.
 */
EStringT *
error_define_string(const char *, const char *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the name and contents entries in the specified vector
 * into named strings.  The vector should be terminated by the macro
 * ``ERROR_END_STRING_LIST''.  This function should only be called once on any
 * vector.
 */
void
error_intern_strings(EStringDataT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function changes the contents of the named string with the specified
 * name.  If the name does not exist, the function returns false, otherwise it
 * returns true.
 */
bool
error_redefine_string(const char *, const char *);

/*
 * This function returns the named string with the specified name.  If the
 * named string does not exist, the function returns the null pointer.
 */
EStringT *
error_lookup_string(const char *);

/*
 * This function returns the contents of the specified named string.  The
 * returned string should not be modified or deallocated.
 */
const char *
error_string_contents(EStringT *);

/*
 * This macro should form the last entry in a vector of ETagDataT objects.
 */
#define ERROR_END_TAG_LIST { NULL }

/*
 * This macro should form the last entry in a vector of ErrorDataT
 * objects.
 */
#define ERROR_END_ERROR_LIST { {NULL, (ESeverityT)0, NULL, NULL} }

/*
 * This macro should form the last entry in a vector of EStringDataT
 * objects.
 */
#define ERROR_END_STRING_LIST { {NULL, NULL} }

#endif /* !defined (H_ERROR) */
