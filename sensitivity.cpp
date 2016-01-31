//
// Created by AnuarYesid on 29.01.2016.
//

#include "sensitivity.h"
void sensitivity (int n, double *c, int k, double **A, double *b) {

    double* solution = lpsolve(n,c,k,A,b);
    double* lowerbounds = new double[n];
    double* upperbounds = new double[n];

    for (int i = 0; i < n; ++i) {
        lowerbounds[i] = findBound(solution, i, -0.1, n, c, k, A, b);
        upperbounds[i] = findBound(solution, i, 0.1, n, c, k, A, b);
    }


    double* shadowArray = lpshadow(n,c,k,A,b);


    cout << endl << "Sensitivitaetsanalyse Schattenpreise:" << endl;

    for (int i = 0; i < k; ++i)
        cout << "x" << i+n+1 << ": " << shadowArray[i] << endl;

    cout << endl << "Sensitivitaetsanalyse c-Vektor:" << endl;
    for (int i = 0; i < n; ++i)
        cout << "Intervall fuer c" << i << ": [ " << lowerbounds[i] << "; " << upperbounds[i] << " ]" << endl;

    delete solution;
}

double findBound (double* solution, int cposition, double factor, int n, double *c, int k, double **A, double *b) {
    bool samecorner = true;
    int counter = 0;
    double* tempC = new double(n);
    double bound = 0;

    for (int j = 0; j < n; ++j)
        tempC[j] = c[j];

    while (samecorner) {
        tempC[cposition] += (counter++ * factor);

        if (tempC[cposition] > 0) {
            double* tempSolution = lpsolve(n,tempC,k,A,b);

            for (int i = 0; i < n; ++i)
                if (solution[i] != tempSolution[i]) {
                    samecorner = false;
                    bound = tempC[cposition];
                    break;
                }

            //delete tempSolution;
        }
        else {
            samecorner = false;
        }


    }

    //delete tempC;

    return bound;
}