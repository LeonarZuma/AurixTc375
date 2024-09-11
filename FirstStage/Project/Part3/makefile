all:
	gcc -c ./Drivers/Scheduler.c -o Bin/Scheduler.o -Wall
	gcc -c ./Drivers/Buffer.c -o Bin/Buffer.o -Wall
	gcc -c ./Drivers/Queue.c -o Bin/Queue.o -Wall
	gcc -c ./Drivers/Phase1.c -o Bin/Phase1.o -Wall
#	gcc -c ./Drivers/UnitTest.c -o Bin/UnitTest.o -Wall
	gcc -c -Wall Project3.c -o Bin/Project3.o
#	gcc Bin/Buffer.o Bin/Phase1.o Bin/Queue.o Bin/Scheduler.o Bin/Project3.o Bin/UnitTest.o -o Project3_main
	gcc Bin/Buffer.o Bin/Phase1.o Bin/Queue.o Bin/Scheduler.o Bin/Project3.o -o Project3_main
	./Project3_main