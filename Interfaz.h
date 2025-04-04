#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <pthread.h>
#include <sys/time.h>

// Define constants
#define DATA_SIZE (1024*1024*64*3)

// Structure for thread parameters
struct parametros {
    int nH;   // Number of threads
    int idH;  // Thread ID
    int N;    // Matrix dimension
};

// Function declarations
void llenar_matriz(int SZ, double *mA, double *mB, double *mC);
void print_matrix(int sz, double *matriz);
void inicial_tiempo(struct timeval *start);
void final_tiempo(struct timeval *start, struct timeval *stop);
void *mult_thread(void *variables);

#endif