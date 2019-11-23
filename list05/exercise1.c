#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
sudo chown root:root a.out
sudo chmod 4755 a.out
*/
int main() {
    char *name[2];
    name[0] = "bash";
    name[1] = NULL;
    setuid(0);    
    execvp("/bin/bash", name);
}
