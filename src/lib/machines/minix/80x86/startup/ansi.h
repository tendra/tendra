#pragma TenDRA begin
#pragma TenDRA no external declaration allow
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow

/* esto debería hacerlo tcc, pero lo hacemos nosotros por si acaso,
   ya se quejará si no le gusta; es importante porque las características
   ansi, que se seleccionan con la definición _ANSI, se ponen cuando
   esta definición vale 1 (ver /usr/include/ansi.h) */

#define __STDC__	1

/* todo lo siguiente es absolutamente necesario, ya que lo hace el ACD,
   y las macros _EM_*SIZE se utilizan explícitamente en muchas cabeceras,
   tanto ansi como posix */

#define __minix		1
#define __i386		1

#define _EM_WSIZE	4
#define _EM_PSIZE	4
#define _EM_SSIZE	2
#define _EM_LSIZE	4
#define _EM_FSIZE	4
#define _EM_DSIZE	8

/* esto se necesita en algunos sitios, pero sólo se asigna (en minix/config.h)
   si __ACK__ está definido, y ese no es nuestro caso, así que tenemos que
   hacerlo manualmente */

#define _WORD_SIZE	_EM_WSIZE

/* finalmente, recordemos que estos ficheros startup serán los que usará el
   compilador para predefinir macros en la instalación final, así que conviene
   disponer de estas otras dos macros */

#define unix		1
#define __unix		1
