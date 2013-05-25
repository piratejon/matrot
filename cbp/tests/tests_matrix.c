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

void rotate_matrix ( void )
{
  ASSERT(1==1, "lolwut");
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( initialize_matrix );
  TEST ( rotate_matrix );
}

