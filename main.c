// A test main function

#include "integr8or_header.h"
#include<stdio.h>
#include<math.h>

#define Z 13
#define A 27
#define Ed 25.0
#define density 2.70

double v(double E);
double Sn(double E);
double Sigma_n(double E);
double Epsilon(double E);
double Se(double E);

int main(void)
{
	double high = 200;
	int gp = 1000;
	int gp_plot = 10;
	double delta = (high - 2.0 * Ed) / gp_plot;

	double NA = 6.022e23;
	double N = density * NA / 27.0;

	// Plot variable high value from Ed to high
	for( int i = 0; i < gp_plot; i++ )
	{
		double E = 2.0*Ed + i*delta;
		double integral = integr8or(v, 2.0*Ed, E, gp);
		double val = 2.0 / E * (N * integral);
		printf("%.2lf\t%e\n", E, val);
	}
	
	return 0;
}

double v(double E)
{
	return Sn(E) + Se(E);
}

double Sn(double E)
{
	double numerator = 8.462e-15 * Z*Z * Sigma_n(E);
	double denominator = 4 * pow(Z,0.23);

	return numerator/denominator;
}

double Sigma_n(double E)
{
	double numerator = 0.5 * log( 1.0 + 1.1383 * Epsilon(E));
	double denominator = Epsilon(E) + 0.01321*pow(Epsilon(E),0.21226)
		+ 0.19593 * sqrt(Epsilon(E));

	return numerator/denominator;
}

double Epsilon(double E)
{
	double numerator = 32.53 * E;
	double denominator = 4 * Z*Z * pow(Z,0.23);
	
	return numerator/denominator;
}

double Se(double E)
{
	return 3.0e-15 * pow(Z,2.0/3.0) * sqrt(E);
}
