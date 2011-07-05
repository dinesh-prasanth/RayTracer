#include<iostream>
#include<math.h>
#include<string>
#include<stdlib.h>
#include<sstream>
#include"Vector.h"
#include"functions.h"
#include "Line.h"
#include "Point.h"
//Assignment operator

	Point& Point :: operator= (const Point& p){
		if (this == &p) return (*this);
		else{
			x = p.x;
			y = p.y;
			z = p.z;
			return (*this);
		}
		}

//Output Format of the point

	string Point :: out(){
		stringstream out;
		out<<"( "<<x<<", "<<y<<", "<<z<<" )";
		return out.str();
		}

//Equality operators
	bool Point :: operator== (Point& p){
		if((x==p.x)&&(y==p.y)&&(z==p.z))
			return 1;
		else
			return 0;
		}
	bool Point :: operator!= (Point& p){
		if((x!=p.x)||(y!=p.y)||(z!=p.z))
			return 1;
		else
			return 0;
		}
// Arithematic operations
	Point& Point :: operator+(const Vector& v){
		x = x + v.x;
		y = y + v.y;
		z = z + v.z;
		return (*this);
		}
	
	Vector Point :: operator-(const Point& p){
		Vector v;
		v.x = x - p.x;
		v.y = y - p.y;
		v.z = z - p.y;
		return v;
		}

	Point Point :: operator- (const Vector& v){
		x = x - v.x;
		y = y - v.y;
		z = z - v.z;
		return (*this);
		}

	Point Point :: operator- (){
		x = -x;
		y = -y;
		z = -z;
		return (*this);
		}
	// function for finding if passed point is lying in the same direction of passed vector from this point as starting point
	bool Point :: isdirection(Vector v,Point t){	// direction vector | testing point passed
		Vector t_v = Vector(t.x,t.y,t.z);
		Vector o_v = Vector(x,y,z);
		Line T = Line(o_v,t_v);
		T.normalize();
		//v.negate();
		if(v.issame(T.dvector())){//cout<<v.out()<<(T.dvector()).out()<<endl;
			return 1;}
		else{		//cout<<v.out()<<"|"<<(T.dvector()).out()<<endl;
			return 0;}
		}
// defining functions for points
	

	Point affine( const Point& p1 , const Point &p2 , const double t ){
		Point p;
		p.x = sample(p1.x + t*(p2.x-p1.x));
		p.y = sample(p1.y + t*(p2.y-p1.y));
		p.z = sample(p1.z + t*(p2.z-p1.z));
		return p;
		}
	Point affine( const Point& p1,const Point& p2,const Point& p3,const double a1,const double a2,const double a3 ){
		Point p;
		p.x = a1*p1.x + a2*p2.x + a3*p3.x;
		p.y = a1*p1.y + a2*p2.y + a3*p3.y;
		p.z = a1*p1.z + a2+p2.z + a3*p3.z;
		return p;
		}
	Point midpoint( const Point& p1,const Point& p2 ){
		return (affine(p1,p2,0.5));
		}
	double Point :: length(const Point p){
		return sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y)+(p.z-z)*(p.z-z));

	}
