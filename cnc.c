#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char **argv) {
    struct termios term_settings;
    struct termios saved_term;
    tcgetattr(0, &term_settings);
    saved_term = term_settings;
    term_settings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(0, TCSANOW, &term_settings);

    pid_t child = fork();
    if (child == 0) {
        argv[argc] = NULL;
        execvp("nc", argv);
        perror("Could not spawn netcat");
        exit(1);
    } else {
        int status;
        wait(&status);
        tcsetattr(0, TCSANOW, &saved_term);

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return 1;
        }
    }
}
