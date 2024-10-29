 #include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// N�mero de threads que vamos criar
#define NUM_THREADS 5

// Declara��o da barreira
pthread_barrier_t barrier;

// Fun��o que ser� executada por cada thread
void* thread_task(void* arg) {
    int thread_id = *((int*) arg);

    // Fase 1: cada thread faz seu trabalho
    printf("Thread %d est� executando a Fase 1...\n", thread_id);
    sleep(1); // Simula��o de trabalho
    printf("Thread %d completou a Fase 1\n", thread_id);

    // Todas as threads esperam aqui na barreira
    pthread_barrier_wait(&barrier);

    // Fase 2: ap�s a sincroniza��o, cada thread continua seu trabalho
    printf("Thread %d est� executando a Fase 2...\n", thread_id);
    sleep(1); // Simula��o de mais trabalho
    printf("Thread %d completou a Fase 2\n", thread_id);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Inicializa a barreira, especificando o n�mero de threads que devem esperar
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Cria as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_task, &thread_ids[i]);
    }

    // Aguarda as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destr�i a barreira
    pthread_barrier_destroy(&barrier);

    printf("Todas as threads completaram as duas fases.\n");
    return 0;
}
