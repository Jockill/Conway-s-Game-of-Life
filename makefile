FLAGS = -g -Iinclude -I/usr/include/cairo -lcairo -lm -lX11

ifeq ($(MODE),TEXTE)
IO =
else
IO = GUI
endif
LIBPATH = ./lib/
OBJPATH = ./obj/
HEADPATH = ./header/
SRCPATH = ./src/


ifeq ($(MODE),TEXTE)
main: $(OBJPATH)main.o $(OBJPATH)jeu.o $(OBJPATH)io.o $(OBJPATH)grille.o
	gcc $^ $(FLAGS) -o jeuDeLaVie
./obj/main.o: $(SRCPATH)main.c $(HEADPATH)grille.h $(HEADPATH)io.h $(HEADPATH)jeu.h
	mkdir -p $(OBJPATH)
	gcc $(FLAGS) -c $(SRCPATH)main.c -o $@;

else
main: $(OBJPATH)main.o $(OBJPATH)jeu.o $(OBJPATH)ioGUI.o $(OBJPATH)grille.o
	gcc $^ $(FLAGS) -o jeuDeLaVie
./obj/main.o: $(SRCPATH)main.c $(HEADPATH)grille.h $(HEADPATH)ioGUI.h $(HEADPATH)jeu.h
	mkdir -p $(OBJPATH)
	gcc $(FLAGS) -c $(SRCPATH)main.c -o $@;
endif

# ifeq ($(MODE),TEXTE)
# endif




./obj/%.o: $(SRCPATH)%.c $(HEADPATH)%.h
	gcc $(FLAGS) -c $< -o $@

lib: $(OBJPATH)main.o $(OBJPATH)jeu.o $(OBJPATH)io.o $(OBJPATH)grille.o
	mkdir -p $(LIBPATH)
	ar -crv $(LIBPATH)libjeu.a $^
	ranlib $(LIBPATH)libjeu.a

clean:
	rm -r $(OBJPATH)* $(LIBPATH)* jeuDeLaVie doc

dist:
	tar cfJ jeuDeLaVie.tar.xz ./src/ ./header/ ./data/ ./Doxyfile ./makefile ./README.md ./CHANGELOG.md

doc:
	doxygen Doxyfile
