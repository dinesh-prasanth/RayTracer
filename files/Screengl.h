#ifndef SCREENGL_H
#define SCREENGL_H
#include<vector>
#include "Color.h"
class Screengl
{
public:
	vector< vector<Color> > p;

	Screengl(){
		}
	Screengl(vector< vector<Color> > P){
		p = P;
		}
	~Screengl(){}
	void allotsize(const unsigned short int x,const unsigned short int y);
	void push(const unsigned short int x,const unsigned short int y,Color c);
};
#endif
