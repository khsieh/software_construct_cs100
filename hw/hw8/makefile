#VARIABLES
COMPLIE = g++
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic
SOURCES = conServer.cpp conClient.cpp itServer.cpp itClient.cpp
OBJECTS = conServer.o conClient.o itServer.o itClient.o
EXECUTABLES = conServer conClient itServer itClient
SCRIPTS = itServer.log itClient.log conServer.log conClient1.log conClient2.log conClient3.log

#TARGETS
all: conServer conClient itServer itClient

conServer: conServer.cpp
	$(COMPLIE) $(FLAGS) conServer.cpp -o conServer

conClient: conClient.cpp
	$(COMPLIE) $(FLAGS) conClient.cpp -o conClient

itServer: itServer.cpp
	$(COMPLIE) $(FLAGS) itServer.cpp -o itServer

itClient: itClient.cpp
	$(COMPLIE) $(FLAGS) itClient.cpp -o itClient

tar:
	tar -czvf hw8.tgz $(SOURCES) $(SCRIPTS) makefile

clean:
	rm -rf $(OBJECTS) $(EXECUTABLES)
	
