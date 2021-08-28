#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#define INF_ROOTS -1
#define PRESISION 0.001
#define test_num 6

/// TODO:
/// - struct
/// - fix naming
/// - initialize all variables

// isfinite()
//----------------------------------------------------------------------------------------------------
//! Checks if the number is NAN
//!
//! @param [in]  a   a-number
//!
//! @return 1 if true, 0 if false
//----------------------------------------------------------------------------------------------------

int Is_NAN (double a);

//----------------------------------------------------------------------------------------------------
//! Read your numbers from keyboard
//!
//! @param [out]  a   a-coefficient
//! @param [out]  b   b-coefficient
//! @param [out]  c   c-coefficient
//!
//----------------------------------------------------------------------------------------------------

void Input_Function (double* a, double* b, double* c);

//----------------------------------------------------------------------------------------------------
//! Counts a diskreminant
//!
//! @param [in]  a   a-coefficient
//! @param [in]  b   b-coefficient
//! @param [in]  c   c-coefficient
//! @param [out] x1  Pointer to the 1st root
//
//! @return diskreminant value
//----------------------------------------------------------------------------------------------------

double Diskr (double a, double b, double c);

//----------------------------------------------------------------------------------------------------
//! Checks if two numbers are equal
//!
//! @param [in]  val1  val1-firs number
//! @param [in]  val2  val2-csecond number
//!
//! @return 1 if true, 0 if false
//----------------------------------------------------------------------------------------------------

int CMP (double val1, double val2);

//----------------------------------------------------------------------------------------------------
//! Solves a liner equation  bx +c = 0
//!
//! @param [in]  b   b-coefficient
//! @param [in]  c   c-coefficient
//! @param [out] x1  Pointer to the 1st root
//!
//! @return Number of roots
//----------------------------------------------------------------------------------------------------
 
int SolveLiner (double b, double c, double* x1);

//----------------------------------------------------------------------------------------------------
//! Solves a square equation axˆ2 + bx +c = 0
//!
//! @param [in]  a   a-coefficient
//! @param [in]  b   b-coefficient
//! @param [in]  c   c-coefficient
//! @param [out] x1  Pointer to the 1st root
//! @param [out] x2  Pointer to the 2nd root
//!
//! @return Number of roots
//! @brief only in case when a != 0
//----------------------------------------------------------------------------------------------------

int SolveSquare (double a, double b, double c, double* x1, double* x2);

//----------------------------------------------------------------------------------------------------
//! Solves both liner and quadratic equations
//!
//! @param [in]  a   a-coefficient
//! @param [in]  b   b-coefficient
//! @param [in]  c   c-coefficient
//! @param [out] x1  Pointer to the 1st root
//! @param [out] x2  Pointer to the 2nd root
//!
//! @return Number of roots
//! @brief Main function which elobarates two above
//----------------------------------------------------------------------------------------------------

int Quadro (double a, double b, double c, double* x1, double* x2);

//----------------------------------------------------------------------------------------------------
//! Compares programm results with true values
//!
//! @param [in] nTest nTest-number of the test
//! @param [in]  a   a-coefficient
//! @param [in]  b   b-coefficient
//! @param [in]  c   c-coefficient
//! @param [in] x1ref  expected value for x1
//! @param [in] x2ref  expected value for x2
//! @param [in] nRootsref expected number of roots
//!
//! @return 0 or 1 wheather the test was failed or not
//----------------------------------------------------------------------------------------------------

int New_Test_anti_copypaste (int nTest, double a, double b, double c, int nRootsref, double x1ref, double x2ref);

//----------------------------------------------------------------------------------------------------
//! Starts the test
//!
//! @brief calls the function New_Test_anti_copypaste
//----------------------------------------------------------------------------------------------------

void Test_Runner ();

//----------------------------------------------------------------------------------------------------
//! print the results
//!
//! @param [in] x1  Pointer to the 1st root
//! @param [in] x2  Pointer to the 2nd root
//! @param [in] nRoots Pointer to the num of roots
//!
//----------------------------------------------------------------------------------------------------

