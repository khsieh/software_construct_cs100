
#Variables
COMPILE = g++
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic

#Target
all: main betterMain bestMain my_ls

main: main.cc Coins.o
	$(COMPILE) $(FLAGS) main.cc Coins.o -o main

betterMain: betterMain.cc Coins.o
	$(COMPILE) $(FLAGS) betterMain.cc Coins.o -o betterMain

bestMain: bestMain.cc Coins.o
	$(COMPILE) $(FLAGS) bestMain.cc Coins.o -o bestMain
	
Coins.o: Coins.cc Coins.h
	$(COMPILE) $(FLAGS) -c Coins.cc
	
my_ls: my_ls.cc
	$(COMPILE) $(FLAGS) my_ls.cc -o my_ls
	
clean:
	rm -rf Coins.o main betterMain bestMain my_ls my_ls.o
