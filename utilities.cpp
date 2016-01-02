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
        double* variables = new double[n];

        for (int i = 0; i < n; ++i) {
            file >> variables[i];
        }

        //Array zum Speichern der Matrix, n+1 da wir eine zusaetzliche Spalte haben
        double** matrice = new double*[k];
        for (int i = 0; i < k; ++i) {
            matrice[i] = new double[n+1];
            for (int j = 0; j < n+1; ++j) {
                file >> matrice[i][j];
            }
        }

        cout << n << " " << k << endl;
        for (int l = 0; l < n; ++l) {
            cout << " " << variables[l];
        }

        for (int i = 0; i < k; ++i) {
            cout << endl;
            for (int j = 0; j < n+1; ++j) {
                cout << " " << matrice[i][j];
            }
        }

    } catch (...) {
        cout << "Filereader Exception";
    }
}