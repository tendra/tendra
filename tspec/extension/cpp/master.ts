# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$UNIQUE = 1 ;
$VERSION = "1.1" ;

# C++ ABI tokens
+IMPLEMENT "cpp", "dummy/basic.h.ts" ;
+IMPLEMENT "cpp", "dummy/ptr_func.h.ts" ;
+IMPLEMENT "cpp", "dummy/ptr_mem.h.ts" ;
+IMPLEMENT "cpp", "dummy/throw.h.ts" ;
+IMPLEMENT "cpp", "dummy/vtable.h.ts" ;

# Standard C headers
+IMPLEMENT "cpp", "cassert.ts" ;
+IMPLEMENT "cpp", "cctype.ts" ;
+IMPLEMENT "cpp", "cerrno.ts" ;
+IMPLEMENT "cpp", "cfloat.ts" ;
+IMPLEMENT "cpp", "climits.ts" ;
+IMPLEMENT "cpp", "clocale.ts" ;
+IMPLEMENT "cpp", "cmath.ts" ;
+IMPLEMENT "cpp", "csetjmp.ts" ;
+IMPLEMENT "cpp", "csignal.ts" ;
+IMPLEMENT "cpp", "cstdarg.ts" ;
+IMPLEMENT "cpp", "cstddef.ts" ;
+IMPLEMENT "cpp", "cstdio.ts" ;
+IMPLEMENT "cpp", "cstdlib.ts" ;
+IMPLEMENT "cpp", "cstring.ts" ;
+IMPLEMENT "cpp", "ctime.ts" ;
+IMPLEMENT "cpp", "cwchar.ts" ;
+IMPLEMENT "cpp", "cwctype.ts" ;

# Standard C++ headers
+IMPLEMENT "cpp", "algorithm.ts" ;
+IMPLEMENT "cpp", "bitset.ts" ;
+IMPLEMENT "cpp", "complex.ts" ;
+IMPLEMENT "cpp", "deque.ts" ;
+IMPLEMENT "cpp", "exception.ts" ;
+IMPLEMENT "cpp", "fstream.ts" ;
+IMPLEMENT "cpp", "functional.ts" ;
+IMPLEMENT "cpp", "iomanip.ts" ;
+IMPLEMENT "cpp", "ios.ts" ;
+IMPLEMENT "cpp", "iosfwd.ts" ;
+IMPLEMENT "cpp", "iostream.ts" ;
+IMPLEMENT "cpp", "istream.ts" ;
+IMPLEMENT "cpp", "iterator.ts" ;
+IMPLEMENT "cpp", "limits.ts" ;
+IMPLEMENT "cpp", "list.ts" ;
+IMPLEMENT "cpp", "locale.ts" ;
+IMPLEMENT "cpp", "map.ts" ;
+IMPLEMENT "cpp", "memory.ts" ;
+IMPLEMENT "cpp", "new.ts" ;
+IMPLEMENT "cpp", "numeric.ts" ;
+IMPLEMENT "cpp", "ostream.ts" ;
+IMPLEMENT "cpp", "queue.ts" ;
+IMPLEMENT "cpp", "set.ts" ;
+IMPLEMENT "cpp", "sstream.ts" ;
+IMPLEMENT "cpp", "stack.ts" ;
+IMPLEMENT "cpp", "stdexcept.ts" ;
+IMPLEMENT "cpp", "streambuf.ts" ;
+IMPLEMENT "cpp", "string.ts" ;
+IMPLEMENT "cpp", "typeinfo.ts" ;
+IMPLEMENT "cpp", "utility.ts" ;
+IMPLEMENT "cpp", "valarray.ts" ;
+IMPLEMENT "cpp", "vector.ts" ;

# C compatibility headers
+IMPLEMENT "cpp", "assert.h.ts" ;
+IMPLEMENT "cpp", "ctype.h.ts" ;
+IMPLEMENT "cpp", "errno.h.ts" ;
+IMPLEMENT "cpp", "float.h.ts" ;
+IMPLEMENT "cpp", "iso646.h.ts" ;
+IMPLEMENT "cpp", "limits.h.ts" ;
+IMPLEMENT "cpp", "locale.h.ts" ;
+IMPLEMENT "cpp", "math.h.ts" ;
+IMPLEMENT "cpp", "setjmp.h.ts" ;
+IMPLEMENT "cpp", "signal.h.ts" ;
+IMPLEMENT "cpp", "stdarg.h.ts" ;
+IMPLEMENT "cpp", "stddef.h.ts" ;
+IMPLEMENT "cpp", "stdio.h.ts" ;
+IMPLEMENT "cpp", "stdlib.h.ts" ;
+IMPLEMENT "cpp", "string.h.ts" ;
+IMPLEMENT "cpp", "time.h.ts" ;
+IMPLEMENT "cpp", "wchar.h.ts" ;
+IMPLEMENT "cpp", "wctype.h.ts" ;

# C++ compatibility headers
+IMPLEMENT "cpp", "iomanip.h.ts" ;
+IMPLEMENT "cpp", "iostream.h.ts" ;
+IMPLEMENT "cpp", "new.h.ts" ;
+IMPLEMENT "cpp", "strstream.h.ts" ;
