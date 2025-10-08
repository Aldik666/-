#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Жаңа процесс жасау

    if (pid == 0) {
        // Бала процесс
        printf("Бала процесс (PID = %d)\n", getpid());
        execlp("/bin/ls", "ls", "-l", NULL); // exec жаңа программа іске қосады
        perror("exec қатесі");
    } else if (pid > 0) {
        // Ата-ана процесс
        printf("Ата-ана процесс күтіп тұр...\n");
        wait(NULL); // бала процесс аяқталғанша күту
        printf("Бала процесс аяқталды.\n");
    } else {
        perror("fork қатесі");
    }

    return 0;
}
