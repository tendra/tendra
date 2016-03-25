/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * exception.h - Exception handling.
 *
 * This file specifies the interface to an exception handling facility.  The
 * facility is built on top of the ANSI C non-local exit mechanism (setjmp
 * and longjmp), and should be used in preference to it.  The mechanism is
 * implemented as a set of macros.
 *
 *
 * This file requires that two functions are provided:
 *
 *	void unhandled(ExceptionT *, char *, unsigned);
 *	void corrupt_handler(char *, unsigned);
 *
 * These are set by exception_unhandled() and exception_corrupt_handler()
 * respectively.
 *
 * The first of these functions will be called if there is an unhandled
 * exception.  The exception will be given as an argument, along with the name
 * of the file, and the line within that file that the exception was thrown
 * from.  The second function will be called if a corrupt exception handler
 * stack is detected.  It will be called with the file name, and line number
 * where the corrupt handler was established.  Neither of these functions
 * should return.  If either function raises an exception, the program will
 * abort.
 *
 * If the PO_EXCEPTION_STACK_DIRECTION macro is defined, then an attempt
 * is made to detect corrupt exception handler stacks (almost certainly due to
 * missing or excessive calls to the UNHANDLE macro).  If the macro is
 * defined to be less than zero, it is assumed that the (system) stack grows
 * downwards; if it defined to be greater than zero, then it is assumed that
 * the (system) stack grows upwards; if it is defined to be zero, then a
 * weaker check that doesn't use the stack direction is used.
 */

#ifndef H_EXCEPTION
#define H_EXCEPTION

#include <setjmp.h>

#include <exds/common.h>


/*
 * This is the type of an exception.  Exceptions are initialised using the
 * EXCEPTION macro (see later).  Once initialised, the exception should
 * not be changed.
 */
typedef char ExceptionT;

/*
 * This type is used internally to store data about the exception being
 * thrown.
 * TODO is this private?
 */
typedef struct ThrowDataT ThrowDataT;
struct ThrowDataT {
	char *exception;
	void *data;
	unsigned line;
	char *file;
};

/*
 * This type is used internally to store data about the exception handler
 * stack.
 * TODO is this private?
 */
typedef struct HandlerT HandlerT;
struct HandlerT {
#ifdef PO_EXCEPTION_STACK_DIRECTION
	unsigned magic_start;
	char *file;
	unsigned line;
#endif /* defined (PO_EXCEPTION_STACK_DIRECTION) */
	HandlerT *next;
	jmp_buf buffer;
#ifdef PO_EXCEPTION_STACK_DIRECTION
	unsigned magic_end;
#endif /* defined (PO_EXCEPTION_STACK_DIRECTION) */
};

/*
 * Set the default behaviour for unhandled exceptions.
 *
 * This must be called before any exception is thrown.
 */
void
exception_unhandled(void (*handler)(ExceptionT *e, const char *file,
	unsigned line));


/*
 * Set the default behaviour for corrupted exception handlers.
 *
 * This must be called before any exception is thrown.
 */
void
exception_corrupt_handler(void (*handler)(const char *file, unsigned line));


/*
 * This function returns the name of the specified exception.  The return
 * value should not be modified or deallocated.
 */
const char *exception_name(ExceptionT *);

extern HandlerT *X__exception_handler_stack;
extern ThrowDataT X__exception_throw_data;
NORETURN X__exception_throw(void);

/*
 * This macro is used to initialise an exception, e.g.:
 *
 *	ExceptionT * XX_exception = EXCEPTION ("an exception");
 *
 * This creates an exception object called XX_exception.  The string used
 * as an argument to the EXCEPTION macro is a description of the
 * exception.  This string is used as a message to be printed when an
 * exception is thrown but not handled.  It can also be accessed through the
 * exception_name function.  The string should be different for each
 * exception (the string content should be different as well, as some
 * compilers put strings with the same content into the same memory location,
 * and the address of the string is used to make the exception unique).
 *
 * Exceptions should only be defined in global scope. Exceptions with
 * automatic scope may cause problems if they are not handled within their
 * scope.
 */
#define EXCEPTION(name) name

/*
 * This macro raises an exception.  The specified exception is thrown, and
 * control passes to the innermost exception handler.  If there are no
 * exception handlers, a message is printed and the program is aborted.
 */
#define THROW(exc) { \
	X__exception_throw_data.exception = (exc); \
	X__exception_throw_data.data      = NULL; \
	X__exception_throw_data.line      = __LINE__; \
	X__exception_throw_data.file      = __FILE__; \
	X__exception_throw(); }

