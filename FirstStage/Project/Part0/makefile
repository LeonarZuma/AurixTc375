all:
	gcc -c -mno-ms-bitfields Buffer.c -o Buffer.o -Wall
	gcc -c -mno-ms-bitfields Phase1.c -o Phase1.o -Wall
	gcc -c -mno-ms-bitfields UnitTest.c -o UnitTest.o -Wall
	gcc -c -mno-ms-bitfields Project0.c -o Project0.o -Wall
	gcc Buffer.o Phase1.o Project0.o UnitTest.o -o Project0_main
	./Project0_main