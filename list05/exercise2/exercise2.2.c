#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	setuid(0);
	printf("%d\n", kill(1, SIGKILL));
	return 0;
}
