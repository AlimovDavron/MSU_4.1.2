//
// Created by alimovdavron on 1/12/20.
//

#ifndef MSU_4_1_2_ODU_H
#define MSU_4_1_2_ODU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double p(double x);
double q(double x);
double r(double x);
double groundTruth(double x);

int memsize_result(double a, double b, double h);
int memsize_tmp();
int AdamsMoultonMethod(double a, double b, double h, double y0, double z0, double *tmp, double* result);
double NewtonMethod(double a, double b, double h, double ya, double yb, double eps, double *tmp, double* result);
void draw(double a, double b, double h, double* result);

#endif //MSU_4_1_2_ODU_H
