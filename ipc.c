#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


#define SHM_NAME "SHARED_MEMORY"
#define SHM_SIZE 4096

int main(int argc, char *argv[]){
    if(argc < 3) { 
        printf("Not enough args passed! Please provide at least two arguments.\n"); 
        exit(1); 
    }

    char* n = argv[1];
    char* x = argv[2];
    int shm = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0666);

    if (shm < 0) {
        printf("Shared memory creation failed.\n");
        exit(1);
    }

    if (ftruncate(shm, SHM_SIZE) == -1) {
        printf("Failed to resize the shared memory.\n");
        exit(1);
    }

    void * maddr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);

    if (maddr == MAP_FAILED) {
        printf("Mapping to shared memory failed.\n");
        exit(1);
    }

    strncpy(maddr, x, strlen(x));

    if (fork() == 0) {
        printf("Child: shared memory content: %s\n", (char*) maddr);
    } else {
        wait(NULL);
        printf("Parent: shared memory content: %s\n", (char*) maddr);
        shm_unlink(SHM_NAME);
    }

    return 0;
}

