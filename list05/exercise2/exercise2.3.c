#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void any_signal_handler(int sig_num)
{
    int qty = 0;
    printf("Signal %i: %i\n", qty, sig_num);
    qty++;
}

int main() {
    for(int i = 1; i < 65; i++) {
        signal(i, any_signal_handler);
    }

    printf("PID: %i\n", getpid());

    while(1) {
        sleep(1);
    }

    return 0;
}
