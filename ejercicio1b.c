#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
	for (int i = 0; i < 4; i++){
        fork();
    }

    printf("PID \n");
    
    return 0;
}
