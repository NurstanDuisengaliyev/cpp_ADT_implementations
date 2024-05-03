


CPP = g++

Exec = .
Source = .

Libs =

Options = -std=c++20 -Wall -pedantic -pedantic-errors

# Linking:

$(Exec)/main : $(Source)/deque.o $(Source)/main.o
	$(CPP) $(Options) -o $(Exec)/main $(Source)/deque.o $(Source)/main.o $(Libs)

# Compiling the source files:

$(Source)/deque.o : $(Source)/deque.cpp $(Source)/deque.h $(Source)/order.h $(Source)/price.h
	$(CPP) -c $(Options) $(Source)/deque.cpp -o $(Source)/deque.o

$(Source)/main.o : $(Source)/main.cpp $(Source)/deque.h $(Source)/order.h $(Source)/price.h
	$(CPP) -c $(Options) $(Source)/main.cpp -o $(Source)/main.o

