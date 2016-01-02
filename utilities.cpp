//
// Created by Al Dorado on 15.11.15.
//
#include "utilities.h"

void filereader(string pathToFile) {

    try {

        ifstream file(pathToFile);
        // n - Variablen (Spalten) , k - Nebenbedingungen (Reihen)
        int n,k;
        file >> n >> k;

        // Array zum Speichern der Variablen
        double* c = new double[n];

        for (int i = 0; i < n; ++i)
            file >> c[i];


        //Array zum Speichern der Matrix, n+1 da wir eine zusaetzliche Spalte haben
        double* b = new double[k];
        double** matrice = new double*[k];
        for (int i = 0; i < k; ++i) {
            matrice[i] = new double[n];

            for (int j = 0; j < n; ++j)
                file >> matrice[i][j];

            file >> b[i];
        }

        cout << n << " " << k << endl;

        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << " " << matrice[i][j];
            }
            cout << " <= " << b[i];
            cout << endl;
        }

        for (int l = 0; l < n; ++l)
            cout << " " << c[l];

    } catch (...) {
        cout << "Filereader Exception";
    }
}