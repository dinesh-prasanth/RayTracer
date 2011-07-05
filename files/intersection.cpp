#include "Object.h"
#include "Line.h"
#include "Point.h"
#include "Vector.h"
#include "Lineseg.h"
#include<math.h>
#include "intersection.h"
#include "Plane.h"

Point zero_pt = Point(0.0,0.0,0.0);

Point ray_sphere(Point p,Vector v,Sphere s,double &len)	// Point , Direction , Sphere , Length
{	
	double B,C,D,V;		// B = perpendicular distance from center of sphere to line	C = distance from center of sphere to point p	D = distance between intersection point and (intersection pt of perpendicular from sphere center and line)	V = distance from point p and (intersection pt of perpendicular from sphere center to line)	len = distance from point p to intersection point
	Vector x;Point X;	//Vector and Point for 'Point of intersection'
	Vector b = Vector((v.cos_a()+p.x),(v.cos_b()+p.y),(v.cos_g()+p.z));
	Vector a = Vector(p.x,p.y,p.z);
	Vector o = Vector(s.o.x,s.o.y,s.o.z);
	Line l1 = Line(a,b);
	Line l2 = Line(a,o);
	Line l3 = Line(b,o);
	if(v.dot(l2.dvector())<0)
		return Point(0.0,0.0,0.0);
	Vector num = Vector(l2.cross(l3));
	if(l1.length()>0)
		B = (1/l1.length())*num.length();
	else
		cout<<p.out()<<v.out()<<"Logical Error occured.\n";
	if(B>s.r){
		return X;
		}
	else{				
		C = l2.length();
		V = sqrt((C*C)-(B*B));
		if(B==s.r)
			D = 0;
		else
			D = sqrt((s.r*s.r)-((C*C)-(V*V)));
		len = V - D;
		x = l1.nextVector(len);
		X = Point(x.x,x.y,x.z);
		return X;
		}
}
Point ray_sphere(Point p,Vector v,Sphere s)	// Point , Direction , Sphere
{	
	double B,C,D,V,len;		// B = perpendicular distance from center of sphere to line	C = distance from center of sphere to point p	D = distance between intersection point and (intersection pt of perpendicular from sphere center and line)	V = distance from point p and (intersection pt of perpendicular from sphere center to line)	len = distance from point p to intersection point
	Vector x;Point X;	//Vector and Point for 'Point of intersection'
	Vector b = Vector((v.cos_a()+p.x),(v.cos_b()+p.y),(v.cos_g()+p.z));
	Vector a = Vector(p.x,p.y,p.z);
	Vector o = Vector(s.o.x,s.o.y,s.o.z);
	Line l1 = Line(a,b);
	Line l2 = Line(a,o);
	Line l3 = Line(b,o);
	if(v.dot(l2.dvector())<0)
		return Point(0.0,0.0,0.0);
	Vector num = Vector(l2.cross(l3));
	if(l1.length()>0)
		B = (1/l1.length())*num.length();
	else
		cout<<"Logical Error occured.\n";
	if(B>s.r){
		return X;
		}
	else{				
		C = l2.length();
		V = sqrt((C*C)-(B*B));
		if(B==s.r)
			D = 0;
		else
			D = sqrt((s.r*s.r)-((C*C)-(V*V)));
		len = V - D;
		x = l1.nextVector(len);
		X = Point(x.x,x.y,x.z);
		return X;
		}
}
Point inside_ray_sphere(Point p,Vector v,Sphere s,double &len){		// Intersection Point, Direction, Sphere of intersection, Length
	double B,C,V;		// B = perpendicular distance from center of sphere to line	C = distance from center of sphere to point p	D = distance between intersection point and (intersection pt of perpendicular from sphere center and line)	V = distance from point p and (intersection pt of perpendicular from sphere center to line)	len = distance from point p to intersection point
	Point X;
	Vector b = Vector((v.cos_a()+p.x),(v.cos_b()+p.y),(v.cos_g()+p.z));
	Vector a = Vector(p.x,p.y,p.z);
	Vector o = Vector(s.o.x,s.o.y,s.o.z);
	Line l1 = Line(a,b);
	Line l2 = Line(a,o);
	Line l3 = Line(b,o);
	if(v.dot(l2.dvector())<0)
		return Point(0.0,0.0,0.0);
	Vector num = Vector(l2.cross(l3));
	if(l1.length()>0)
		B = (1/l1.length())*num.length();
	else
		cout<<"Logical Error occured.\n";
	
	if(B>s.r){
		return X;
		}
	else{				
		C = l2.length();
		V = 2*sqrt((C*C)-(B*B));	// intersection length
		Vector x = l1.nextVector(V);
		X = Point(x.x,x.y,x.z);
		return X;
	}

}
bool shadow_check( Point in,const Point l, Object ob)
{
	Point temp;	//checking interuptions in the path to the light
	Vector i_v = Vector(in.x,in.y,in.z);
	Vector l_v = Vector(l.x,l.y,l.z);
	Line sh = Line(i_v,l_v);
	Vector sh_v = sh.dvector();
	sh_v.normalize();
	for(int i=0;i<ob.s.size();i++){
		temp = ray_sphere(in,sh_v,ob.s[i]);
		if(temp != zero_pt)
			return 1;
	}
	for(int i=0;i<ob.p.size();i++){

//		if(i>2)
//			cout<<i<<endl;
		//if(i==5)
		//	cout<<ob.p[i].out()<<endl;
		temp = ray_plane(in,sh_v,ob.p[i]);
		if(temp != zero_pt){
//		Line temp_l = Line(Point in,Point temp);
//		Vector temp_v = temp_l.dvector();
//		temp_v.normalize();
//		if((in.x>10&&in.x<20)&&(in.y>45.0&&in.y<46.0)&&(in.z>10.0&&in.z<20.0)){//cout<<in.out()<<"|"<<temp.out()<<"|"<<"|"<<sh_v.out()<<endl;			
			if( (in.out() != temp.out()) && (in.isdirection(sh_v,temp)) ){//cout<<in.out()<<"||"<<temp.out()<<"|"<<l_v.out()<<"|"<<sh_v.out()<<endl;
			return 1;}//}
		
		}
	}
	return 0;
}
Point ray_plane(Point p,Vector dr,Plane l,double &len){		// (p0 - i0).n / (i.n)

	Vector nr = Vector(l.p1.x-p.x,l.p1.y-p.y,l.p1.z-p.z);
//	cout<<nr.out()<<endl;
	Vector n = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);
	Vector v2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
	n.cross(v2);
