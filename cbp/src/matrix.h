#ifndef _MATRIX_H
#define _MATRIX_H

#include <sys/types.h>

typedef struct _tag_SquareMatrix {
  int n;
  void * a;
} SquareMatrix;

SquareMatrix * initialize_square_matrix ( int, size_t );
void free_square_matrix ( SquareMatrix * );
void matrix_fill ( SquareMatrix *, void(*)(SquareMatrix *, int, int, void *) );
void fill_matrix_random ( SquareMatrix *, int, int, void * );

#endif // _MATRIX_H

