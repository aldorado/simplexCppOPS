#include "utilities.h"
#include "simplex.h"

using namespace std;

int main() {
    string pathtosimplex;
    cout << "Geben Sie den Pfad zum Simplex-File an:" << endl;
    cin >> pathtosimplex;

    Tableau t = filereader(pathtosimplex);
    //Tableau t = filereader("F:\\simplextest");

    double* solution = lpsolve(t);
    cout << endl << "LOESUNGSWERTE:" << endl;

    for(int i = 0; i < t.getN(); ++i)
        cout << "x" << i+1 << " = " << solution[i] << endl;

    cout << "Optimaler ZF-Wert = " << solution[t.getN()] << endl;

    return 0;
}