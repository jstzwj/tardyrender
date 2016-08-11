#pragma once
#ifndef MATH
#define MATH

#define PI 3.1415926535898
#define LNE 2.718281828459

#define tardy_max(x,y) (((x)>(y))?(x):(y))
#define tardy_min(x,y) (((x)<(y))?(x):(y))

const static double tritable[26][3];

long tardy_abs(long n);

double tardy_fabs(double n);

double tardy_pow(double n, int x);

double tardy_exp(int n);

double tardy_sqrt(double n);

double tardy_sin(double n);

double tardy_cos(double n);

double tardy_tan(double n);




#endif // !MATH
