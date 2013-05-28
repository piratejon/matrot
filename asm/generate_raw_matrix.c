#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void asmrotatematrix(uint64_t *, int);
void asmfillmatrixrandom(void *, int);
void asmfillmatrixsequential(void *, int);
void asmfillmatrixfixed(void *, int, int);
void testvalgrindboundschecking(void *, int);

void crotatematrix(uint64_t * a, int n) {
  int r, c;
  int a0, a1, a2, a3;
  uint64_t tmp;

  for ( r = n >> 1; r >= 0; r -= 1 ) {
    a0 = r*(n+1);
    a1 = (n-1)*(r+1);
    a2 = (n*n) - (r*(n+1)) - 1;
    a3 = (n-r)*(n-1);

    for ( c = 0; c < n - 1 - (2*r); c += 1 ) {

      tmp = *(a+a3);
      *(a+a3) = *(a+a2);
      *(a+a2) = *(a+a1);
      *(a+a1) = *(a+a0);
      *(a+a0) = tmp;

      a0 += 1;
      a1 += n;
      a2 -= 1;
      a3 -= n;
    }
  }
}

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

  printf("Filled:\n");
  for ( col = 0; col < n; col += 1 ) {
    for ( row = 0; row < n; row += 1 ) {
      printf("%02" PRIx64 " ", matrix[ (col*n) + row ]);
    }
    printf("\n");
  }
  printf("\nRotated:\n");

  asmrotatematrix(matrix, n);

  for ( col = 0; col < n; col += 1 ) {
    for ( row = 0; row < n; row += 1 ) {
      printf("%02" PRIx64 " ", matrix[ (col*n) + row ]);
    }
    printf("\n");
  }

  free ( matrix );
  return 0;
}

