test : test.o base64.o
	g++ -o test test.o base64.o

test.o : test.cc base64.h
	g++ -c test.cc

base64.o : base64.cc base64.h
	g++ -c base64.cc

clean :
	rm *.o