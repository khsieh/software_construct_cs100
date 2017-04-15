#Variables
COMPILE = g++
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic
ALLSOURCES = my_shell.cpp Makefile typescript countWords.cpp integerSeparator.cpp my_which.sh my_dircheck.sh my_find.sh README.txt shell_typescript
ALLOBJECTS = my_shell.o coundtWords.o integerSeparator.o
ALLEXECUTABLE = my_shell countWords integerSeparator

#Target
all: $(ALLEXECUTABLE)

my_shell: my_shell.cpp
	$(COMPILE) $(FLAGS) my_shell.cpp -o my_shell

countWords: countWords.cpp
	$(COMPILE) $(FLAGS) countWords.cpp -o countWords

integerSeparator: integerSeparator.cpp
	$(COMPILE) $(FLAGS) integerSeparator.cpp -o integerSeparator

tar:
	tar -czvf hw7.tgz $(ALLSOURCES)
	
clean:
	rm -rf $(ALLEXECUTABLE) $(ALLOBJECTS)
 
