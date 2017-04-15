#Variables
COMPILE = g++
FLAGS = -ggdb -W -Wall -Werror -ansi -pedantic
ALLSOURCES = leagueOfLegends.cpp leagueOfLegends.h my_shell.cpp Makefile typescript
ALLOBJECTS = leagueOfLegends.o my_shell.o
ALLEXECUTABLE = leagueOfLegends my_shell

#Target
all: leagueOfLegends my_shell
	
leagueOfLegends: leagueOfLegends.cpp leagueOfLegends.h
	$(COMPILE) $(FLAGS) leagueOfLegends.cpp -o leagueOfLegends

my_shell: my_shell.cpp
	$(COMPILE) $(FLAGS) my_shell.cpp -o my_shell
	
tar:
	tar -czvf hw5.tgz $(ALLSOURCES)

strip:
	strip -s $(ALLEXECUTABLE)

print:
	groff -Tps my_shell.cpp > my_shell.ps
	ps2pdf my_shell.ps my_shell.pdf
	
clean:
	rm -rf $(ALLEXECUTABLE) $(ALLOBJECTS) my_shell.ps
