#include<sstream>
#include "Point.h"
#include "Color.h"
#include "Sphere.h"
	string Sphere :: out(){
		stringstream out;
		out<<"Sphere[ "<<o.out()<<" "<<"Radius( "<<r<<" ) "<<c.out()<<" Opacity( "<<a<<" ) "<<"R.Index( "<<u<<" ) ]";
		return out.str();
		}
