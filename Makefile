all: mi mc mb

mi: mi.c
	gcc -O2 mi.c -o mi

mc: mc.c
	gcc -O2 mc.c -o mc

mb: mb.c
	gcc -O2 mb.c -o mb

clean:
	rm -f mc mi mb *.o

tar:
	tar cvf mouse.tar *.c *.m Makefile
	gzip mouse.tar
