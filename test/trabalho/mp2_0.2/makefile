COMPILER=gcc
LINKER=gcc
WARNINGS=-O3 -g -Wall
DO_NOT_LINK=-c
OUTPUT=-o
OBJS=main.o rua.o grafo.o pontoInteresse.o fifo.o misc.o

all: $(OBJS)
	$(LINKER) $(OBJS) $(OUTPUT) file

main.o: main.c all.h
	$(COMPILER) $(DO_NOT_LINK) $(WARNINGS) main.c

pontoInteresse.o: pontoInteresse.c all.h
	$(COMPILER) $(DO_NOT_LINK) $(WARNINGS) pontoInteresse.c

rua.o: rua.c all.h
	$(COMPILER) $(DO_NOT_LINK) $(WARNINGS) rua.c

fifo.o: fifo.c all.h
	$(COMPILER) $(DO_NOT_LINK) $(WARNINGS) fifo.c

grafo.o: grafo.c all.h
	$(COMPILER) $(DO_NOT_LINK) $(WARNINGS) grafo.c

misc.o: misc.c all.h
	$(COMPILER) $(DO_NOT_LINK) $(WARNINGS) misc.c

clean:
	rm -rf *.o *.*~ *~ file
