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
    double** tableauArray; // pointer for the 2D array in which we save the tableau
    int tableauColumns; // we save the number of columns and rows seperately for the future ease of use while executing the algorithm
    int tableauRows;
    bool optimum = false; // the optimum variable describes the state of the computation, if the optimum is found the variable is set to true

    int pivotColumn; // after we find the pivot using the findPivot() function, we save the pivot column and row
    int pivotRow;   //  into these variables.
    double pivotElement; // the pivot element is saved into this variable so we don't have to use the array index

    Tableau() {}

public:
    Tableau(int n, double* c, int k, double** A, double* b); // the custom constructor for our tableau class
    ~Tableau();
    int getN() { return tableauColumns - tableauRows; }
    int getK() { return tableauRows - 1; }

    void findPivot();       // <-
    void simplexStep();     // <-   a better description for these
    bool checkOptimum();    // <-   functions is found in the
                            //      cpp file, since these are only
    double* solution();     // <-   function declarations
    void printTableau();    // <
};


#endif //SIMPLEX_TABLEAU_H