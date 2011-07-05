/**
*
*@author Dinesh Prasanth
*@guidance Prof Jaya S Nair
*
*

*@about class Vector for representing a vector in free space and functions for mathematical operations in a vector.
*
*/
#ifndef VECTOR_H
#define VECTOR_H
#include<iostream>
#include<math.h>
#include<string>
#include<stdlib.h>
#include<sstream>
using namespace std;

class Vector {

// co ordinates in the 3d space
public:
	double x,y,z;

// defining constructors for the class
	Vector(){
		x=0.0;y=0.0;z=0.0;
	}

	Vector(const double X,const double Y,const double Z){
		x=X;y=Y;z=Z;
	}
	
	Vector(const Vector& v){
		x=v.x; y=v.y; z=v.z;
	}

	~Vector(){
		
	}
	
// return the private information
//------------------------------------------------------------------------------------------>
	double getx() {return x;}
	double gety() {return y;}
	double getz() {return z;}


	Vector& operator= (const Vector& v);
	string out();
	bool operator== (const Vector& v2);
	bool operator!= (const Vector& v2);
	Vector operator+ (const Vector& v1);
	Vector operator- (const Vector& v1);
	Vector operator* (const double& c);
	Vector& operator/ (const double&c );
	double cos_a();
	double cos_b();
	double cos_g();
	double length();
	bool issame(Vector v);
	void negate();
	void normalize();
	void perpendicular();
	Vector nextVector(double len);
	double dot( const Vector& v );
	Vector& cross( const Vector& v );

};

#endif
