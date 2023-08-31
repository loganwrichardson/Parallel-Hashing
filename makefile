IDIR =./include
BINDIR=./
BIN=hash
OBJDIR=./obj
SRCDIR=./src

CC=gcc
CFLAGS=-I$(IDIR) -g -c -Wall
LFLAGS=-lpthread

_OBJ = producerConsumer1.o producerConsumer2.o linked_list.o hash_table.o \
	Hashingv1.o Hashingv2.o Hashingv3.o Hashingv4.o hashing.o helpers.o wrappers.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

_DEPS= hash_table.h hashingversions.h helpers.h linked_list.h macros.h producerConsumer1.h \
	producerConsumer2.h wrappers.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

$(BIN): $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY run:
run: $(BIN)
	 ./$(BIN) $(args)

.PHONY clean:
	rm $(OBJDIR)/*.o
	rm $(BIN)