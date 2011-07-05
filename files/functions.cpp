#include "functions.h"
#include<math.h>
#include "Point.h"

double returndecimal(double k){
	double temp = floor(k);
	temp = k - temp;
	return temp;
}

double sample(double i)
{
	double temp = returndecimal(i);
	temp = temp*10.0;
	temp = returndecimal(temp);
	temp = i-(temp/10);	
	if(temp>0.0&&temp<0.1)return 0;
	else return temp;
}

