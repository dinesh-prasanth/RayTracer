#include "Physics.h"
#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "Line.h"
#include "Lineseg.h"
#include "Rayseg.h"
#include "functions.h"
#include <stdlib.h>
#include "Ray.h"
#include "Sphere.h"
#include "Object.h"
#include "intersection.h"
#include "Point.h"
using namespace std;

Point zero_p = Point(0.0,0.0,0.0);
Color zero_c = Color(0.0,0.0,0.0);

Point closest_int(Point p,Vector r_d,Object ob,double &min_in_l,Color &tmp_c,Sphere &tmp_s,Plane &tmp_p){	//closest intersection with object data structure

double in_l = 0.0;	// temperory intersection length
Point in_p,min_in_p;

for(int k=0;k<ob.s.size();k++){	// Loop for finding minimum intersection point from all spheres
	Sphere sp = ob.s[k];
	in_p = ray_sphere(p,r_d,sp,in_l);	//intersection point
	if(in_p!=zero_p){//cout<<"1";
		if(in_l<min_in_l){cout<<min_in_l<<endl;
			min_in_l = in_l;
			min_in_p = in_p;
			tmp_c = ob.s[k].c;
			tmp_s = ob.s[k];
			}
		}
	}

for(int k=0;k<ob.p.size();k++){//Loop for finding minimum intersection point from all planes
	Plane pl = ob.p[k];
	in_p = ray_plane(p,r_d,pl,in_l);
	if(in_p!=zero_p){//cout<<in_p.out()<<min_in_l;
		if((in_l<min_in_l)&&(in_l>=0.000001)){cout<<endl<<"Length : "<<in_l<<"|"<<min_in_l<<endl;
			min_in_l = in_l;
			min_in_p = in_p;
			tmp_c = ob.p[k].c;
//			cout<<ob.p[k].out()<<endl;
			tmp_p = ob.p[k];
			}
		}
	}

return min_in_p;
}



