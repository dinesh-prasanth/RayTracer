/**
*
*@author Dinesh Prasanth
*@guidance Prof Jaya S Nair
*
*

*@about class Rayseg for representing a light raysegment which has property of a line and color.
*
*/
#ifndef RAYSEG_H
#define RAYSEG_H
#include "Lineseg.h"
#include "Color.h"
#include<sstream>
class Rayseg{
public:	
	Lineseg l;
	Color c;

//definition of constructors

	Rayseg(){}
	Rayseg(const Rayseg& R){
		l = R.l;
		c = R.c;
	}
	Rayseg(const Lineseg& L,const Color& C){
		l = L;
		c = C;
		}
	Rayseg(const Lineseg& L,const double R,const double G,const double B){
		l = L;
		c.r = R;
		c.g = G;
		c.b = B;
		}
	~Rayseg(){}

// function for displaying the Raysegment
	string out();
};

#endif
