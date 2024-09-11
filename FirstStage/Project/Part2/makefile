#CC = gcc
#INC_DIR = Drivers/Phase1
#SRC_DIR = Drivers
#OBJ_DIR = Drivers
#CFLAGS  = -c -Wall -I.
#SRCS = $(SRC_DIR)/Phase1/Phase1.c $(SRC_DIR)/Buffer/Buffer.c
#OBJS = $(OBJ_DIR)/Phase1/Phase1.o $(OBJ_DIR)/Buffer/Buffer.o
## Note: The above will soon get unwieldy.
## The wildcard and patsubt commands will come to your rescue.
#
#DEPS = $(INC_DIR)/Phase1.h
## Note: The above will soon get unwieldy.
## You will soon want to use an automatic dependency generator.
#
#all: $(OBJS)
#
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJ_DIR)/Buffer/Buffer.o: $(DEPS)

#CC=gcc
#INC_DIR = ../../
#CFLAGS=-c -Wall -I$(INC_DIR)
#DEPS = Phase1.h
#
#all: Drivers/Phase1/Phase1.o Drivers/Buffer/Buffer.o
#
#%.o: %.c $(DEPS)
#	$(CC) -o $@ $< $(CFLAGS)
#
#clean:
#	rm -rf *o all

#OTHERDIR = Drivers/Buffer/Buffer.c
#
#VPATH=$(OTHERDIR)
#
#all:
#	gcc -c  Buffer.c -o Buffer.o -Wall
#	gcc -c Queue.c -o Queue.o -Wall
#	gcc -c Phase1.c -o Phase1.o -Wall
#	gcc -c Project2.c -o Project2.o -Wall
#	gcc Buffer.o Phase1.o Project2.o Queue.o -o Project2_main
#	./Project2_main

#OBJDIR = ../Drivers/Buffer/Buffer.c ../Drivers/Phase1/Phase1.c
#
#  VPATH = $(OBJDIR)
#
#  %.o : %.c
#			$(COMPILE.c) $< -o $(OBJDIR)/$@
#
#  all: foo
#
#  foo: Phase1.o Buffer.o
#			$(LINK.o) $^ $(LDLIBS) -o $(OBJDIR)/$@

CC = gcc
CFLAGS = -Wall -g -std=c99 -I

BIN = ./Bin/
SRC = ./Drivers/
INC = ./Drivers/

$(BIN)Project2:     $(BIN)Project2.o $(BIN)Phase1.o $(BIN)Buffer.o $(BIN)Queue.o $(BIN)Scheduler.o
		$(CC) -o $(BIN)Project2 $(BIN)Project2.o $(BIN)Phase1.o $(BIN)Queue.o $(BIN)Scheduler.o

$(BIN)Phase1.o:   $(SRC)Phase1/Phase1.c
	$(CC) $(CFLAGS) -c $(SRC)Phase1.c

$(BIN)Buffer.o:      $(SRC)Buffer/Buffer.c $(INC)Phase1/Phase1.h
	$(CC) $(CFLAGS) -c $(SRC)Buffer/Buffer.c

$(BIN)Queue.o:  $(SRC)Queue/Queue.c $(INC)Phase1/Phase1.h $(INC)Buffer/Buffer.h
	$(CC) $(CFLAGS) -c $(SRC)Queue/Queue.c

$(BIN)Scheduler.o:  $(SRC)Scheduler/Scheduler.c
	$(CC) $(CFLAGS) -c $(SRC)Scheduler/Scheduler.c

$(BIN)Project2.o:   ./Executables/Project2.c ./Drivers/Phase1/Phase1.h ./Drivers/Buffer/Buffer.h ./Drivers/Queue/Queue.c
	$(CC) $(CFLAGS) -c ./Executables/Project2.c