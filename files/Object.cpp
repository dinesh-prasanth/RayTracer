#include "Sphere.h"
#include<vector>
#include<sstream>
#include "Plane.h"
#include "Object.h"
#include "Cuboid.h"
	void Object :: push(const Sphere& S){
		s.push_back(S);
	}
	void Object :: push(const Plane P){
		p.push_back(P);
	}
	void Object :: push(const Cuboid C){
		c.push_back(C);
	}
	void Object :: pop(){
		s.pop_back();
	}
	void Object :: convertCtoP(){	// to break down all the sides of square to individual planes.
		for(int i=0;i<c.size();i++){
			p.push_back(c[i].p1);
			p.push_back(c[i].p2);
			p.push_back(c[i].p3);
			p.push_back(c[i].p4);
			p.push_back(c[i].p5);
			p.push_back(c[i].p6);
		}
	}
	string Object :: out(){
		stringstream out;
		out<<"Object[ ";
		for(int i=0;i<s.size();i++)
			out<<s[i].out()<<" ";
		for(int i=0;i<p.size();i++)
			out<<p[i].out()<<" ";
		out<<" ]";
		return out.str();
		}
