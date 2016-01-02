//
// Created by AnuarYesid on 02.01.2016.
//

#ifndef SIMPLEX_TABLEAU_H
#define SIMPLEX_TABLEAU_H


class Tableau {
private:
    double **tableauArray;
    int tableauColumns;
    int tableauRows;
    bool optimum = false;

    int pivotColumn;
    int pivotRow;

    bool checkOptimum();
    Tableau() {}

public:
    Tableau(int n, int k, double *b, double *c, double **A);

    void findPivot();
    bool getOptimum();
    void simplexStep();
};


#endif //SIMPLEX_TABLEAU_H
