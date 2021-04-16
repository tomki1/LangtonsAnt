output: main.o menu.o ant.o board.o inputValidation.o
	g++ -std=c++0x main.o menu.o ant.o board.o inputValidation.o -o output

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

menu.o: menu.cpp menu.hpp
	g++ -std=c++0x -c menu.cpp

ant.o: ant.cpp ant.hpp
	g++ -std=c++0x -c ant.cpp
	
board.o: board.cpp board.hpp
	g++ -std=c++0x -c board.cpp

inputValidation.o: inputValidation.cpp inputValidation.hpp

clean:
	rm *.o output

zip: 
	zip -D Project1_Tom_Kimberly.zip menu.cpp ant.cpp board.cpp inputValidation.cpp menu.hpp ant.hpp board.hpp inputValidation.hpp main.cpp makefile AntDesign.pdf

