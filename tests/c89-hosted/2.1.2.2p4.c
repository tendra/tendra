#include <assert.h>
#include <stddef.h>
#include <string.h>

int main(int argc, char *argv[]) {
	/*
	 * S2.1.2.2p4.1 "The value of argc shall be nonnegative."
	 */
	assert(argc >= 0);

	/*
	 * S2.1.2.2p4.2 "argv[argc] shall be a null pointer."
	 */
	assert(argv[argc] == NULL);

	/*
	 * S2.1.2.2p4.3 "If the value of argc is greater than zero, the array members
	 * argv[0] through argv[argc-1] inclusive shall contain pointers to
	 * strings, which are given implementation-defined values by the host
	 * environment prior to program startup."
	 */
	if (argc > 0) {
		int i;
		for (i = 0; i <= argc - 1; i++) {
			assert(strlen(argv[i]) >= 0);
		}
	}

	/*
	 * 2.1.2.2p4.4 "If the value of argc is greater than zero,
	 * the string pointed to by argv[0] represents the program name;
	 * argv[0][0] shall be the null character if the program name
	 * is not available from the host environment."
	 */
	/* UNTESTED: "argv[0] represents the program name" */
	if (argc > 0) {
		assert(strlen(argv[0]) > 0 || argv[0][0] == '\0');
	}

	/*
	 * 2.1.2.2p4.4 "If the value of argc is greater than one, the strings
	 * pointed to by argv[1] through argv[argc-1] represent the program
	 * parameters."
	 */
	/* UNTESTED: "argv[1] through argv[argc-1] represent the program parameters" */
	if (argc > 0) {
		int i;
		for (i = 1; i <= argc - 1; i++) {
			assert(strlen(argv[i]) >= 0);
		}
	}

	/*
	 * 2.1.2.2p4.5 "The parameters argc and argv and the strings pointed
	 * to by the argv array shall be modifiable by the program ..."
	 */
	if (argc > 0) {
		unsigned int z;
		char *p;
		int i;
		z = 0U;
		for (i = 0; i <= argc - 1; i++) {
			for (p = argv[i]; *p != '\0'; p++) {
				*p = "abcdef"[z++ % 6];
			}
		}
	}

	/*
	 * 2.1.2.2p4.5 "... and retain their last-stored values between program
	 * startup and program termination."
	 */
	if (argc > 0) {
		unsigned int z;
		char *p;
		int i;
		z = 0U;
		for (i = 0; i <= argc - 1; i++) {
			for (p = argv[i]; *p != '\0'; p++) {
				assert(*p == "abcdef"[z++ % 6]);
			}
		}
	}

	return 0;
}

