LDFLAGS=-fPIC -shared
objects=main.o module.o processpool.o time.so issue.so cpuinfo.so process.so disk.so
server:$(objects)
	g++ -rdynamic -o server $(objects) -ldl
main.o:main.cpp module.h processpool.h option.h
	g++ -c main.cpp
module.o:module.cpp module.h
	g++ -c module.cpp
processpool.o:processpool.cpp module.h processpool.h html_template.h
	g++ -c processpool.cpp
time.so:
	g++ $(LDFLAGS) time.cpp -o time.so
issue.so:
	g++ $(LDFLAGS) issue.cpp -o issue.so
cpuinfo.so:
	g++ $(LDFLAGS) cpuinfo.cpp -o cpuinfo.so
process.so:
	g++ $(LDFLAGS) process.cpp -o process.so
disk.so:
	g++ $(LDFLAGS) disk.cpp -o disk.so
.PHONY: clean
clean:
	rm -f *.o *.so
