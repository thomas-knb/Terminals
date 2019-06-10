EXEC=terminals
SRC=$(wildcard *.cc)
OBJ=$(SRC:.cc=.o)
CC=g++ -std=c++11 -g
LDFLAGS=-lsfml-graphics  -lsfml-window -lsfml-system
$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS)  -o $(EXEC)
%.o: %.cc
	$(CC) -Wall -c $< -o $@

.depend: $(SRC)
	g++ -std=c++11 -MM $(SRC) > .depend
-include .depend
clean:
	rm -f $(OBJ) $(EXEC)

re: clean $(EXEC)

screen.o: screen.cc screen.h
game.o: game.cc game.h screen.h
main.o: main.cc screen.h point.h
