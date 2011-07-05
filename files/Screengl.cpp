#include<vector>
#include "Color.h"
#include "Screengl.h"
	void Screengl :: allotsize(const unsigned short int x,const unsigned short int y){
		for(unsigned short int i=0;i<x;i++){
			p.push_back( vector<Color>(y) );
			}
	}
	void Screengl :: push(const unsigned short int x,const unsigned short int y,Color c){
		p[x][y] = c;
	}