//	cout<<v2.out()<<n.out()<<dr.out()<<dr.dot(n)<<endl;
	double ndot = nr.dot(n);
	double ddot = dr.dot(n);
	if((ndot==0)&&(ddot==0))	//lies in the plane
		return zero_pt;
	else if(ddot==0)			// parallel to the plane but does not lie
		return zero_pt;
	else{					//intersects the infinite plane at some point | Sum of angles between lines joining 4pts and pt p must be 360 deg.
		double d = ndot/ddot;
		Vector in = Vector( p.x + d*dr.x , p.y + d*dr.y , p.z + d*dr.z );
		Vector e1 = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);	// edges of the plane
		Vector e2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
		Vector e3 = Vector(l.p4.x-l.p3.x,l.p4.y-l.p3.y,l.p4.z-l.p3.z);
		Vector e4 = Vector(l.p1.x-l.p4.x,l.p1.y-l.p4.y,l.p1.z-l.p4.z);
//		cout<<in.out()<<l.p1.out()<<l.p3.out()<<endl;
		Vector t1,t2;	//testing temperory vectors
		t1 = Vector(l.p1.x-in.x,l.p1.y-in.y,l.p1.z-in.z);
		t2 = Vector(l.p1.x-l.p4.x,l.p1.y-l.p4.y,l.p1.z-l.p4.z);
