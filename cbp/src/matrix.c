#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
  memcpy(addr, &lol, m->s);
}

void fill_matrix_random ( SquareMatrix * m, int row, int col, void * addr )
{
  Int lol;
  lol.lol = rand() % 100;
  memcpy(addr, &lol, m->s);
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
      printf("%08x ", ((Int*)MatrixAt(m, row, col))->lol);
    }
    printf("\n");
  }
}

void matrix_cell_copy ( SquareMatrix * m, int dst_row, int dst_col, int src_row, int src_col ) {
  if ( dst_row == src_row && dst_col == src_col ) return;
  else {
    memcpy(MatrixAt(m, dst_row, dst_col), MatrixAt(m, src_row, src_col), m->s);
  }
}

void matrix_rotate ( SquareMatrix * m ) {
  int row, col, i_max, j_max, s;
  void * tmp;

  tmp = malloc(m->s);

  j_max = ceil(m->n / 2.);
  i_max = j_max - (m->n & 1);

  s = m->n - 1;

  for ( col = 0; col < j_max; col += 1 ) {
    for ( row = 0; row < i_max; row += 1 ) {
      memcpy(tmp, MatrixAt(m, row, col), m->s);
      matrix_cell_copy(m, row, col, col, s - row);
      matrix_cell_copy(m, col, s - row, s - row, s - col);
      matrix_cell_copy(m, s - row, s - col, s - col, row);
      memcpy(MatrixAt(m, s - col, row), tmp, m->s);
    }
  }

  /*
        tmp = self.a[i][j]
        self.a[i][j] = self.a[j][s-i]
        self.a[j][s-i] = self.a[s-i][s-j]
        self.a[s-i][s-j] = self.a[s-j][i]
        self.a[s-j][i] = tmp
        */

  free ( tmp );
}

SquareMatrix * matrix_copy ( SquareMatrix * orig )
{
  SquareMatrix * cpy;

  cpy = initialize_square_matrix ( orig->n, orig->s );

  memcpy ( cpy->a, orig->a, cpy->s * cpy->n * cpy->n );

  return cpy;
}

