/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * An example of exception handling.
 *
 * These examples attempt to provide a tour of the most obvious features,
 * without digressing into minutiae.
 *
 * Exceptions may be nested to form stacks
 * (these examples don't nest deeply, for brevity). They may be thrown from
 * other functions (which is not illustrated, again for brevity).
 *
 * The reader is encouraged to experiment by modifying this file.
 */

#include <stdlib.h>
#include <stdio.h>

#include <exds/common.h>
#include <exds/exception.h>

/*
 * Three example user-defined exceptions with which to demonstrate.
 */
ExceptionT *x_a = EXCEPTION("exception a");
ExceptionT *x_b = EXCEPTION("exception b");
ExceptionT *x_c = EXCEPTION("exception c");

/*
 * Top-level handler, as required by exception.h. This should not return.
 */
static void unhandled(ExceptionT *e, const char *file, unsigned line) {
	printf("unhandled exception \"%s\": %s (%d)\n",
		exception_name(e), file, line);
	exit(EXIT_FAILURE);
}

int main(void) {
	exception_unhandled(unhandled);

	/*
	 * Throwing an exception and catching it.
	 */
	HANDLE {

		printf("0: About to throw \"%s\" from %s:%d\n",
			exception_name(x_a), __FILE__, __LINE__ + 2);

		THROW(x_a);

		printf("1: \"%s\" thrown; this should not be reached\n",
			exception_name(x_a));

	} WITH {

		printf("\t2: Handling \"%s\" from %s:%d\n",
			exception_name(EXCEPTION_EXCEPTION()),
			EXCEPTION_FILE(), EXCEPTION_LINE());

	} END_HANDLE;


	/*
	 * Throwing an exception, catching it, and rethrowing it for an
	 * outer handler.
	 */
	HANDLE {

		HANDLE {

			printf("3: About to throw \"%s\" from %s:%d\n",
				exception_name(x_a), __FILE__, __LINE__ + 2);

			THROW(x_a);

			printf("4: \"%s\" thrown; this should not be reached\n",
				exception_name(x_a));

		} WITH {

			printf("\t5: Handling \"%s\" from %s:%d\n",
				exception_name(EXCEPTION_EXCEPTION()),
				EXCEPTION_FILE(), EXCEPTION_LINE());

			printf("\t6: About to rethrow \"%s\" from %s:%d\n",
				exception_name(EXCEPTION_EXCEPTION()),
				__FILE__, __LINE__ + 2);

			RETHROW();

			printf("7: \"%s\" rethrown; this should not be reached\n",
				exception_name(EXCEPTION_EXCEPTION()));

		} END_HANDLE;

	} WITH {

		printf("\t8: Handling \"%s\" from %s:%d\n",
			exception_name(EXCEPTION_EXCEPTION()),
			EXCEPTION_FILE(), EXCEPTION_LINE());

	} END_HANDLE;


	/*
	 * Throwing an exception, catching it, and throwing another for an
	 * outer handler.
	 */
	HANDLE {

		HANDLE {

			printf("9: About to throw \"%s\" from %s:%d\n",
				exception_name(x_a), __FILE__, __LINE__ + 2);

			THROW(x_a);

			printf("10: \"%s\" thrown; this should not be reached\n",
				exception_name(x_a));

		} WITH {

			printf("\t11: Handling \"%s\" from %s:%d\n",
				exception_name(EXCEPTION_EXCEPTION()),
				EXCEPTION_FILE(), EXCEPTION_LINE());

			printf("\t12: About to throw \"%s\" from %s:%d\n",
				exception_name(x_b),
				__FILE__, __LINE__ + 2);

			THROW(x_b);

			printf("13: \"%s\" thrown; this should not be reached\n",
				exception_name(x_b));

		} END_HANDLE;

	} WITH {

		printf("\t14: Handling \"%s\" from %s:%d\n",
			exception_name(EXCEPTION_EXCEPTION()),
			EXCEPTION_FILE(), EXCEPTION_LINE());

	} END_HANDLE;


	/*
	 * Throwing an exception with a value.
	 */
	HANDLE {

		int i = 57;

		printf("15: About to throw \"%s\"/%d from %s:%d\n",
			exception_name(x_a), i, __FILE__, __LINE__ + 2);

		THROW_VALUE(x_a, &i);

		printf("16: \"%s\" thrown; this should not be reached\n",
			exception_name(x_a));

	} WITH {

		printf("\t17: Handling \"%s\"/%d from %s:%d\n",
			exception_name(EXCEPTION_EXCEPTION()), *(int *)EXCEPTION_VALUE(),
			EXCEPTION_FILE(), EXCEPTION_LINE());

	} END_HANDLE;


	/*
	 * Throwing an exception and passing on to an outer handler.
	 */
	HANDLE {

		HANDLE {

			/* Imagine code which might throw x_a or x_b here */

			printf("18: About to throw \"%s\" from %s:%d\n",
				exception_name(x_a), __FILE__, __LINE__ + 2);

			THROW(x_a);

		} WITH {

			if(EXCEPTION_EXCEPTION() == x_b) {
				/*
				 * This handler is intended for x_b (which isn't thrown above,
				 * but imagine it could be).
				 */

				printf("\t19: Handling \"%s\" from %s:%d; this should not be reached\n",
					exception_name(EXCEPTION_EXCEPTION()),
					EXCEPTION_FILE(), EXCEPTION_LINE());
			} else {
				/*
				 * Otherwise, this is an exception we don't handle; pass it
				 * along for the next handler in the stack.
				 */

				printf("\t20: About to rethrow \"%s\" from %s:%d\n",
					exception_name(EXCEPTION_EXCEPTION()),
					__FILE__, __LINE__ + 2);

				RETHROW();
			}

		} END_HANDLE;

	} WITH {

		/*
		 * Only x_a should reach here.
		 */

		printf("\t21: Handling \"%s\" from %s:%d\n",
			exception_name(EXCEPTION_EXCEPTION()),
			EXCEPTION_FILE(), EXCEPTION_LINE());

	} END_HANDLE;


	/*
	 * A less verbose example of handling one of several exceptions, and passing
	 * on to an outer handler. This serves to demonstrate a slightly more
	 * compact formatting for conditions in handlers:
	 *
	 *  HANDLE {
	 *      ...
	 *  } WITH if(EXCEPTION_EXCEPTION() == ...) {
	 *      ...
	 *  } else if(EXCEPTION_EXCEPTION() == ...) {
	 *      ...
	 *  } else RETHROW() END_HANDLE;
	 *
	 */
	HANDLE {

		HANDLE {

			/* Imagine code which might throw x_a or x_b here */

			printf("22: About to throw \"%s\" from %s:%d\n",
				exception_name(x_a), __FILE__, __LINE__ + 2);

			THROW(x_a);

		} WITH if(EXCEPTION_EXCEPTION() == x_b) {

			/*
			 * This handler is intended for x_b (which isn't thrown above,
			 * but imagine it could be).
			 */

			printf("\t23: Handling \"%s\" from %s:%d; this should not be reached\n",
				exception_name(EXCEPTION_EXCEPTION()),
				EXCEPTION_FILE(), EXCEPTION_LINE());

		} else if(EXCEPTION_EXCEPTION() == x_c) {

			/*
			 * This handler is intended for x_c (which isn't thrown above,
			 * but imagine it could be).
			 */

			printf("\t24: Handling \"%s\" from %s:%d; this should not be reached\n",
				exception_name(EXCEPTION_EXCEPTION()),
				EXCEPTION_FILE(), EXCEPTION_LINE());

		} else RETHROW() END_HANDLE;

	} WITH {

		/*
		 * Only x_a should reach here.
		 */

		printf("\t25: Handling \"%s\" from %s:%d\n",
			exception_name(EXCEPTION_EXCEPTION()),
			EXCEPTION_FILE(), EXCEPTION_LINE());

	} END_HANDLE;

	return 0;
}

