#include "utilities.h"
#include "simplex.h"

using namespace std;

int main() {
    Tableau t = filereader("F:\\simplextest");

    double* solution = lpsolve(t);
    cout << endl << "LOESUNGSWERT:" << endl;

    for(int i = 0; i < 2; ++i)
        cout << "x" << i+1 << "=" << solution[i] << endl;

    return 0;
}