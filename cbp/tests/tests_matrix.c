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
  print_matrix(mat);
  free_square_matrix ( mat );

  mat = initialize_square_matrix ( 19, sizeof(Int) );
  ASSERT(mat != NULL, "Wrong value for square matrix pointer after init.");
  ASSERT(mat->n == 19, "Wrong size for square matrix after init.");
  ASSERT(mat->a != NULL, "Matrix body NULL.");
  matrix_fill(mat, fill_matrix_random);
  print_matrix(mat);
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

  SquareMatrix * mat = initialize_square_matrix ( 22, sizeof(Int) );
  matrix_fill(mat, fill_matrix_sequential);
  print_matrix(mat);
  matrix_rotate(mat);

  half_width = ceil(mat->n/2.);
  for ( row = 0; row < half_width; row += 1 ) {
    for ( col = 0; col < half_width; col += 1 ) {
    }
  }

  print_matrix(mat);
  free_square_matrix ( mat );

  mat = initialize_square_matrix ( 23, sizeof(Int) );
  matrix_fill(mat, fill_matrix_sequential);
  print_matrix(mat);
  matrix_rotate(mat);
  print_matrix(mat);
  free_square_matrix ( mat );
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( initialize_matrix );
  TEST ( copy_matrix );
  TEST ( rotate_matrix );
}

