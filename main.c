// A test main function

#include<stdio.h>
#include<math.h>

#define Z 6
#define M 56

double v(double E);
double Sn(double E);
double Sigma_n(double E);
double Epsilon(double E);
double Se(double E);

int main(void)
{
	return 0;
}

double v(double E)
{
	return Sn(E) + Se(E);
}

double Sn(double E)
{
	double numerator = 8.462e-15 * Z*Z * M * Sigma_n(E);
	double denominator = 4 * M * pow(Z,0.23);

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
	double numerator = 32.53 * M * E;
	double denominator = 4 * Z*Z * M * pow(Z,0.23);
	
	return numerator/denominator;
}

double Se(double E)
{
	return 3.0e-15 * pow(Z,2.0/3.0) * sqrt(E);
}
