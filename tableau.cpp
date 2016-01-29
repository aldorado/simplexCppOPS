//
// Created by AnuarYesid on 02.01.2016.
//

#include "tableau.h"

Tableau::Tableau(int n, double *c, int k, double **A, double *b) {

    tableauColumns = n+k+1;
    tableauRows = k+1;

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

Tableau::~Tableau() {
    for (int i = 0; i < tableauRows; ++i)
        delete tableauArray[i];

    delete tableauArray;
}
/*
 * Ueberprueft ob das Optimum schon erreicht wurde.
 * Falls das Optimum nicht erreicht wurde, wird die Pivotspalte festgelegt
 */
bool Tableau::checkOptimum() {

    double min = 0; // variable used for comparison of elements in the last row (first row in our code), to find the most negative value
    optimum = true; // the optimum stays true (optimal solution), unless we find a negative value

    for (int j = 0; j < tableauRows-1; ++j) //  we iterate trough the elements and if we find a value that's lower than 0,
        if(tableauArray[0][j] < min) {      //  we save it into our min variable and continue on comparing until we find the most negative one
            min = tableauArray[0][j];       //  and we change the optimum value to false since the optimal state was not found
            pivotColumn = j;                //  since the most negative value defines the pivotColumn, we assign in to our pivotColumn variable
            optimum = false;
        }

    return optimum;
}
/*
 * Pivotreihe suchen und damit das Pivotelement bestimmen
 */
void Tableau::findPivot() { // since the pivot column is already known to us from the previous function, we need
                            // to find the pivot row. From the moment we know which row is the pivot row
                            // and which column is the pivot column, we can identify the pivot element.
    double min = -1;

    for (int i = 1; i < tableauRows; ++i)
        if (tableauArray[i][pivotColumn] > 0 && min == -1) { // finding the first potential pivot row
            min = tableauArray[i][tableauColumns-1] / tableauArray[i][pivotColumn];
            pivotRow = i;
        }
        else if (tableauArray[i][pivotColumn] > 0 && tableauArray[i][tableauColumns-1] / tableauArray[i][pivotColumn] < min) {
            min = tableauArray[i][tableauColumns-1] / tableauArray[i][pivotColumn];
            pivotRow = i;
        }

    pivotElement = tableauArray[pivotRow][pivotColumn]; // assign step for the pivot element

}

/*
 * Hier wird ein Simplex Schritt ausgefuehrt, d.h. alle Elemente im Simplextableau werden neu berechnet
 */
void Tableau::simplexStep() {
    for (int i = 0; i < tableauRows; ++i)           // in these two nested for loops, we compute all table elements,
        for (int j = 0; j < tableauColumns; ++j)    // exluding the pivot row and column elements. We used a formula from the
            if ( i != pivotRow && j != pivotColumn) // lecture documents for this procedure.
                tableauArray[i][j] = tableauArray[i][j] - ((tableauArray[i][pivotColumn]*tableauArray[pivotRow][j])/pivotElement);
    for (int i = 0; i < tableauColumns; ++i)        // in this loop we calculate the pivot row elements
        tableauArray[pivotRow][i] = tableauArray[pivotRow][i] / pivotElement;
    for (int i = 0; i < tableauRows; ++i)           // and set the pivot column elements to 0 in this for loop
        if (i != pivotRow)
            tableauArray[i][pivotColumn] = 0;
}
/*
 * Gibt ein Array mit den Lösungswerten der Basisvariablen und dem optimalen Wert der Zielfunktion aus.
 */
double* Tableau::solution() {
    int n = tableauColumns - tableauRows;   // we can subtract the row count from the column count, since the column count is
    double* solution = new double(n+1);     // initially enlarged, because each constraint introduces a slack variable
    bool valid_solution = false;

    for(int i = 0; i < n+1; ++i)
        solution[i] = 0;

    solution[n] = tableauArray[0][tableauColumns-1];


    for (int i = 0; i < n; ++i) {                       // in thos for loop, we chceck on the feasibility
        int row = -1;                                   // of the computated result by our implementation
        for (int j = 1; j < tableauRows; ++j)           //  of the simplex algorithm
            if (tableauArray[j][i] == 1 && row == -1) {
                row = j;
                valid_solution = true;
            }
            else if (row > -1 && tableauArray[j][i] != 0) {
                valid_solution = false;
                break;
            }

        cout << "" << endl;

        if(valid_solution)  // if the solution is feasible, we assign it into the solution array on the index of the current loop step
            solution[i] = tableauArray[row][tableauColumns-1];
    }
    return solution;
}
/*
 * Gibt das Tableau aus
 */
void Tableau::printTableau() {  // in this function, we use a simple nested loop to print out the content of the table

    for (int i = 0; i < tableauRows; ++i) {
        for (int j = 0; j < tableauColumns; ++j) {
            cout << right << setw(6) << setfill(' ') << tableauArray[i][j];
        }
        cout << endl;
    }

    cout << endl << endl;

}