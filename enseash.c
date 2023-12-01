#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash%"
#define EXIT "Bye bye..."
int main() {
    /* Buffer for storing the user's command */
    char command[100];

    /* Print the welcome message */
    write(1, WELCOME_MSG, strlen(WELCOME_MSG));

    /* Loop indefinitely to accept commands */
    while (1) {
        /* Print the shell prompt */
        write(1, PROMPT, strlen(PROMPT));

        /* Read the command from the user */
        int bytes_read = read(0, command, 100);
        command[bytes_read-1] = 0;

        /* Check if the command is "exit" */
        if (strcmp(command, "exit") == 0) {
            /* Exit the shell */
            write(1, EXIT, strlen(EXIT));
            exit(0);

        }
        else {
            // Fork to create a child process
            pid_t pid = fork();

            // Child process
            if (pid == 0) {
                execlp(command, command, (char *) NULL);
                /* Exit with a failure status if exec fails */
                exit(1);

            }
                // Parent process
                // Wait for the child process to finish
            else {
                wait(NULL);
            }
        }
    }
    return 0;
}

