#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int n;
    int suma = 0;

    printf("Introduce el tamaño de la matriz (n x n): ");
    scanf("%d", &n);

    int* matriz = (int*)malloc(n * n * sizeof(int));

    srand(time(NULL));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i * n + j] = rand() % 10 + 1;
        }
    }

    double start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:suma) collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            suma += matriz[i * n + j];
        }
    }
    double end_time = omp_get_wtime();
    printf("Suma de los elementos: %d\n", suma);
    printf("Tiempo de ejecución: %f segundos\n", end_time - start_time);

    free(matriz);

    return 0;
}
