#include "matrix.h"
#include "tests.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
}

