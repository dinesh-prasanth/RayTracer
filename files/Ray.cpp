#include "Color.h"
#include <sstream>
#include "Line.h"
#include "Ray.h"
	string Ray :: out(){
		stringstream out;
		out<<"Ray[ "<<l.a.out()<<" "<<l.b.out()<<" "<<c.out()<<" ]";
		return out.str();
	}

