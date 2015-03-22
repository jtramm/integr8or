// A test main function

#include "integr8or_header.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define Z 13
#define Ed 25.0

double v(double E);
double Sn(double E);
double Sigma_n(double E);
double Epsilon(double E);
double Se(double E);
double K_P( double E );

int main(void)
{
	int gp = 1000;
	int gp_plot = 10000;
	double f = 0.90;
	
	// Energy Grid
	double * E = (double *) malloc( gp_plot * sizeof(double));
	double * Vt = (double *) malloc( gp_plot * sizeof(double));
	for( int i = 0; i < gp_plot; i++ )
	{
		double delta = 8.0 / gp_plot;
		E[i] = pow(10.0, delta*i);
	}

	// Plot variable high value from Ed to high
	for( int i = 0; i < gp_plot; i++ )
	{
		double val;
		if( E[i] <= 2.0 * Ed )
			 val = K_P(E[i]);	
		else
		{
			double integral = integr8or(v, 0.0001, E[i], gp);
			val = integral / (2.0*Ed);
		}
		Vt[i] = val;
		//printf("%e\t%e\t%e\n", E[i], val, K_P(E[i]));
	}
	
	double max = Vt[gp_plot-1];
	double cutoff = max * f;
	printf("V max = %lf\n", max);
	printf("cutoff = %lf\n", cutoff);

	for( int i = 0; i < gp_plot-1; i++ )
	{
		if( Vt[i] >= cutoff)
		{
			printf("Ed = %e\n", E[i]);
			printf("V(Ed) = %lf\n", Vt[i]);
			printf("idx = %d out of %d\n", i, gp_plot);
			break;
		}
	}


	return 0;
}


double K_P( double E )
{
	// Al
	double me = 5.4857990946e-4;
	double M =  26.981539;
	double I =  5.98577;
	/*
	// Pb
	double me = 5.4857990946e-4;
	double M =  208;
	double I =  7.41666;
	*/
	double Ec = M * I / (4 * me);
	if( E < Ed )
		return 0;
	else if( E >= Ed && E <= 2.0 * Ed )
		return 1.0;
	else if( E > 2.0 * Ed && E <= Ec )
		return E / (2.0 * Ed);
	else
		return Ec / (2.0*Ed);
}

double v(double E)
{
	E *= 1e-3;
	return Sn(E) / (Sn(E) + Se(E));
}

double Sn(double E)
{
	double numerator = 8.462e-15 * Z*Z * Sigma_n(E);
	double denominator = 4.0 * pow(Z,0.23);
	if( denominator <= 0 )
		printf("SN denom = %lf\n", denominator);

	return numerator/denominator;
}

double Sigma_n(double E)
{
	double numerator = 0.5 * log( 1.0 + 1.1383 * Epsilon(E));
	double epE = Epsilon(E);
	if( epE <= 0 )
		printf("epE = %lf\n", epE);
	double denominator = Epsilon(E) + 0.01321*pow(Epsilon(E),0.21226)
		+ 0.19593 * pow(Epsilon(E),0.5);
	if( denominator <= 0 )
		printf("Sigma_n denom = %lf\n", denominator);

	return numerator/denominator;
}

double Epsilon(double E)
{
	double numerator = 32.53 * E;
	double denominator = 4 * Z*Z * pow(Z,0.23);
	if( denominator <= 0 )
		printf("Epsilon denom = %lf\n", denominator);

	return numerator/denominator;
}

double Se(double E)
{
	return 3.0e-15 * pow(Z,2.0/3.0) * sqrt(E);
}
