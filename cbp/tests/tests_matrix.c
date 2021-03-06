#include <math.h>

#include "matrix.h"
#include "tests.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void initialize_matrix ( void )
{
  SquareMatrix * mat = initialize_square_matrix ( 22, sizeof(Int) );
  ASSERT(mat != NULL, "Wrong value for square matrix pointer after init.");
  ASSERT(mat->n == 22, "Wrong size for square matrix after init.");
  ASSERT(mat->a != NULL, "Matrix body NULL.");
  matrix_fill(mat, fill_matrix_random);
  // print_matrix(mat);
  free_square_matrix ( mat );

  mat = initialize_square_matrix ( 19, sizeof(Int) );
  ASSERT(mat != NULL, "Wrong value for square matrix pointer after init.");
  ASSERT(mat->n == 19, "Wrong size for square matrix after init.");
  ASSERT(mat->a != NULL, "Matrix body NULL.");
  matrix_fill(mat, fill_matrix_random);
  // print_matrix(mat);
  free_square_matrix ( mat );
}

void copy_matrix ( void )
{
  SquareMatrix * mat, * cpy;
  int row, col;

  mat = initialize_square_matrix ( 29, sizeof(Int) );
  matrix_fill(mat, fill_matrix_random);
  cpy = matrix_copy ( mat );

  ASSERT(cpy->n == mat->n, "Copy has wrong dimension.");
  ASSERT(cpy->a != mat->a, "Copy uses same memory as original.");

  for ( row = 0; row < mat->n; row += 1 ) {
    for ( col = 0; col < mat->n; col += 1 ) {
      ASSERT((mat->a + (col*mat->n + row)) != (cpy->a + (col*cpy->n + row)), "Copy cell has same address as original cell.");
      ASSERT( ((Int*)(mat->a + (col*mat->n + row)))->lol == ((Int*)(cpy->a + (col*cpy->n + row)))->lol, "Copy cell has different value than original cell.");
    }
  }

  free_square_matrix ( mat );
  free_square_matrix ( cpy );
}

void rotate_matrix ( void )
{
  int row, col, half_width;
  SquareMatrix * mat, * rot;

  mat = initialize_square_matrix ( 99, sizeof(Int) );
  matrix_fill(mat, fill_matrix_random);
  rot = matrix_copy(mat);
  matrix_rotate(rot);

  ASSERT ( rot->n == mat->n, "Wrong dimensions after copy/rotate." );

  print_matrix(mat);
  printf("\n");
  print_matrix(rot);

  half_width = ceil(mat->n/2.);
  for ( col = 0; col < half_width; col += 1 ) {
    for ( row = 0; row < half_width; row += 1 ) {
      ASSERT ( ((Int*)MatrixAt(rot, row, col))->lol == ((Int*)MatrixAt(mat, col, mat->n - 1 - row))->lol, "Wrong rotated value." );
      ASSERT ( ((Int*)MatrixAt(rot, col, rot->n - 1 - row))->lol == ((Int*)MatrixAt(mat, mat->n - 1 - row, mat->n - 1 - col))->lol, "Wrong rotated value." );
      ASSERT ( ((Int*)MatrixAt(rot, rot->n - 1 - row, rot->n - 1 - col))->lol == ((Int*)MatrixAt(mat, mat->n - 1 - col, row))->lol, "Wrong rotated value." );
      ASSERT ( ((Int*)MatrixAt(rot, rot->n - 1 - col, row))->lol == ((Int*)MatrixAt(mat, row, col))->lol, "Wrong rotated value." );
    }
  }

  free_square_matrix ( mat );
  free_square_matrix ( rot );

  mat = initialize_square_matrix ( 102, sizeof(Int) );
  matrix_fill(mat, fill_matrix_random);
  rot = matrix_copy(mat);
  matrix_rotate(rot);

  ASSERT ( rot->n == mat->n, "Wrong dimensions after copy/rotate." );

  print_matrix(mat);
  printf("\n");
  print_matrix(rot);

  half_width = ceil(mat->n/2.);
  for ( col = 0; col < half_width; col += 1 ) {
    for ( row = 0; row < half_width; row += 1 ) {
      ASSERT ( ((Int*)MatrixAt(rot, row, col))->lol == ((Int*)MatrixAt(mat, col, mat->n - 1 - row))->lol, "Wrong rotated value." );
      ASSERT ( ((Int*)MatrixAt(rot, col, rot->n - 1 - row))->lol == ((Int*)MatrixAt(mat, mat->n - 1 - row, mat->n - 1 - col))->lol, "Wrong rotated value." );
      ASSERT ( ((Int*)MatrixAt(rot, rot->n - 1 - row, rot->n - 1 - col))->lol == ((Int*)MatrixAt(mat, mat->n - 1 - col, row))->lol, "Wrong rotated value." );
      ASSERT ( ((Int*)MatrixAt(rot, rot->n - 1 - col, row))->lol == ((Int*)MatrixAt(mat, row, col))->lol, "Wrong rotated value." );
    }
  }

  free_square_matrix ( mat );
  free_square_matrix ( rot );
}

void do_tests ( void )
{
  srand(0);
  TEST ( sanity_check_zero );
  TEST ( initialize_matrix );
  TEST ( copy_matrix );
  TEST ( rotate_matrix );
}

