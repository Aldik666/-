#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

int main(void) {
    int fd = open("/dev/tty", O_RDWR);
    if (fd < 0) { perror("open"); return 1; }

    struct termios t;
    if (tcgetattr(fd, &t) == -1) { perror("tcgetattr"); close(fd); return 1; }

    struct termios orig = t;
    t.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(fd, TCSANOW, &t) == -1) { perror("tcsetattr"); close(fd); return 1; }

    printf("Canonical mode disabled. Press Enter to restore.\n");
    getchar();
    tcsetattr(fd, TCSANOW, &orig);
    close(fd);
    return 0;
}
