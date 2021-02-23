#include "robot.h"
#include "geom2d.h"
#include "image.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>






int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Usage : %s <pbm> <contour>\n", argv[0]);
		return 1;
	}

    Image img = lire_fichier_image(argv[1]);
	FILE *sortie = fopen(argv[2], "w");
	if (sortie == NULL) {
		printf("Impossible de créer le fichier de contour\n");
		return 1;
	}
    
	Liste_Liste_Point laliste;
    laliste = tracer_tous_les_contours(img);
    int cont = 0;
    int point = 0;
	fprintf(sortie, "%d\n", laliste.taille);
	Cellule_Liste_Liste_Point *cell_cont = laliste.first;
	while (cell_cont) {
        cont++;
		Liste_Point cont = cell_cont->data;
		Cellule_Liste_Point *c = cont.first;
		fprintf(sortie, "%d\n", cont.taille);
		while (c) {
            point++;
			fprintf(sortie, "%f %f\n", c->data.x, c->data.y);
			c = c->suiv;
		}
		cell_cont = cell_cont->suiv;
	}
    
    printf("Nombre de contours : %d\n", cont);
    printf("Nombre de points : %d\n", point);
    printf("Nombre de segments : %d\n", point - cont);


    fclose(sortie);
	
	return 0;
}
