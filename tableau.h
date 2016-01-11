//
// Created by AnuarYesid on 02.01.2016.
//
#include <iostream>
#include <iomanip>
#ifndef SIMPLEX_TABLEAU_H
#define SIMPLEX_TABLEAU_H

using namespace std;

class Tableau {
private:
    double** tableauArray;
    int tableauColumns;
    int tableauRows;
    bool optimum = false;

    int pivotColumn;
    int pivotRow;
    double pivotElement;

    int* x;

    Tableau() {}

public:
    Tableau(int n, double* c, int k, double** A, double* b);
    ~Tableau();
    int getN() { return tableauColumns - tableauRows; }
    int getK() { return tableauRows - 1; }

    void findPivot();
    void simplexStep();
    bool checkOptimum();

    double* solution();
    void printTableau();
};


#endif //SIMPLEX_TABLEAU_H