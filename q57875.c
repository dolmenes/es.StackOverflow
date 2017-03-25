#include <stdio.h>

#define SIZE 3
#define MAXVALS 100

int main( void ) {
  int Matrix[SIZE * SIZE];
  int Values[MAXVALS] = { 0 };

  int idx;

  // Solicitar datos.
  for( idx = 0; idx < SIZE * SIZE; ++idx ) {
    printf( "Valor de la celda ( %d, %d ): ", idx / SIZE, idx % SIZE );
    scanf( "%d", &Matrix[idx] );
  }

  // Contar las veces que aparece cada valor.
  for( idx = 0; idx < SIZE * SIZE; ++idx )
    ++Values[Matrix[idx]];

  printf( "\nNúmeros repetidos:\n" );

  // Mostrar los valores repetidos:
  for( idx = 0; idx < SIZE * SIZE; ++idx )
    if( Values[idx] > 1 )
      printf( "%d ( %d veces )\n", idx, Values[idx] );

  // Reemplazarlos por '0'.
  for( idx = 0; idx < SIZE * SIZE; ++idx )
    if( Values[Matrix[idx]] > 1 )
      Matrix[idx] = 0;

  printf( "Matriz final:\n" );
  // Mostrar la matriz final.
  for( idx = 0; idx < SIZE * SIZE; ++idx ) {
    if( !( idx % SIZE ) )
      printf( "\n" );

    printf( "%d ", Matrix[idx] );
  }

  printf( "\n" );

  return 0;
}