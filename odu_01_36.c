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

void AdamsMoultonMethod(double a, double b, double h, double y0, double z0, double *tmp, double* result){
    int n = (b - a) / h, i, j;
    double k11, k12, k13, k14;
    double k21, k22, k23, k24;
    double X0, Y0, Y1, Zo, Z1;
    double *Y_last = tmp;
    double *Z_last = tmp + 4;

    X0 = a;
    Y0 = y0;
    Zo = z0;

    result[0] = y0;
    for(i = 0; i < min(n, 4); i++, X0 += h) {

        k11 = h * g(X0, Y0, Zo);
        k21 = h * f(X0, Y0, Zo);

        k12 = h * g(X0 + h / 2, Y0 + k21 / 2, Zo + k11 / 2);
        k22 = h * f(X0 + h / 2, Y0 + k21 / 2, Zo + k11 / 2);

        k13 = h * g(X0 + h / 2, Y0 + k22 / 2, Zo + k12 / 2);
        k23 = h * f(X0 + h / 2, Y0 + k22 / 2, Zo + k12 / 2);

        k14 = h * g(X0 + h, Y0 + k23, Zo + k13);
        k24 = h * f(X0 + h, Y0 + k23, Zo + k13);

        Z1 = Zo + (k11 + 2 * k12 + 2 * k13 + k14) / 6;
        Y1 = Y0 + (k21 + 2 * k22 + 2 * k23 + k24) / 6;

        Y_last[i] = Y1;
        Z_last[i] = Z1;

        Y0 = Y1;
        Zo = Z1;

        *(result + i + 1) = Y0;
    }

    for(i = 4; i < n; i++, X0 += h){
        Y1 = Y_last[3] + h * (55*f(X0, Y_last[3], Z_last[3]) - 59 * f(X0 - h, Y_last[2], Z_last[2]) +
                37*f(X0 - 2 * h, Y_last[1], Z_last[1]) - 9 * f(X0 - 3 * h, Y_last[0], Z_last[0])) / 24;

        Z1 = Z_last[3] + h * (55 * g(X0, Y_last[3], Z_last[3]) - 59 * g(X0 - h, Y_last[2], Z_last[2]) +
                37 * g(X0 - 2 * h, Y_last[1], Z_last[1]) - 9 * g(X0 - 3 * h, Y_last[0], Z_last[0])) / 24;

        Y1 = Y_last[3] + h * (9*f(X0 + h, Y1, Z1) + 19 * f(X0, Y_last[3], Z_last[3]) -
                5*f(X0 - h, Y_last[2], Z_last[2]) + f(X0 - 2 * h, Y_last[1], Z_last[1])) / 24;

        Z1 = Z_last[3] + h * (9 * g(X0 + h, Y1, Z1) + 19 * g(X0, Y_last[3], Z_last[3]) -
                5 * g(X0 - h, Y_last[2], Z_last[2]) + g(X0 - 2 * h, Y_last[1], Z_last[1])) / 24;

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