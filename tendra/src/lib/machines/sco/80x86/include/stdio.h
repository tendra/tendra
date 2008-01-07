#ifndef __HACKED_SCO_STDIO_INCLUDED
#define __HACKED_SCO_STDIO_INCLUDED

#define __filbuf _filbuf
#define __flsbuf _flsbuf
#define __unlink unlink

#include_next <stdio.h>

#endif
