#ifndef OBJECT_H
#define OBJECT_H
#include "Sphere.h"
#include<vector>
#include<sstream>
#include "Plane.h"
#include "Cuboid.h"
class Object
{
public:
	vector<Sphere> s;
	vector<Plane> p;
	vector<Cuboid> c;
	Object(){
		}
	Object(const Sphere& S){
		Sphere sp = Sphere(S);
		s.push_back(sp);
		}
	Object(const Plane& P){
		Plane pl = Plane(P);
		p.push_back(pl);
		}
	Object(const Cuboid& C){
		Cuboid cb = Cuboid(C);
		c.push_back(cb);
		}
	Object(const Object& O){
		Sphere sp;		
		for(int i=0;i<O.s.size();i++){		
			sp = Sphere(O.s[i]);
			s.push_back(sp);
			}
		Plane pl;
		for(int i=0;i<O.p.size();i++){		
			pl = Plane(O.p[i]);
			p.push_back(pl);
			}
		for(int i=0;i<O.c.size();i++){
			Cuboid cb = Cuboid(O.c[i]);
			c.push_back(cb);
			}
		}
	~Object(){}

	void push(const Sphere& S);
	void push(const Plane P);
	void push(const Cuboid C);
	void convertCtoP();	//to break down all the sides of square to individual planes.
	void pop();
	string out();
};
#endif
