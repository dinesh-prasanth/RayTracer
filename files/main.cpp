#include "Physics.h"
#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "Line.h"
#include "Lineseg.h"
#include "Rayseg.h"
#include <stdlib.h>
#include "Ray.h"
#include "Sphere.h"
#include "Object.h"
#include "intersection.h"
#include "Screengl.h"
#include "functions.h"
#include<algorithm>
using namespace std;

/*Global Variables*/
Point zero_p = Point(0.0,0.0,0.0);
Color zero_c = Color(0.0,0.0,0.0);
Vector zero_v = Vector(0.0,0.0,0.0);
double pwidth = 0.1;
short int s_x=1024;
short int s_y=1024;
double X = s_x*pwidth;
double Y = s_y*pwidth;
short int ref_depth = 2;

/*Important functions*/

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

Color rec_ref(Point p,Point min_in_p,Color ref_c,Object ob,Sphere &tmp_s,short int depth){
	double min_ref_l;Sphere ref_s;Point min_ref_p;
	Vector ref_v = reflect_sphere(p,min_in_p,tmp_s);
	min_ref_l = X;
	if(ref_v!=zero_v)
		min_ref_p = closest_int(min_in_p,ref_v,ob,min_ref_l,ref_c,ref_s);
	if(min_ref_p != zero_p){
		if(depth==0)
			return ref_c;
		else{
			depth-=1;
			return rec_ref(min_in_p,min_ref_p,ref_c,ob,ref_s,depth);
			}
		}
	else if(depth<ref_depth)
			return ref_c;
	return zero_c;
}


/*Important functions ends here*/



int main(){
/* All the data sets comes here */

Point light = Point(1.0,100.0,14.0);
Object ob;
ob.push(Sphere(Point(35.0,50.0,30.0),25.0,Color(1.0,1.0,0.0),1.0));
ob.push(Sphere(Point(70.0,30.0,30.0),5.0,Color(0.0,0.0,1.0),1.0));
//ob.push(Sphere(Point(60.0,70.0,11.0),15.0,Color(0.0,0.1,1.0),1.0));
//ob.push(Sphere(Point(60.0,50.0,10.0),17.0,Color(1.0,0.1,0.1),1.0));
Vector r_d = Vector(0.0,0.0,1.0);	// ray direction from the screen
Screengl s;

s.allotsize(s_x,s_y);
cout<<"Pixel width : "<<pwidth<<" units"<<endl<<"Viewing screen size : "<<X<<" x "<<Y<<" units"<<endl;
double min_in_l = X;	//minimum intersection length

/* All the data sets ends here */



Color ref_c;Sphere tmp_s;	//reflection variable defined

Point min_in_p,chk_in;	// intersection point , minimum intersection point and Intersection check of reflected ray


Color tmp_c;		//temperory color value of sphere
for(int i=0;i<s_x;i++)
{
	for(int j=0;j<s_y;j++){
		min_in_p = zero_p;
		min_in_l = X;
		Point p = Point(i*pwidth,j*pwidth,0.0);
		min_in_p = closest_int(p,r_d,ob,min_in_l,tmp_c,tmp_s);
		if(min_in_l!=X){
			ref_c = rec_ref(p,min_in_p,ref_c,ob,tmp_s,2);	// function call for recursive reflection to find color

			if( ref_c != zero_c){
				tmp_c = ref_c;}
	
			if(shadow_check(min_in_p,light,ob))	//Loop for checking if the point is in shadow region
				tmp_c.alter(0.15);		//Ambient coefficient	
			else
				tmp_c.alter(0.15 + (0.85*(shade_sphere(min_in_p,light,tmp_s))));	//Diffuse coefficient
			s.p[i][j] = tmp_c;
			}
		}
}
//for(int i=9;i<31;i++)
//{
//for(int j=0;j<25;j++)
//{

//cout<<s.p[20][10].out();
//}
//cout<<endl<<i<<endl;}
}

