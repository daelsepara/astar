# A* Pathfinding Algorithm Studies Implemented in C++

This tiny repository contains implementations of the singly-linked lists and the A* Pathfinding algorithm implemented in C++. The main **data structure** or **class** used internally by the A* algorithm is implemented as a singly-linked list through the parent as opposed to children.

There are three programs in this repository:

- linked_list.cpp
- linked_listv2.cpp
- astar.cpp

In addition two header files can be used by astar.cpp:

- astar.hpp
- astarv2.hpp

Both **linked_list.cpp** and **astar.hpp** uses raw pointers and allocate objects on the heap which we can ignore for small problem sizes as the memory the leak can be ignored, though it is not a good practice to do so. Typically, C or C++ programmers have to manage the memory themselves. These things often go beyond simply matching new and delete.

To improve on this, **linked_listv2.cpp** and **astarv2.hpp** have been implemented smart pointers. In this which are available in C++11 and higher. In this case, through some memory reference counting mechanisms, all objects allocated on the heap are automattically deleted once it goes out of scope.

# A* Pathfinding

The main purpose of this repo is to present a C++ implementation of the C# A* Pathfinding example I found here [https://dotnetcoretutorials.com/2020/07/25/a-search-pathfinding-algorithm-in-c/](https://dotnetcoretutorials.com/2020/07/25/a-search-pathfinding-algorithm-in-c/). I have also made some minor modifications to the C++ implmentation so that it can easily attach to other projects. The linked list part of this repository was simply a stepping stone towards A*.

# Compiling

