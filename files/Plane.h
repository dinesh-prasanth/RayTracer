#ifndef PLANE_H
#define PLANE_H
#include<sstream>
#include "Point.h"
#include "Color.h"

class Plane{
public:
	Point p1,p2,p3,p4;
	Color c;
	double a;		//Opacity
	Plane(){
		a=1.0;
		}
	Plane(const Point P1,const Point P2,const Point P3,const Point P4){
		p1 = P1;
		p2 = P2;
		p3 = P3;
		p4 = P4;
		}
	Plane(const Point P1,const Point P2,const Point P3,const Point P4,const Color C){
		p1 = P1;
		p2 = P2;
		p3 = P3;
		p4 = P4;
		c = C;
		}
	Plane(const Point P1,const Point P2,const Point P3,const Point P4,const Color C,const double A){
		p1 = P1;
		p2 = P2;
		p3 = P3;
		p4 = P4;
		c = C;
		a = A;
		}
	Plane(const Plane& p){
		p1 = p.p1;
		p2 = p.p2;
		p3 = p.p3;
		p4 = p.p4;
		c = p.c;
		a = p.a;
		}
	~Plane(){}
	string out();
	bool operator!= (Plane& p);

};

#endif
