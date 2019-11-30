/**
	\file io.c
	\brief Source contenant le corps des fonctions de io.h
	\author JOCHYMSKI Hugo, powered by Unistra.
*/

#include "../header/io.h"
#include "../header/jeu.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>



void cairoAfficheGrille(cairo_surface_t *surface, grille *g, int sizeX, int sizeY, int cellSize, int lineWidth)
{
	cairo_t *cr;
	cr = cairo_create(surface);


	//Background
	cairo_set_source_rgb(cr, 1, 1, 1); //Blanc
	cairo_paint(cr);

	//Lignes verticales
	cairo_set_source_rgb(cr, 0, 0, 0); //Noir
  cairo_set_line_width (cr, lineWidth);
	for(int i=cellSize; i<sizeX; i+=cellSize)
	{
		cairo_move_to(cr, (int)i+(lineWidth/2), 0);
    cairo_line_to(cr, (int)i+(lineWidth/2), sizeY);
    cairo_stroke(cr);
    i+=lineWidth;
	}
	// Lignes horizontales
	for(int i=cellSize; i<sizeY; i+=cellSize)
  {
    cairo_move_to(cr, 0, i+3);
    cairo_line_to(cr, sizeX, i+3);
    cairo_stroke(cr);
    i+=lineWidth;
  }


	// Cellules
	for(int y=0; y<g->nbl; y++)
	{
		for(int x=0; x<g->nbc; x++)
		{
			if(g->cellules[y][x]==-1) cairo_set_source_rgb(cr, 0.00, 0.15, 0.90); //Bleu fonce - Non viable
			else if(g->cellules[y][x] >7 || g->cellules[y][x]==0) cairo_set_source_rgb(cr, 1.00, 1.00, 1.00); //Blanc - Morte
			else if(g->cellules[y][x] == 1)	cairo_set_source_rgb(cr, 0.95, 0.75, 0.00); //Jaune - Vivante
			else if(g->cellules[y][x] >1 && g->cellules[y][x] <8)
			{ //NEED PATCH !
				int ageFact = (g->cellules[y][x]-1)*0.10;
				cairo_set_source_rgb(cr, (0.90-(0.20+ageFact)), (0.75-(ageFact)), 0.00); //Degrade vieillesse
			}
			cairo_rectangle(cr, (x*cellSize+x*lineWidth), (y*cellSize+y*lineWidth), 50, 50);
			cairo_fill(cr);
		}
	}

	cairo_destroy(cr);
}







void debut_jeu(grille *g, grille *gc){
	Display *dpy;
  Window rootwin;
  Window win;
  XEvent e;
  int scr;

	char buff = 0;
	KeySym key;

	g->cyclique = 0;
	g->vieillissement = 0;
	// int sizeX = g->nbc * cellSize + (g->nbc-1)*lineWidth;
	// int sizeY = g->nbl * cellSize + (g->nbl-1)*lineWidth;
	int sizeX = 1225;
	int sizeY = 720;
	int cellSize = 50;
	int lineWidth = 6;


	//Init Display
  if(!(dpy=XOpenDisplay(NULL)))
  {
    fprintf(stderr, "ERREUR\n");
    exit(1);
  }

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, sizeX, sizeY, 0, BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "GameOfLife");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|ButtonReleaseMask|KeyPressMask|KeyReleaseMask);
	XMapWindow(dpy, win);

	//Surface cairo
	cairo_surface_t *cs;
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), sizeX, sizeY);

	//Event loop
	while(1)
	{
		XNextEvent(dpy, &e);
		switch(e.type)
		{
			case Expose:
				cairoAfficheGrille(cs, g, sizeX, sizeY, cellSize, lineWidth);
			break;
			case ButtonPress:
				switch (e.xbutton.button)
				{
					case 1:
						evolue(g, gc);
						cairoAfficheGrille(cs, g, sizeX, sizeY, cellSize, lineWidth);
					break;
					case 3:
						cairo_surface_destroy(cs);
						XCloseDisplay(dpy);
					return;
				}
			break;
			case KeyRelease:
				XLookupString(&e.xkey, &buff, 1, &key, NULL);
				switch(buff)
				{
					case 'c':
						g->cyclique = !g->cyclique;
					break;
					case 'v':
						g->vieillissement = !g->vieillissement;
					break;
					case 'n':
						changementGrille(g, gc);
					break;
					case 'o':
						oscillation(*g, *gc);
					break;
				}
		}
		cairoAfficheGrille(cs, g, sizeX, sizeY, cellSize, lineWidth);

	}


	cairo_surface_destroy(cs);
	XCloseDisplay(dpy);
	return;
}
