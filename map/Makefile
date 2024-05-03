
CPP = g++

Exec = .
Source = .

Libs =

Options = -std=c++20 -Wall -pedantic -pedantic-errors -flto -O3

# Linking:

$(Exec)/main : $(Source)/map.o $(Source)/main.o $(Source)/timetable.o
	$(CPP) $(Options) -o $(Exec)/main $(Source)/map.o $(Source)/main.o $(Source)/timetable.o $(Libs)

# Compiling the source files:

$(Source)/map.o : $(Source)/map.cpp $(Source)/map.h
	$(CPP) -c $(Options) $(Source)/map.cpp -o $(Source)/map.o

$(Source)/main.o : $(Source)/main.cpp $(Source)/map.h $(Source)/timer.h $(Source)/timetable.h
	$(CPP) -c $(Options) $(Source)/main.cpp -o $(Source)/main.o

$(Source)/timetable.o : $(Source)/timetable.cpp $(Source)/timetable.h
	$(CPP) -c $(Options) $(Source)/timetable.cpp -o $(Source)/timetable.o

