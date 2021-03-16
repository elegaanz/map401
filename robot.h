#ifndef _ROBOT_H_
#define _ROBOT_H_
#include "geom2d.h"
#include "image.h"
#include "types_macros.h"

typedef enum { Nord, Est, Sud, Ouest } Orientation;

typedef struct Cellule_Liste_Point_ {
    Point data;
    struct Cellule_Liste_Point_ *suiv;
} Cellule_Liste_Point;

typedef struct Liste_Point_ {
    UINT taille;
    Cellule_Liste_Point *first;
    Cellule_Liste_Point *last;
} Liste_Point;

typedef Liste_Point Contour;

typedef struct Tableau_Point_ {
    UINT taille;
    Point *tab;
} Tableau_Point;

Cellule_Liste_Point *creer_element_liste_Point(Point v);

Liste_Point creer_liste_Point_vide();

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);


void ecrire_contour(Liste_Point L);

Liste_Point tracer_contour(Image img, Image masque, UINT x, UINT y);

typedef struct Cellule_Liste_Liste_Point_ {
	Liste_Point data;
	struct Cellule_Liste_Liste_Point_ *suiv;
} Cellule_Liste_Liste_Point;

typedef struct {
	UINT taille;
	Cellule_Liste_Liste_Point *first;
	Cellule_Liste_Liste_Point *last;
} Liste_Liste_Point;


typedef struct Cellule_Liste_Segment_ {
    Segment data;
    struct Cellule_Liste_Segment_ *suiv;
} Cellule_Liste_Segment;

typedef struct Liste_Segment_ {
    UINT taille;
    Cellule_Liste_Segment *first;
    Cellule_Liste_Segment *last;
} Liste_Segment;

Liste_Segment creer_liste_segment_vide();

Liste_Segment ajouter_element_liste_segment(Liste_Segment L, Segment e);

Liste_Segment supprimer_liste_segment(Liste_Segment L);

Liste_Segment concatener_liste_Segment(Liste_Segment L1, Liste_Segment L2);


Image creation_image_masque(Image img);

Liste_Liste_Point tracer_tous_les_contours(Image img);

#endif
