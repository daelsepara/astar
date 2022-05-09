CCFLAGS=-O3

UNAME_S=$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
        CCFLAGS+=-stdlib=libc++ -std=c++17
endif

all: clean linked_list linked_listv2 astar astarv2 maze

astar:
	g++ astar.cpp -o astar.exe $(CCFLAGS)

astarv2:
	g++ astar.cpp -o astarv2.exe -DUSEV2 $(CCFLAGS)

linked_list:
	g++ linked_list.cpp -o linked_list.exe $(CCFLAGS)

linked_listv2:
	g++ linked_listv2.cpp -o linked_listv2.exe $(CCFLAGS)

maze:
	g++ maze.cpp -o maze.exe $(CCFLAGS)

clean:
	rm -f *.exe *.o
