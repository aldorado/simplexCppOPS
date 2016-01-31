//
// Created by AnuarYesid on 02.01.2016.
//
#include <iostream>
#include <iomanip>
#ifndef SIMPLEX_TABLEAU_H
#define SIMPLEX_TABLEAU_H

using namespace std;

/*
 *@class Tableau represents a custom class for the Simplex tableau used in our inplementation
 *
 * Detailed description:
 *      @double** tableauArray - pointer for the 2D array in which we save the tableau variables
 *      @int tableColumns - number of columns in our array
 *      @int tableRows - number of rows in our array
 *      @bool optimum - set to false by default, and is set to true if the optimum has been found
 *      @int pivotColumn - holder for the vertical index od the pivot
 *      @int pivotRow - holder for the horizontal index of the pivot
 *      @double pivotElement - the value of the pivot element itself
 *
 * The functions are described in the .cpp file
 */

class Tableau {
private:
    double** tableauArray;
    int tableauColumns;
    int tableauRows;
    bool optimum = false;

    int pivotColumn;
    int pivotRow;
    double pivotElement;

    Tableau() {}

public:
    Tableau(int n, double* c, int k, double** A, double* b);
    ~Tableau();
    double* solutionArray;
    double* shadowArray;

    void findPivot();
    void simplexStep();
    bool checkOptimum();

    double* solution();
    double* shadowPrices();
    void printTableau();
};


#endif //SIMPLEX_TABLEAU_H