//
// Created by AnuarYesid on 02.01.2016.
//

#include "tableau.h"

Tableau::Tableau(int n, double *c, int k, double **A, double *b) {

    tableauColumns = n+k+1;
    tableauRows = k+1;
    solutionArray = new double[n+1];
    shadowArray = new double[k];

    //Erstellen des Tableaus
    tableauArray = new double*[tableauRows];
    for (int i = 0; i < tableauRows; ++i)
        tableauArray[i] = new double[tableauColumns];
    //Initialisierung des Tableaus mit Nullen
    for (int i = 0; i < tableauRows; ++i)
        for (int j = 0; j < tableauColumns; ++j)
            tableauArray[i][j] = 0;
    //Einfuegen der Schlupfvariablen ins Tableau
    for (int i = 1; i < tableauRows; ++i)
        tableauArray[i][i+n-1] = 1;
    //Einfuegen der Werte des c-Vektors
    for (int i = 0; i < n; ++i)
        tableauArray[0][i] -= c[i];
    //Einfuegen der Werte des b-Vektors
    for (int i = 1; i < tableauRows; i++)
        tableauArray[i][n+k] = b[i-1];
    //Einfuegen der Werte des Arrays A
    for (int i = 1; i < tableauRows; ++i)
        for (int j = 0; j < n; ++j)
            tableauArray[i][j] = A[i-1][j];
}
/*
 * @~Tableau() deletes the allocated two dimensional array in our class
 */

Tableau::~Tableau() {
   for (int i = 0; i < tableauRows; ++i)
        delete tableauArray[i];

    delete tableauArray;
}

/*
 * @checkOptimum() checks the tableau for the optimal state and returns
 * a boolean (@optimum) value.
 * @min - variable used for comparison of elements in the last row (first row in our code)
 *
 * Detailed description:
 *      We iterate trough the elements and if we find a value that's lower than 0 and
 *      save it into our min variable. We continue on comparing until we find the most negative one
 *      and change the optimum value to false since the optimal state was not found.
 *      The most negative value defines the pivotColumn, therefore we assign in to our pivotColumn variable
 */
bool Tableau::checkOptimum() {

    double min = 0;
    optimum = true;

    for (int j = 0; j < tableauRows-1; ++j)
        if(tableauArray[0][j] < min) {
            min = tableauArray[0][j];
            pivotColumn = j;
            optimum = false;
        }

    return optimum;
}

/*
 * @findPivot() searches for the pivotRow and pivotElement
 *
 * Detailed description:
 *      Since the pivot column is already known to us from the previous function, we need
 *      to find the pivot row. From the moment we know which row is the pivot row
 *      and which column is the pivot column, we can identify the pivot element
 *      and assign it into the pivotElement variable.
 */
void Tableau::findPivot() {
    double min = -1;

    for (int i = 1; i < tableauRows; ++i)
        if (tableauArray[i][pivotColumn] > 0 && min == -1) {
            min = tableauArray[i][tableauColumns-1] / tableauArray[i][pivotColumn];
            pivotRow = i;
        }
        else if (tableauArray[i][pivotColumn] > 0 && tableauArray[i][tableauColumns-1] / tableauArray[i][pivotColumn] < min) {
            min = tableauArray[i][tableauColumns-1] / tableauArray[i][pivotColumn];
            pivotRow = i;
        }

    pivotElement = tableauArray[pivotRow][pivotColumn];
}
/*
 * @simplexStep() executes one step of the simplex algorithm and recalculates all elements in the tableau
 *
 * Detailed description:
 *      The first nested loop computes all table elements, excluding the pivot row and pivot column elements.
 *      We used a formula from the lecture documents for this recalculation. In the following loops we, calculate
 *      the pivot row elements and set the pivot column elements to 0 excluding the pivot element itself.
 */
void Tableau::simplexStep() {
    for (int i = 0; i < tableauRows; ++i)
        for (int j = 0; j < tableauColumns; ++j)
            if ( i != pivotRow && j != pivotColumn)
                tableauArray[i][j] = tableauArray[i][j] - ((tableauArray[i][pivotColumn]*tableauArray[pivotRow][j])/pivotElement);
    for (int i = 0; i < tableauColumns; ++i)
        tableauArray[pivotRow][i] = tableauArray[pivotRow][i] / pivotElement;
    for (int i = 0; i < tableauRows; ++i)
        if (i != pivotRow)
            tableauArray[i][pivotColumn] = 0;
}
/*
 * @solution() returns an array with the solution to the basic
 * variables and the optimal value to the objective function.
 *
 * Detailed description:
 *      To create the solution array, we take the number of columns and subtract the number
 *      of rows in the tableau to calculate its size. This works since the initial array is
 *      enlarged by the addition of slack variables.
 *      The feasibility of the results is checked as well and returned afterwards
 */
double* Tableau::solution() {
    int n = tableauColumns - tableauRows;
    bool valid_solution = false;

    for(int i = 0; i < n+1; ++i)
        solutionArray[i] = 0;

    solutionArray[n] = tableauArray[0][tableauColumns-1];

    for (int i = 0; i < n; ++i) {
        int row = -1;
        for (int j = 1; j < tableauRows; ++j)
            if (tableauArray[j][i] == 1 && row == -1) {
                row = j;
                valid_solution = true;
            }
            else if (row > -1 && tableauArray[j][i] != 0) {
                valid_solution = false;
                break;
            }

        cout << "" << endl;
        if(valid_solution)
            solutionArray[i] = tableauArray[row][tableauColumns-1];
    }

    return solutionArray;
}

double* Tableau::shadowPrices() {
    for(int i = 0; i < tableauRows - 1; ++i)
        shadowArray[i] = tableauArray[0][i+tableauColumns-tableauRows];

    return shadowArray;
}
/*
 * @printTableau() prints the values of the tableau Array into the console
 *
 * Detailed description:
 *      A simple nested loop is used to iterate trough each index field of the array,
 *      and each value is printed out in the console.
 */
void Tableau::printTableau() {
    for (int i = 0; i < tableauRows; ++i) {
        for (int j = 0; j < tableauColumns; ++j) {
            cout << right << setw(6) << setfill(' ') << tableauArray[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}