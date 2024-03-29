CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror -std=c89 -g
OBJ = UserInterface.o FileManager.o Game.o LinkedList.o
EXEC = mnk

ifdef SECRET
CFLAGS += -D SECRET
SECRET : clean $(EXEC)
endif

ifdef EDITOR
CFLAGS += -D EDITOR
EDITOR : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

UserInterface.o : UserInterface.c UserInterface.h FileManager.h LinkedList.h Game.h
	$(CC) -c UserInterface.c $(CFLAGS)

FileManager.o : FileManager.c FileManager.h LinkedList.h Game.h
	$(CC) -c FileManager.c $(CFLAGS)

Game.o : Game.c Game.h LinkedList.h FileManager.h
	$(CC) -c Game.c $(CFLAGS)

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)