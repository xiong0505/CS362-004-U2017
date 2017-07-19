CFLAGS = -Wall -fpic -coverage -lm

testme: 
	echo "Result for running quiz2 testme.c:">randomtestresults.out
	gcc -o testme -g testme.c $(CFLAGS)
	testme>>randomtestresults.out
	gcov testme.c >> randomtestresults.out

all: testme

clean:
	rm -f *.exe *.gcno *.gcda *.out *.gcov testme 