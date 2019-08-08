#include "processpool.h"
#include "module.h"
#include "html_template.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/epoll.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <unistd.h>

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

//externals
extern module **module_html;
extern int module_count;

const int MAX_SIZ = 4096;
const char *str_index("/");
const char *str_test("/test.html");

processpool::processpool(int sock, int processnum) : sock(sock), processnum(processnum), idx(-1)
{
    subprocess = new process[processnum];
    for (int i = 0; i < processnum; i++)
    {
        if (pipe(subprocess[i].pipefd) < 0)
        {
            cout << "pipe num "
                 << "i"
                 << " error" << endl;
        }
        subprocess[i].mypid = fork();
        if (subprocess[i].mypid < 0)
        {
            cout << "fork num "
                 << "i"
                 << " error" << endl;
        }
        if (subprocess[i].mypid > 0)
        {
            close(subprocess[i].pipefd[0]);
            continue;
        }
        else
        {
            close(subprocess[i].pipefd[1]);
            idx = i;
            break;
        }
    }
}

processpool *processpool::get(int sock)
{
    if (pool == NULL)
    {
        pool = new processpool(sock);
    }
    return pool;
}

processpool::~processpool()
{
    delete[] subprocess;
}

void processpool::run()
{
    if (idx != -1)
    {
        runchild();
        return;
    }
    runparent();
}

void processpool::runchild()
{
    while (1)
    {
        int b;
        int *buf = &b;
        read(subprocess[idx].pipefd[0], buf, sizeof(int));
        if (*buf == idx)
        {
            struct sockaddr_in client;
            socklen_t client_addrlength = sizeof(client);
            int connfd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
            if (connfd < 0)
            {
                cout << "[processpool]Accept ERROR!" << endl;
                exit(1);
            }
            else
            {
                cout << "\n[processpool]Child process No." << idx << " is working." << endl;
                char request[MAX_SIZ];
                read(connfd, request, MAX_SIZ);
                request[strlen(request) + 1] = '\0';

                char http_method[32];
                char http_url[32];
                memset(http_method, 0, sizeof(http_method));
                memset(http_url, 0, sizeof(http_url));

                //GET Method and url from head
                sscanf(request, "%s %s", http_method, http_url);
                printf("http_method:%s\n", http_method);
                printf("http_url:%s\n", http_url);

                bool flag = false;
                int fd; //file descriptor

                for (int i = 0; i < module_count; i++)
                {
                    if (strcmp(http_url, module_html[i]->item) == 0)
                    {
                        flag = true; //load modules
                        send(connfd, module_html[i]->local_buf, strlen(module_html[i]->local_buf), 0);
                    }
                }
                if (flag == false) //load fundamental pages
                {
                    if (strcmp(http_url, str_index) == 0)
                    {
                        send(connfd, ok_response, strlen(ok_response), 0);
                        fd = open("index.html", O_RDONLY);
                        sendfile(connfd, fd, NULL, MAX_SIZ);
                    }
                    else if (strcmp(http_url, str_test) == 0)
                    {
                        send(connfd, ok_response, strlen(ok_response), 0);
                        fd = open("test.html", O_RDONLY);
                        sendfile(connfd, fd, NULL, MAX_SIZ);
                    }
                    else
                    {
                        send(connfd, not_found_response, strlen(not_found_response), 0);
                    }
                }
                close(fd);
                close(connfd);
            }
        }
    }
}

void processpool::runparent()
{
    int epollfd = epoll_create(5);
    epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = sock;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &event) < 0)
    {
        cout << "epoll_ctl error" << endl;
        exit(1);
    }
    epoll_event events[5];
    for (int j = 0; j < 10240; j++)
    {
        int i = j % 4;
        if (epoll_wait(epollfd, events, 5, -1) < 0)
        {
            cout << "epoll_wait error" << endl;
            continue;
        }
        if (events[0].data.fd == sock)
        {
            int b = i;
            int *buf = &b;
            write(subprocess[i].pipefd[1], buf, sizeof(int));
        }
    }
    close(epollfd);
}
processpool *processpool::pool = NULL;
