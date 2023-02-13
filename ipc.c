#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_KEY 123456
#define SHM_SIZE 1024

int main(int argc, char *argv[]) {
    int num, shm_id, i, pid;
    char letra;
    char *shm_ptr;

    // Recibir el número y la letra desde la línea de comandos
    if (argc < 3) {
        printf("Uso: %s <numero> <letra>\n", argv[0]);
        return 1;
    }
    num = atoi(argv[1]);
    letra = argv[2][0];

    // Crear o conectarse a un espacio de memoria compartida
    shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if (shm_id == -1) {
        shm_id = shmget(SHM_KEY, SHM_SIZE, S_IRUSR | S_IWUSR);
        if (shm_id == -1) {
            perror("shmget");
            return 1;
        }
    }

    // Mapear la memoria compartida a un puntero y crear un proceso hijo
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *) -1) {
        perror("shmat");
        return 1;
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    // Proceso padre
    if (pid > 0) {
        for (i = 0; i < SHM_SIZE; i++) {
            if (i % num == 0) {
                shm_ptr[i] = letra;
                printf("Proceso padre: escribiendo %c en posición %d\n", letra, i);
            }
        }
        wait(NULL);
        printf("Contenido de la memoria compartida:\n");
        for (i = 0; i < SHM_SIZE; i++) {
            printf("%c", shm_ptr[i]);
        }
        printf("\n");
    }
    // Proceso hijo
    else {
        for (i = 0; i < SHM_SIZE; i++) {
            if (shm_ptr[i] == letra) {
                printf("Proceso hijo: leyendo");
            }
        }
    }
    return 0;
}
