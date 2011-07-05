/**
*
*@author Dinesh Prasanth
*@guidance Prof Jaya S Nair
*
*

*@about class Line for representing a line with only direction for vector (v2 - v1) where v1 and v2 are vectors.
*
*/
#ifndef LINE_H
#define LINE_H
#include "Vector.h"
#include <string.h>
#include<vector>
#include<sstream>
#include<stdlib.h>
using namespace std;

class Line{
public:
	Vector a,b;

	Line(){}
	Line(const Vector A,const Vector B){
		a.x = A.x; b.x = B.x;
		a.y = A.y; b.y = B.y;
		a.z = A.z; b.z = B.z;
		}
	Line(const Line& l){
		a = l.a;
		b = l.b;
		}
	~Line(){}

	string out();
	double length();
	Vector normalize();
	Vector dvector();
	double cos_a();
	double cos_b();
	double cos_g();
	void reverse();
	Vector nextVector(double len);
	double cos( Line& l );		
	double dot( const Line& l );
	Vector cross( const Line& l );

};

#endif
