CC = gcc
CFLAGS = -g -c -Wall
OBJ = bst.o BSTv1.o helpers.o BSTv2.o BSTv3.o BSTv4.o \
 wrappers.o producerConsumer1.o	producerConsumer2.o linked_list.o hash_table.o \
 Hashingv1.o Hashingv2.o Hashingv3.o

.c.o:
	$(CC) $(CFLAGS) $< -o $@

bst: $(OBJ)
	gcc $(OBJ) -o bst -lpthread

bst.o: BSTversions.h 

BSTv1.o: BSTv1.c helpers.h macros.h

Hashingv1.o: Hashingv1.c hash_table.h linked_list.h

Hashingv2.o: Hashingv2.c hash_table.h linked_list.h

Hashingv3.o: Hashingv3.c Hashingv3.h linked_list.h

BSTv2.o: BSTv2.c helpers.h macros.h

BSTv3.o: BSTv3.c helpers.h macros.h

BSTv4.o: BSTv4.c helpers.h macros.h

helpers.o: helpers.c helpers.h

wrappers.o: wrappers.c wrappers.h

producerConsumer1.o: producerConsumer1.c producerConsumer1.h

producerConsumer2.o: producerConsumer2.c producerConsumer2.h

hash_table.o: hash_table.c hash_table.h linked_list.h

linked_list.o: linked_list.c linked_list.h

main.o: main.c linked_list.h hash_table.h

main: main.o linked_list.o hashing.o
	$(CC) -o test_structs $^

clean:
	rm *.o
	rm bst
	rm a.out
