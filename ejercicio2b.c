#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid1, pid2, pid3;
    clock_t start, end;
    
    start = clock();
    pid1 = fork();
    /*proceso hijo*/

    if(pid1 == 0){
        pid2 = fork();
        /*Proceso Nieto*/
        if(pid2 == 0){ 
            pid3 = fork();
            /*proceso bisnieto*/
            if(pid3 == 0){
                for(int i =0; i<1000000; i++){} 
                exit(0);
            } else {
                wait(NULL);
                for(int i =0; i<1000000; i++){} 
                exit(0);
            }
        } else {
            wait(NULL);
            for(int i =0; i<1000000; i++){} 
            exit(0);
        }
    } else {
        wait(NULL);
        end = clock();
        double rest = (double)(end-start);
        printf("%f\n", rest);
        return 0;
    }
}

