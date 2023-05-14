#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    char *args[] = { "/bin/ls", "-l", NULL };
    if (execve("/bin/ls", args, NULL) == -1) {
        if (errno == EACCES) {
            printf("Permission denied\n");
        } else {
            printf("Error: %s\n", strerror(errno));
        }
    }
    return 0;
}