/*
 * This macro raises an exception.  The specified exception is thrown, and
 * control passes to the innermost exception handler.  If there are no
 * exception handlers, a message is printed and the program is aborted.
 * Unlike the THROW macro, this macro also passes a value to the exception
 * handler.  The value should be a pointer to a non-function object.  The
 * object pointed to should not be automatically allocated (unless it is
 * guaranteed to be caught within its scope).
 */
#define THROW_VALUE(exc,val) { \
	X__exception_throw_data.exception = (exc); \
	X__exception_throw_data.data      = ((val)); \
	X__exception_throw_data.line      = __LINE__; \
	X__exception_throw_data.file      = __FILE__; \
	X__exception_throw(); }

#ifdef PO_EXCEPTION_STACK_DIRECTION
# define X__EXCEPTION_MAGIC (0x1234)

/*
 * These macros are used to handle an exception. They should be used as in the
 * following example:
 *
 *	HANDLE
 *		normal code - possible variable corruption here
 *	WITH
 *		exception handler code
 *	END_HANDLE
 *
 * The HANDLE macro begins an exception handler construct.  This should be
 * followed by the normal code to be executed.  The WITH macro begins the
 * exception handler region.  This macro is followed by the code to handle the
 * exception.  The END_HANDLE macro terminates the exception handler
 * construct.
 *
 * If any part of the construct is omitted, the code will not compile, or the
 * exception handler stack will become corrupted at run time.
 *
 * The exception handler is removed by the WITH macro, so throwing another
 * exception in the exception handler region (between the WITH macro and
 * the END_HANDLE macro) will cause the next error handler to be invoked.
 *
 * When an exception is caught, it is possible that some of the variables in
 * scope will not contain the correct value.  It is best to declare any
 * variables you wish to use inside an exception handler as volatile.
 * This program assumes that what the ANSI C library specifiaction says about
 * setjmp and longjmp holds, so only non-volatile automatic variables
 * in the indicated region should become corrupted.
 */
# define HANDLE { \
	HandlerT X___exception_handler; \
	X___exception_handler.magic_start = X__EXCEPTION_MAGIC; \
	X___exception_handler.file        = __FILE__; \
	X___exception_handler.line        = __LINE__; \
	X___exception_handler.next        = X__exception_handler_stack; \
	X___exception_handler.magic_end   = X__EXCEPTION_MAGIC; \
	X__exception_handler_stack        = &X___exception_handler; \
	if (!setjmp(X___exception_handler.buffer)) {
#else
# define HANDLE { \
	HandlerT X___exception_handler; \
	X___exception_handler.next = X__exception_handler_stack; \
	X__exception_handler_stack = &X___exception_handler; \
	if (!setjmp(X___exception_handler.buffer)) {
#endif /* defined (PO_EXCEPTION_STACK_DIRECTION) */

#define WITH \
		X__exception_handler_stack = X___exception_handler.next; \
	} else { \
		X__exception_handler_stack = X___exception_handler.next; {

#define END_HANDLE }}}

/*
 * This macro returns the current exception.  It should only be used within
 * the exception handler region (between the WITH and END_HANDLE
 * macros).
 */
#define EXCEPTION_EXCEPTION() X__exception_throw_data.exception

/*
 * This macro returns the data that was thrown with the current exception.  It
 * should only be used within the exception handler region (between the
 * WITH and END_HANDLE macros).
 */
#define EXCEPTION_VALUE() X__exception_throw_data.data

/*
 * This macro returns the line from which the current exception was thrown.
 * It should only be used within the exception handler region (between the
 * WITH and END_HANDLE macros).
 */
#define EXCEPTION_LINE() X__exception_throw_data.line

/*
 * This macro returns the file from which the current exception was thrown.
 * It should only be used within the exception handler region (between the
 * WITH and END_HANDLE macros).
 */
#define EXCEPTION_FILE() X__exception_throw_data.file

/*
 * This macro should only be used in the exception handler region (between the
 * WITH and END_HANDLE macros), and causes the current exception to be
 * rethrown (to be caught by the next outermost exception handler).
 */
#define RETHROW() X__exception_throw();

/*
 * This macro MUST be used before using a goto or return that would
 * cause the normal code region (between the HANDLE and WITH macros)
 * to be exited (otherwise the exception handler stack will become corrupt at
 * run time).
 */
#define UNHANDLE X__exception_handler_stack = X___exception_handler.next;

#endif /* !defined (H_EXCEPTION) */
