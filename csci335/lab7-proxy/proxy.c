#include "listener.h"
#include "request.h"

#include <stdlib.h>
#include <stdio.h>

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

void test(void *arg) {
    handlrq(*(int *)arg);
}

int main(int argc, char **argv) {
    printf("%s", user_agent_hdr);
    plisten(46678, &test);
    return 0;
}
