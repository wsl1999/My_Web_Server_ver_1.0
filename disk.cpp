#include "module.h"
#include "html_template.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
module *mod_disk;
const char *disk_head = "\n<h3>GET disk information</h3>\n";

extern "C" void GetDiskInfo(char *text)
{
    char text_copy[SIZ];
    memset(text_copy, 0, sizeof(text_copy));
    char buf_disk[SIZ];
    memset(buf_disk, 0, sizeof(buf_disk));
    FILE *disk_fd = popen("df -lh", "r");
    if (disk_fd == NULL)
    {
        cout << "[get_disk_information]Failed to get disk information!" << endl;
        exit(1);
    }
    fread(buf_disk, SIZ, sizeof(char), disk_fd);
    Buf_HTML_Table(buf_disk, text_copy, SIZ);
    strcat(text_copy, disk_head);
    Generate_html(text, text_copy);
    pclose(disk_fd);
}

extern "C" module *mod_generate()
{
    mod_disk = new module("/disk", GetDiskInfo);
    printf("[DISKINFO_MODULE Generated!]\n");
    return mod_disk;
}
