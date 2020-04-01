output : muliq.o driver.o multiq.h
	gcc -pg -o final.exe driver.o muliq.o
	./final.exe
	gprof final.exe gmon.out > prof_output
	make clean

muliq.o : muliq.c
	gcc -c muliq.c

driver.o : driver.c
	gcc -c driver.c

clean :
	rm *.o
	rm *.exe
