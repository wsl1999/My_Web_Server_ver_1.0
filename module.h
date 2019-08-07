#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

class module
{
public:
    char item[16];
    char local_buf[4096];

public:
    module();
    module(const char *item, void (*manipulate)(char *text));
    void *handle;
    void (*manipulate)(char *text);
};
void module_load();

#endif // MODULE_H_INCLUDED
