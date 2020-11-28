#include "request.h"
#include "httprq.h"
#include "ioutil.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

void handlrq(int sockd) {
    // Begin reading request information from this buffer.
    char *buffer = malloc(sizeof(char) * BUFSIZ);
    ssize_t rcnt = recv(sockd, buffer, BUFSIZ, 0);

    // If read more bytes than expected.
    if (rcnt > BUFSIZ) {
        ERRPRNT("Read %ld bytes but buffer size is only %d.\n", rcnt, BUFSIZ);
        exit(1);
    }

    DBGPRNT("%s\n", buffer);

    // Begin parsing the request information. 
    // First, downgrade the HTTP version to 1.0.
    struct reqpsr *req = init(buffer);
    struct reqhdr *hdr = ps_header(req);

    // DBGPRNT("%s\n", host);
}