#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds); // stdin

    struct timeval tv = {5, 0}; // 5 секунд күту

    printf("5 секунд ішінде енгізу күтілуде...\n");
    int ret = select(1, &readfds, NULL, NULL, &tv);

    if (ret > 0)
        printf("Енгізу анықталды!\n");
    else
        printf("Уақыт аяқталды.\n");

    return 0;
}
