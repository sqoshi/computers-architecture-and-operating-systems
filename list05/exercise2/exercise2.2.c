#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    
    for(int i = 0; i < 50; i++) {
        printf("Signal%i\n",  i);
        if(kill(atoi(argv[1]), SIGUSR1) < 0) {
           printf("error: %d\n", i);
        }
    }
      kill(atoi(argv[1]), SIGUSR2);
    return 0;
}
