# Simple calculator

## Compile

The code have successfully been compiled on Windows with the Microsoft C++ compiler, through the Developer Command Prompt provide with Visual Studios. It has also successfully been cimpiled on Linux with g++. The code requires C++11.

### Windows

Open a Developer Command Prompt and navigate to the main folder (where the Makefile is).

Compile the code with:

`cl /EHsc src/*.cpp /link /out:run.exe`

And run the code with:

`run.exe`

Or run with an input file:

`run.exe a.txt`

### Linux

Open a terminal and navigate to the main folder (where the Makefile is).

The code can then be compiled either by using the Makefile, by simply typing:

`make`

Or compile the code directly with g++:

`g++ -std=c++11 src/*.cpp -o run.o`

And then run the code with:

`./run.o`

Or run with an input file:

`./run.o a.txt`
