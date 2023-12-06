#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash%"
#define EXIT "Bye bye..."

// We develop this function in order to print any integer using the write function
void write_int(int num) {
    char str[20];
    int i = 0;
    int val = num;
    if (val == 0) {
        str[i++] = '0';
    }
    else {
        while (val) {
            str[i++] = (val % 10) + '0';
            val /= 10;
        }
    }
    str[i] = '\0';
    write(1, str, i);
}
int main() {
    /* Buffer for storing the user's command */
    char command[100];
    int exit_res, signal_res;/*Variables to store the exit and signal status of the child process*/
    float time_elapsed_in_seconds;
    /* Print the welcome message */
    write(1, WELCOME_MSG, strlen(WELCOME_MSG));

    /* Loop indefinitely to accept commands */
    while (1) {

        int status, exit_status, signal_status;
        struct timespec start, end;

        /* Print the shell prompt */
        write(1,"\nenseash",8);  /*Writes the enseash prompt to the standard output*/

        if (exit_res == 1){
            write(1," [exit:",7); // Writes the exit status to the standard output
            char exit_status_str[10]; //Variable to store the exit status string
            int i = 0;
            int val = exit_status;
            if (val == 0) {
                exit_status_str[i++] = '0';
            }
            else {
                while (val) {
                    exit_status_str[i++] = (val % 10) + '0';
                    val /= 10;
                }
            }
            write(1, exit_status_str, i);
            write(1,"|",1);
            write_int(time_elapsed_in_seconds);
            write(1,"ms]",3);

        }

        if (signal_res == 1){
            write(1," [signal:",9);  // Writes the signal status to the standard output
            char signal_status_str[10]; //Variable to store the signal status string
            int i = 0;
            int val = signal_status;
            if (val == 0) {
                signal_status_str[i++] = '0';
            }
            else {
                while (val) {
                    signal_status_str[i++] = (val % 10) + '0';
                    val /= 10;
                }
            }

            write(1, signal_status_str, i);
            write(1,"|",1);
            write_int(time_elapsed_in_seconds);
            write(1,"ms]",3);
        }

        write(1," % ",3);  // Writes the prompt symbol to the standard output

        /* Read the command from the user */
        int bytes_read = read(0, command, 100);
        command[bytes_read - 1] = 0;

        exit_res = 0; //set exit_res to 0
        signal_res = 0; //set signal_res to 0
        clock_gettime(CLOCK_MONOTONIC, &start); // Start of time counting
        /* Fork to create a child process*/
        pid_t pid = fork();
        //We tokenize the read command in order to store its arguments in an array
        if (pid == 0) {
            char *args[10];
            char* token = strtok(command, " ");
            int i = 0;
            while(token != NULL){
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;
            if(i>=10){
                write(1,"Too many arguments\n", 19);
                exit(EXIT_SUCCESS);
            }
            execvp(args[0], args);
            exit(EXIT_SUCCESS);
        } else {
            wait(&status);
            if (WIFEXITED(status)) {
                exit_status = WEXITSTATUS(status);
                exit_res = 1;

            }else if (WIFSIGNALED(status)) {
                signal_status = WTERMSIG(status);
                signal_res = 1;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end );// End of time counting

        //We defined the elapsed time in miliseconds with this formula
        time_elapsed_in_seconds= (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1e6;


        /* Check if the command is "exit" */
        if (strcmp(command, "exit") == 0) {
            write(1, EXIT, strlen(EXIT));
            exit(0);
        }
        if (strcmp(command, ">") == 0) {

        }
    }
    return 0;
}
