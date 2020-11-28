#ifndef HTTPRQ_H
#define HTTPRQ_H

// Definitions for request types. 
#define REQ_GET 0
#define REQ_POST 1

struct reqpsr {
    char *reqstr;
    char **lines;
};

struct reqhdr {
    char *verb;
    char *host;
    char *path;

    int port;
};

// Create a new request parser struct.
struct reqpsr* init(char *reqstr);

char *ps_host(struct reqpsr *req);
struct reqhdr* ps_header(struct reqpsr *req);

#endif