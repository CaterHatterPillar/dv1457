#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi */

extern void start_game(int len, int n_apples);

int main(int argc, char *argv[])
{
  int len, apples;

  if (argc < 3)
    {
      printf("Usage: %s LEN APPLES\n", argv[0]);
      return 1;
    }

  len = atoi(argv[1]);
  apples = atoi(argv[2]);

  if( apples>100 )
  {
    printf( "Can only support up to 100 apples!\n" );
    return 1;
  }

  start_game(len, apples);

  return 0;
}