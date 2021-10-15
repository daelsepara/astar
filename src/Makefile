all: clean linked_list astar astarv2 maze

astar:
	g++ astar.cpp -o astar.exe -O3

astarv2:
	g++ astar.cpp -o astarv2.exe -O3 -DUSEV2

linked_list:
	g++ linked_list.cpp -o linked_list.exe -O3

maze:
	g++ maze.cpp -o maze.exe -O3

clean:
	rm -f *.exe *.o
