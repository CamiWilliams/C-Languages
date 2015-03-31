all: uthread uthread_tests

clean:
	rm uthread_tests uthread.o

uthread:
	gcc -c uthread.c -lpthread

uthread_tests:
	gcc -o uthread_tests uthread_tests.c -lpthread
