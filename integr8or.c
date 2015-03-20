#include<stdlib.h>

double integr8or( double (*f)(double), double min, double max, int gp )
{
	double range = max - min;
	double del = range / gp;
	double integral = 0;

	for( int i = 0; i < gp; i++ )
	{
		double low = min + del*i;
		double high = min + del*(i+1);
		double mid = (low+high)/2;

		double A = (*f)(low);
		double B = (*f)(mid);
		double C = (*f)(high);

		integral += (high-low)/6.0 * (A + 4.0*B + C);
	}

	return integral;
}
