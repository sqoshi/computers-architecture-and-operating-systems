#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int signo) {
    		printf("received SIGUSR1\n");
	
}
int main() {
	if(signal(SIGUSR1, sig_handler) == SIG_ERR){
		printf("cannot catch SIGUSR1\n");	
	}	
	pid_t pid;
	pid = fork();
	
	if(pid==0){
		while(1);
	}
	else
	{
	
		kill(pid, SIGUSR1);

		sleep(1);
		kill(pid, SIGUSR1);

		kill(pid, SIGUSR1);
		kill(pid, SIGUSR1);
		kill(pid, SIGUSR1);
		kill(pid, SIGUSR1);
		kill(pid, SIGUSR1);
		
		while (1);
	}
		
	return 0;
}
// nie sa kolejkowane

