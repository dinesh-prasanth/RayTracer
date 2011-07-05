#include<GL/glut.h>
#include<X11/Xlib.h>
#include<iostream>
#include<algorithm>
#include "Physics.h"
#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include<vector>
#include "Line.h"
#include "Lineseg.h"
#include "Rayseg.h"
#include <stdlib.h>
#include "Ray.h"
#include "Sphere.h"
#include "Object.h"
#include "intersection.h"
#include "Screengl.h"
#include "Plane.h"
#include "Cuboid.h"
using namespace std;

/*Global Variables*/

Plane zero_P;Sphere zero_S;
Point zero_p = Point(0.0,0.0,0.0);
Color zero_c = Color(0.0,0.0,0.0);
Vector zero_v = Vector(0.0,0.0,0.0);
double pwidth = 0.1;
short int s_x=1024;
short int s_y=1024;
double X = s_x*pwidth;
double Y = s_y*pwidth;
short int ref_depth = 3;	//reflection depth
short int rfr_depth = 2;
double out_ri = 1.0;		//outside environment refractive index
double infy = 1000.0;		// some big number representing infinity
Point light = Point(5.0,100.0,20.0);
double ref_cff = 0.5;		// reflection coefficient of spheres 1.0 = Perfect reflection 0.0 = Zero reflection
Point eye = Point(X/2,Y/2+100.0,-200.0);	//eye of the viewer

void init(void)
{

	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,X,0.0,Y,0.0,max(X,Y));
}


/*Important functions*/

