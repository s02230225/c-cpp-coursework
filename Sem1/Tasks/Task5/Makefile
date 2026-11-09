PROG = shell
CFLAGS = -g -Wall
all: $(PROG)

isword.o: isword.c isword.h
	$(CC) $(CFLAGS) -c $< -o $@
list.o: list.c list.h
	$(CC) $(CFLAGS) -c $< -o $@
tree.o: tree.c tree.h list.o isword.o
	$(CC) $(CFLAGS) -c $< -o $@
shlfunc.o: shlfunc.c shlfunc.h tree.o list.o 
	$(CC) $(CFLAGS) -c $< -o $@
$(PROG): shell.c list.o tree.o shlfunc.o isword.o
	$(CC) $(CFLAGS) shell.c list.o tree.o shlfunc.o isword.o -o $(PROG)

clean:
	rm -f *.o $(PROG)

run:
	valgrind --leak-check=full ./$(PROG)
