#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {

    if (argc < 2) {
        printf("ERROR: no arguments\n");
        return 1;
    }

    int mid = argc / 2;
    char *eargs[4];

    eargs[0] = "echo";

    if ((argc - 1) % 2 == 0) {
        eargs[1] = argv[mid - 1];
        eargs[2] = argv[mid];
        eargs[3] = NULL;
    } else {
        eargs[1] = argv[mid];
        eargs[2] = NULL;
    }

    int ret = execv("/bin/echo", eargs);
    if (ret == -1) {
        perror("execv");
        return 1;
    }

    return 0;
}
