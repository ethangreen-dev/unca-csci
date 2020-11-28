#include "listener.h"
#include "ioutil.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int plisten(int port, void (*handler)) {
    // Create a new socket.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, 15, &opt, sizeof(opt));

    // Init our binding information.
    struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind to the address and port.
    int bindrs = bind(sockfd, (struct sockaddr*)addr, sizeof(*addr));

    // Begin listening for a new connection.
    socklen_t socklen = sizeof(*addr);
    int listnrs = listen(sockfd, 5);
    DBGPRNT("Listening on port %d.\n", port);

    int nsockd = accept(sockfd, (struct sockaddr*)addr, &socklen);
    DBGPRNT("Accepted new connection with socket ID %d\n", nsockd);

    // Start a new thread to handle reading and responding to this connection.
    pthread_t thread;
    pthread_create(&thread, NULL, handler, (void *)&nsockd);

    while (1);

    return 0;
}