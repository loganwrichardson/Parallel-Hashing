CC = gcc
CFLAGS = -g -c -Wall
OBJ = bst.o BSTv1.o helpers.o BSTv2.o BSTv3.o BSTv4.o \
 wrappers.o

.c.o:
	$(CC) $(CFLAGS) $< -o $@

bst: $(OBJ)
	gcc $(OBJ) -o bst -lpthread

bst.o: BSTversions.h 

BSTv1.o: BSTv1.c helpers.h macros.h

BSTv2.o: BSTv2.c helpers.h macros.h

BSTv3.o: BSTv3.c helpers.h macros.h

BSTv4.o: BSTv4.c helpers.h macros.h

helpers.o: helpers.c helpers.h

wrappers.o: wrappers.h wrappers.c

clean:
	rm *.o
	rm bst
