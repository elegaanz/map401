#include "robot.h"
#include "geom2d.h"
#include "image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cellule_Liste_Point *creer_element_liste_Point(Point v) {
    Cellule_Liste_Point *el;
    el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_Point : allocation impossible \n");
        exit(-1);
    }
    el->suiv = NULL;
    el->data = v;
    return el;
}

Liste_Point creer_liste_Point_vide() {
    Liste_Point L = {0, NULL, NULL};
    return L;
}

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e) {
    Cellule_Liste_Point *el;
    el = creer_element_liste_Point(e);
    if (L.taille == 0) {
        L.first = L.last = el;
    } else {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

Liste_Point supprimer_liste_Point(Liste_Point L) {
    Cellule_Liste_Point *el = L.first;
    while (el) {
        Cellule_Liste_Point *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2) {
    if (L1.taille == 0)
        return L2;
    if (L2.taille == 0)
        return L1;

    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;
    return L1;
}

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L) {
    Tableau_Point T;
    T.taille = L.taille;

    T.tab = malloc(sizeof(Point) * T.taille);
    if (T.tab == NULL) {
        fprintf(stderr, "sequence_points_liste_vers_tableau : ");
        fprintf(stderr, "allocation impossible\n");
        exit(-1);
    }

    int k = 0;
    Cellule_Liste_Point *el = L.first;
    while (el) {
        T.tab[k] = el->data;
        k++;
        el = el->suiv;
    }
    return T;
}

void ecrire_contour(Liste_Point L) {
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int k;
    int nP = TP.taille;
    printf("%d points : [", nP);
    for (k = 0; k < nP; k++) {
        Point P = TP.tab[k];
        printf(" (%5.1f, %5.1f)", P.x, P.y);
    }
    printf("]\n");
    free(TP.tab);
}

bool trouver_pixel_depart(Image img, UINT *x, UINT *y) {
    for (int i = 1; i <= img.H; i++) {
        for (int j = 1; j <= img.L; j++) {
            if (get_pixel_image(img, j, i) == NOIR &&
                get_pixel_image(img, j, i - 1) == BLANC) {
                *x = j;
                *y = i;
                return true;
            }
        }
    }
    return false;
}

void memoriser_position(Liste_Point *contour, Point position) {
    *contour = ajouter_element_liste_Point(*contour, position);
}

void tourner_a_gauche(Orientation *o) {
    switch (*o) {
    case Nord:
        (*o) = Ouest;
        break;
    case Sud:
        (*o) = Est;
        break;
    case Est:
        (*o) = Nord;
        break;
    case Ouest:
        (*o) = Sud;
        break;
    }
}

void tourner_a_droite(Orientation *o) {
    switch (*o) {
    case Nord:
        *o = Est;
        break;
    case Sud:
        *o = Ouest;
        break;
    case Ouest:
        *o = Nord;
        break;
    case Est:
        *o = Sud;
        break;
    }
}

Orientation nouvelle_orientation(Image img, Point position, Orientation o) {
    Pixel pG, pD;
    switch (o) {
    case Est:
        pG =
            get_pixel_image(img, (int)ceil(position.x), (int)floor(position.y));
        pD = get_pixel_image(img, (int)ceil(position.x), (int)ceil(position.y));
        break;
    case Ouest:

        pG =
            get_pixel_image(img, (int)floor(position.x), (int)ceil(position.y));
        pD = get_pixel_image(img, (int)floor(position.x),
                             (int)floor(position.y));
        break;

    case Nord:
        pG = get_pixel_image(img, (int)floor(position.x),
                             (int)floor(position.y));
        pD =
            get_pixel_image(img, (int)ceil(position.x), (int)floor(position.y));
        break;

    case Sud:
        pG = get_pixel_image(img, (int)ceil(position.x), (int)ceil(position.y));
        pD =
            get_pixel_image(img, (int)floor(position.x), (int)ceil(position.y));
        break;
    }
    if (pG == NOIR) {
        tourner_a_gauche(&o);
    } else if (pD == BLANC) {
        tourner_a_droite(&o);
    }
    return o;
    /*printf("gauche = ");
    if (pG == NOIR) printf("noir\n"); else printf("blanc\n");
    printf("droite = ");
    if (pD == NOIR) printf("noir\n"); else printf("blanc\n");
    */
}

Point avancer(Image img, Point position, Orientation o) {
    switch (o) {
    case Est:
        return set_point(position.x + 1.0, position.y);
    case Ouest:
        return set_point(position.x - 1.0, position.y);
    case Nord:
        return set_point(position.x, position.y - 1.0);
    case Sud:
        return set_point(position.x, position.y + 1.0);
    }
}

bool double_egal(double a, double b) {
    static double EPSILON = 0.01;
    double diff = a - b;

    return (-EPSILON < diff) && (diff < EPSILON);
}

Liste_Point tracer_contour(Image img, Image masque, UINT x, UINT y) {
    Liste_Point contour = creer_liste_Point_vide();
    double x0, y0;
    /*if (!trouver_pixel_depart(img, &x, &y)) {
        // on retourne une liste vide si jamais il n'y a aucun
        // pixel de départ possible (l'image est surement vide)
        return contour;
    }*/
    Point position;
    x0 = x - 0.5;
    y0 = y - 0.5;
    position.x = x0;
    position.y = y0;
    Orientation orientation = Est;
    bool boucle = true;
	printf("----\n");
    while (boucle) {
		if (orientation == Est) {
			printf("set_pixel %d %d \n", (int)ceil(position.x), (int)ceil(position.y));
			set_pixel_image(masque, (int)ceil(position.x), (int)ceil(position.y), BLANC);
        }
        memoriser_position(&contour, position);
        position = avancer(img, position, orientation);
        orientation = nouvelle_orientation(img, position, orientation);

		printf("%f, %f %d\n", position.x, position.y, orientation);
		ecrire_image(masque);

        if (double_egal(position.x, x0) && double_egal(position.y, y0) &&
            orientation == Est) {

            boucle = false;
        }
    }
    memoriser_position(&contour, position);
    return contour;
}


Image creation_image_masque(Image img) {
    Pixel pi;
    Pixel voisin;
    printf("création masque \n");
    Image masque = creer_image(img.L, img.H);
    for (int i = 1; i<=img.L; i++){
        for (int j = 1; j<=img.H; j++) {
            pi = get_pixel_image(img, i, j);
            voisin = get_pixel_image(img, i, j-1);
            if (pi == NOIR && voisin == BLANC) {
                set_pixel_image(masque, i, j, NOIR);
            }
        }
    }
	return masque;
}



Liste_Liste_Point tracer_tous_les_contours(Image img) {
	Image masque = creation_image_masque(img);
	Liste_Liste_Point contour_au_pluriel;
    printf("tracer les contours \n");
	contour_au_pluriel.first = NULL;
	contour_au_pluriel.last = NULL;
	contour_au_pluriel.taille = 0;
	for (int y = 1; y <= img.H; y++) {
		for (int x = 1; x < img.L; x++) {
			if (get_pixel_image(masque, y, x) == NOIR) {
                Liste_Point contour_au_singulier;
				contour_au_singulier = tracer_contour(img, masque, x, y);
				Cellule_Liste_Liste_Point *cell_cont = malloc(sizeof(Cellule_Liste_Liste_Point));
				cell_cont->suiv = NULL;
				cell_cont->data = contour_au_singulier;

				if (contour_au_pluriel.taille == 0) {
					contour_au_pluriel.first = cell_cont;
					contour_au_pluriel.last = cell_cont;
				} else {
					contour_au_pluriel.last->suiv = cell_cont;
					contour_au_pluriel.last = cell_cont;
				}
				contour_au_pluriel.taille++;
                printf("wesh c fini \n\n\n\n\n\n\n\n\n\n");
			}
		}
	}
	
	return contour_au_pluriel;
}