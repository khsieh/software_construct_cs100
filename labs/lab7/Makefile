#Variables
COMPILE = g++
ALLSOURCES = phoneBook.cpp stack.cpp vec.cpp my_set.cpp deque.cpp
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic
ALLEXECUTABLE = phoneBook stack vec my_set deque

#Target
all: $(ALLEXECUTABLE)
	
vec: vec.cpp 
	$(COMPILE) $(FLAGS) vec.cpp -o vec

deque: deque.cpp
	$(COMPILE) $(FLAGS) deque.cpp -o deque
    
stack: stack.cpp 
	$(COMPILE) $(FLAGS) stack.cpp -o stack
	
phoneBook: phoneBook.cpp 
	$(COMPILE) $(FLAGS) phoneBook.cpp -o phoneBook
	
my_set: my_set.cpp 
	$(COMPILE) $(FLAGS) my_set.cpp -o my_set
	
tar:
	tar -czvf lab7.tgz $(ALLSOURCES)
	
clean:
	rm -rf $(ALLEXECUTABLE) $(ALLOBJECTS) 
