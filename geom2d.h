#ifndef _GEOM2D_H_
#define _GEOM2D_H_

#include "types_macros.h"

typedef struct Vecteur_ {
    double x, y;
} Vecteur;

typedef struct Point_ {
    double x, y;
} Point;

typedef struct Segment_ {
	Point a, b;
} Segment;

/**
 * Crée le point de coordonnées (x, y).
 */
Point set_point(double x, double y);

/**
 * Somme P1 + P2.
 */
Point add_point(Point P1, Point P2);

/**
 * Vecteur correspondant au bipoint AB
 */
Vecteur vect_bipoint(Point A, Point B);

void afficher_point(Point p);

/**
* 
*/
double distance_point_segment(Segment s, Point p);

#endif
