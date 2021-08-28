#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define inf_roots -1
#define p 0.00000000001
int IsZero (float a, float b, float c){
    double d =  b * b - 4 * a * c;
    if (fabs(d)<p)
        return 1;
    else
        return 0;
}

int SolveSquare (float a, float b, float c, float* x1, float* x2){

        double d = b * b - 4 * a * c;
        printf ("d = %g\n",d);
        if (IsZero(a, b, c)){
            *x1 = (-b / (2 * a));
            return 1;
        }
        else if (d > 0){
            *x1 = (-b + sqrt(d)) / (2 * a);
            *x2 = (-b - sqrt(d)) / (2 * a);
            return 2;
        }
        else {
            return 0;
        }
}

int SolveLiner (float b, float c, float* x1){

        if ((b == 0) && ( c == 0)){
            return inf_roots;
        }
        else if (b != 0){
            *x1 = (-c / b);
            return 1;
        }
}

int main()
{
    float a = 0, b = 0, c = 0;
    scanf ("%f %f %f", &a, &b, &c);
    printf("a = %f\n", a);
    printf("b = %f\n", b);
    printf("c = %f\n", c);

    float x1 = 0, x2 = 0;
    if (a != 0){
    int nRoots = SolveSquare (a, b, c, &x1, &x2); //возвращает кол во корней
     switch (nRoots)
     {
        case 0: printf ("No roots\n");
                break;
        case 1: printf ("x=%f\n", x1);
                break;
        case 2: printf ("x1=%f x2=%f\n", x1, x2);
 

               break;
        case inf_roots: printf("Any number\n");
                break;
        default: printf ("main(): ERROR: nRoots=%d\n", nRoots);

    }
    }
    else {
        int nRoots = SolveLiner (b, c, &x1);
        switch (nRoots){
            case inf_roots: printf("Any number\n");
                break;
            case 1: printf ("x=%f\n", x1);
                break;
        }
    }
    return 0;
}
//assert (std :: isfinite (val)) возвращает верно ли высказывание
//isfinite (val) - является ли аргумент конечным числом
//NULL - нулевой адресс
