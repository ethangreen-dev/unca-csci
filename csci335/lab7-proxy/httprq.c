#include "httprq.h"
#include "ioutil.h"

#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include <sys/types.h>

struct reqpsr* init(char *reqstr) {
    struct reqpsr *rq = malloc(sizeof(struct reqpsr));
    rq->reqstr = malloc(sizeof(char) * BUFSIZ);

    strcpy(rq->reqstr, reqstr);

    return rq;
}

struct reqhdr* ps_header(struct reqpsr *req) {
    // Isolate the header.
    char *hdst = malloc(255);
    sscanf(req->reqstr, "%*99[^ ] %199[^ ] %*99[^\n]", hdst);

    DBGPRNT("hdst: %s\n", hdst);

    struct reqhdr *hdr = malloc(sizeof(struct reqhdr));

    regex_t reg;
    char *ptrn = "/^(.*:)\\/\\/([A-Za-z0-9\\-\\.]+)(:[0-9]+)?(.*)$/igx";

    if (regcomp(&reg, ptrn, REG_EXTENDED | REG_ICASE) != 0) {
        ERRPRNT("Could not compile regular expression with pattern %s.\n", ptrn);
        exit(1);
    }

    // Ideally we should see 4 matches.
    int matc = 5;
    regmatch_t *match = malloc(sizeof(regmatch_t) * matc);

    if (regexec(&reg, hdst, matc, match, 0) == 0) {
        ERRPRNT("Could not execute regex expression with pattern %s.\n", ptrn);
        exit(1);
    }

    // Begin parsing the output matches.
    for (int i = 0; i < matc; i++) {
        DBGPRNT("%d - %d\n", match[i].rm_so, match[i].rm_eo);
    }

    return NULL;
}

char *ps_host(struct reqpsr *req) {
    // Get the host address from the HOST parameter.
    char *host = malloc(255);
    char *path = malloc(255);
    int port = 80;
    int succ_parsing = 0;

    if (sscanf(req->reqstr, "%*s[^ ]http://%99[^:]:%i/%199[^\n]", host, &port, path) == 3) { succ_parsing = 1;}
    else if (sscanf(req->reqstr, "%*s[^ ]http://%99[^/]/%199[^\n]", host, path) == 2) { succ_parsing = 1;}
    else if (sscanf(req->reqstr, "%*s[^ ]http://%99[^:]:%i[^\n]", host, &port) == 2) { succ_parsing = 1;}
    else if (sscanf(req->reqstr, "%*s[^ ]http://%99[^\n]", host) == 1) { succ_parsing = 1;}

    DBGPRNT("host: %s, path: %s, port: %d\n", host, path, port);

    return NULL;
}
