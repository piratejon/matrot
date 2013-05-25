#include <stdlib.h>
#include "matrix.h"

SquareMatrix * initialize_square_matrix ( int dimension, size_t size )
{
  SquareMatrix * out;
  void * lol = malloc((sizeof(*out))+(size*dimension*dimension));
  out = lol;
  out->n = dimension;
  out->a = lol+(sizeof*out);
  return out;
}

void free_square_matrix ( SquareMatrix * m )
{
  free(m);
}

void fill_matrix_random ( SquareMatrix * m, int row, int col, void * addr ) {
}

void matrix_fill( SquareMatrix * m, void(*filler)(SquareMatrix *, int, int, void *) )
{
}

