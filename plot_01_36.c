//
// Created by alimovdavron on 1/12/20.
//

#include "odu_01_36.h"

void draw(double a, double b, double h, double* result){
    FILE *pipe = popen("gnuplot -persistent", "w");

    /*fprintf(pipe, "set terminal push # save current terminal\n"
                  "set terminal unknown\n");*/
    fprintf(pipe, "plot '-' with linespoints pointtype 0 lw 5 lt rgb \"#7CFC00\"  title 'Исходная функция'");
    fprintf(pipe, " , '-' with linespoints pointtype 7 lt -1 title 'Приближение'\n");

    double left = a, right = b;
    for(; left < right; left += 0.001)
        fprintf(pipe, "%lf %lf\n", left, groundTruth(left));

    fprintf(pipe, "%s\n", "e");
    fflush(pipe);

    int n = (b - a) / h + 1; left = a;
    for(int i = 0; i < n; i++, left += h){
        fprintf(pipe, "%lf %lf\n", left, result[i]);
    }

    fprintf(pipe, "%s\n", "e");
    fflush(pipe);
    /*fprintf(pipe, "set terminal pop # restore previous terminal\n"
                  "\n"
                  "min = (GPVAL_Y_MIN < GPVAL_X_MIN ? GPVAL_Y_MIN : GPVAL_X_MIN)\n"
                  "max = (GPVAL_Y_MAX > GPVAL_X_MAX ? GPVAL_Y_MAX : GPVAL_X_MAX)\n"
                  "\n"
                  "set xrange[min:max]\n"
                  "set yrange[min:max]\n"
                  "\n"
                  "replot\n");*/
    fflush(pipe);
    pclose(pipe);
}