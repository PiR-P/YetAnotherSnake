CXX = g++
CXXFLAGS = -Wno-deprecated -g -std=c++11

LDLIBS = -lglut -lGL -lGLU -lX11 -lm
LIBDIRS= -L/usr/X11R6/lib

# Executable
snake: main.o Cell.o Snake_cell.o Snake.o
$(CXX) $(CXXFLAGS) $(LIBDIRS) $(LDLIBS) -o snake main.o Cell.o Snake_cell.o Snake

main.o: main.cpp Utility.hpp Cell.hpp Snake_cell.hpp Snake.hpp
$(CXX) $(CXXFLAGS) $(LIBDIRS) $(LDLIBS) -c main.cpp

Cell.o: Cell.hpp

Snake_cell.o: Snake_cell.hpp Cell.hpp

Snake.o: Snake.hpp Snake_cell.hpp
