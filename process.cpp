#include "module.h"
#include "html_template.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
module *mod_process;
const char *process_head = "\n<h3>GET process information</h3>\n";

extern "C" void GetProcessInfo(char *text)
{
    char text_copy[SIZ];
    memset(text_copy, 0, sizeof(text_copy));
    char buf_process[SIZ];
    memset(buf_process, 0, sizeof(buf_process));
    FILE *process_fd = popen("ps -u", "r");
    if (process_fd == NULL)
    {
        cout << "[get_process_information]Failed to get process information!" << endl;
        exit(1);
    }
    fread(buf_process, SIZ, sizeof(char), process_fd);
    Buf_HTML_Table(buf_process, text_copy, SIZ);
    strcat(text_copy, process_head);
    Generate_html(text, text_copy);
    pclose(process_fd);
}

extern "C" module *mod_generate()
{
    mod_process = new module("/process", GetProcessInfo);
    printf("[PROCESSINFO_MODULE Generated!]\n");
    return mod_process;
}
