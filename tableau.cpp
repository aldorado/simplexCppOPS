//
// Created by AnuarYesid on 02.01.2016.
//

#include "tableau.h"

Tableau::Tableau(int n, int k, double *b, double *c, double **A) {

    tableauColumns = n+k+1;
    tableauRows = k+1;

    //Erstellen des Tableaus
    tableauArray = new double*[k+1];
    for(int i = 0; i < tableauRows; ++i)
        tableauArray[i] = new double[tableauColumns];
    //Initialisierung des Tableaus
    for(int i = 0; i < tableauRows; ++i)
        for(int j = 0; j < tableauColumns; ++j)
            tableauArray[i][j] = 0;
    //Einfuegen der Werte des c-Vektors
    for(int i = 0; i < n; ++i)
        tableauArray[k][i] = c[i];
    //Einfuegen der Werte des b-Vektors
    for(int i = 0; i < k; i++)
        tableauArray[i][n+k] = b[i];
    //Einfuegen der Werte des Arrays A
    for(int i = 0; i < k; ++i)
        for(int j = 0; j < n; ++j)
            tableauArray[i][j] = A[i][j];
}