//		cout<<t1.out()<<t2.out()<<endl;
//		cout<<endl<<in.out();
		len = p.length(Point(in.x,in.y,in.z));
		t1.cross(e1);
		t2.cross(e1);
//		cout<<t1.out()<<t2.out()<<endl<<t1.dot(t2)<<endl;
		
		if(t1.dot(t2)<0.0)
			return zero_pt;
		else{
			t1 = Vector(l.p2.x-in.x,l.p2.y-in.y,l.p2.z-in.z);
			t2 = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);
			t1.cross(e2);
			t2.cross(e2);
			if(t1.dot(t2)<0.0)
				return zero_pt;
			else{
				t1 = Vector(l.p3.x-in.x,l.p3.y-in.y,l.p3.z-in.z);
				t2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
				t1.cross(e3);
				t2.cross(e3);
				if(t1.dot(t2)<0.0)
					return zero_pt;
				else{
//					cout<<in.out()<<endl;
					t1 = Vector(l.p4.x-in.x,l.p4.y-in.y,l.p4.z-in.z);
					t2 = Vector(l.p4.x-l.p3.x,l.p4.y-l.p3.y,l.p4.z-l.p3.z);
					t1.cross(e4);
					t2.cross(e4);
					if(t1.dot(t2)<0.0){
						return zero_pt;}
					else{
						return Point(in.x,in.y,in.z);}
					}
				}
		}





	}
}

Point ray_plane(Point p,Vector dr,Plane l){		// (p0 - i0).n / (i.n)

	Vector nr = Vector(l.p1.x-p.x,l.p1.y-p.y,l.p1.z-p.z);
//	cout<<nr.out()<<endl;
	Vector n = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);
	Vector v2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
	n.cross(v2);
//	cout<<v2.out()<<n.out()<<dr.out()<<dr.dot(n)<<endl;
	double ndot = nr.dot(n);
	double ddot = dr.dot(n);
	if((ndot==0)&&(ddot==0))	//lies in the plane
		return zero_pt;
	else if(ddot==0)			// parallel to the plane but does not lie
		return zero_pt;
	else{					//intersects the infinite plane at some point | Sum of angles between lines joining 4pts and pt p must be 360 deg.
		double d = ndot/ddot;
		Vector in = Vector( p.x + d*dr.x , p.y + d*dr.y , p.z + d*dr.z );
		Vector e1 = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);	// edges of the plane
		Vector e2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
		Vector e3 = Vector(l.p4.x-l.p3.x,l.p4.y-l.p3.y,l.p4.z-l.p3.z);
		Vector e4 = Vector(l.p1.x-l.p4.x,l.p1.y-l.p4.y,l.p1.z-l.p4.z);
//		cout<<in.out()<<l.p1.out()<<l.p3.out()<<endl;
		Vector t1,t2;	//testing temperory vectors
		t1 = Vector(l.p1.x-in.x,l.p1.y-in.y,l.p1.z-in.z);
		t2 = Vector(l.p1.x-l.p4.x,l.p1.y-l.p4.y,l.p1.z-l.p4.z);
//		cout<<t1.out()<<t2.out()<<endl;
//		cout<<endl<<in.out();
		t1.cross(e1);
		t2.cross(e1);
