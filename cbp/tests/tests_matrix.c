#include "matrix.h"
#include "tests.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void initialize_matrix ( void )
{
  SquareMatrix * mat = initialize_square_matrix ( 22 );
  ASSERT(mat == NULL, "Wrong value for square matrix pointer after init.");
  free_square_matrix ( mat );

  mat = initialize_square_matrix ( 19 );
  ASSERT(mat == NULL, "Wrong value for square matrix pointer after init.");
  free_square_matrix ( mat );
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( initialize_matrix );
}

