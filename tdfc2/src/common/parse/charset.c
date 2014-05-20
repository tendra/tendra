#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

static void
swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a  = *b;
	*b  = tmp;
}

/* a value in the semi open interval [0..n) */
static unsigned
randn(unsigned n)
{
	return rand() % n; /* distributed evenly enough for us */
}

static void
range(char map[], char c, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) {
		map[i] = c + i; /* XXX: assumes A-Z, a-z are contigious */
	}
}

static void
permute(char map[], size_t n)
{
	size_t i, j;

	/* Fisher-Yates shuffle */
	for (i = 0; i < n; i++) {
		j = i + randn(n - i);
		assert(i <= j && j < n);

		swap(map + i, map + j);
	}
}

static void
reverse(char map[], size_t n)
{
	size_t i, j;

	for (i = 0, j = n - 1; i < n / 2; i++, j--) {
		swap(map + i, map + j);
	}
}

static void
rotate(char map[], size_t n, int d)
{
	if (d < 0) {
		d = n - abs(d);
	}

	/* An algorithm so famous it doesn't have a name */
	reverse(map, n);
	reverse(map, d);
	reverse(map + d, n - d);
}

static void
slide(char map[], size_t n, char a[], size_t l)
{
	size_t i, j;
	size_t d;

	assert(a >= map);
	assert(n >= l);

	/*
	 * Conceptually, this slides a[] all the way to the left edge
	 * of its containing range, and then right by a random delta,
	 * up to a maximum of the right edge. The result is that a[]
	 * can be moved around, but will never wrap over the end.
	 */

	i = a - map;
	j = n - l;

	d = randn(j + 1);
	assert(d <= j);

	rotate(map, n, d - i);
}

static int
x(char map[], FILE *f)
{
	char buf[1024];

	while (fgets(buf, sizeof buf, f) != NULL) {
		const char *p;
		int n;

buf[strcspn(buf, "\n")] = '\0'; /* XXX */

		for (p = buf; *p != '\0'; p += n) {
			unsigned char x;
			unsigned char v, v1, v2;
			unsigned char w1, w2;
			char c, c1, c2;
			int d;

			if (1 == sscanf(p, " %[#]%n", &c, &n)) {
				n += strcspn(p + n, "\n");
				continue;
			}

			if (2 == sscanf(p, " '%c' -> %hhu ; %n", &c, &v, &n)) {
				range(map + v, c, 1);
				continue;
			}

			if (2 == sscanf(p, " '\\0%hho' -> %hhu ; %n", &x, &v, &n)) {
				range(map + v, x, 1);
				continue;
			}

			if (2 == sscanf(p, " '\\%hhu' -> %hhu ; %n", &x, &v, &n)) {
				range(map + v, x, 1);
				continue;
			}

			if (2 == sscanf(p, " '\\%c' -> %hhu ; %n", &c, &v, &n)) {
				switch (c) {
				case '\\': c = '\\'; break;
				case '\'': c = '\''; break;
				case 't':  c = '\t'; break;
				case 'v':  c = '\v'; break;
				case 'f':  c = '\f'; break;
				case 'a':  c = '\a'; break;
				case 'b':  c = '\b'; break;
				case 'r':  c = '\r'; break;
				case 'n':  c = '\n'; break;
				/* TODO: others */
				default:
					goto error;
				}

				range(map + v, c, 1);
				continue;
			}

			if (2 == sscanf(p, " '\\x%hhx' -> %hhu ; %n", &x, &v, &n)) {
				range(map + v, x, 1);
				continue;
			}

			if (4 == sscanf(p, " '%c'..'%c' -> %hhu..%hhu ; %n", &c1, &c2, &v1, &v2, &n)) {
				size_t n;

				/* TODO: assert v2 >= v1 */

				/* TODO: assert character range is within A..Z, a..z or 0..9 only */

				if (abs(c2 - c1) != v2 - v1) {
					fprintf(stderr, "arity error: %c..%c -> %u..%u\n", c1, c2, v1, v2); /* XXX */
					goto error;
				}

				n = v2 - v1 + 1;

				if (c2 > c1) {
					range(map + v1, c1, n);
				} else {
					range(map + v1, c2, n);
					reverse(map + v1, n);
				}

				continue;
			}

			if (4 == sscanf(p, " %hhu..%hhu -> %hhu..%hhu ; %n", &w1, &w2, &v1, &v2, &n)) {
				size_t n;

				/* TODO: assert v2 >= v1 */

				if (abs(w2 - w1) != v2 - v1) {
					fprintf(stderr, "arity error: %u..%u -> %u..%u\n", w1, w2, v1, v2); /* XXX */
					goto error;
				}

				n = v2 - v1 + 1;

				if (w2 > w1) {
					range(map + v1, w1, n);
				} else {
					range(map + v1, w2, n);
					reverse(map + v1, n);
				}

				continue;
			}

			if (2 == sscanf(p, " permute %hhu..%hhu ; %n", &v1, &v2, &n)) {
				/* TODO: assert v2 >= v1 */
				permute(map + v1, v2 - v1 + 1);
				continue;
			}

			if (2 == sscanf(p, " reverse %hhu..%hhu ; %n", &v1, &v2, &d)) {
				reverse(map + v1, v2 - v1 + 1);
				continue;
			}

			if (3 == sscanf(p, " rotate %hhu..%hhu by %d ; %n", &v1, &v2, &d, &n)) {
				rotate(map + v1, v2 - v1 + 1, d);
				continue;
			}

			if (4 == sscanf(p, " slide %hhu..%hhu in %hhu..%hhu ; %n", &w1, &w2, &v1, &v2, &n)) {
				/* TODO: assert w1,w2 is within v1,v2 */
				slide(map + v1, v2 - v1 + 1, map + w1, w2 - w1 + 1);
				continue;
			}

			fprintf(stderr, "syntax error: %s\n", p);

error:

			return -1;
		}
	}

	/* TODO: validate constraints */

	return 0;
}

int main(int argc, char *argv[]) {
	char map[256] = { 1 };
	unsigned i;

	srand(argc == 2 ? atoi(argv[1]) : 0);

	if (-1 == x(map, stdin)) {
		perror("x");
	}

	for (i = 0; i < sizeof map; i++) {
		char c;

		c = map[i];

		if (!isspace(c) && isprint(c)) {
			printf(" %c", c);
		} else if (c == '\t') {
			printf("\\t");
		} else if (c == '\v') {
			printf("\\v");
		} else if (c == '\f') {
			printf("\\f");
		} else if (c == '\a') {
			printf("\\a");
		} else if (c == '\b') {
			printf("\\b");
		} else if (c == '\r') {
			printf("\\r");
		} else if (c == '\n') {
			printf("\\n");
		} else if (c <= 0x9) {
			printf("%02X", (unsigned char) c);
		} else {
			printf("%02X", (unsigned char) c);
		}

		printf("%s", (i + 1) % 16 ? " " : "\n");
	}

	return 0;
}