//		cout<<t1.out()<<t2.out()<<endl<<t1.dot(t2)<<endl;
		
		if(t1.dot(t2)<0.0)
			return zero_pt;
		else{
			t1 = Vector(l.p2.x-in.x,l.p2.y-in.y,l.p2.z-in.z);
			t2 = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);
			t1.cross(e2);
			t2.cross(e2);
			if(t1.dot(t2)<0.0)
				return zero_pt;
			else{
				t1 = Vector(l.p3.x-in.x,l.p3.y-in.y,l.p3.z-in.z);
				t2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
				t1.cross(e3);
				t2.cross(e3);
				if(t1.dot(t2)<0.0)
					return zero_pt;
				else{
//					cout<<in.out()<<endl;
					t1 = Vector(l.p4.x-in.x,l.p4.y-in.y,l.p4.z-in.z);
					t2 = Vector(l.p4.x-l.p3.x,l.p4.y-l.p3.y,l.p4.z-l.p3.z);
					t1.cross(e4);
					t2.cross(e4);
					if(t1.dot(t2)<0.0){
						return zero_pt;}
					else{
						return Point(in.x,in.y,in.z);}
					}
				}
		}





	}
}
Point ray_plane_frwd(Point p,Vector dr,Plane l){		// (p0 - i0).n / (i.n)

	Vector nr = Vector(l.p1.x-p.x,l.p1.y-p.y,l.p1.z-p.z);
//	cout<<nr.out()<<endl;
	Vector n = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);
	Vector v2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
	n.cross(v2);
//	cout<<v2.out()<<n.out()<<dr.out()<<dr.dot(n)<<endl;
	double ndot = nr.dot(n);
	double ddot = dr.dot(n);
	if((ndot==0)&&(ddot==0))	//lies in the plane
		return zero_pt;
	else if(ddot==0)			// parallel to the plane but does not lie
		return zero_pt;
	else{					//intersects the infinite plane at some point | Sum of angles between lines joining 4pts and pt p must be 360 deg.
		double d = ndot/ddot;
		Vector in = Vector( p.x + d*dr.x , p.y + d*dr.y , p.z + d*dr.z );
		Vector e1 = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);	// edges of the plane
		Vector e2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
		Vector e3 = Vector(l.p4.x-l.p3.x,l.p4.y-l.p3.y,l.p4.z-l.p3.z);
		Vector e4 = Vector(l.p1.x-l.p4.x,l.p1.y-l.p4.y,l.p1.z-l.p4.z);
//		cout<<in.out()<<l.p1.out()<<l.p3.out()<<endl;
		Vector t1,t2;	//testing temperory vectors
		t1 = Vector(l.p1.x-in.x,l.p1.y-in.y,l.p1.z-in.z);
		t2 = Vector(l.p1.x-l.p4.x,l.p1.y-l.p4.y,l.p1.z-l.p4.z);
//		Line in_l = Line(Vector p,Vector in);
//		in_l.normalize();
//		cout<<t1.out()<<t2.out()<<endl;
//		cout<<endl<<in.out();
		t1.cross(e1);
		t2.cross(e1);
//		cout<<t1.out()<<t2.out()<<endl<<t1.dot(t2)<<endl;
		
		if(t1.dot(t2)<0.0)
			return zero_pt;
		else{
			t1 = Vector(l.p2.x-in.x,l.p2.y-in.y,l.p2.z-in.z);
			t2 = Vector(l.p2.x-l.p1.x,l.p2.y-l.p1.y,l.p2.z-l.p1.z);
			t1.cross(e2);
			t2.cross(e2);
			if(t1.dot(t2)<0.0)
				return zero_pt;
			else{
				t1 = Vector(l.p3.x-in.x,l.p3.y-in.y,l.p3.z-in.z);
				t2 = Vector(l.p3.x-l.p2.x,l.p3.y-l.p2.y,l.p3.z-l.p2.z);
				t1.cross(e3);
				t2.cross(e3);
				if(t1.dot(t2)<0.0)
					return zero_pt;
				else{
//					cout<<in.out()<<endl;
					t1 = Vector(l.p4.x-in.x,l.p4.y-in.y,l.p4.z-in.z);
					t2 = Vector(l.p4.x-l.p3.x,l.p4.y-l.p3.y,l.p4.z-l.p3.z);
					t1.cross(e4);
					t2.cross(e4);
					if(t1.dot(t2)<0.0){
						return zero_pt;}
					else{
						return Point(in.x,in.y,in.z);}
					}
				}
		}





	}
}


