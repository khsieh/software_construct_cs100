#Variables
COMPILE = g++
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic
ALLSOURCES = my_shell.cpp Makefile typescript Array.cpp Array.h Matrix.h Matrix.cpp ArrayMain.cpp MatrixMain.cpp linux.txt
ALLOBJECTS = my_shell.o Array.o Matrix.o
ALLEXECUTABLE = my_shell Array Matrix

#Target
all: my_shell Array Matrix

my_shell: my_shell.cpp
	$(COMPILE) $(FLAGS) my_shell.cpp -o my_shell

Array: Array.cpp Array.h ArrayMain.cpp
	$(COMPILE) $(FLAGS) Array.cpp ArrayMain.cpp -o Array

Matrix: Matrix.cpp Array.h Matrix.h MatrixMain.cpp
	$(COMPILE) $(FLAGS) Matrix.cpp MatrixMain.cpp -o Matrix
	
tar:
	tar -czvf hw6.tgz $(ALLSOURCES)
	
clean:
	rm -rf $(ALLEXECUTABLE) $(ALLOBJECTS)
