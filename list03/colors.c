#include <stdio.h>
int main (int argc, char const *argv[]) {
 for(int i=0;i<=256;i++) 
  		printf("%d: \x1b[38;5;" "%d" "m Hello World!" "\x1b[0m" 
  		"\n",i,i);
/*	for(int j=0;j<8;j++) printf("\x1b[4%dm Hello World! \x1b[0m 
		\n",j);
	for(int k=0;k<=8;k++) printf("\x1b[%dm Hello World!\x1b[0m 
		\n",k);
  */ return 0;
}
