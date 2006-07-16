#include <stdio.h>

/*#define Ada_Main B0000 */
#define APPLY(m) QUOTE(m)
#define QUOTE(x) #x

extern void Ada_Main();

static int Result = 0;

void Report (char status)
{
  Result = status;
}

main ()
{
  Ada_Main();
  printf ("Result %s %d\n", APPLY(Ada_Main), Result);
  return Result != 1;
}
