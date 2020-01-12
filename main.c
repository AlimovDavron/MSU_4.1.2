#include "odu.h"

int main() {


    double a = 0, b = 2, h = 0.1;

    double* result = malloc(memsize_result(a, b, h));
    double* tmp = malloc(memsize_tmp());

    // double parameter = NewtonMethod(a, b, h, 1, groundTruth(b), 1e-10, tmp, result);
    AdamsMoultonMethod(a, b, h, 1, -1, tmp, result);

    draw(a, b, h, result);

    return 0;
}
