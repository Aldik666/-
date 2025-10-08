
1. Жүйелік шақыру (System call) деген не?

Жүйелік шақыру — бұл пайдаланушы бағдарламасы мен операциялық жүйенің ядросы арасындағы байланыс механизмі.
Бағдарлама ядро функцияларын тікелей шақыра алмайды, сондықтан ол жүйелік шақыру арқылы ядроға өтініш жібереді.

Мысалы:

open() – файлды ашу

read() – файлдан оқу

write() – файлға жазу

fork() – жаңа процесс жасау





 Пайдаланушы режимі мен ядро режимі арасындағы өту

Операциялық жүйеде екі негізгі режим бар:

Режим	Сипаттамасы

Пайдаланушы режимі (User Mode)	Бағдарлама тек өз жадымен жұмыс істей алады.
Ядро режимі (Kernel Mode)	Процессор мен құрылғыларға толық қолжетімді режим.


2. fork(), exec(), wait() жүйелік шақырулары

Бұл жүйелік шақырулар процестерді басқаруға арналған:

Шақыру	Міндеті

fork()	Жаңа процесс (бала процесс) жасайды.
exec()	Ағымдағы процестің кодын басқа программа кодымен алмастырады.
wait()	Ата-ана процесс бала процесстің аяқталуын күтеді.

 Мысал бағдарлама:

 
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
3. open(), read(), write(), close() жүйелік шақырулары қолданылған мысал

Төмендегі программа бір файлды ашып, оның ішін оқып, басқа файлға жазады:

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int src, dest;
    char buffer[100];
    ssize_t bytes;

    src = open("input.txt", O_RDONLY); // input.txt файлын ашу
    if (src < 0) {
        perror("input.txt ашылмады");
        return 1;
    }

    dest = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // жаңа файл
    if (dest < 0) {
        perror("output.txt ашылмады");
        close(src);
        return 1;
    }

    while ((bytes = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytes); // деректерді жазу
    }

    close(src);
    close(dest);

    printf("Файл көшіру аяқталды!\n");
    return 0;
}

 Қалай тексеруге болады

1. Мысалы, бірінші кодты fork_exec_wait.c, екіншісін file_syscalls.c деп сақта.


2. Терминалда орында:

gcc fork_exec_wait.c -o fork_exec_wait
./fork_exec_wait

және

echo "Hello system call!" > input.txt
gcc file_syscalls.c -o file_syscalls
./file_syscalls
cat output.txt


3. Барлығы дұрыс болса — output.txt ішінде "Hello system call!" мәтіні пайда болады.
