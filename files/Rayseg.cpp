#include "Lineseg.h"
#include "Color.h"
#include "Rayseg.h"
#include<sstream>

// function for displaying the Raysegment
	string Rayseg :: out(){
		stringstream out;
		out<<"Raysegment[\t"<<l.out()<<"\t\t"<<c.out()<<"\t]";
		return out.str();
	}

