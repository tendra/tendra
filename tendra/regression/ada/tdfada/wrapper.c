#include <stdio.h>

/*#define Ada_Main B0000 */

extern void Ada_Main();

static int Result = 0;

void Report (char status)
{
  Result = status;
}

main ()
{
  Ada_Main();
  printf ("Result %d\n", Result);
  return Result != 1;
}
