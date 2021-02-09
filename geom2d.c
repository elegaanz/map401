#include "geom2d.h"
#include "types_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Crée le point de coordonnées (x, y).
 */
Point set_point(double x, double y) {
    Point P = {x, y};
    return P;
}

/**
 * Somme P1 + P2.
 */
Point add_point(Point P1, Point P2) {
    return set_point(P1.x + P2.x, P1.y + P2.y);
}

/**
 * Vecteur correspondant au bipoint AB
 */
Vecteur vect_bipoint(Point A, Point B) {
    Vecteur V = {B.x - A.x, B.y - A.y};
    return V;
}

/**
 * Affiche un point sur la sortie standard
 */
void afficher_point(Point p) { printf("{ %f, %f }", p.x, p.y); }

/*
int main (int argc, char ** argv) {
        Point A, B, C;
        Vecteur U;
        A = set_point(1.0, -3.0);
        B = set_point(4.0, 1.0);
        C = add_point(A, B);
        U = vect_bipoint(C,A);
        printf("C = (%f,%f)\n", C.x, C.y);
        printf("U = (%f,%f)\n", U.x, U.y);
        return 0;
        }
*/