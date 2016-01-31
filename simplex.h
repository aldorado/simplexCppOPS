//
// Created by AnuarYesid on 18.11.2015.
//
#include "tableau.h"
#ifndef SIMPLEX_SIMPLEX_H
#define SIMPLEX_SIMPLEX_H

using namespace std;
/*
 * LPSOLVE wie in der Angabe lpsolve(int n, double *c, int k, double **A, double *b)
 * lpsolve(Tableau t) hinzugefuegt, da der filereader eine Objekt der Klasse Tableau mit den selben Variablen erstellt.
 * */

double* lpsolve(int n, double *c, int k, double **A, double *b);
double* lpshadow(int n, double* c, int k, double** A, double* b);
#endif //SIMPLEX_SIMPLEX_H
