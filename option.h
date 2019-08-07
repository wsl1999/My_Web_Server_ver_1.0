#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED

#include <getopt.h>
#include <cstdio>
#include <cstdlib>

struct options
{
    bool verbose;
    const char *addr_str;
    int port;
    const char *module_catalog;
};

const char *short_opts = "hva:p:m:";
const struct option long_opts[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {"address", required_argument, NULL, 'a'},
        {"port", required_argument, NULL, 'p'},
        {"modir", required_argument, NULL, 'm'},
        {NULL, 0, NULL, 0}};

void print_help(char *prog)
{
    printf("[Usage]\n");
    printf("%s -a 127.0.0.1 -p 8800 -m time\n", prog);
    printf("[Default Settings]\n");
    printf("-a: IP address, default: 127.0.0.1\n");
    printf("-p: port number, default: 8800\n");
    printf("-m: module name, default: module waiting to be loaded..\n");
}

void opt_default_set(options &opt)
{
    opt.addr_str = "127.0.0.1";
    opt.module_catalog = "module waiting to be loaded..";
    opt.port = 8800;
    opt.verbose = false;
}

int opt_response(int argc, char *const *argv, options &opt)
{
    int opt_ch = 0;
    while ((opt_ch = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1)
    {
        switch (opt_ch)
        {
        case 'v':
            opt.verbose = true;
            break;
        case 'a':
            opt.addr_str = optarg;
            break;
        case 'p':
            opt.port = atoi(optarg);
            break;
        case 'm':
            opt.module_catalog = optarg;
            break;
        case 'h':
        case '?':
            print_help(argv[0]);
            return -1;
        default:
            printf("Unknown error!\n");
            print_help(argv[0]);
            return argc;
        }
    }
    return 0;
}

#endif // OPTION_H_INCLUDED
