#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int contador = 0;

void handler(int signal_number) {
    contador++;
}

int main()
{
    struct sigaction sa = {};
    sa.sa_handler = &handler;
    sigaction(SIGUSR1, &sa, NULL);
    while (getchar() != 'E')
        ;
    printf("SIGUSR1 recebido %d vezes\n", contador);
    return 0;
}