#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

SquareMatrix * initialize_square_matrix ( int dimension, size_t size )
{
  SquareMatrix * out;
  void * lol = malloc((sizeof(*out))+(size*dimension*dimension));
  out = lol;
  out->s = size;
  out->n = dimension;
  out->a = lol+(sizeof*out);
  return out;
}

void free_square_matrix ( SquareMatrix * m )
{
  free(m);
}

void fill_matrix_sequential ( SquareMatrix * m, int row, int col, void * addr )
{
  Int lol;
  lol.lol = col*m->n + row;
  memcpy(addr, &lol, sizeof(lol));
}

void fill_matrix_random ( SquareMatrix * m, int row, int col, void * addr )
{
  Int lol;
  lol.lol = rand();
  memcpy(addr, &lol, sizeof(lol));
}

void matrix_fill( SquareMatrix * m, void(*filler)(SquareMatrix *, int, int, void *) )
{
  int row, col;

  for ( col = 0; col < m->n; col += 1 ) {
    for ( row = 0; row < m->n; row += 1 ) {
      (*filler)(m, row, col, MatrixAt(m, row, col));
    }
  }
}

void print_matrix ( SquareMatrix * m )
{
  int row, col;
  for ( col = 0; col < m->n; col += 1 ) {
    for ( row = 0; row < m->n; row += 1 ) {
      printf("%3d ", ((Int*)MatrixAt(m, row, col))->lol);
    }
    printf("\n");
  }
}

void matrix_rotate ( SquareMatrix * m ) {
}

SquareMatrix * matrix_copy ( SquareMatrix * orig )
{
  int row, col;
  SquareMatrix * cpy;

  cpy = initialize_square_matrix ( orig->n, orig->s );

  memcpy ( cpy->a, orig->a, cpy->s * cpy->n * cpy->n );

  return cpy;
}

