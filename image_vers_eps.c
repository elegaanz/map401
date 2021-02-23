#include "robot.h"
#include "geom2d.h"
#include "image.h"





int main(int argc, char **argv) {
	if (argc < 4) {
		printf("Usage: %s <pbm> <sortie> <mode>\n", argv[0]);
		return 1;
	}
    Image img = lire_fichier_image(argv[1]);
    ecrire_image(img);
	Liste_Point cont = tracer_contour(img);
	FILE *sortie = fopen(argv[2], "w");

    char mode = argv[3][0];
	
    fprintf(sortie, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    int l = largeur_image(img);
    int h = hauteur_image(img);
    fprintf(sortie, "%%%%BoundingBox: 0 0 %d %d\n", l, h );
    Cellule_Liste_Point *actcel = cont.first;
    fprintf(sortie, "%.2f %.2f moveto\n", actcel->data.x, h - actcel->data.y);
	actcel = actcel->suiv;
    while (actcel != NULL) {
        fprintf(sortie, "%.2f %.2f lineto\n", actcel->data.x, h - actcel->data.y);
        actcel = actcel->suiv;
    }
    fprintf(sortie, "0.1 setlinewidth\n");
    if ( mode == '1' || mode == '2'){
        fprintf(sortie, "stroke\n");
    } else {
        fprintf(sortie, "fill\n");
    }

    if (mode == '2') {
		actcel = cont.first;
		while (actcel != NULL) {
			fprintf(sortie, "newpath\n");
			fprintf(sortie, "%.2f %.2f 0.2 0 360  arc\n", actcel->data.x, h - actcel->data.y);
			fprintf(sortie, "0 1 0 setrgbcolor\n");
			fprintf(sortie, "fill\n");
			fprintf(sortie, "closepath\n");
			actcel = actcel->suiv;
		}
    }
    fprintf(sortie, "showpage\n");
	fclose(sortie);
	return 0;
}
