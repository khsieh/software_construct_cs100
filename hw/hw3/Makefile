
#Variables
COMPILE = g++
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic

#Target
all: testString fork ioExercise

testString: testString.cpp String.o
	$(COMPILE) $(FLAGS) testString.cpp String.o -o testString
	
String.o: String.cpp String.h
	$(COMPILE) $(FLAGS) -c String.cpp

fork: fork.cpp
	$(COMPILE) $(FLAGS) fork.cpp -o fork
	
ioExercise: ioExercise.cpp
	$(COMPILE) $(FLAGS) ioExercise.cpp -o ioExercise
	
clean:
	rm -rf String.o testString.o testString fork.o fork ioExercise ioExercise.o
