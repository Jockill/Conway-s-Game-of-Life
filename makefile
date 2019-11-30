FLAGS = -Iinclude -I/usr/include/cairo -lcairo -lm -lX11

LIBPATH = ./lib/
OBJPATH = ./obj/
HEADPATH = ./header/
ifeq ($(MODE),TEXTE)
SRCPATH = ./src/
else
SRCPATH = ./srcGUI/
endif



main: $(OBJPATH)main.o $(OBJPATH)jeu.o $(OBJPATH)io.o $(OBJPATH)grille.o
	gcc $^ $(FLAGS) -o jeuDeLaVie


./obj/main.o: $(SRCPATH)main.c $(HEADPATH)grille.h $(HEADPATH)io.h $(HEADPATH)jeu.h
	mkdir -p $(OBJPATH)
	gcc $(FLAGS) -c $(SRCPATH)main.c -o $@;\


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
