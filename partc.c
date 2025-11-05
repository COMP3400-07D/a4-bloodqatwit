#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("ERROR: no arguments\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child: run grep
        char *args[] = { "grep", "-s", "-q", argv[1], argv[2], NULL };
        execv("/usr/bin/grep", args);
        perror("execv");
        exit(1);
    } else {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                printf("FOUND: %s\n", argv[1]);
                return 0;
            } else if (exit_code == 1) {
                printf("NOT FOUND: %s\n", argv[1]);
                return 0;
            } else if (exit_code == 2) {
                printf("ERROR: %s doesn't exist\n", argv[2]);
                return 2;
            }
        } else {
            printf("ERROR: grep failed\n");
            return 2;
        }
    }

    return 0;
}
