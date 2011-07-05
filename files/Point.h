/**
*
*@author Dinesh Prasanth
*@guidance Prof Jaya S Nair
*
*

*@about class Point to define any point in 3 dimensional space.
*
*/
#ifndef POINT_H
#define POINT_H
#include<iostream>
#include<math.h>
#include<string>
#include<stdlib.h>
#include<sstream>
#include"Vector.h"
#include"functions.h"
#include "Line.h"
class Point{
public:

	double x,y,z;



// Defining Constructors for the class
	Point(){
		x=0.0;
		y=0.0;
		z=0.0;
		}
	Point(double X,double Y,double Z){
		x=X;
		y=Y;
		z=Z;
		}
	Point(const Point& p){
		x = p.x;
		y = p.y;
		z = p.z;
		}
	~Point(){}


//Assignment operator

	Point& operator= (const Point& p);

//Output Format of the point

	string out();

//Equality operators
	bool operator== (Point& p);
	bool operator!= (Point& p);
// Arithematic operations
	Point& operator+(const Vector& v);
	Vector operator-(const Point& p);
	Point operator- (const Vector& v);
	Point operator- ();
	// function for finding if passed point is lying in the same direction of passed vector from this point as starting point
	bool isdirection(Vector v,Point t);	// direction vector | testing point passed
	double length(const Point p);

};
// defining functions for points
	

	Point affine( const Point& p1 , const Point &p2 , const double t );
	Point affine( const Point& p1,const Point& p2,const Point& p3,const double a1,const double a2,const double a3 );
	Point midpoint( const Point& p1,const Point& p2 );

#endif
