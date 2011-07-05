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
	double x,y,z;
public:

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
//	double x() {return this.x;}
//	double y() {return this.y;}
//	double z() {return this.z;}

// defining assignment operator
	Vector& operator= (const Vector& v){
		if(this == &v) return(*this);
		else{
			x=v.x;y=v.y;z=v.z;
			return (*this);
		}
		}

// Output format of any vector
	string out(){
		stringstream out;
		out << "< "<<x<<" "<<y<<" "<<z<<" >";
		return out.str();
		}


// Comparing the operators
	bool operator== (const Vector& v2){
		if((x==v2.x)&&(y==v2.y)&&(z==v2.z))
			return 1;
		else
			return 0;
		}

// defining arithmetic operators
	Vector operator+ (const Vector& v1){
		Vector v;
		v.x = x + v1.x;
		v.y = y + v1.y;
		v.z = z + v1.z;
		return (v);
		}
	Vector operator- (const Vector& v1){
		Vector v;
		v.x = x - v1.x;
		v.y = y - v1.y;
		v.z = z - v1.z;
		return (v);
		}

	Vector operator* (const double& c){
		Vector v;
		v.x = c*x;
		v.y = c*y;
		v.z = c*z;
		return (v);
		}

//--------------------------------------------------------------------------------> Another case for multiplication
	Vector& operator/ (const double&c ){
		if(c!=0.0){
			x = x/c; y = y/c; z= z/c;		
			return (*this);		
		}
		else{
			cout<<"\nLogical Error Occured : Division (No changed performed)\n";
			return (*this);
		}
		}
	

// Defining the vector operations

// Finding length of the vector

	double length(){
			double l;
			l = sqrt( x*x + y*y + z*z );
			return l;
		}

// Normalizing to an unit vector

	void normalize(){
			double  l = length();
			x = x/l;
			y = y/l;
			z = z/l;
		}

// Return dot product of two vectors

	double dot( const Vector& v ){
		double d;
		d = (x*v.x) + (y*v.y) + (z*v.z);
		return d;
	}
	Vector& cross( const Vector& v ){
			x = ( y * v.z - z * v.y );
			y = ( z * v.x - x * v.z );
			z = ( z * v.y - y * v.x );
			return (*this);
		}

};


