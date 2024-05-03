
# Automatically generated Makefile
# Makefile-generator created by Hans de Nivelle, 2023

CPP = g++

Exec = .
Source = .

Libs =

Options = -std=c++20 -Wall -pedantic -pedantic-errors

# Linking:

$(Exec)/main : $(Source)/queue.o $(Source)/main.o
	$(CPP) $(Options) -o $(Exec)/main $(Source)/queue.o $(Source)/main.o $(Libs)

# Compiling the source files:

$(Source)/queue.o : $(Source)/queue.cpp $(Source)/queue.h
	$(CPP) -c $(Options) $(Source)/queue.cpp -o $(Source)/queue.o

$(Source)/main.o : $(Source)/main.cpp $(Source)/queue.h
	$(CPP) -c $(Options) $(Source)/main.cpp -o $(Source)/main.o

