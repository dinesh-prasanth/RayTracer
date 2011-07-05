#include "Point.h"
#include<math.h>
#include<sstream>
#include<string.h>
#include<vector>
#include "Lineseg.h"

	void Lineseg :: push(const Point p1){
		p.push_back(p1);
	}
	string Lineseg :: out(){
		stringstream out;
		out<<"Linesegment( " <<(p[0]).out() <<(p[1]).out() << " )";
		return out.str();	
	}
	string Lineseg :: outall(){
		stringstream out;
		out<<"Linesegment( ";
		for(int i=0;i<p.size();i++)
			out<<p[i].out()<<" ";
		out<<" )";
		return out.str();
	}
	double Lineseg :: totallength(){
		double len = 0.0;
		for(int i=0;i<(p.size()-1);i++)
			len+=linelength(p[i],p[i+1]);
		return len;
		}
	double Lineseg :: linelength(const Point p1,const Point p2){
		double l;
		double _x,_y,_z;
		_x = (p1.x-p2.x);
		_y = (p1.y-p2.y);
		_z = (p1.z-p2.z);
		l = sqrt( _x*_x + _y*_y + _z*_z );
		return l;
	}


