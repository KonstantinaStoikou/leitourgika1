OBJS 	= main.o main_functions.o graph.o
SOURCE	= main.c LinkedList.c OrderedLinkedList.c
HEADER  = MyHeader.h LinkedList.h OrderedLinkedList.h
OUT  	= mygraph
CC		= gcc
FLAGS   = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAGS) main.c

main_functions.o: main_functions.c
	$(CC) $(FLAGS) main_functions.c

graph.o: graph.c
	$(CC) $(FLAGS) graph.c

clean:
	rm -f $(OBJS) $(OUT)
