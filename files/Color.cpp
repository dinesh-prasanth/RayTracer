#include<string.h>
#include<sstream>
#include<math.h>
#include "Color.h"
using namespace std;
// assignment operators

	Color& Color :: operator= (const Color& c){
		if( this == &c ) return (*this);
		r = c.r;
		b = c.b;
		g = c.g;
		return (*this);
		}
	Color& Color :: operator+ (const Color& c){
		r += c.r;
		g += c.g;
		b += c.b;
		if(r<0.0)
			r = 0.0;
		else if(r>1.0)
			r = 1.0;
		if(b<0.0)
			b = 0.0;
		else if(b>1.0)
			b = 1.0;
		if(g<0.0)
			g = 0.0;
		else if(g>1.0)
			g = 1.0;
		return (*this);

		}
// outputting format

	string Color :: out(){
		stringstream out;
		out<<"Color ( "<<r<<" "<<g<<" "<<b<<" )";
		return out.str();
		}
	bool Color :: operator==(Color& c){
		if((r==c.r)&&(r==c.r)&&(r==c.r))
			return 1;
		else
			return 0;
		}
	bool Color :: operator!=(Color& c){
		if((r!=c.r)||(g!=c.g)||(b!=c.b))
			return 1;
		else
			return 0;
		}
	void Color :: alter(double f){
		r = r*f;
		if(r<0.0)
			r = 0.0;
		else if(r>1.0)
			r = 1.0;
		b = b*f;
		if(b<0.0)
			b = 0.0;
		else if(b>1.0)
			b = 1.0;
		g = g*f;
		if(g<0.0)
			g = 0.0;
		else if(g>1.0)
			g = 1.0;
	}