Point closest_int(Point p,Vector r_d,Object ob,double &min_in_l,Color &tmp_c,Sphere &tmp_s,Plane &tmp_p){	//closest intersection with object data structure

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

for(int k=0;k<ob.p.size();k++){//Loop for finding minimum intersection point from all planes
	Plane pl = ob.p[k];
	in_p = ray_plane(p,r_d,pl,in_l);
	if(in_p!=zero_p){
		if(in_l<min_in_l){
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
Color find_shade(Point p,Point min_in_p,Object ob,Sphere tmp_s,Color tmp_c,Point light)
{
/*Shadow check and Phong lightning call starts*/
double phong;
if(shadow_check(min_in_p,light,ob))	//Loop for checking if the point is in shadow region
	tmp_c.alter(0.5);		//Ambient coefficient	
else{
	phong = phong_sphere(light,p,min_in_p,tmp_s);
	if(phong){
		Color ph_c = Color(0.8,0.8,0.8);
		ph_c.alter(phong);
		tmp_c.alter(0.5 + (0.5*(shade_sphere(min_in_p,light,tmp_s))));
		tmp_c.alter(1-phong);
		tmp_c = tmp_c + ph_c;
		}
	else
		tmp_c.alter(0.5 + (0.5*(shade_sphere(min_in_p,light,tmp_s))));	//Diffuse coefficient
	}
return tmp_c;
/*Shadow and Phong ends here*/
}


Color rec_ref(Point p,Point min_in_p,Color ref_c,Object ob,Sphere &tmp_s,Plane &tmp_p,short int depth){
	double min_ref_l;Sphere ref_s;Plane ref_p;Point min_ref_p;Vector ref_v;

	if(tmp_p != zero_P)
		ref_v = reflect_plane(p,min_in_p,tmp_p);
	else
		ref_v = reflect_sphere(p,min_in_p,tmp_s);

	min_ref_l = infy;
	if(ref_v!=zero_v)
		min_ref_p = closest_int(min_in_p,ref_v,ob,min_ref_l,ref_c,ref_s);
	if(min_ref_p != zero_p){
		if(depth==1){ref_c = find_shade(min_in_p,min_ref_p,ob,ref_s,ref_c,light);ref_c.alter(ref_s.a);ref_c.alter(ref_s.a);
			return ref_c;}
		else{
			depth-=1;
			return rec_ref(min_in_p,min_ref_p,ref_c,ob,ref_s,ref_p,depth);
			}
		}
	else if(depth<ref_depth){ref_c = find_shade(p,min_in_p,ob,tmp_s,ref_c,light);ref_c.alter(ref_s.a);ref_c.alter(tmp_s.a);
		return ref_c;}
	return zero_c;
}


Color rec_rfr(Point p,Point min_in_p,Color rfr_c,Object ob,Sphere &tmp_s,short int depth){
	Sphere rfr_s;Plane rfr_p;Vector rf_v;	//refraction sphere and refracted vector
	Point inter2,inter3;Vector refr2;	//refraction variables
	double in2_l,in3_l;		//interception length in the sphere while refraction.
	rf_v = refract_sphere(p,min_in_p,tmp_s,out_ri,tmp_s.u);		// primary refraction to the sphere
	in2_l = infy;
	inter2 = inside_ray_sphere(min_in_p,rf_v,tmp_s,in2_l);	//secondary intersection inside the sphere
	refr2 = refract_sphere(min_in_p,inter2,tmp_s,tmp_s.u,out_ri);	// secondary refraction from the sphere
	in3_l = infy;
	if(refr2!=zero_v)
		inter3 = closest_int(inter2,refr2,ob,in3_l,rfr_c,rfr_s);	//intersection of refracted ray
	if(in3_l!=infy){
		if(depth==1){
			rfr_c = find_shade(inter2,inter3,ob,rfr_s,rfr_c,light);rfr_c.alter(rfr_s.a);//apply shadings for the last sphere which return color
			return rfr_c;}
		else{
			depth-=1;
			

			return rec_rfr(inter2,inter3,rfr_c,ob,rfr_s,depth);
			}
		return rfr_c;
		}
	else if(depth<rfr_depth){rfr_c = find_shade(p,min_in_p,ob,tmp_s,rfr_c,light);rfr_c.alter(tmp_s.a);	//apply shadings for the last sphere which return color
		return rfr_c;}
	return zero_c;
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
/*starts*/

Object ob;
/*
// Group of white spheres
ob.push(Sphere(Point(20.0,50.0,15.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(25.0,50.0,35.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(30.0,50.0,55.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(35.0,50.0,75.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(40.0,50.0,95.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(45.0,50.0,115.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(50.0,50.0,135.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(55.0,50.0,155.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(60.0,50.0,175.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(65.0,50.0,195.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(70.0,50.0,215.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(75.0,50.0,235.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));
ob.push(Sphere(Point(80.0,50.0,255.0),5.0,Color(1.0,1.0,1.0),0.8,1.5));*/



ob.push(Plane(Point(0.0,0.0,0.0),Point(0.0,0.0,120.0),Point(110.0,0.0,120.0),Point(110.0,0.0,0.0),Color(1.0,1.0,1.0),1.5));
ob.push(Cuboid(Point(30.0,0.0,20.0),Point(20.0,0.0,30.0),Point(10.0,0.0,20.0),Point(20.0,0.0,10.0),Point(30.0,50.0,20.0),Point(20.0,50.0,30.0),Point(10.0,50.0,20.0),Point(20.0,50.0,10.0),Color(1.0,0.0,0.0)));

ob.push(Sphere(Point(60.0,30.0,50.0),10.0,Color(1.0,1.0,0.0),1.0,1.5));
ob.push(Sphere(Point(60.0,60.0,60.0),10.0,Color(1.0,1.0,0.0),1.0,1.5));
// cuboid near the main cuboid
ob.push(Cuboid(Point(10.0,0.0,10.0),Point(10.0,0.0,30.0),Point(30.0,0.0,30.0),Point(30.0,0.0,10.0),Point(15.0,15.0,15.0),Point(15.0,15.0,25.0),Point(25.0,15.0,25.0),Point(25.0,15.0,15.0),Color(0.0,0.0,1.0)));
//	cuboid near the sphere
ob.push(Cuboid(Point(40.0,0.0,40.0),Point(40.0,0.0,60.0),Point(60.0,0.0,60.0),Point(60.0,0.0,40.0),Point(35.0,30.0,35.0),Point(35.0,30.0,65.0),Point(65.0,30.0,65.0),Point(65.0,30.0,35.0),Color(0.0,1.0,1.0)));

/*ob.push(Sphere(Point(25.0,50.0,15.0),10.0,Color(1.0,0.0,0.0),0.6,1.5));
ob.push(Sphere(Point(40.0,40.0,80.0),10.0,Color(0.0,0.0,1.0),0.6,1.5));
ob.push(Sphere(Point(40.0,60.0,80.0),10.0,Color(0.0,1.0,0.0),0.6,1.5));
ob.push(Sphere(Point(60.0,50.0,110.0),15.0,Color(1.0,0.2,0.5),0.6,1.5));
ob.push(Sphere(Point(70.0,45.0,140.0),12.0,Color(0.2,0.2,0.2),0.6,1.5));*/
/*ob.push(Sphere(Point(25.0,42.5,30.0),7.0,Color(0.1,1.0,0.0),1.0,1.5));
ob.push(Sphere(Point(25.0,62.5,30.0),7.0,Color(0.2,0.1,1.0),1.0,1.5));
ob.push(Sphere(Point(40.0,25.0,30.0),7.0,Color(1.0,0.1,0.1),1.0,1.5));
ob.push(Sphere(Point(60.0,25.0,30.0),7.0,Color(0.2,0.5,1.0),1.0,1.5));
ob.push(Sphere(Point(40.0,75.0,30.0),7.0,Color(0.5,0.6,1.0),1.0,1.5));
ob.push(Sphere(Point(60.0,75.0,30.0),7.0,Color(0.0,0.4,0.1),1.0,1.5));
ob.push(Sphere(Point(75.0,42.5,30.0),7.0,Color(0.5,0.2,0.4),1.0,1.5));
ob.push(Sphere(Point(75.0,62.5,30.0),7.0,Color(0.3,0.3,0.9),1.0,1.5));
ob.push(Sphere(Point(50.0,50.0,30.0),10.0,Color(0.8,0.8,0.8),1.0,1.5));
ob.push(Sphere(Point(10.0,90.0,30.0),5.0,Color(1.0,0.1,0.1),1.0,1.5));
ob.push(Sphere(Point(10.0,10.0,30.0),5.0,Color(1.0,0.1,0.1),1.0,1.5));
ob.push(Sphere(Point(90.0,90.0,30.0),5.0,Color(1.0,0.1,0.1),1.0,1.5));
ob.push(Sphere(Point(90.0,10.0,30.0),5.0,Color(1.0,0.1,0.1),1.0,1.5));
//----------

ob.push(Sphere(Point(32.5,33.0,70.0),4.0,Color(0.1,1.0,0.0),1.0,1.5));
ob.push(Sphere(Point(25.0,50,70.0),4.0,Color(0.2,0.1,1.0),1.0,1.5));
ob.push(Sphere(Point(50.0,25.0,70.0),4.0,Color(1.0,0.1,0.1),1.0,1.5));
ob.push(Sphere(Point(67.0,33.0,70.0),4.0,Color(0.2,0.5,1.0),1.0,1.5));
ob.push(Sphere(Point(33.0,67.0,70.0),4.0,Color(0.5,0.6,1.0),1.0,1.5));
ob.push(Sphere(Point(50.0,75.0,70.0),4.0,Color(0.0,0.4,0.1),1.0,1.5));
ob.push(Sphere(Point(67.0,67.0,70.0),4.0,Color(0.5,0.2,0.4),1.0,1.5));
ob.push(Sphere(Point(75.0,50.0,70.0),4.0,Color(0.3,0.3,0.9),1.0,1.5));
ob.push(Sphere(Point(50.0,50.0,70.0),6.0,Color(0.8,0.8,0.8),1.0,1.5));
ob.push(Sphere(Point(10.0,50.0,70.0),3.0,Color(1.0,0.1,0.1),1.0,1.5));
ob.push(Sphere(Point(50.0,10.0,70.0),3.0,Color(1.0,0.1,0.1),1.0,1.5));
ob.push(Sphere(Point(50.0,90.0,70.0),3.0,Color(1.0,0.1,0.1),1.0,1.5));
ob.push(Sphere(Point(90.0,50.0,70.0),3.0,Color(1.0,0.1,0.1),1.0,1.5));*/

Vector r_d;	// ray direction from the screen
Screengl s;
s.allotsize(s_x,s_y);
double min_in_l = infy;	//minimum intersection length
/* All the data sets ends here */



ob.convertCtoP();

Color ref_c,rfr_c;		//reflection and refraction color defined
Sphere tmp_s;Plane tmp_p,ref_p;
double phong;Color ph_c;
Point min_in_p,chk_in;	// intersection point , minimum intersection point and Intersection check of reflected ray
Color tmp_c;		//temperory color value of sphere
Sphere org_s;Color org_c;		//original sphere in iteration
Color smp_c,tmp1_c,tmp2_c;		// color used for just reference(sample) for a back up color.
for(int i=0;i<s_x;i++)
{
	for(int j=0;j<s_y;j++){
		min_in_p = zero_p;
		min_in_l = infy;
		tmp_s = zero_S;tmp_p = zero_P;ref_p = zero_P;
		Point p = Point(i*pwidth,j*pwidth,0.0);		//pixel position
		r_d = Vector(p.x-eye.x,p.y-eye.y,p.z-eye.z);
		min_in_p = closest_int(p,r_d,ob,min_in_l,tmp_c,tmp_s,tmp_p);	// first intersection from the screen to the object
		if(min_in_l!=infy){
			org_s = tmp_s;org_c = tmp_s.c;smp_c = org_c;
			//cout<<min_in_p.out()<<min_in_l<<tmp_c.out()<<endl;






			/*Reflection call starts*/
			if( tmp_p != zero_P )
				{}
			else{
			ref_c = rec_ref(p,min_in_p,ref_c,ob,tmp_s,ref_p,ref_depth);	// function call for recursive reflection to find color
			if( ref_c != zero_c)
				ref_c.alter(ref_cff);
			smp_c.alter(1-ref_cff);
			tmp1_c = ref_c + smp_c;
			/*Reflection ends here*/
			

			rfr_c = rec_rfr(p,min_in_p,rfr_c,ob,tmp_s,rfr_depth);
			rfr_c.alter(1-org_s.a);
			org_c.alter(org_s.a);
			tmp2_c = org_c + rfr_c;

			if(tmp1_c!=zero_c&&tmp2_c!=zero_c)
			{
				//tmp1_c.alter(org_s.a);
				//tmp2_c.alter(1-org_s.a);
				tmp_c = ref_c + rfr_c;
			}
			else if(tmp1_c!=zero_c)
				tmp_c=tmp1_c;
			else if(tmp2_c!=zero_c)
				tmp_c=tmp2_c;
			}
			/*Shadow check and Phong lightning call starts*/
			if(shadow_check(min_in_p,light,ob)){	//Loop for checking if the point is in shadow region
				tmp_c.alter(0.15);		//Ambient coefficient

				}
			else{
				if(tmp_p != zero_P){
					tmp_c.alter(0.15 + (0.85*(shade_plane(min_in_p,light,tmp_p))));

					}
				else{
					phong = phong_sphere(light,p,min_in_p,tmp_s);
					if(phong){
						ph_c = Color(0.8,0.8,0.8);
						ph_c.alter(phong);
						tmp_c.alter(0.15 + (0.85*(shade_sphere(min_in_p,light,tmp_s))));
						tmp_c.alter(1-phong);
						tmp_c = tmp_c + ph_c;
						}
					else
						tmp_c.alter(0.15 + (0.85*(shade_sphere(min_in_p,light,tmp_s))));	//Diffuse coefficient
					}
				}
			/*Shadow and Phong ends here*/
			
			s.p[i][j] = tmp_c;
			}
		}
}
for(int i=0;i<s_x;i++)
{
for(int j=0;j<s_y;j++)
{
glColor3f(s.p[i][j].r,s.p[i][j].g,s.p[i][j].b);
glBegin(GL_POLYGON);		
	glVertex3f(i*pwidth,j*pwidth,0.0);
	glVertex3f(i*pwidth,j*pwidth+pwidth,0.0);
	glVertex3f(i*pwidth+pwidth,j*pwidth+pwidth,0.0);
	glVertex3f(i*pwidth+pwidth,j*pwidth,0.0);
glEnd();
}
}
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250,250);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Shading for planes");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
