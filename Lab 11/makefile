output : data.h create.h del.h find.h util.h print.h manual_traverse.h insert.h kmin_range.h create.o del.o find.o util.o print.o manual_traverse.o insert.o addbal.o kmin_range.o
	gcc -o final.exe main.o create.o del.o find.o util.o print.o manual_traverse.o insert.o kmin_range.o
	./final.exe
	make clean

main.o : main.c
	gcc -c main.c

create.o : create.c
	gcc -c create.c

del.o : del.c
	gcc -c del.c

find.o : find.c
	gcc -c find.c

util.o : util.c
	gcc -c util.c

print.o : print.c
	gcc -c print.c

manual_traverse.o : manual_traverse.c
	gcc -c manual_traverse.c

insert.o : insert.c
	gcc -c insert.c

kmin_range.o : kmin_range.c
	gcc -c kmin_range.c

clean :
	rm *.o
	rm *.exe