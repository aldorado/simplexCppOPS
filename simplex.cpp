//
// Created by AnuarYesid on 18.11.2015.
//

#include "simplex.h"
double* lpsolve(int n, double* c, int k, double** A, double* b) {
    Tableau t = Tableau(n, c, k, A, b);
    int counter = 1;

    cout << "Ausgangstableau" << endl;
    t.printTableau();

    while (!t.checkOptimum()) {
        t.findPivot();
        t.simplexStep();
        cout << "Tableau nach Simpexschritt " << counter++ << endl;
        t.printTableau();
    }

    return t.solution();
}