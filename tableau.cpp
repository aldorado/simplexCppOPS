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
 * Pivotreihe suchen und damit das Pivotelement bestimmen
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
 * Hier wird ein Simplex Schritt ausgefuehrt, d.h. alle Elemente im Simplextableau werden neu berechnet
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
 * Gibt ein Array mit den Lösungswerten der Basisvariablen und dem optimalen Wert der Zielfunktion aus.
 */
double* Tableau::solution() {
    int n = tableauColumns - tableauRows;
    double* solution = new double(n+1);
    bool valid_solution = false;

    for(int i = 0; i < n+1; ++i)
        solution[i] = 0;

    solution[n] = tableauArray[0][tableauColumns-1];


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
            solution[i] = tableauArray[row][tableauColumns-1];
    }


    return solution;
}
/*
 * Gibt das Tableau aus
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