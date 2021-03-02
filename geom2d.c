#include "geom2d.h"
#include "types_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

Vecteur add_vecteur(Vecteur v, Vecteur u) {
	Vecteur res;
	res.x = v.x + u.x;
	res.y = v.y + u.y;
	return res;
}

/**
 * Affiche un point sur la sortie standard
 */
void afficher_point(Point p) { printf("{ %f, %f }", p.x, p.y); }



double distance_points(Point p, Point q) {
	return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
}


Point mul_point(float lambda, Point A) {
    A.x = A.x * lambda;
    A.y = A.y * lambda;
    return A;
}

Point sub_point(Point P1, Point P2) {
    return set_point(P1.x - P2.x, P1.y - P2.y);
}

double norme(Vecteur v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

double produit_scalaire(Vecteur v, Vecteur u) {
	return 0.5 * (
		pow(norme(add_vecteur(u, v)), 2) -
		pow(norme(u), 2) -
		pow(norme(v), 2)
	);
}



double distance_point_segment(Segment AB, Point C) {
    if (AB.a.x == AB.b.x && AB.a.y == AB.b.y) {
        return distance_points(AB.a, C);
    } else {
        float lambda;
        Vecteur AB_vect = vect_bipoint(AB.b, AB.a);
		Vecteur AC = vect_bipoint(C, AB.a);
        lambda = produit_scalaire(AC, AB_vect) / produit_scalaire(AB_vect, AB_vect);

		if (lambda < 0.0) {
			return distance_points(AB.a, C);
		} else if (lambda <= 1.0) {
			Point q = add_point(
				AB.a,
				mul_point(lambda, sub_point(AB.b, AB.a))
			);
			return distance_points(q, C);
		} else {
            return distance_points(AB.b, C);
		}
    }
}






