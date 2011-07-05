#include<iostream>
#include<math.h>
#include<string>
#include<stdlib.h>
#include<sstream>
#include "Vector.h"
using namespace std;


// defining assignment operator
	Vector& Vector :: operator= (const Vector& v){
		if(this == &v) return(*this);
		else{
			x=v.x;y=v.y;z=v.z;
			return (*this);
		}
		}

// Output format of any vector
	string Vector :: out(){
		stringstream out;
		out << "< "<<x<<" "<<y<<" "<<z<<" >";
		return out.str();
		}

	
// Comparing the operators
	bool Vector :: operator== (const Vector& v2){
/*		cout<<"< "<<x<<" "<<y<<" "<<z<<" >"<<"< "<<v2.x<<" "<<v2.y<<" "<<v2.z<<" >"<<"$";
		if((float)x==(float)v2.x)
			cout<<"x";
		if((float)y==(float)v2.y)
			cout<<"y";
		if((float)z==(float)v2.z)
			cout<<"z";
		cout<<endl;*/
		if(((float)x==(float)v2.x)&&((float)y==(float)v2.y)&&((float)z==(float)v2.z))
			return 1;
		else
			return 0;
		}
	bool Vector :: operator!= (const Vector& v2){
		if((x!=v2.x)||(y!=v2.y)||(z!=v2.z))
			return 1;
		else
			return 0;
		}
// defining arithmetic operators
	Vector Vector :: operator+ (const Vector& v1){
		Vector v;
		v.x = x + v1.x;
		v.y = y + v1.y;
		v.z = z + v1.z;
		return (v);
		}
	Vector Vector :: operator- (const Vector& v1){
		Vector v;
		v.x = x - v1.x;
		v.y = y - v1.y;
		v.z = z - v1.z;
		return (v);
		}

	Vector Vector :: operator* (const double& c){
		Vector v;
		v.x = c*x;
		v.y = c*y;
		v.z = c*z;
		return (v);
		}

//--------------------------------------------------------------------------------> Another case for multiplication
	Vector& Vector :: operator/ (const double&c ){
		if(c!=0.0){
			x = x/c; y = y/c; z= z/c;		
			return (*this);		
		}
		else{
			cout<<"\nLogical Error Occured : Division (No changed performed)\n";
			return (*this);
		}
		}
	
	double Vector :: cos_a(){
		if(length()>0)
			return (x/length());
		else
			cout<<"Logical Error occured.\n";return 0;	
	}
	double Vector :: cos_b(){
		if(length()>0)
			return (y/length());
		else
			cout<<"Logical Error occured.\n";return 0;	
	}
	double Vector :: cos_g(){
		if(length()>0)
			return (z/length());
		else
			cout<<"Logical Error occured.\n";return 0;	
	}
// Defining the vector operations
// Finding length of the vector

	double Vector :: length(){
			double l;
			l = sqrt( x*x + y*y + z*z );
			return l;
		}
	bool Vector :: issame(Vector v){	//check if two vectors are same
		Vector u;
		if((x>=0&&v.x>=0)||(x<0&&v.x<0)){
		//double x1=x,y1,z1,x2=v.x,y2,z2;
		u.x = x;u.y = y;u.z = z;
//		cout<<u.out()<<"|"<<v.out()<<endl;
		double fact = 1/u.x;
		u.x=1.0;u.y=u.y*fact;u.z=u.z*fact;
		fact = 1/v.x;
		v.x=1.0;v.y=v.y*fact;v.z=v.z*fact;
//		cout<<u.out()<<"|"<<v.out()<<"|"<<fact<<endl;
		if(u==v){//cout<<endl<<"1"<<endl;
			return 1;}}//cout<<endl<<"0"<<endl;
//		cout<<(u==v)<<"|"<<u.out()<<"|"<<v.out()<<"|"<<fact<<endl;
		return 0;
	}
	void Vector :: negate(){	//reverse the direction
		x=-x;y=-y;z=-z;
	}
// Normalizing to an unit vector

	void Vector :: normalize(){
			double  l = length();
			x = x/l;
			y = y/l;
			z = z/l;
		}
	void Vector :: perpendicular(){
			if(x!=0)
				x = -1*(1/x);
			if(y!=0)
				y = -1*(1/y);
			if(z!=0)
				z = -1*(1/z);
		}
// Return dot product of two vectors
	Vector Vector :: nextVector(double len){
		Vector v;
		v.x = x + (len*cos_a());
		v.y = y + (len*cos_b());
		v.z = z + (len*cos_g());
		return v;
	}
	double Vector :: dot( const Vector& v ){
		double d;
		d = (x*v.x) + (y*v.y) + (z*v.z);
		return d;
	}
	Vector& Vector :: cross( const Vector& v ){
			double x1 = ( y * v.z - z * v.y );
			double y1 = ( z * v.x - x * v.z );
			double z1 = ( x * v.y - y * v.x );
			x=x1;y=y1;z=z1;
			return (*this);
		}

