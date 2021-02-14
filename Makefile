CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic
OBJ = PTree.o
DEPS = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXE = tree

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
