
#Variables
COMPILE = g++
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic
ALLSOURCES = testLinkString.cpp String.cpp String.h my_shell.cpp handle_signals.cpp unix.txt Makefile typescript
ALLEXECUTABLE = testLinkString my_shell handle_signals
ALLOBJECTS = String.o testLinkString.o my_shell.o  handle_signals.o

#Target
all: testLinkString my_shell handle_signals

testLinkString: testLinkString.cpp String.o
	$(COMPILE) $(FLAGS) testLinkString.cpp String.o -o testLinkString
	
String.o: String.cpp String.h
	$(COMPILE) $(FLAGS) -c String.cpp

my_shell: my_shell.cpp
	$(COMPILE) $(FLAGS) my_shell.cpp -o my_shell

handle_signals: handle_signals.cpp
	$(COMPILE) $(FLAGS) handle_signals.cpp -o handle_signals

tar:
	tar -czvf hw4.tgz $(ALLSOURCES)

strip:
	strip -S $(ALLEXECUTABLE)

print:
	cat String.cpp
	
clean:
	rm -rf $(ALLEXECUTABLE) $(ALLOBJECTS)
