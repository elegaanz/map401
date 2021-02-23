#include "robot.h"
#include "geom2d.h"
#include "image.h"





int main(int argc, char **argv) {
	if (argc < 4) {
		printf("Usage: %s <pbm> <sortie> <mode>\n", argv[0]);
		return 1;
	}
    Image img = lire_fichier_image(argv[1]);
    
	Liste_Liste_Point cont = tracer_tous_les_contours(img);
	FILE *sortie = fopen(argv[2], "w");
    Cellule_Liste_Liste_Point *celliste = cont.first;
    char mode = argv[3][0];
	
    fprintf(sortie, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    int l = largeur_image(img);
    int h = hauteur_image(img);
    fprintf(sortie, "%%%%BoundingBox: 0 0 %d %d\n", l, h );
    
    while (celliste != NULL) {
        Cellule_Liste_Point *actcel = celliste->data.first;
        fprintf(sortie, "%.2f %.2f moveto\n", actcel->data.x, h - actcel->data.y);
	    actcel = actcel->suiv;
        while (actcel != NULL) {
            fprintf(sortie, "%.2f %.2f lineto\n", actcel->data.x, h - actcel->data.y);
            actcel = actcel->suiv;
        }
        if ( mode == '1' || mode == '2'){
			fprintf(sortie, "0.1 setlinewidth\n");
            fprintf(sortie, "stroke\n");
        }
        if (mode == '2') {
            actcel = cont.first->data.first;
            while (actcel != NULL) {
                fprintf(sortie, "newpath\n");
                fprintf(sortie, "%.2f %.2f 0.2 0 360  arc\n", actcel->data.x, h - actcel->data.y);
                fprintf(sortie, "0 1 0 setrgbcolor\n");
                fprintf(sortie, "fill\n");
                fprintf(sortie, "closepath\n");
                actcel = actcel->suiv;
            }
        }
        celliste = celliste->suiv;
    }
    if (mode == '3') {
        fprintf(sortie, "fill\n");
    }
    fprintf(sortie, "showpage\n");
	fclose(sortie);
	return 0;
}
