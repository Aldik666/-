#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Сигнал өңдеуші функция
void handle_signal(int sig) {
    printf("Сигнал қабылданды: %d\n", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // SIGINT (Ctrl+C) сигналын өңдеуші ретінде тіркеу
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        printf("Күтіп тұр...\n");
        sleep(2);
    }
    return 0;
}
