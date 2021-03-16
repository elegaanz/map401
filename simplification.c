#include "robot.h"
#include "geom2d.h"
#include "image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Point nieme (Liste_Point C, int n) {
	Cellule_Liste_Point *cell = C.first;
	while (n > 0) {
		cell = cell->suiv;
		if (cell == NULL) {
			printf("[simplification.c:nieme] n trop grand\n");
		}
		n--;
	}
	return cell->data;
}

Liste_Segment simplification(Liste_Point C, int j1, int j2, float d) {
    int dmax = 0;
    int k = j1;
    for (int j = j1 + 1; j <= j2; j++) {
		double dj = distance_point_segment((Segment){
			nieme(C, j1),
			nieme(C, j2)
		}, nieme(C, j));
		if (dmax < dj) {
			dmax = dj;
			k = j;
		}
	}

    Liste_Segment L = creer_liste_segment_vide();
	if (dmax <= d) {
		L = ajouter_element_liste_segment(L, (Segment){
			nieme(C, j1),
			nieme(C, j2)
		});
	} else {
        Liste_Segment L1 = simplification(C, j1, k, d);
        Liste_Segment L2 = simplification(C, k, j2, d);
		L = concatener_liste_Segment(L1, L2);
    }

	return L;
}



void eps(int h, Liste_Segment segs, FILE *sortie) {
    Cellule_Liste_Segment *cell = segs.first;
	fprintf(sortie, "%.2f %.2f moveto\n", cell->data.a.x, h - cell->data.a.y);
    while (cell != NULL) {
        fprintf(sortie, "%.2f %.2f lineto\n", cell->data.b.x, h - cell->data.b.y);
        cell = cell->suiv;
		if (cell != NULL) {
			fprintf(sortie, "%.2f %.2f lineto\n", cell->data.a.x, h - cell->data.a.y);
		}
    }
}


int main (int argc, char ** argv) {
    if (argc < 3) {
		printf("Usage : %s <pbm> <eps> <seuil>\n", argv[0]);
		return 1;
	}


    Image img = lire_fichier_image(argv[1]);
	FILE *sortie = fopen(argv[2], "w");
	if (sortie == NULL) {
		printf("Impossible de créer le fichier EPS\n");
		return 1;
	}
    

	int seuil;
	sscanf(argv[3], "%d", &seuil);

    //fichier eps
	Liste_Liste_Point cont = tracer_tous_les_contours(img);
    Liste_Segment seg;

    int contseg1 = 0;
    Cellule_Liste_Liste_Point *celliste = cont.first;
    fprintf(sortie, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    int l = largeur_image(img);
    int h = hauteur_image(img);
    fprintf(sortie, "%%%%BoundingBox: 0 0 %d %d\n", l, h );
    int contseg = 0;
    while(celliste != NULL) {
        contseg1 = contseg1 + celliste->data.taille - 1;
        seg = simplification(celliste->data, 0, celliste->data.taille - 1, seuil);
        contseg = contseg + seg.taille;
        eps(h, seg, sortie);
        celliste = celliste->suiv;
    }

    
    
    fprintf(sortie, "fill\n");
    fprintf(sortie, "showpage\n");
	fclose(sortie);

	printf("Nb de contours : %d\n", cont.taille);
    printf("Nb segments avant simplification : %d\n", contseg1);
    printf("Nb segments après simplification : %d\n", contseg);
	return 0;
}