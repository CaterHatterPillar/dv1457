
all: link
link: compile
	g++ -o ../../bin/cave_server *.o -lpthread
compile: clean
	g++ -c *.h *.cpp
clean:
	rm -f *.gch *.o