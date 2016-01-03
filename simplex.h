//
// Created by AnuarYesid on 18.11.2015.
//
#include "tableau.h"
#ifndef SIMPLEX_SIMPLEX_H
#define SIMPLEX_SIMPLEX_H

double* lpsolve(int n, double *c, int k, double **A, double *b);
double* lpsolve(Tableau t);

#endif //SIMPLEX_SIMPLEX_H
