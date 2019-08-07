#include "module.h"
#include <dlfcn.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
int module_count = 0;
module **module_html;

module::module()
{
    memset(this->item, '\0', sizeof(this->item));
    memset(this->local_buf, '\0', sizeof(this->local_buf));
}

module::module(const char *item, void (*manipulate)(char *))
{
    this->manipulate = manipulate;
    memset(this->item, '\0', sizeof(this->item));
    strcpy(this->item, item);
    memset(this->local_buf, '\0', sizeof(this->local_buf));
}

void module_load()
{
    FILE *mod_fd = fopen("modulelist", "r");
    if (mod_fd == NULL)
    {
        cout << "Failed loading modules!" << endl;
        exit(1);
    }
    char mod_buf[128];
    memset(mod_buf, 0, sizeof(mod_buf));

    while (fgets(mod_buf, sizeof(mod_buf), mod_fd))
    {
        if (mod_buf[0] != '#') //use "#" to invalidate a module.
        {
            module_count++;
        }
    }

    memset(mod_buf, 0, sizeof(mod_buf));
    fseek(mod_fd, 0, SEEK_SET);
    module_html = new module *[module_count];
    int mod_num = 0;

    while (fgets(mod_buf, sizeof(mod_buf), mod_fd))
    {
        if (mod_buf[0] != '#')
        {
            char temp[4] = "./";
            char filename[16];
            sscanf(mod_buf, "%s\n", filename);
            void *handle = dlopen(strcat(temp, filename), RTLD_NOW);
            module *(*mod_generate)() = (module * (*)()) dlsym(handle, "mod_generate");
            module_html[mod_num] = mod_generate();
            module_html[mod_num]->manipulate(module_html[mod_num]->local_buf);
            module_html[mod_num]->handle = handle;
            mod_num++;
        }
    }
    fclose(mod_fd);
}
