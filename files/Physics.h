#ifndef PHYSICS_H
#define PHYSICS_H
#include "Vector.h"
#include "Line.h"
#include "Sphere.h"
#include "Point.h"
#include "Color.h"
#include "Plane.h"

Vector reflect_sphere(Point i,Point o,Sphere s);

Vector reflect_plane(Point i,Point o,Plane p);

Vector refract_sphere(Point i,Point o,Sphere s,double n1,double n2);

double shade_sphere(Point o,Point l,Sphere s);	// Light,Intersection point and sphere

double phong_sphere(Point l,Point x,Point i,Sphere s);	// Light,Intersection point and sphere

double shade_plane(Point o,Point l,Plane p);	// Light,Intersection point and plane
#endif
