#include "processpool.h"
#include "module.h"
#include "option.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <assert.h>
using namespace std;

int main(int argc, char *argv[])
{
	options opt;
	opt_default_set(opt);
	int opt_result = opt_response(argc, argv, opt);
	if (opt_result != 0)
	{
		printf("Please input the command line argument according to the usage!\n");
		return 1;
	}
	printf("IP address:%s\n", opt.addr_str);
	printf("port number:%d\n", opt.port);
	printf("module name:%s\n", opt.module_catalog);
	printf("show verbose:%d\n", opt.verbose);

	int sock;
	struct sockaddr_in server_address;
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = PF_INET;

	if (!opt.addr_str)
		server_address.sin_addr.s_addr = htons(INADDR_ANY);
	else
		server_address.sin_addr.s_addr = inet_addr(opt.addr_str);
	server_address.sin_port = htons(opt.port);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	int ret = bind(sock, (struct sockaddr *)&server_address, sizeof(server_address));
	assert(ret != -1);

	if (ret >= 0)
		cout << "Bind success!Connect to http://" << opt.addr_str << ":" << opt.port << "/" << endl;
	cout << "Please enter " << opt.addr_str << ":" << opt.port << " in your website address column." << endl;

	module_load(); //load modules
	ret = listen(sock, 8);
	assert(ret != -1);

	processpool *pool = processpool::get(sock);
	if (pool)
	{
		pool->run();
		delete pool;
	}
	close(sock);

	return 0;
}
