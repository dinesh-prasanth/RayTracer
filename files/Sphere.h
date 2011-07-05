#ifndef SPHERE_H
#define SPHERE_H
#include<sstream>
#include "Point.h"
#include "Color.h"
class Sphere{
public:
	Point o;
	double r;
	Color c;
	double a;	//opacity
	double u;	// refractive index
	Sphere(){
		r=0.0;a = 1.0;u=1.5;
		}
	Sphere(const Point& O,const double R,const Color& C,const double A){
		o = O;
		r = R;
		c = C;
		a = A;
		}
	Sphere(const Point& O,const double R,const Color& C){
		o = O;
		r = R;
		c = C;
		}
	Sphere(const Point& O,const double R,const Color& C,const double A,const double U){
		o = O;
		r = R;
		c = C;
		a = A;
		u = U;
		}
	Sphere(const Sphere& s){
		o = s.o;
		r = s.r;
		c = s.c;
		a = s.a;
		u = s.u;		
		}
	~Sphere(){}
	

	string out();
};

#endif
