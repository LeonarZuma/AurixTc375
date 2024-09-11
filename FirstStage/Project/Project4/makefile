all:
	gcc -c ./Drivers/RTCC.c -o Bin/RTCC.o -Wall
	gcc -c ./Drivers/Scheduler.c -o Bin/Scheduler.o -Wall
	gcc -c ./Drivers/Buffer.c -o Bin/Buffer.o -Wall
	gcc -c ./Drivers/Queue.c -o Bin/Queue.o -Wall
	gcc -c ./Drivers/Phase1.c -o Bin/Phase1.o -Wall
	gcc -c -Wall Project4.c -o Bin/Project4.o
	gcc Bin/Buffer.o Bin/Phase1.o Bin/Queue.o Bin/Scheduler.o Bin/Project4.o Bin/RTCC.o -o Project4_main
	./Project4_main

#---Generates project documentation with doxygen---------------------------------------------------
docs :
	doxygen .doxyfile
# chrome Build/doxygen/html/index.html