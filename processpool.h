#ifndef PROCESSPOOL_H_INCLUDED
#define PROCESSPOOL_H_INCLUDED
#include <unistd.h>
#include <sys/types.h>

class process
{
public:
    process() : mypid(-1){};
    pid_t mypid;
    int pipefd[2];
};

class processpool
{
private:
    processpool(int sock, int processnum = 4);
    int processnum;
    int sock;
    process *subprocess;
    int idx;
    void runparent();
    void runchild();
    static processpool *pool;

public:
    ~processpool();
    void run();
    static processpool *get(int sock);
};

#endif // PROCESSPOOL_H_INCLUDED
