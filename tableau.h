//
// Created by AnuarYesid on 02.01.2016.
//

#ifndef SIMPLEX_TABLEAU_H
#define SIMPLEX_TABLEAU_H


class Tableau {
private:
    int n;
    int k;
    double *b;
    double *c;
    double **A;
    bool optimum = false;

    double& findPivot();
    bool checkOptimum();
    
    Tableau() {}
public:
    Tableau(int n, int k, double *b, double *c, double **A);

    bool getOptimum();
    void simplexStep();
};


#endif //SIMPLEX_TABLEAU_H