Point closest_ref(Point p,Vector r_d,Object ob,double &min_in_l,Color &tmp_c,Sphere &tmp_s){	//closest intersection with object data structure

double in_l = 0.0;	// temperory intersection length
Point in_p,min_in_p;
//cout<<p.out()<<" : "<<r_d.out()<<endl;
for(int k=0;k<ob.s.size();k++){	// Loop for finding minimum intersection point from all spheres
	Sphere sp = ob.s[k];cout<<endl<<"adsasd";
	cout<<sp.out()<<"324"<<endl;
		if(in_l<min_in_l){
	in_p = ray_sphere(p,r_d,sp,in_l);	//intersection point
	cout<<in_l<<in_p.out()<<"<=int_len--"<<endl;
	if(in_p!=zero_p){
			cout<<"\n"<<in_p.out()<<endl;
			min_in_l = in_l;
			min_in_p = in_p;
			tmp_c = ob.s[k].c;
			tmp_s = ob.s[k];
			}
		}
	}
cout<<endl<<min_in_p.out()<<endl;
return min_in_p;

}
Point closest_int(Point p,Vector r_d,Object ob,double &min_in_l,Color &tmp_c,Sphere &tmp_s){	//closest intersection with object data structure

double in_l = 0.0;	// temperory intersection length
Point in_p,min_in_p;
for(int k=0;k<ob.s.size();k++){	// Loop for finding minimum intersection point from all spheres
	Sphere sp = ob.s[k];
	in_p = ray_sphere(p,r_d,sp,in_l);	//intersection point
	if(in_p!=zero_p){
		if(in_l<min_in_l){
			min_in_l = in_l;
			min_in_p = in_p;
			tmp_c = ob.s[k].c;
			tmp_s = ob.s[k];
			}
		}
	}
return min_in_p;
}
int main(){
/*	Vector v1,v2;Line line;

	v1 = Vector(1.0,2.0,3.0);
	v2 = Vector(1.0,2.2,3.0);
	bool a = (v1==v2);
	cout<< a<<v1.out()<< " " <<( v1 * 2.0).out();
	cout<<endl<<(v1 / 0.0).out();
	cout<<endl<<v1.dot(v2)<<endl;
	cout<<"------------------------------"<<endl;
	Point p1,p2;
	p1 = Point(2.0,0.0,1.0);
	p2 = p1;
	cout<<p2.out()<<endl;
	cout<<"---------------------------------"<<endl;
	cout<<"TESTING FOR COLOR"<<endl;
	Color c = Color(0.1,0.5,0.3);
	cout<<c.out()<<endl;	
	cout<<"TESTING FOR LINE SEGMENT\n";
	Lineseg l1;
	Point p4,p5;
	p4 = Point(12.0,0.0,1.0);
	p5 = Point(2.0,3.0,0.0);
	l1 = Lineseg(p4,p5);
	cout<<l1.out()<<endl;
	cout<<"TESTING FOR RAY SEGMENT\n"<<endl;
	Rayseg r;
	r = Rayseg(l1,c);
	cout<<r.out()<<endl;
	cout<<"TESTING FOR A RAY\n";
	line = Line(v1,v2);
	Ray ry = Ray(line,c);
	cout<<ry.out()<<endl;
	/*cout<<"TESTING FOR OBJECTS\n";
	Sphere s1 = Sphere(p1,2.0,c,1.0);
	Sphere s2 = Sphere(p4,1.0,c,0.6);
	Object obj = Object(s1);
	obj.push(s2);
	cout<<obj.out()<<endl;
	cout<<"TESTING FOR INTERSECTION-----------------\n";
	Vector v3 = Vector(0.0,0.0,1.0);
	Point p6 = Point(3.0,5.0,0.0);
	Point p7 = Point(3.0,5.0,5.0);
	Sphere s3 = Sphere(p7,2.0,c,0.6);
	Point x = ray_sphere(p6,v3,s3);
	cout<<"Intersection Point"<<x.out()<<endl;
	cout<<"TESTING FOR REFLECTION---------------\n";
	//Point p8 = Point(0.0,2.0,1.0);
	//Point p9 = Point(2.0,2.0,1.0);
	Point p10 = Point(50.0,50.0,0.0);
	Object ob1,ob2;
	Sphere s4 = Sphere(Point(40.0,50.0,30.0),10.0,Color(0.1,1.0,0.0),1.0);Color tmp_c,tmp_c2;double min_in_l=200.00,min_in_l2=200.00;
	Sphere s5 = Sphere(Point(50.0,50.0,60.0),10.0,Color(0.0,0.1,1.0),1.0);
	ob1 = Object(s4);ob2 = Object(s5);Vector r_d = Vector(0.0,0.0,1.0);
	Sphere s_temp,s_temp2;
	Point clos_p = closest_ref(p10,r_d,ob1,min_in_l,tmp_c,s_temp);	
	Vector refl = Vector(reflect_sphere(p10,clos_p,s4));
	Point clos_ref = closest_ref(clos_p,refl,ob2,min_in_l2,tmp_c2,s_temp2);
	cout<<"Reflected vector : "<<clos_p.out()<<"--"<<refl.out()<<clos_ref.out()<<"--"<<endl;
	/*cout<<"TESTING FOR SHADOW RAY--------------\n";
	Object ob;
	Point p12 = Point(2.0,2.0,1.0);		//centre
	Sphere s5 = Sphere(p12,1.0,c,1.0);
	//Point p13 = Point(-0.9,-1.0,1.4);
	//Sphere s6 = Sphere(p13,1.0,c,1.0);
	ob = Object(s5);
	Point p11 = Point(2.0,3.0,1.0);		//point
	Point light = Point(4.0,4.0,1.0);
	//ob.push(s6);
	cout<<"Shadow status : "<<shadow_check(p11,light,ob)<<endl;
	cout<<"TESTING FOR REFRACTION------------\n";
	Vector d = Vector(0.0,0.0,1.0);		//direction
	Point p15 = Point(2.7,2.0,0.0);		//starting point
	Point p16 = Point(2.0,2.0,5.0);
	Sphere s7 = Sphere(p16,1.0,Color(0.3,0.1,0.4),0.3,1.33);
	Sphere s8 = Sphere(Point(1.2,2.0,9.0),1.0,Color(0.2,0.2,0.2),0.3,1.33);
	Object ob;ob.push(s7);ob.push(s8);
	double min_l = 100.0;bool bl;
	Color temp_c;Sphere temp_s;
	Point inter = closest_int(p15,d,ob,min_l,temp_c,temp_s);
	Vector refr = refract_sphere(p15,inter,s7,1.0,1.5,bl);
	Point inter2 = inside_ray_sphere(inter,refr,s7,min_l);
	Vector refr2 = refract_sphere(inter,inter2,s7,1.5,1.0,bl);
	Point inter3 = closest_int(inter2,refr2,ob,min_l,temp_c,temp_s);
	cout<<"\nRefracted Vector : "<<inter.out()<<inter2.out()<<refr.out()<<refr2.out()<<inter3.out()<<endl;
	/*cout<<"TESTING FOR BRIGHTNESS------------\n";
	Point p17 = Point(-1.0,0.0,0.0);
	Point p18 = Point(2.0,1.0,0.0);
	Point p19 = Point(3.0,0.0,0.0);
//	Sphere s8 = Sphere(p19,1.0,Color(1.0,0.3,0.0),0.3);
//	Color c1 = shade_sphere(p18,p17,s8);
//	cout<<"Brightness change : "<<s8.c.out()<<" : "<<c1.out()<<endl;
	cout<<endl<<"TESTING FOR PLANE INTERSECTION\n";
	Vector v = Vector(1.0,1.0,1.0);
	Point p = Point(0.0,0.0,0.0);
	Plane P = Plane( Point(0.0,0.0,2.0) , Point(2.0,0.0,2.0) , Point(2.0,2.0,2.0) , Point(0.0,2.0,2.0) );
	Point in = ray_plane(p,v,P);cout<<endl<<in.out()<<endl;*/
Object ob;	
ob.push(Plane(Point(0.0,0.0,0.0),Point(0.0,0.0,120.0),Point(110.0,0.0,120.0),Point(110.0,0.0,0.0),Color(1.0,1.0,1.0),1.5));
ob.push(Cuboid(Point(30.0,0.0,20.0),Point(20.0,0.0,30.0),Point(10.0,0.0,20.0),Point(20.0,0.0,10.0),Point(30.0,50.0,20.0),Point(20.0,50.0,30.0),Point(10.0,50.0,20.0),Point(20.0,50.0,10.0),Color(1.0,0.0,0.0)));

ob.push(Sphere(Point(60.0,30.0,50.0),10.0,Color(1.0,1.0,0.0),1.0,1.5));
ob.push(Sphere(Point(60.0,60.0,60.0),10.0,Color(1.0,1.0,0.0),1.0,1.5));
// cuboid near the main cuboid
ob.push(Cuboid(Point(10.0,0.0,10.0),Point(10.0,0.0,30.0),Point(30.0,0.0,30.0),Point(30.0,0.0,10.0),Point(15.0,15.0,15.0),Point(15.0,15.0,25.0),Point(25.0,15.0,25.0),Point(25.0,15.0,15.0),Color(0.0,0.0,1.0)));
//	cuboid near the sphere
ob.push(Cuboid(Point(40.0,0.0,40.0),Point(40.0,0.0,60.0),Point(60.0,0.0,60.0),Point(60.0,0.0,40.0),Point(35.0,30.0,35.0),Point(35.0,30.0,65.0),Point(65.0,30.0,65.0),Point(65.0,30.0,35.0),Color(0.0,1.0,1.0)));



	Point min_in_p = Point( 15.0, 0.0 , 39.2405 );
	Vector ref_v = Vector(0.0 , 1.0 , 0.1 );
	double min_ref_l=1000.0;Color ref_c;Sphere ref_s;Plane ref_p;
	Point min_ref_p = closest_int(min_in_p,ref_v,ob,min_ref_l,ref_c,ref_s,ref_p);
	cout<<min_ref_p.out()<<ref_c.out()<<endl;


	return 0;
}

