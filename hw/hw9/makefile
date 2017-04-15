#VARIABLES
COMPLIE = g++
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic -pthread
SOURCES = conServer.cpp conClient.cpp
OBJECTS = conServer.o conClient.o 
EXECUTABLES = conServer conClient
SCRIPTS = conServer.log conClient.log

#TARGETS
all: conServer conClient itServer itClient

conServer: conServer.cpp
	$(COMPLIE) $(FLAGS) conServer.cpp -o conServer

conClient: conClient.cpp
	$(COMPLIE) $(FLAGS) conClient.cpp -o conClient

tar:
	tar -czvf hw9.tgz $(SOURCES) $(SCRIPTS) makefile 

clean:
	rm -rf $(OBJECTS) $(EXECUTABLES)
