all:
	gcc -c ./Drivers/Scheduler.c -o Bin/Scheduler.o -Wall
	gcc -c ./Drivers/Buffer.c -o Bin/Buffer.o -Wall
	gcc -c ./Drivers/Queue.c -o Bin/Queue.o -Wall
	gcc -c ./Drivers/Phase1.c -o Bin/Phase1.o -Wall
	gcc -c -Wall Project2.c -o Bin/Project2.o
	gcc Bin/Buffer.o Bin/Phase1.o Bin/Queue.o Bin/Scheduler.o Bin/Project2.o -o Project2_main
	./Project2_main