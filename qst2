#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <memory.h>
#include <string.h>

//define error msg

#define NOT_ENOUGH_ARGS "Not enough argument\n"
#define TOO_MUCH_ARGUMENTS "too much arguments\n"
#define ERROR_STATUS "Status error :"

#define IP_msg "server ip : "
#define  PRT ":"
#define PORT "69"


// Information about Hostname & Filename

char bufferServerName[128];
char fileName[128];
char ipAdress[128];

// Files Descriptors

int terminal = STDOUT_FILENO;
struct stat sbFileInput;

// Addrinfo

struct addrinfo hints;
struct addrinfo * result = NULL;
int status;


void checkFormat(int argc, char ** argv){
    // Check if the number of arguments is sup to 4
    if (argc>4){
        write(terminal,TOO_MUCH_ARGUMENTS,sizeof(TOO_MUCH_ARGUMENTS));
        close(terminal);
        exit(EXIT_FAILURE);
    }
    // Check if the number of arguments is inf to 4
    if (argc<4){
        write(terminal,NOT_ENOUGH_ARGS,sizeof(NOT_ENOUGH_ARGS));
        close(terminal);
        exit(EXIT_FAILURE);
    }
}

// Function to obtain information about the server 
void getInfo(char * hostname, struct addrinfo hints){

    memset(&hints,0,sizeof(hints));

    hints.ai_protocol=IPPROTO_UDP;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family=AF_INET;

// Get server address information
    status = getaddrinfo(hostname,PORT,&hints,&result);

    if(status != 0){
        write(terminal,ERROR_STATUS,sizeof(ERROR_STATUS));
        write(terminal,gai_strerror(status),sizeof(gai_strerror(status)));
        write(terminal,"\n",1);
        exit(EXIT_FAILURE);
    }

    // Get readable information about the server 
    status = getnameinfo(result->ai_addr,result->ai_addrlen,ipAdress,128,bufferServerName,128, NI_NUMERICHOST | NI_NUMERICSERV);

    if(status !=0){
        write(terminal,gai_strerror(status),sizeof(gai_strerror(status)));
        write(terminal,"\n",1);
    }

    // Show the result
    write(terminal,IP_msg,sizeof(IP_msg));
    write(terminal,ipAdress,strlen(ipAdress));
    write(terminal,PRT,sizeof(PRT));
    write(terminal,bufferServerName,strlen(bufferServerName));
    write(terminal,"\n",1);

    freeaddrinfo(result);
}



int main(int argc,char ** argv){

    checkFormat(argc,argv);
//Call the checkformat to validate the arguments 
    getInfo(argv[2], hints);

    close(terminal);
    return 0;
}

