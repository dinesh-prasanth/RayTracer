/**
*
*@author Dinesh Prasanth
*@guidance Prof Jaya S Nair
*
*

*@about class Lineseg to represent a line segment, length is size of the line segment and size is size of sampling(default = 0.1).
*
*/
#ifndef LINESEG_H
#define LINESEG_H
#include "Point.h"
#include<math.h>
#include<sstream>
#include<string.h>
#include<vector>

class Lineseg{
public:
	vector<Point> p;
	float length;	//length between the points
		
//defining construtors

	Lineseg(){
		length = 0.0;
	}
	Lineseg(const Point p1,const Point p2){
		length = linelength(p1,p2);
		p.push_back(p1);
		p.push_back(p2);
	}
	Lineseg(const Lineseg& l){
		length = l.length;
		p = l.p;
	}
	~Lineseg(){}
	
	void push(const Point p1);
	string out();
	string outall();
	double totallength();
	double linelength(const Point p1,const Point p2);


};




#endif
