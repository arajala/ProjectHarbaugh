# Project Chemo Makefile
CC = g++
CFLAGS = -Wall -Werror -std=c++11
OFLAGS = -O3
DFLAGS = -g
GTKFLAGS = `pkg-config --cflags gtk+-3.0`
GTKLIBS = `pkg-config --libs gtk+-3.0`
DLIBS = -pthread
SRC = chemotaxis.cpp
NAME = ct

debug:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(DFLAGS) $(GTKFLAGS) $(GTKLIBS) $(DLIBS)

# g++ -o ct chemotaxis.cpp -Wall -Werror -std=c++11 -O3 `pkg-config --cflags --libs gtk+-3.0` -pthread
all:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(OFLAGS) $(GTKFLAGS) $(GTKLIBS) $(DLIBS)

clean:
	rm $(NAME).*
