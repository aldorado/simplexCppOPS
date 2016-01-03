//
// Created by AnuarYesid on 18.11.2015.
//

#include "simplex.h"
double* lpsolve(int n, double* c, int k, double** A, double* b) {
    Tableau t = Tableau(n, c, k, A, b);

    t.printTableau();

    while (!t.checkOptimum()) {
        t.findPivot();
        t.simplexStep();
        t.printTableau();
    }

    return t.solution();
}

double* lpsolve(Tableau t) {
    t.printTableau();

    while (!t.checkOptimum()) {
        t.findPivot();
        t.simplexStep();
        t.printTableau();
    }

    return t.solution();
}