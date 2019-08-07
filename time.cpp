#include "module.h"
#include "html_template.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
module *mod_time;
const char *time_head = "\n<h3>GET System Time</h3>\n";

extern "C" void GetSystemTime(char *text)
{
    char buf_time[SIZ];
    memset(buf_time, 0, sizeof(buf_time));
    FILE *time_fd = popen("date", "r");
    if (time_fd == NULL)
    {
        cout << "[get_system_time]Failed to open /date !" << endl;
        exit(1);
    }
    fread(buf_time, SIZ, sizeof(char), time_fd);
    strcat(buf_time, time_head);
    Generate_html(text, buf_time);
    pclose(time_fd);
}

extern "C" module *mod_generate()
{
    mod_time = new module("/time", GetSystemTime);
    printf("[TIME_MODULE Generated!]\n");
    return mod_time;
}
