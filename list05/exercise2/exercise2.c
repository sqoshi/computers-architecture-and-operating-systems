#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

printf("sigkill: %d\n", kill(1, SIGKILL)); 
printf("sigint: %d\n", kill(1, SIGINT)); 
return 0;
}
