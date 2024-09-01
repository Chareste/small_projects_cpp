CXX = g++
CXXFLAGS = -std=c++0x -Wall

OBJECTS = mathgame.o game_functions.o user.o

MATH: $(OBJECTS)
		$(CXX) $(CXXFLAGS) -o $@ $^


mathgame.o: mathgame.cpp
				$(CXX) -c mathgame.cpp

game_functions.o: game_functions.cpp game_functions.hpp
					$(CXX) -c game_functions.cpp

user.o: user.cpp user.hpp
					$(CXX) -c user.cpp