These programs were implemented and tested in a Linux environment (Ubuntu 20.04 LTS). To compile the programs here, go towards the **src/** directory and type:

```
make
```

or you can build the programs individually

```
make linked_list
make linked_listv2

make astar
make astarv2
```

# Example A* output

To demonstrate A*, you can type on the command line:

```
./astar.exe
```

or for the version that uses smart pointers:

```
./astarv2.exe 
```

It defaults an 6x11 (rows x columns) layout:

```
A          
--| |------
           
   |-----| 
   |     | 
---|     |B
```

It will then try to find a path from **A** to **B**. **A** can only move through open spaces in four directions (Left, Right, Up, or Down) and **B**.

If a path is found, it will print the coordinates of **A**'s movement towards **B** similar to:

```
(0, 0) R
(1, 0) R
(2, 0) R
(3, 0) D
(3, 1) D
(3, 2) R
(4, 2) R
(5, 2) R
(6, 2) R
(7, 2) R
(8, 2) R
(9, 2) R
(10, 2) D
(10, 3) D
(10, 4) D
(10, 5)
```

Afterwards, it will be marked on the map with an __*__:

```
A***       
--|*|------
   ********
   |-----|*
   |     |*
---|     |B
```

## Complete output

```
Initial Map:
A          
--| |------
           
   |-----| 
   |     | 
---|     |B

Path from A to B (X, Y) required 15 steps:
(0, 0) R
(1, 0) R
(2, 0) R
(3, 0) D
(3, 1) D
(3, 2) R
(4, 2) R
(5, 2) R
(6, 2) R
(7, 2) R
(8, 2) R
(9, 2) R
(10, 2) D
(10, 3) D
(10, 4) D
(10, 5)

Map:
A***       
--|*|------
   ********
   |-----|*
   |     |*
---|     |B
```

# Custom mazes

To find a path in a custom maze, construct a maze and store it in a text file. The text file should already contain both **A** and **B**. Afterwards, call **astar** fom the command line with the file you have created. Several examples are provided here. They are found in the ![examples](examples/) directory of this repository.

## Example

```
./astarv2.exe examples/maze7.txt
```

## Output

```
Initial Map:
- - - - - - - - - - - - - - - - - - - - - 
|                       |       |       B 
-   -   - - - - - - -   -   -   -   - - - 
|   |   |                   |   |       | 
- - -   - - - - -   - - - - -   - - -   - 
|       |       |   |       |           | 
-   - - -   -   - - -   -   - - - - -   - 
|           |           |       |   |   | 
-   - - - - - - - - - - - - -   -   -   - 
|       |   |       |           |   |   | 
- - -   -   -   -   -   - - - - -   -   - 
|   |   |   |   |   |   |               | 
-   -   -   -   -   -   - - - - - - -   - 
|   |       |   |       |           |   | 
-   - - -   -   - - - - -   - - -   -   - 
|       |   |       |       |   |   |   | 
- - -   -   - - -   -   - - -   -   -   - 
|       |   |       |   |       |   |   | 
-   - - -   -   - - -   - - -   -   - - - 
|           |                   |       | 
- A - - - - - - - - - - - - - - - - - - - 

Path from A to B (X, Y) required 65 steps:
(2, 20) U
(2, 19) R
(3, 19) R
(4, 19) R
(5, 19) R
(6, 19) R
(7, 19) R
(8, 19) R
(9, 19) U
(9, 18) U
(9, 17) U
(9, 16) U
(9, 15) U
(9, 14) U
(9, 13) U
(9, 12) U
(9, 11) U
(9, 10) U
(9, 9) U
(9, 8) U
(9, 7) U
(9, 6) U
(9, 5) U
(9, 4) U
(9, 3) R
(10, 3) R
(11, 3) R
(12, 3) R
(13, 3) R
(14, 3) R
(15, 3) R
(16, 3) R
(17, 3) R
(18, 3) R
(19, 3) R
(20, 3) R
(21, 3) R
(22, 3) R
(23, 3) R
(24, 3) R
(25, 3) R
(26, 3) U
(26, 2) U
(26, 1) R
(27, 1) R
(28, 1) R
(29, 1) R
(30, 1) R
(31, 1) D
(31, 2) D
(31, 3) D
(31, 4) D
(31, 5) R
(32, 5) R
(33, 5) U
(33, 4) U
(33, 3) U
(33, 2) U
(33, 1) R
(34, 1) R
(35, 1) R
(36, 1) R
(37, 1) R
(38, 1) R
(39, 1) R
(40, 1)

Map:
- - - - - - - - - - - - - - - - - - - - - 
|                       | ******|*******B 
-   -   - - - - - - -   - * -  *-*  - - - 
|   |   |****************** |  *|*      | 
- - -   -*- - - -   - - - - -  *-*- -   - 
|       |*      |   |       |  ***      | 
-   - - -*  -   - - -   -   - - - - -   - 
|        *  |           |       |   |   | 
-   - - -*- - - - - - - - - -   -   -   - 
|       |*  |       |           |   |   | 
- - -   -*  -   -   -   - - - - -   -   - 
|   |   |*  |   |   |   |               | 
-   -   -*  -   -   -   - - - - - - -   - 
|   |    *  |   |       |           |   | 
-   - - -*  -   - - - - -   - - -   -   - 
|       |*  |       |       |   |   |   | 
- - -   -*  - - -   -   - - -   -   -   - 
|       |*  |       |   |       |   |   | 
-   - - -*  -   - - -   - - -   -   - - - 
| ********  |                   |       | 
- A - - - - - - - - - - - - - - - - - - -
```

# Final note about smart pointers

Memory leaks are mostly invisible and in the worse case scenario, the program crashes. To see the difference between both versions, you can use a tool called [valgrind](https://valgrind.org/). In Linux environments, provided it is installed, one simply invokes in the following manner:

```
valgrind --undef-value-errors=no ./astarv2.exe
```

Where it outputs:

```
==10433== Memcheck, a memory error detector
==10433== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==10433== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==10433== Command: ./astarv2.exe
==10433== 

Initial Map:
A          
--| |------
           
   |-----| 
   |     | 
---|     |B

Path from A to B (X, Y) required 15 steps:
(0, 0) R
(1, 0) R
(2, 0) R
(3, 0) D
(3, 1) D
(3, 2) R
(4, 2) R
(5, 2) R
(6, 2) R
(7, 2) R
(8, 2) R
(9, 2) R
(10, 2) D
(10, 3) D
(10, 4) D
(10, 5)

Map:
A***       
--|*|------
   ********
   |-----|*
   |     |*
---|     |B
==10433== 
==10433== HEAP SUMMARY:
==10433==     in use at exit: 0 bytes in 0 blocks
==10433==   total heap usage: 363 allocs, 363 frees, 101,000 bytes allocated
==10433== 
==10433== All heap blocks were freed -- no leaks are possible
==10433== 
==10433== For lists of detected and suppressed errors, rerun with: -s
==10433== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

For the raw veresion:

```
valgrind --undef-value-errors=no ./astar.exe
```

It outputs:

```
==10456== Memcheck, a memory error detector
==10456== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==10456== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==10456== Command: ./astar.exe
==10456== 

Initial Map:
A          
--| |------
           
   |-----| 
   |     | 
---|     |B

Path from A to B (X, Y) required 15 steps:
(0, 0) R
(1, 0) R
(2, 0) R
(3, 0) D
(3, 1) D
(3, 2) R
(4, 2) R
(5, 2) R
(6, 2) R
(7, 2) R
(8, 2) R
(9, 2) R
(10, 2) D
(10, 3) D
(10, 4) D
(10, 5)

Map:
A***       
--|*|------
   ********
   |-----|*
   |     |*
---|     |B
==10456== 
==10456== HEAP SUMMARY:
==10456==     in use at exit: 2,160 bytes in 90 blocks
==10456==   total heap usage: 363 allocs, 273 frees, 87,680 bytes allocated
==10456== 
==10456== LEAK SUMMARY:
==10456==    definitely lost: 1,632 bytes in 68 blocks
==10456==    indirectly lost: 528 bytes in 22 blocks
==10456==      possibly lost: 0 bytes in 0 blocks
==10456==    still reachable: 0 bytes in 0 blocks
==10456==         suppressed: 0 bytes in 0 blocks
==10456== Rerun with --leak-check=full to see details of leaked memory
==10456== 
==10456== For lists of detected and suppressed errors, rerun with: -s
==10456== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Notice in the original version that uses raw pointers, valgrind reports about the memory leaks while in the smart pointers version

```
==10433== All heap blocks were freed -- no leaks are possible
```

No memory are leaked. Eagle eyed readers will also notice that I invoked valgrind with the **--undef-value-errors=no** option. I had removed the **Conditional jump or move depends on uninitialised value(s)** errors from the output as the errors reported point valgrind's problems with C++'s **stl** library, specifically the **std::sort()** function. However, that discussion, we will reserve for another day. The important take away here (for now) is that smart pointers are a way to address memory leaks.

# Bugs and Reporting

Feel free to re-use these codes and report to me any bugs or issues.