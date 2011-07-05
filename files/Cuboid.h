#ifndef CUBOID_H
#define CUBOID_H
#include<sstream>
#include "Plane.h"
#include "Point.h"
#include "Color.h"
class Cuboid {
public:
	Plane p1,p2,p3,p4,p5,p6;
	Cuboid(){}
	Cuboid(Point P1,Point P2,Point P3,Point P4,Point P5,Point P6,Point P7,Point P8){
		p1 = Plane(P1,P2,P3,P4);
		p2 = Plane(P2,P6,P7,P3);
		p3 = Plane(P6,P5,P8,P7);
		p4 = Plane(P5,P1,P4,P8);
		p5 = Plane(P2,P1,P5,P6);
		p6 = Plane(P3,P7,P8,P4);
	}
	Cuboid(Point P1,Point P2,Point P3,Point P4,Point P5,Point P6,Point P7,Point P8,const Color C){
		p1 = Plane(P1,P2,P3,P4,C);
		p2 = Plane(P2,P6,P7,P3,C);
		p3 = Plane(P6,P5,P8,P7,C);
		p4 = Plane(P5,P1,P4,P8,C);
		p5 = Plane(P2,P1,P5,P6,C);
		p6 = Plane(P3,P7,P8,P4,C);
	}
	Cuboid(Point P1,Point P2,Point P3,Point P4,Point P5,Point P6,Point P7,Point P8,const Color C,const double A){
		p1 = Plane(P1,P2,P3,P4,C,A);
		p2 = Plane(P2,P6,P7,P3,C,A);
		p3 = Plane(P6,P5,P8,P7,C,A);
		p4 = Plane(P5,P1,P4,P8,C,A);
		p5 = Plane(P2,P1,P5,P6,C,A);
		p6 = Plane(P3,P7,P8,P4,C,A);
	}
	Cuboid(Plane P1,Plane P2,Plane P3,Plane P4,Plane P5,Plane P6){
		p1 = P1;
		p2 = P2;
		p3 = P3;
		p4 = P4;
		p5 = P5;
		p6 = P6;
	}
	Cuboid(const Cuboid &c){
		p1 = c.p1;	p1.c = c.p1.c;	p1.a = c.p1.a;
		p2 = c.p2;	p2.c = c.p2.c;	p2.a = c.p2.a;
		p3 = c.p3;	p3.c = c.p3.c;	p3.a = c.p3.a;
		p4 = c.p4;	p4.c = c.p4.c;	p4.a = c.p4.a;
		p5 = c.p5;	p5.c = c.p5.c;	p5.a = c.p5.a;
		p6 = c.p6;	p6.c = c.p6.c;	p6.a = c.p6.a;
	}
	~Cuboid(){}
	string out();

};
#endif
