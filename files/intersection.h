#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Object.h"
#include "Line.h"
#include "Point.h"
#include "Vector.h"
#include "Lineseg.h"
#include<math.h>
#include "Plane.h"
Point ray_sphere(Point p,Vector v,Sphere s,double &len);
Point ray_sphere(Point p,Vector v,Sphere s);
Point inside_ray_sphere(Point p,Vector v,Sphere s,double &len);
bool shadow_check( Point in,const Point l, Object ob);
Point ray_plane(Point p,Vector dr,Plane l,double &len);
Point ray_plane(Point p,Vector dr,Plane l);

#endif
