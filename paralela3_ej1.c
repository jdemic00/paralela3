#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int n;
    int suma = 0;

    printf("Introduce el tamaño del vector: ");
    scanf("%d", &n);

    int* vector = (int*)malloc(n * sizeof(int));
    if (vector == NULL) {
        printf("Error al asignar memoria.\n");
        return -1;
    }

    srand(time(NULL));

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        vector[i] = rand() % 100 + 1; 

    double start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:suma)
    for (int i = 0; i < n; i++) {
        suma += vector[i];
    }
    double end_time = omp_get_wtime();
    printf("Suma con reduction: %d, Tiempo: %f segundos\n", suma, end_time - start_time);

    suma = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp atomic
        suma += vector[i];
    }
    end_time = omp_get_wtime();
    printf("Suma con atomic: %d, Tiempo: %f segundos\n", suma, end_time - start_time);

    suma = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp critical
        {
            suma += vector[i];
        }
    }
    end_time = omp_get_wtime();
    printf("Suma con critical: %d, Tiempo: %f segundos\n", suma, end_time - start_time);

    free(vector);

    return 0;
}
