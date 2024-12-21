#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int n;
    printf("Introduce el tamaño de las matrices (n x n): ");
    scanf("%d", &n);
    int* A = (int*)malloc(n * n * sizeof(int));
    int* B = (int*)malloc(n * n * sizeof(int));
    int* C = (int*)malloc(n * n * sizeof(int));
    srand(time(NULL));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = rand() % 10 + 1;
            B[i * n + j] = rand() % 10 + 1;
        }
    }

    double start_time = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
    double end_time = omp_get_wtime();
    printf("Producto de las matrices calculado.\n");
    printf("Tiempo de ejecución: %f segundos\n", end_time - start_time);

    free(A);
    free(B);
    free(C);

    return 0;
}
