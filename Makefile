NTHREADS = cat /proc/cpuinfo | grep processor | wc -l 
EXEC = test

partie1:

.PHONY: clean

clean:
	rm -rf *.o $(EXEC)