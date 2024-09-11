all:
	gcc -c -mno-ms-bitfields Buffer.c -o Buffer.o -Wall
	gcc -c -mno-ms-bitfields Queue.c -o Queue.o -Wall
	gcc -c -mno-ms-bitfields Phase1.c -o Phase1.o -Wall
	gcc -c -mno-ms-bitfields UnitTest.c -o UnitTest.o -Wall
	gcc -c -mno-ms-bitfields Project1.c -o Project1.o -Wall
	gcc Buffer.o Phase1.o UnitTest.o Project1.o Queue.o -o Project1_main
	./Project1_main