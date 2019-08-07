#include "module.h"
#include "html_template.h"
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

class CPUITEM
{
public:
	char *item;
	char *value;
	CPUITEM(char *_item, char *_value) : item(_item), value(_value){};
};

module *mod_cpu;
const char *cpu_head = "\n<h3>GET Cpu Infomation</h3>\n";
const char *c1 = ":";
const char *c2 = "\n<br/>";

extern "C" void GetCpuInfo(char *text)
{
	char buf_cpu[SIZ];
	char buf_copy[SIZ];
	memset(buf_cpu, 0, sizeof(buf_cpu));
	memset(buf_copy, 0, sizeof(buf_copy));
	int cpu_fd = open("/proc/cpuinfo", O_RDONLY);
	if (!cpu_fd)
	{
		cout << "[get_cpu_infomation]Failed to open /proc/cpuinfo !" << endl;
		exit(1);
	}
	read(cpu_fd, buf_cpu, SIZ);
	char *_buffer = buf_cpu;

	while (*_buffer != '\n')
	{
		int i = strcspn(_buffer, ":");
		_buffer[i] = '\0';
		int j = strcspn(_buffer + i + 1, "\n");
		_buffer[i + 1 + j] = '\0';
		CPUITEM *_items = new CPUITEM(_buffer, _buffer + i + 1);
		strcat(buf_copy, _items->item);
		strcat(buf_copy, c1);
		strcat(buf_copy, _items->value);
		strcat(buf_copy, c2);
		_buffer += i + j + 2;
	}
	strcat(buf_copy, cpu_head);
	Generate_html(text, buf_copy);
	close(cpu_fd);
}

extern "C" module *mod_generate()
{
	mod_cpu = new module("/cpuinfo", GetCpuInfo);
	printf("[CPUINFO_MODULE Generated!]\n");
	return mod_cpu;
}
