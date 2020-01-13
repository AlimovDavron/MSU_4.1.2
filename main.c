#include "odu.h"

int validateFile(char* filename)
{
    FILE *f = fopen(filename, "rb");
    return f != NULL;
}

int readInputData(char *inputFile, double *a, double *b, double *c, double *d, double *h, double *eps)
{
    int checkInput;
    FILE *in = fopen(inputFile, "r");

    checkInput = fscanf(in, "%lf", a);
    if(checkInput == EOF)
        return 5;
    if(checkInput == 0)
        return 6;

    checkInput = fscanf(in, "%lf", b);
    if(checkInput == EOF)
        return 5;
    if(checkInput == 0)
        return 6;

    checkInput = fscanf(in, "%lf", c);
    if(checkInput == EOF)
        return 5;
    if(checkInput == 0)
        return 6;

    checkInput = fscanf(in, "%lf", d);
    if(checkInput == EOF)
        return 5;
    if(checkInput == 0)
        return 6;

    checkInput = fscanf(in, "%lf", h);
    if(checkInput == EOF)
        return 5;
    if(checkInput == 0)
        return 6;

    checkInput = fscanf(in, "%lf", eps);
    if(checkInput == EOF)
        return 5;
    if(checkInput == 0)
        return 6;

    return 0;
}

int main(int argc, char* argv[]) {
    double a, b, c, d, h, eps;
    char* inputFile = "input.txt";
    char* outputFile = "output.txt";
    if(argc > 1){
        inputFile = argv[1];
        if(argc > 2) {
            outputFile = argv[2];
        }
    }

    if (!validateFile(inputFile)) {
        printf("ValidationError: There is no such file.\n");
        return 3;
    }

    readInputData(inputFile, &a, &b, &c, &d, &h, &eps);

    double* result = malloc(memsize_result(a, b, h));
    double* tmp = malloc(memsize_tmp());

    NewtonMethod(a, b, h, c, d, eps, tmp, result);
    draw(a, b, h, result);


    return 0;
}
