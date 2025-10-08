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
