
CPP = g++

Exec = .
Source = .

Libs =

Options = -std=c++20 -Wall -pedantic -pedantic-errors -O3 -flto

# Linking:

$(Exec)/main : $(Source)/set.o $(Source)/main.o $(Source)/timetable.o
	$(CPP) $(Options) -o $(Exec)/main $(Source)/set.o $(Source)/main.o $(Source)/timetable.o $(Libs)

# Compiling the source files:

$(Source)/set.o : $(Source)/set.cpp $(Source)/set.h
	$(CPP) -c $(Options) $(Source)/set.cpp -o $(Source)/set.o

$(Source)/main.o : $(Source)/main.cpp $(Source)/set.h $(Source)/timer.h $(Source)/timetable.h
	$(CPP) -c $(Options) $(Source)/main.cpp -o $(Source)/main.o

$(Source)/timetable.o : $(Source)/timetable.cpp $(Source)/timetable.h
	$(CPP) -c $(Options) $(Source)/timetable.cpp -o $(Source)/timetable.o

