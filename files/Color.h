/**
*
*@author Dinesh Prasanth
*@guidance Prof Jaya S Nair
*
*

*@about class Color for representing color attribute for any class. RGB method of representation is followed.
*
*/
#ifndef COLOR_H
#define COLOR_H
#include<string.h>
#include<sstream>
#include<math.h>
using namespace std;
class Color{

public:
	double r,g,b;

// define the constructors

	Color(){
		r = 0.0;
		g = 0.0;
		b = 0.0;
		}
	Color(const double R,const double G,const double B){
		r=R;
		if(r<0.0) r = 0.0;
		else if(r>1.0) r = 1.0;

		g=G;
		if(g<0.0) g=0.0;
		else if(g>1.0) g=1.0;

		b=B;
		if(b<0.0) b=0.0;
		else if(b>1.0) b=1.0;
		}
	Color(const Color& c){
		r = c.r;
		b = c.b;
		g = c.g;
		}
	~Color(){}

// assignment operators

	Color& operator= (const Color& c);
	Color& operator+ (const Color& c);
// outputting format

	string out();
	bool operator==(Color& c);
	bool operator!=(Color& c);
	void alter(double f);
};
#endif
