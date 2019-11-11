FLAGS = -Wall -Wextra -g
OBJPATH = ./obj/
HEADPATH = ./header/
SRCPATH = ./src/


main: $(OBJPATH)main.o $(OBJPATH)jeu.o $(OBJPATH)io.o $(OBJPATH)grille.o
	gcc $(FLAGS) $^ -o jeuDeLaVie

./obj/main.o: $(SRCPATH)main.c $(HEADPATH)grille.h $(HEADPATH)io.h $(HEADPATH)jeu.h
	mkdir -p $(OBJPATH)
	gcc $(FLAGS) -c $(SRCPATH)main.c -o $@


./obj/%.o: $(SRCPATH)%.c $(HEADPATH)%.h
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -r $(OBJPATH)* jeuDeLaVie doc

dist:
	tar cfJ jeuDeLaVie.tar.xz ./src/ ./header/ ./data/ ./Doxyfile ./makefile ./README.md ./CHANGELOG.md

doc:
	doxygen Doxyfile
