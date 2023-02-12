#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(){
	clock_t start, end;
	start = clock();
	//for 1
	for(int i = 0; i<1000000; i++){
		printf("%d\n", i);
	}
	//for 2
	for(int i = 0; i<1000000; i++){
		printf("%d\n", i);
	}
	//for 3
	for(int i = 0; i<1000000; i++){
		printf("%d\n", i);
	}
	end = clock();
	
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f\n", elapsed);
    return 0;
}
