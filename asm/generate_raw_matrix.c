#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int asmrotatematrix(void *, int);
void asmfillmatrixrandom(void *, int);
void asmfillmatrixsequential(void *, int);
void asmfillmatrixfixed(void *, int, int);
void testvalgrindboundschecking(void *, int);

int main ( int arfc, char ** arfv ) {
  int n, row, col;
  uint64_t * matrix;
  if ( arfc != 2 ) { printf("need a single argument specifying the dimension of the matrix to rotate\n"); return 1; }

  n = strtol(arfv[1], NULL, 10);

  matrix = malloc((sizeof*matrix)*n*n);

  if (!matrix) { printf("failed to allocate space for %dx%d elements\n", n, n); return 1; } 

  /*
  printf("matrix memory: %p-%p\n", (void*)matrix, (void*)(matrix+(n*n)));
  if (0) testvalgrindboundschecking(matrix, n*n);
  */

  srand(time(NULL));
  asmfillmatrixsequential(matrix, n);

  /*
  printf("Filled:\n");
  for ( col = 0; col < n; col += 1 ) {
    for ( row = 0; row < n; row += 1 ) {
      printf("%02" PRIx64 " ", matrix[ (col*n) + row ]);
    }
    printf("\n");
  }
  printf("\nRotated:\n");
  */

  asmrotatematrix(matrix, n);

  /*
  for ( col = 0; col < n; col += 1 ) {
    for ( row = 0; row < n; row += 1 ) {
      printf("%02" PRIx64 " ", matrix[ (col*n) + row ]);
    }
    printf("\n");
  }
  */

  free ( matrix );
  return 0;
}

