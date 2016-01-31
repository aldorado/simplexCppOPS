//
// Created by AnuarYesid on 18.11.2015.
//

#include "simplex.h"
/*
 *@lpsolve(int n, double* c, int k, double** A, double* b) us responsible for the solution
 * of the linear problem using functions out of our Tableau class.
 *
 * Detailed description:
 *      @int n - number of variables (columns)
 *      @double* c - pointer to an array
 *      @int k - number of constraints (rows)
 *      @double** A - pointer to an a 2dimensional array
 *      @double* b - pointer to an array
 *      @int counter - counter for the number of steps necessary to finish the algorithm
 *
 *      The function uses a while loop, where the condition is the existance of an
 *      optimum in the table. If the optimum doesnt exist, the loop continues and uses
 *      functions implemented in the Tableau class to calculate the optimum.
 *      The table is printed before the first step and after each step to visualize
 *      the progress of the algorithm. The function returns a double array with the solution
 */

double* lpsolve(int n, double* c, int k, double** A, double* b) {
    Tableau t = Tableau(n, c, k, A, b);
    int counter = 1;

    cout << "Ausgangstableau" << endl;
    t.printTableau();

    while (!t.checkOptimum()) {
        t.findPivot();
        t.simplexStep();
        cout << "Tableau nach Simplexschritt " << counter++ << endl;
        t.printTableau();
    }

    return t.solution();
}