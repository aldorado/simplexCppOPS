//
// Created by AnuarYesid on 18.11.2015.
//

#include "simplex.h"
double* lpsolve(int n, double* c, int k, double** A, double* b) {
    Tableau t = Tableau(n, c, k, A, b); // instantiation of our Tableau class, which saves the given parameters and constraints from the file, and transforms them into a simplex tableau
    int counter = 1; // counter for the number of simplex steps

    cout << "Ausgangstableau" << endl;
    t.printTableau();

    while (!t.checkOptimum()) { //in this loop, we calculate the simplex algorithm. At first we check if the oprimum for the tableau has been already found, if not the loop continues
        t.findPivot();      // 1. find a pivot for the simplex algorithm
        t.simplexStep();    // 2. execute the simplex step
        cout << "Tableau nach Simplexschritt " << counter++ << endl;
        t.printTableau(); // after each simplex step, the tableau is printed to visualize the process
    } // at this point we return to the while loop condition and check again for the optimum

    return t.solution(); // if the return of the final solution
}