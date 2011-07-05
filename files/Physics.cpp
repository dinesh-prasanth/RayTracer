#include "Vector.h"
#include "Line.h"
#include "Sphere.h"
#include "Point.h"
#include "Color.h"
#include "Physics.h"
#include "Plane.h"
Vector reflect_sphere(Point i,Point o,Sphere s)
{	
	Vector o_v = Vector(o.x,o.y,o.z);
	Vector i_v = Vector(i.x,i.y,i.z);
	Vector c = Vector(s.o.x,s.o.y,s.o.z);	//center of sphere
	Line in = Line(i_v,o_v);	// incidence to sphere
	Line nl = Line(c,o_v);	// normal to sphere
	i_v = in.dvector();
	Vector n_v = Vector(nl.dvector());
	i_v.normalize();
	n_v.normalize();
	double cos = -(n_v.dot(i_v));
	if(cos>=0){
		Vector out;
		out.x = i_v.x + (2.0*cos*n_v.x);
		out.y = i_v.y + (2.0*cos*n_v.y);
		out.z = i_v.z + (2.0*cos*n_v.z);
		if(i_v==out)
			return Vector(0.0,0.0,0.0);
		return out;
		}
	else{
		cout<<"Error occurred in reflection calculation.";}
}
Vector reflect_plane(Point i,Point o,Plane p)
{

}
Vector refract_sphere(Point i,Point o,Sphere s,double n1,double n2)
{	
	Vector out;
	Vector zero = Vector(0.0,0.0,0.0);
	double n,cos;
	Vector o_v = Vector(o.x,o.y,o.z);
	Vector i_v = Vector(i.x,i.y,i.z);
	Vector c = Vector(s.o.x,s.o.y,s.o.z);	//center of sphere
	if(i_v==o_v)
		return i_v;
	Line in = Line(i_v,o_v);	// incidence to sphere
	Line nl = Line(c,o_v);	// normal to sphere
	i_v = in.dvector();
	Vector n_v = Vector(nl.dvector());
	i_v.normalize();
	n_v.normalize();
//	n_v.perpendicular();
	if(n1>n2)
		n_v.negate();		// changing the direction of normal for refraction from sphere to air.
	cos = -(n_v.dot(i_v));
	if((n1>0)&&(n2>0))
		n = n1*(1/n2);
	else{
		cout<<"Error occured in refraction calculation.";
		return zero;	
		}
	if(cos>0.0){
		double sin = n*n*(1.0-(cos*cos));
		if(sin>1.0)
			return zero;	// Total Internal Reflection case ruled out
		double cos_t = sqrt(1.0-sin);
		out.x = (n*i_v.x) + ((n*cos)-cos_t)*n_v.x;
		out.y = (n*i_v.y) + ((n*cos)-cos_t)*n_v.y;
		out.z = (n*i_v.z) + ((n*cos)-cos_t)*n_v.z;//cout<<"yup!"<<cos<<"|"<<out.out();
		return out;
		}
	else if(cos==0.0){
		return i_v;}
	else{
		cout<<cos<<in.out()<<"||"<<n_v.out()<<"|"<<i_v.out()<<"Error occured in refraction calculation";
		return zero;
		}
}
double shade_plane(Point o,Point l,Plane p)	// Intersection point , Light and plane
{
	Vector o_v = Vector(o.x,o.y,o.z);
	Vector l_v = Vector(l.x,l.y,l.z);
//	Vector n_v = (Vector(p.p1.x,p.p1.y,p.p1.z)).cross(Vector(p.p2.x,p.p2.y,p.p2.z));
//	n_v.normalize();
//	Line lt = Line(o_v,l_v);
	Vector lt_v = l_v - o_v;
	Line l1 = Line(Vector(p.p1.x,p.p1.y,p.p1.z),Vector(p.p2.x,p.p2.y,p.p2.z));
	Line l2 = Line(Vector(p.p1.x,p.p1.y,p.p1.z),Vector(p.p3.x,p.p3.y,p.p3.z));
	Vector n_v = (l1.dvector()).cross(l2.dvector());
//	if(!(((n_v.x >= 0 && lt_v.x >=0)||(n_v.x < 0 && lt_v.x < 0))&&((n_v.y >= 0 && lt_v.y >=0)||(n_v.y < 0 && lt_v.y < 0))&&((n_v.z >= 0 && lt_v.z >=0)||(n_v.z < 0 && lt_v.z < 0)))){
//		n_v = (l2.dvector()).cross(l1.dvector());
//		}
	lt_v.normalize();
	n_v.normalize();
//	cout<<lt_v.out()<<n_v.out()<<endl;
	double shade = lt_v.dot(n_v);
//	cout<<shade<<endl;
	if(shade<0){
		n_v = (l2.dvector()).cross(l1.dvector());
		n_v.normalize();
		shade = lt_v.dot(n_v);
		if(shade<0)
			shade = 0;
		///cout<<shade<<endl;
		}
//	cout<<shade<<endl;
	return pow(shade,0.5);
}
double shade_sphere(Point o,Point l,Sphere s)	// Intersection point , Light and sphere
{
	Vector o_v = Vector(o.x,o.y,o.z);
	Vector l_v = Vector(l.x,l.y,l.z);
	Vector c = Vector(s.o.x,s.o.y,s.o.z);
	Line l1 = Line(c,l_v);
	Line l2 = Line(c,o_v);
	l_v = l1.dvector();
	o_v = l2.dvector();
	l_v.normalize();
	o_v.normalize();
	double shade = l_v.dot(o_v);
	if(shade<0)
		shade = 0;
	return pow(shade,2);
}
double phong_sphere(Point l,Point x,Point i,Sphere s)	// Light,Starting Point,Intersection point and sphere
{
	Vector x_v = Vector(x.x,x.y,x.z);
	Vector i_v = Vector(i.x,i.y,i.z);
	Line x_i = Line(i_v,x_v);
	x_v = x_i.dvector();
	x_v.normalize();		// intersection vector
	Vector r_v = reflect_sphere(l,i,s);	//light reflected vector
	r_v.normalize();

	double shade = x_v.dot(r_v);
	if(shade<0)
		shade = 0;
	return pow(shade,20);
}
