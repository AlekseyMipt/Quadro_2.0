#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#define inf_roots -1
#define p 0.001
#define test_num 6

int IsNAN(double a) {
  return (a != a);
}

void Input_Function (double* a, double* b, double* c) {
    int num = scanf ("%lf %lf %lf", a, b, c);
	while (num != 3) {
        printf ("repeat your input:\n");
        fflush(stdin);
        num = scanf("%lf %lf %lf", a, b, c);

	}
}
//----------------------------------------------------------------------------------------------------
//! Counts a diskreminant
//
// @param [in]  a   a-coefficient
// @param [in]  b   b-coefficient
// @param [in]  c   c-coefficient
// @param [out] x1  Pointer to the 1st root
//
// @return diskreminant value
//----------------------------------------------------------------------------------------------------
double Diskr (double a, double b, double c) {
    assert(isfinite (a));
    assert(isfinite (b));
    assert(isfinite (c));

    return b * b - 4 * a * c;
}
//----------------------------------------------------------------------------------------------------
//!
//
// @param [in]  val1  val1-firs number
// @param [in]  val2  val2-csecond number
//
// @return
//----------------------------------------------------------------------------------------------------
int cmp (double val1, double val2) {
    if ((!IsNAN(val1)) && (!IsNAN(val2))) {

        if (fabs(val1 - val2) < p) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else
        return 1;
}

//----------------------------------------------------------------------------------------------------
//! Solves a liner equation  bx +c = 0
//
// @param [in]  b   b-coefficient
// @param [in]  c   c-coefficient
// @param [out] x1  Pointer to the 1st root
//
// @return Number of roots
//----------------------------------------------------------------------------------------------------
 int SolveLiner (double b, double c, double* x1) {
    assert(isfinite (b));
    assert(isfinite (c));
    assert (x1 != NULL);

    if ((cmp(b, 0)) && (cmp(c, 0))){
        return inf_roots;
    }
    if (!cmp(b, 0)) {
        *x1 = (-c / b);
        return 1;
    }
    else
        return 0;
}
//----------------------------------------------------------------------------------------------------
//! Solves a square equation axˆ2 + bx +c = 0
//
// @param [in]  a   a-coefficient
// @param [in]  b   b-coefficient
// @param [in]  c   c-coefficient
// @param [out] x1  Pointer to the 1st root
// @param [out] x2  Pointer to the 2nd root
//
// @return Number of roots
// @brief only in case when a != 0
//----------------------------------------------------------------------------------------------------
int SolveSquare (double a, double b, double c, double* x1, double* x2) {
    double D = Diskr(a, b, c);
    assert (x1 != x2);
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1 != NULL);
    assert (x2 != NULL);

    if (cmp(D, 0)) {
        *x1 = (-b / (2 * a));
            return 1;
    }
    else if (D > 0) {
        *x1 = (-b + sqrt(D)) / (2 * a);
        *x2 = (-b - sqrt(D)) / (2 * a);
        return 2;
    }
    else if (D < 0) {
        return 0;
    }
    return 2;
}
//----------------------------------------------------------------------------------------------------
//! Solves both liner and quadratic equations
//
// @param [in]  a   a-coefficient
// @param [in]  b   b-coefficient
// @param [in]  c   c-coefficient
// @param [out] x1  Pointer to the 1st root
// @param [out] x2  Pointer to the 2nd root
//
// @return Number of roots
// @brief beses on two results from
//----------------------------------------------------------------------------------------------------
int Quadro (double a, double b, double c, double* x1, double* x2) {
    assert (x1 != x2);
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (&x1 != NULL);
    assert (&x2 != NULL);
    if (!cmp(a, 0))
        return SolveSquare(a, b, c, x1, x2);
    else {
        return SolveLiner (b, c, x1);

    }
}
int New_Test_anti_copypaste (int nTest, double a, double b, double c, int nRootsref, double x1ref, double x2ref) {
    double x1 = NAN, x2 = NAN;
    int nRoots = Quadro (a, b, c, &x1, &x2);
    if ((nRoots != nRootsref) || (!cmp(x1, x1ref)) || (!cmp(x2, x2ref))) {
            printf ("Test %d failed\nThe result is x1=%g and x2=%g, nRoots=%d\nBut it should've been: x1=%f, x2=%f and nRoots=%d\n", nTest, x1, x2, nRoots, x1ref, x2ref, nRootsref);
            return 0;
    }
    else
        printf ("Test %d success\n", nTest);
    return 1;
 }
void Test_Runner(){      //a  b  c  nR  x1  x2
  double M[test_num][6] = {{1, 1, 1, 0, NAN, NAN},
                          {1, 3, 2, 2, -1, -2},
                          {0, 3, 2, 1, -0.666667, NAN},
                          {3, 2, -6, 2, 1.11963, -1.7863},
                          {0, 0, 4, 0, NAN, NAN},
                          {0, 0, 0, inf_roots, NAN, NAN}};
    int nTest;
    for ( nTest = 0; nTest < test_num; nTest++) {

    	New_Test_anti_copypaste(nTest, M[nTest][0], M[nTest][1], M[nTest][2], M[nTest][3], M[nTest][4], M[nTest][5]);
	}
}
void Output_Function (int* nRoots,double* x1, double* x2){
     switch (*nRoots)
     {
        case 0: printf ("Unfortunatly:\nNo roots\n");
                break;

        case 1: printf ("Your solution is:\nx = %g\n", *x1);
                break;

        case 2: printf ("Your solutions are:\nx1 = %f x2 = %g\n", *x1, *x2);
                break;

        case inf_roots: printf("You've got too much:\ninfinity many roots\n");
                break;

        default: printf ("main(): ERROR: nRoots = %d\n", *nRoots);

    }
}
int main() {
    Test_Runner();

    printf ("This program solves quadratic equations like ax^2+bx+c\nPlease print your coefficients separated by a space:\n");

    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;

	Input_Function(&a, &b, &c);


	int nRoots = Quadro (a, b, c, &x1, &x2);

    Output_Function(&nRoots, &x1, &x2);

    return 0;
}
