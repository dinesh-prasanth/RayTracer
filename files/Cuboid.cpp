#include<sstream>
#include "Plane.h"
#include "Cuboid.h"
string Cuboid :: out(){
	stringstream out;
	out<<"Cuboid [ "<<p1.out()<<" "<<p2.out()<<" "<<p3.out()<<" "<<p4.out()<<" "<<p5.out()<<" "<<p6.out()<<" ]";
	return out.str();
}
