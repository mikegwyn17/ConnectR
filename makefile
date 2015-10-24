#####################################
# Makefile for ConnectR project     #
# Felipe Spinolo                    #
# CS4523-02 Artificial Intelligence #
# Dr. Michael Franklin              #
# Project 2                         #
#####################################

##########
# MACROS #
##########
OBJS = main.o MiniMax.o
CC = g++
DEBUG = -g
CPP11 = -std=c++11
WARNINGS = -Wall -Wextra -pedantic
CFLAGS = $(WARNINGS) -c $(DEBUG) $(CPP11)
LFLAGS = $(WARNINGS) $(DEBUG) $(CPP11)


##############
# EXECUTABLE #
##############
connectR : $(OBJS)
	$(CC) $(LFLAGS) -o connectR $(OBJS)


###########
# OBJECTS #
###########
main.o : MiniMax.h
	$(CC) $(CFLAGS) main.cpp

MiniMax.o : MiniMax.h
	$(CC) $(CFLAGS) MiniMax.cpp


###########
# DUMMIES #
###########
clean:
	\rm -f *.o *~ connectR

