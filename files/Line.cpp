/**
*
*@author Dinesh Prasanth
*@guidance Prof Jaya S Nair
*
*

*@about class Line for representing a line with only direction for vector (v2 - v1) where v1 and v2 are vectors.
*
*/
#include "Vector.h"
#include <string.h>
#include<vector>
#include<sstream>
#include<stdlib.h>
#include "Line.h"
#include "math.h"
using namespace std;

	string Line :: out(){
		stringstream out;
		out<<"Line[ ";
		out<<a.out()<<" "<<b.out()<<" ]";
		return out.str();
	}
	double Line :: length(){
		double l;
		l = sqrt(((b.x-a.x)*(b.x-a.x)) + ((b.y-a.y)*(b.y-a.y)) + ((b.z-a.z)*(b.z-a.z)));
		return l;
	}
	Vector Line :: normalize(){
		Vector v;		
		double  l = length();
		v.x = (b.x-a.x)/l;
		v.y = (b.y-a.y)/l;
		v.z = (b.z-a.z)/l;
		return v;
	}
	Vector Line :: dvector(){
		Vector v = Vector(b.x-a.x,b.y-a.y,b.z-a.z);
		return v;
	}
	double Line :: cos_a(){
		if(length()>0)
			return ((b.x-a.x)/length());
		else
			cout<<"Logical Error occured.\n";return 0;	
	}
	double Line :: cos_b(){
		if(length()>0)
			return ((b.y-a.y)/length());
		else
			cout<<"Logical Error occured.\n";return 0;	
	}
	double Line :: cos_g(){
		if(length()>0)
			return ((b.z-a.z)/length());
		else
			cout<<"Logical Error occured.\n";return 0;	
	}
	void Line :: reverse(){
		Vector temp;
		temp = a;
		a = b;
		b = temp;
	}
	Vector Line :: nextVector(double len){
		Vector v;
		v.x = a.x + (len*cos_a());
		v.y = a.y + (len*cos_b());
		v.z = a.z + (len*cos_g());
		return v;
	}
		
	double Line :: dot( const Line& l ){
		double d;
		d = ((b.x-a.x)*(l.b.x-l.a.x)) + ((b.y-a.y)*(l.b.y-l.a.y)) + ((b.z-a.z)*(l.b.z-l.a.z));
		return d;
	}
	Vector Line :: cross( const Line& l ){
		Vector v;
		v.x = ( (b.y-a.y) * (l.b.z-l.a.z) - (b.z-a.z) * (l.b.y-l.a.y) );
		v.y = ( (b.z-a.z) * (l.b.x-l.a.x) - (b.x-a.x) * (l.b.z-l.a.z) );
		v.z = ( (b.x-a.x) * (l.b.y-l.a.y) - (b.y-a.y) * (l.b.x-l.a.x) );
		return v;
	}
	double Line :: cos( Line& l ){
		Vector v1 = dvector();
		Vector v2 = l.dvector();
		return ( v1.dot(v2) / sqrt((v2.x-v1.x)*(v2.x-v1.x)+(v2.y-v1.y)*(v2.y-v1.y)+(v2.z-v1.z)*(v2.z-v1.z)) );
	}

//	double Line :: angle( const Line& l ){
//		Vector v = dvector;
//		return acos(v.dot(l.dvector())/)
//	}
