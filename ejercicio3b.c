#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid1, pid2, pid3;
    clock_t start, end;

    start = clock();
    pid1 = fork();
    /*process child*/
    if(pid1 == 0){
        pid2 = fork();
        /*process grandchild*/
        if(pid2 == 0){
            pid3 = fork();
            /*process great-grandchild*/
            if(pid3 == 0){
                /*loop of one million iterations*/
                for(int i=0; i<1000000; i++){
                    printf("%d\n", i);
                }
            }
            else{
                /*loop of one million iterations*/
                for(int i=0; i<1000000; i++){
                    printf("%d\n", i);
                }
                wait(NULL) ;
            }
        }
        else{
            /*loop of one million iterations*/
            for(int i=0; i<1000000; i++){
                printf("%d\n", i);
            }
            wait(NULL) ;
        }
    } else{
        wait(NULL);
        end = clock();
        /*execution time*/
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%f\n", elapsed);
        return 0;
    }
}

