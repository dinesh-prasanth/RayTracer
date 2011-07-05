#include "Plane.h"
#include "Point.h"
#include "Color.h"
#include <sstream>
string Plane :: out(){
	stringstream out;
	out<<"Plane[ "<<p1.out()<<" "<<p2.out()<<" "<<p3.out()<<" "<<p4.out()<<" "<<c.out()<<" Opacity( "<<a<<" ) ]";
	return out.str();
}
bool Plane :: operator!= ( Plane& pl){
	if((p1==pl.p1)&&(p2==pl.p2)&&(p3==pl.p3)&&(p4==pl.p4))
		return 0;
	else
		return 1;

}
