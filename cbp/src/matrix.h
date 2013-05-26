#ifndef _MATRIX_H
#define _MATRIX_H

#include <sys/types.h>

typedef struct _tag_SquareMatrix {
  int n;
  size_t s;
  void * a;
} SquareMatrix;

typedef struct _tag_int {
  int lol;
} Int;

SquareMatrix * initialize_square_matrix ( int, size_t );
void free_square_matrix ( SquareMatrix * );
void matrix_fill ( SquareMatrix *, void(*)(SquareMatrix *, int, int, void *) );
void print_matrix ( SquareMatrix * );
void matrix_rotate ( SquareMatrix * );
SquareMatrix * matrix_copy ( SquareMatrix * );

void fill_matrix_random ( SquareMatrix *, int, int, void * );
void fill_matrix_sequential ( SquareMatrix * m, int row, int col, void * addr );

#endif // _MATRIX_H

