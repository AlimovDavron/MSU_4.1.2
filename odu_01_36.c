//
// Created by alimovdavron on 1/12/20.
//
#include "odu_01_36.h"

int memsize_result(double a, double b, double h){
    int n = (b - a) / h + 1;
    return n*sizeof(double);
}

int memsize_tmp(){
    return 8*sizeof(double);
}

double g(double x, double y, double z){
    return - p(x)*z - q(x)*y + r(x);
}

double f(double x, double y, double z){
    return z;
}

int min(int a, int b){
    if(a < b)
        return a;
    else return b;
}

int AdamsMoultonMethod(double a, double b, double h, double y0, double z0, double *tmp, double* result){
    int n = (b - a) / h, i, j;
    double k1, k2, k4, k3;
    double q1, q2, q4, q3;
    double Xo, Yo, Y1, Zo, Z1;
    double *Y_last = tmp;
    double *Z_last = tmp + 4;

    Xo = a;
    Yo = y0;
    Zo = z0;

    result[0] = y0;
    for(i = 0; i < min(n, 4); i++, Xo += h) {

        k1 = h * g(Xo, Yo, Zo);
        q1 = h * f(Xo, Yo, Zo);

        k2 = h * g(Xo + h / 2, Yo + q1 / 2, Zo + k1 / 2);
        q2 = h * f(Xo + h / 2, Yo + q1 / 2, Zo + k1 / 2);

        k3 = h * g(Xo + h / 2, Yo + q2 / 2, Zo + k2 / 2);
        q3 = h * f(Xo + h / 2, Yo + q2 / 2, Zo + k2 / 2);

        k4 = h * g(Xo + h, Yo + q3, Zo + k3);
        q4 = h * f(Xo + h, Yo + q3, Zo + k3);

        Z1 = Zo + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        Y1 = Yo + (q1 + 2 * q2 + 2 * q3 + q4) / 6;

        Y_last[i] = Y1;
        Z_last[i] = Z1;

        Yo = Y1;
        Zo = Z1;

        *(result + i + 1) = Yo;
    }

    for(i = 4; i < n; i++, Xo += h){
        Y1 = Y_last[3] + h * (55*f(Xo, Y_last[3], Z_last[3]) - 59*f(Xo-h, Y_last[2], Z_last[2]) +
                37*f(Xo-2*h, Y_last[1], Z_last[1]) - 9*f(Xo-3*h, Y_last[0], Z_last[0])) / 24;

        Z1 = Z_last[3] + h * (55 * g(Xo, Y_last[3], Z_last[3]) -59 * g(Xo - h, Y_last[2], Z_last[2]) +
                37 * g(Xo - 2 * h, Y_last[1], Z_last[1]) - 9 * g(Xo - 3 * h, Y_last[0], Z_last[0])) / 24;

        Y1 = Y_last[3] + h * (9*f(Xo+h, Y1, Z1) + 19*f(Xo, Y_last[3], Z_last[3]) -
                5*f(Xo-h, Y_last[2], Z_last[2]) + f(Xo-2*h, Y_last[1], Z_last[1])) / 24;

        Z1 = Z_last[3] + h * (9 * g(Xo + h, Y1, Z1) + 19 * g(Xo, Y_last[3], Z_last[3]) -
                5 * g(Xo - h, Y_last[2], Z_last[2]) + g(Xo - 2 * h, Y_last[1], Z_last[1])) / 24;

        for(j = 0; j < 3; j++){
            Y_last[j] = Y_last[j+1];
            Z_last[j] = Z_last[j+1];
        }

        Y_last[3] = Y1;
        Z_last[3] = Z1;

        *(result + i + 1) = Y1;
    }
}

double F(double x, double yb, double a, double b, double h, double ya, double* tmp, double* result){
    AdamsMoultonMethod(a, b, h, ya, x, tmp, result);
    int n = (b - a) / h + 1;
    double t = result[n-1];
    return t - yb;
}

double NewtonMethod(double a, double b, double h, double ya, double yb, double eps, double *tmp, double* result){
    double x0 = 1;
    double x1 = - F(x0, yb, a, b, h, ya, tmp, result) / ( (F(x0+eps, yb, a, b, h, ya, tmp, result) - F(x0, yb, a, b, h, ya, tmp, result)) / eps );
    while(fabs(x1 - x0) > eps){
        x0 = x1;
        x1 = x0 - F(x0, yb, a, b, h, ya, tmp, result) / ( (F(x0+eps, yb, a, b, h, ya, tmp, result) - F(x0, yb, a, b, h, ya, tmp, result)) / eps );
    }

    return x1;
}