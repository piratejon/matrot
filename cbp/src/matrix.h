#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct _tag_SquareMatrix {
  int n;
  void * a;
} SquareMatrix;

SquareMatrix * initialize_square_matrix ( int );
void free_square_matrix ( SquareMatrix * );

#endif // _MATRIX_H

