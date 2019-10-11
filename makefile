FLAGS = -Wall -Wextra -g
OBJPATH = ./obj/
HEADPATH = ./header/
SRCPATH = ./src/


main: $(OBJPATH)main.o $(OBJPATH)jeu.o $(OBJPATH)io.o $(OBJPATH)grille.o
	gcc $(FLAGS) $^ -o main

./obj/main.o: ./src/main.c ./header/grille.h ./header/io.h ./header/jeu.h
	gcc $(FLAGS) -c ./src/main.c -o $@


./obj/%.o: ./src/%.c ./header/%.h
	gcc $(FLAGS) -c $< -o $@

clean:
	rm $(OBJPATH)(wildcard *)

dist:
	tar cfJ jeuVide.tar.xz ./
