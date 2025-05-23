#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Interfaz.h"

static double MEM_CHUNK[DATA_SIZE];
double *mA, *mB, *mC;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        return -1;
    }

    int SZ = atoi(argv[1]);
    int n_threads = atoi(argv[2]);

    pthread_t p[n_threads];
    pthread_attr_t atrMM;
    struct timeval start, stop;

    mA = MEM_CHUNK;
    mB = mA + SZ * SZ;
    mC = mB + SZ * SZ;

    llenar_matriz(SZ, mA, mB, mC);
    print_matrix(SZ, mA);
    print_matrix(SZ, mB);

    inicial_tiempo(&start);

    pthread_mutex_init(&MM_mutex, NULL);
    pthread_attr_init(&atrMM);
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *)malloc(sizeof(struct parametros));
        datos->idH = j;
        datos->nH = n_threads;
        datos->N = SZ;
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos);
    }

    for (int j = 0; j < n_threads; j++) {
        pthread_join(p[j], NULL);
    }

    final_tiempo(&start, &stop);
    print_matrix(SZ, mC);

    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);
    return 0;
}