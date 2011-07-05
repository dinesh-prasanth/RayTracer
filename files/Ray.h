#ifndef RAY_H
#define RAY_H
#include "Color.h"
#include <sstream>
#include "Line.h"
class Ray
{
public:
	Line l;
	Color c;

	Ray(){}
	Ray(const Line& L,const Color& C){
		l = L;c = C;
	}
	Ray(const Ray& r){
		l = r.l;
		c = r.c;
	}
	~Ray(){}

	string out();
};
#endif
