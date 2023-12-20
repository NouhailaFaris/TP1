#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NOT_ENOUGH_ARGS "Not enough argument\n"
#define TOO_MUCH_ARGUMENTS "too much arguments\n"
#define ERROR_STATUS "Status error :"

#define IP_msg "server ip : "
#define PRT ":"
#define PORT "69"

char bufferServerName[128];
char fileName[128];
char ipAdress[128];
int terminal = STDOUT_FILENO;
struct addrinfo hints;
struct addrinfo *result = NULL;
int status;

void checkFormat(int argc, char **argv) {
    if (argc > 4) {
        write(terminal, TOO_MUCH_ARGUMENTS, sizeof(TOO_MUCH_ARGUMENTS));
        close(terminal);
        exit(EXIT_FAILURE);
    }
    if (argc < 4) {
        write(terminal, NOT_ENOUGH_ARGS, sizeof(NOT_ENOUGH_ARGS));
        close(terminal);
        exit(EXIT_FAILURE);
    }
}

void getInfo(char *hostname) {
    memset(&hints, 0, sizeof(hints));
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_INET;

    status = getaddrinfo(hostname, PORT, &hints, &result);
    if (status != 0) {
        write(terminal, ERROR_STATUS, sizeof(ERROR_STATUS));
        write(terminal, gai_strerror(status), sizeof(gai_strerror(status)));
        write(terminal, "\n", 1);
        exit(EXIT_FAILURE);
    }

    status = getnameinfo(result->ai_addr, result->ai_addrlen, ipAdress, 128, bufferServerName, 128, NI_NUMERICHOST | NI_NUMERICSERV);

    if (status != 0) {
        write(terminal, gai_strerror(status), sizeof(gai_strerror(status)));
        write(terminal, "\n", 1);
    }

    write(terminal, IP_msg, sizeof(IP_msg));
    write(terminal, ipAdress, strlen(ipAdress));
    write(terminal, PRT, sizeof(PRT));
    write(terminal, bufferServerName, strlen(bufferServerName));
    write(terminal, "\n", 1);
}

void connectToServer(char *hostname) {
    int sockfd;

    sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, result->ai_addr, result->ai_addrlen) == -1) {
        perror("connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server!\n");

    freeaddrinfo(result);

    // Use 'sockfd' for communication or perform other operations
    // Don't forget to close the socket when done
    close(sockfd);
}

int main(int argc, char **argv) {
    checkFormat(argc, argv);
    getInfo(argv[2]);
    connectToServer(argv[2]);
    return 0;
}