void Output_Function (int* nRoots, double* x1, double* x2);

int main() {
    Test_Runner();

    printf ("This program solves quadratic equations like ax^2+bx+c\nPlease print your coefficients separated by a space:\n");

    double a = NAN;
    double b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;

	Input_Function(&a, &b, &c);


	int nRoots = Quadro (a, b, c, &x1, &x2);

    Output_Function(&nRoots, &x1, &x2);

    return 0;
}
//Определение функций:
int Is_NAN (double a) {
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

double Diskr (double a, double b, double c) {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    return b * b - 4 * a * c;
}

int CMP (double val1, double val2) {
    if ((!Is_NAN(val1)) && (!Is_NAN(val2))) {

        if (fabs(val1 - val2) < PRESISION) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else
        return 1;
}

int SolveLiner (double b, double c, double* x1) {
    assert(isfinite (b));
    assert(isfinite (c));
    assert (x1 != NULL);

    if ((CMP(b, 0)) && (CMP(c, 0))){
        return INF_ROOTS;
    }

    if (!CMP(b, 0)) {
        *x1 = (-c / b);
        return 1;
    }
    else
        return 0;
}

int SolveSquare (double a, double b, double c, double* x1, double* x2) {
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    double D = Diskr(a, b, c);
    double sqD = sqrt (D);
    if (CMP(D, 0)) {
        *x1 = (-b / (2 * a));
        return 1;
    }
    else if (D > 0) {
        *x1 = (-b + sqD) / (2 * a);
        *x2 = (-b - sqD) / (2 * a);
        return 2;
    }
    else if (D < 0) {
        return 0;
    }

    return 777;
}

int Quadro (double a, double b, double c, double* x1, double* x2) {
    assert (&x1 != NULL);
    assert (&x2 != NULL); 
    assert (x1 != x2);
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));

    if (!CMP(a, 0))
        return SolveSquare(a, b, c, x1, x2);
    else 
        return SolveLiner (b, c, x1);
}

int New_Test_anti_copypaste (int nTest, double a, double b, double c, int nRootsref, double x1ref, double x2ref) {
    double x1 = NAN, x2 = NAN;
    int nRoots = Quadro (a, b, c, &x1, &x2);
    
    if ((nRoots != nRootsref) || (!CMP(x1, x1ref)) || (!CMP(x2, x2ref))) {
            printf ("Test %d failed\nThe result is x1=%g and x2=%g, nRoots=%d\nBut it should've been: x1=%f, x2=%f and nRoots=%d\n", nTest, x1, x2, nRoots, x1ref, x2ref, nRootsref);
            return 0;
    }
    else
        printf ("Test %d success\n", nTest);
    return 1;
 }

 void Test_Runner () {      //a  b  c  nR        x1         x2
  double M[test_num][6] = {{1, 1, 1,  0,         NAN,       NAN},
                           {1, 3, 2,  2,         -1,        -2},
                           {0, 3, 2,  1,         -0.666667, NAN},
                           {3, 2, -6, 2,         1.11963,   -1.7863},
                           {0, 0, 4,  0,         NAN,       NAN},
                           {0, 0, 0,  INF_ROOTS, NAN,       NAN}};

    int nTest;

    for (nTest = 0; nTest < test_num; nTest++) {
    	New_Test_anti_copypaste(nTest, M[nTest][0], M[nTest][1], M[nTest][2], M[nTest][3], M[nTest][4], M[nTest][5]);
	}
}

void Output_Function (int* nRoots, double* x1, double* x2) {
     switch (*nRoots)
     {
        case 0: printf ("Unfortunatly:\nNo roots\n");
                break;

        case 1: printf ("Your solution is:\nx = %g\n", *x1);
                break;

        case 2: printf ("Your solutions are:\nx1 = %f x2 = %g\n", *x1, *x2);
                break;

        case INF_ROOTS: printf("You've got too much:\ninfinity many roots\n");
                break;

        default: printf ("main(): ERROR: nRoots = %d\n", *nRoots);

    }
}