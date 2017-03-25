#include <stdio.h>
#include <stdlib.h>

struct Matrix {
  int x;
  int y;
  int data[0]; /* Para facilitarnos la vida. */
};

int main( void ) {
  struct Matrix *m;
  int x, y;
  int total;
  int actual;

  fflush( stdin );
  printf( "Filas: " );
  scanf( "%d", &y );
  printf( "Columnas: " );
  scanf( "%d", &x );

  total = x * y;
  m = (struct Matrix *)malloc( sizeof( struct Matrix ) + ( sizeof( int ) * total ) );

  /* Pedimos los valores. */
  for( actual = 0; actual < total; ++actual ) {
    printf( "Valor de (%d, %d): ", actual / y, actual % y );
    scanf( "%d", &(m->data)[actual] );
  }

  /* Los imprimimos. */
  for( actual = 0; actual < total; ++actual ) {
    printf( "Valor de (%d, %d): %d\n", actual / y, actual % y, (m->data)[actual] );
  }

  return 0;
}