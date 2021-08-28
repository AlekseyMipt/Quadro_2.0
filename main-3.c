
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#define inf_roots -1
#define p 0.001

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
double Diskr (float a, float b, float c) {
    assert(isfinite (a));
    assert(isfinite (b));
    assert(isfinite (c));

    return b * b - 4 * a * c;
}
//----------------------------------------------------------------------------------------------------
//! Shows how close are two numbers to each other
//
// @param [in]  val1  val1-firs number
// @param [in]  val2  val2-csecond number
//
// @return
//----------------------------------------------------------------------------------------------------
int cmp (double val1, double val2) {
    assert(isfinite (val1));
    assert(isfinite (val2));
    if (fabs(val1 - val2) < p) {
        return 1;
    }
    else {
        return 0;
    }
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
 int SolveLiner (float b, float c, float* x1) {
    assert(isfinite (b));
    assert(isfinite (c));
    assert (&x1 != NULL);

    if ((cmp(b, 0)) && (cmp(c, 0))){
        return inf_roots;
    }
    if (!cmp(b, 0)) {
        *x1 = (-c / b);
        return 1;
    }
    else return 0;
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
// @brief only in case when a!=0
//----------------------------------------------------------------------------------------------------
int SolveSquare (float a, float b, float c, float* x1, float* x2) {
    assert (x1 != x2);
    assert(isfinite (a));
    assert(isfinite (b));
    assert(isfinite (c));
    assert (&x1 != NULL);
    assert (&x2 != NULL);

    if (cmp(Diskr(a, b, c), 0)) {
        *x1 = (-b / (2 * a));
            return 1;
    }
    else if (Diskr(a, b, c) > 0) {
        *x1 = (-b + sqrt(Diskr(a, b, c))) / (2 * a);
        *x2 = (-b - sqrt(Diskr(a, b, c))) / (2 * a);
        return 2;
    }
    else if (Diskr(a, b, c) < 0) {
        return 0;
    }

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
int Quadro (float a, float b, float c, float* x1, float* x2) {
    assert (x1 != x2);
    assert(isfinite (a));
    assert(isfinite (b));
    assert(isfinite (c));
    assert (&x1 != NULL);
    assert (&x2 != NULL);
    if (a!=0)
        return SolveSquare(a, b, c, x1, x2);
    else {
        return SolveLiner (b, c, x1);

    }
}
void Test () {
    float x1 = 0, x2 = 0;
    if (Quadro(1, 1, 1, &x1, &x2)!=0)
        printf ("a mistake is in the first test\n");
    if (Quadro(1, 3, 2, &x1, &x2)!=2 || cmp(x1, -1)==0 || cmp(x2, -2)==0)
        printf ("a mistake is in the second test\n");
    if (Quadro(0, 3, 2, &x1, &x2)!=1 || cmp(x1, -0.6666667)==0)
        printf ("a mistake is in the third test\n");
    if (Quadro(3, 2, -6, &x1, &x2)!=2 || (cmp(x1, 1.11963)==0) || cmp(x2, -1.7863)==0)
        printf ("a mistake is in the forth test");
    else
    printf ("success\n");
}

int main()
{
    printf ("tests results: ");
    Test();
    float a = NAN, b = NAN, c = NAN;
    scanf ("%f %f %f", &a, &b, &c);
    assert(isfinite (a));
    assert(isfinite (b));
    assert(isfinite (c));

    float x1 = 0, x2 = 0;

    int nRoots = Quadro (a, b, c, &x1, &x2); //возвращает кол во корней
     switch (nRoots)
     {
        case 0: printf ("No roots\n");
                break;
        case 1: printf ("x=%f\n", x1);
                break;
        case 2: printf ("x1=%f x2=%f\n", x1, x2);
                break;
        case inf_roots: printf("infinity many roots\n");
                break;
        default: printf ("main(): ERROR: nRoots=%d\n", nRoots);

    }
    return 0;
}


