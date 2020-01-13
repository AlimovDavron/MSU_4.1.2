#include "odu_01_36.h"

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
        return 2;
    if(checkInput == 0)
        return 3;

    checkInput = fscanf(in, "%lf", b);
    if(checkInput == EOF)
        return 2;
    if(checkInput == 0)
        return 3;

    checkInput = fscanf(in, "%lf", c);
    if(checkInput == EOF)
        return 2;
    if(checkInput == 0)
        return 3;

    checkInput = fscanf(in, "%lf", d);
    if(checkInput == EOF)
        return 2;
    if(checkInput == 0)
        return 3;

    checkInput = fscanf(in, "%lf", h);
    if(checkInput == EOF)
        return 2;
    if(checkInput == 0)
        return 3;

    checkInput = fscanf(in, "%lf", eps);
    if(checkInput == EOF)
        return 2;
    if(checkInput == 0)
        return 3;

    return 0;
}

int main(int argc, char* argv[]) {
    double a, b, c, d, h, eps;
    char* inputFile = "input_01_36.txt";
    char* outputFile = "output_01_36.txt";
    if(argc > 1){
        inputFile = argv[1];
        if(argc > 2) {
            outputFile = argv[2];
        }
    }

    if (!validateFile(inputFile)) {
        printf("ValidationError: There is no such file.\n");
        return 1;
    }

    switch (readInputData(inputFile, &a, &b, &c, &d, &h, &eps)){
        case 0:
            break;
        case 2:
            printf("ValidationError: There is no enough parameters.");
            return 2;
        case 3:
            printf("ValidationError: Incorrect input");
            return 3;
        default:
            break;
    }

    double* result = malloc(memsize_result(a, b, h));
    double* tmp = malloc(memsize_tmp());

    NewtonMethod(a, b, h, c, d, eps, tmp, result);
    draw(a, b, h, result);


    return 0;
}
