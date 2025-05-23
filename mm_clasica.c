#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "Interfaz.h"

pthread_mutex_t MM_mutex;

void llenar_matriz(int SZ, double *mA, double *mB, double *mC) {
    srand48(time(NULL));
    for (int i = 0; i < SZ * SZ; i++) {
        mA[i] = 1.1 * i;
        mB[i] = 2.2 * i;
        mC[i] = 0;
    }
}

void print_matrix(int sz, double *matriz) {
    if (sz < 12) {
        for (int i = 0; i < sz * sz; i++) {
            if (i % sz == 0) printf("\n");
            printf(" %.3f ", matriz[i]);
        }
        printf("\n>-------------------->\n");
    }
}

void inicial_tiempo(struct timeval *start) {
    gettimeofday(start, NULL);
}

void final_tiempo(struct timeval *start, struct timeval *stop) {
    gettimeofday(stop, NULL);
    stop->tv_sec -= start->tv_sec;
    printf("\n:-> %9.0f µs\n", (double)(stop->tv_sec * 1000000 + stop->tv_usec));
}

void *mult_thread(void *variables) {
    struct parametros *data = (struct parametros *)variables;
    int idH = data->idH;
    int nH = data->nH;
    int N = data->N;

    extern double *mA, *mB, *mC; // Declared in main.c

    int ini = (N / nH) * idH;
    int fin = (N / nH) * (idH + 1);

    for (int i = ini; i < fin; i++) {
        for (int j = 0; j < N; j++) {
            double *pA = mA + (i * N);
            double *pB = mB + j;
            double sumaTemp = 0.0;
            for (int k = 0; k < N; k++, pA++, pB += N) {
                sumaTemp += (*pA * *pB);
            }
            mC[i * N + j] = sumaTemp;
        }
    }

    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);
    pthread_exit(NULL);
}