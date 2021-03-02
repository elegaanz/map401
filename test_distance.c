#include "geom2d.h"
#include <stdio.h>

int main(int argc, char** argv) {
	FILE *input = stdin;
	if (argc == 2) {
		input = fopen(argv[1], "r");
		if (input == NULL) {
			perror("Erreur : ");
			return 1;
		}
	}

    Point P;
    Point A;
    Point B;
	if (input == stdin) printf("Coordonnées de P : ");
	fscanf(input, "%lf %lf", &P.x, &P.y);
    if (input == stdin) printf("Coordonnées de A : ");
	fscanf(input, "%lf %lf", &A.x, &A.y);
    if (input == stdin) printf("Coordonnées de B : ");
	fscanf(input, "%lf %lf", &B.x, &B.y);

	Segment AB = { A, B };
	printf("Distance entre P et AB : %f\n", distance_point_segment(AB, P));
	return 0;
}