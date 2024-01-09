#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ava.h"
#include "config.h"

int
main(int argc, char *argv[])
{

    int sockfd = socket( AF_INET, SOCK_STREAM, 0 );
    if (sockfd < 0) { 
        fprintf(stderr, "[ERROR] Error Creating Socket\n");
        return -1;
    }

    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(80);
    cliaddr.sin_addr.s_addr = inet_addr("64.233.164.94");
    memset(&(cliaddr.sin_zero), 0, 8);

    connect(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    if (sockfd < 0) {
        fprintf(stderr, "[ERROR] Error connecting to %s\n", cp);
        close(sockfd);
        return -1;
    }

    char *httpRequest = "GET / HTTP/1.1\r\n"
            "Host: www.google.com\r\n"
            "\r\n";

    int send_result = send(sockfd, httpRequest, strlen(httpRequest), 0);
    if (send_result < 0) {
        fprintf(stderr, "[ERROR] Failed to send https request\n");
        printf("send_result: %d\n", send_result);
        close(sockfd);
        return -1;
    }
    
    char *buffer_read = malloc(BUFFER_CAP);
    int recv_result = recv(sockfd, buffer_read, BUFFER_CAP, 0);
    if (recv_result < 0) {
        fprintf(stderr, "[ERROR] Failed to recive response\n");
        printf("recv status: %d\n", recv_result);
        close(sockfd);
        return -1;
    }

    buffer_read[BUFFER_CAP] = '\0';
    puts(buffer_read);

    free(buffer_read);
    close(sockfd);

    return 0;
}
