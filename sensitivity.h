//
// Created by AnuarYesid on 29.01.2016.
//
#include <iostream>
#include "simplex.h"
#ifndef SIMPLEX_SENSITIVITY_H
#define SIMPLEX_SENSITIVITY_H

void sensitivity(int n, double *c, int k, double **A, double *b);
double findBound (double* solution, int cposition, double factor,int n, double *c, int k, double **A, double *b);

#endif //SIMPLEX_SENSITIVITY_H