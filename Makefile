

all: grade clean


test:
	@$gcc test.c -o test


grade: test
	@./test

clean:
	@rm -rf *.o test