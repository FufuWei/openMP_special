#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main()
{
    int i, j, k;
    double A[N][N + 1], x[N], tmp;

    // Generate a random NxN+1 matrix
    srand(0);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N + 1; j++) {
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }

    // Forward elimination
    for (k = 0; k < N - 1; k++) {
#pragma omp parallel for private(i, j, tmp)
        for (i = k + 1; i < N; i++) {
            tmp = A[i][k] / A[k][k];
            for (j = k + 1; j < N + 1; j++) {
                A[i][j] -= tmp * A[k][j];
            }
            A[i][k] = 0;
        }
    }

    // Back substitution
    for (i = N - 1; i >= 0; i--) {
        tmp = A[i][N];
        for (j = i + 1; j < N; j++) {
            tmp -= A[i][j] * x[j];
        }
        x[i] = tmp / A[i][i];
    }

    // Print the solution
    for (i = 0; i < N; i++) {
        printf("%f ", x[i]);
    }
    printf("\n");

    return 0;
}
