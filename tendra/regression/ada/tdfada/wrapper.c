#include <stdio.h>

/*#define Ada_Main B0000 */
#define APPLY(m) QUOTE(m)
#define QUOTE(x) #x

extern void Ada_Init();
extern void Ada_Main();

static int Result = 55;

void Report (char status)
{
  Result = status;
}

void TDF_Exception (int code)
{
  printf ("TDF_Exception: %d\n", code);
}

main ()
{
  Ada_Init();
  Ada_Main();
  printf ("Result %s %d\n", APPLY(Ada_Main), Result);
  return Result != 1;
}
