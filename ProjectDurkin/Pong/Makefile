# Project Durkin Makefile

# Global flags
CC = g++
CFLAGS = -Wall -Werror -std=c++11
OFLAGS = -O3
DFLAGS = -g
GTKFLAGS = `pkg-config --cflags gtk+-3.0`
GTKLIBS = `pkg-config --libs gtk+-3.0`
DLIBS = -ldl -pthread

# Pong flags
PONG_SRC = Pong.cpp
PONG_NAME = pong

# Player flags
PLYR_SRC = Player.cpp
PLYR_NAME = player

# AI flags
AI_SRC = AI.cpp
AI_NAME = ai

all: pong player ai

pong: $(PONG_SRC)
	$(CC) -o $(PONG_NAME) $(PONG_SRC) $(CFLAGS) $(DLIBS)

player: $(PLYR_SRC)
	$(CC) -o $(PLYR_NAME) $(PLYR_SRC) $(CFLAGS) $(DLIBS) $(GTKFLAGS) $(GTKLIBS)

ai: $(AI_SRC)
	$(CC) -o $(AI_NAME) $(AI_SRC) $(CFLAGS) $(DLIBS) $(GTKFLAGS) $(GTKLIBS)

clean: clean_pong clean_player clean_ai

clean_pong:
	rm $(PONG_NAME)

clean_player:
	rm $(PLYR_NAME)

clean_ai:
	rm $(AI_NAME)
