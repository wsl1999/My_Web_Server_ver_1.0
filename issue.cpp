#include "module.h"
#include "html_template.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
module *mod_issue;
const char *issue_head = "\n<h3>GET Ubuntu Version</h3>\n";

extern "C" void GetSystemIssue(char *text)
{
    char buf_issue[SIZ];
    memset(buf_issue, 0, sizeof(buf_issue));
    FILE *issue_fd = popen("lsb_release -d", "r");
    if (issue_fd == NULL)
    {
        cout << "[get_system_issue]Failed to get system issue!" << endl;
        exit(1);
    }
    fread(buf_issue, SIZ, sizeof(char), issue_fd);
    strcat(buf_issue, issue_head);
    Generate_html(text, buf_issue);
    pclose(issue_fd);
}

extern "C" module *mod_generate()
{
    mod_issue = new module("/issue", GetSystemIssue);
    printf("[ISSUE_MODULE Generated!]\n");
    return mod_issue;
}
