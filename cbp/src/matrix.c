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

void fill_matrix_random ( SquareMatrix * m, int row, int col, void * addr )
{
  int val = col*m->n + row;
  memcpy(addr, &val, sizeof(val));
}

void matrix_fill( SquareMatrix * m, void(*filler)(SquareMatrix *, int, int, void *) )
{
  int row, col;

  for ( col = 0; col < m->n; col += 1 ) {
    for ( row = 0; row < m->n; row += 1 ) {
      (*filler)(m, row, col, &(m->a[col*m->n + row]));
    }
  }
}

