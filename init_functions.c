#include "odu_01_36.h"

double p(double x){
    return -1;
}

double q(double x){
    return -2;
}

double r(double x){
    return 0;
}

double groundTruth(double x){
    return -2*exp(-x);
}