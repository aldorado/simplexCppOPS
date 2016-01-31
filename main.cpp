#include "utilities.h"
#include "simplex.h"
#include "sensitivity.h"

using namespace std;

int main() {


    string pathtosimplex;
    // variable responsible for the input instructions for the program
    char eingabe = '#';
    // variable responsible for the duration of the program execution
    bool beenden = false;
    // variables for the specification of what type of optimization problem we want to calculate
    bool minimum = false;
    bool sensitivity = false;
    // pointer to the solution array in which the feasible solution is saved
    double* solution;

    cout << endl
         << "+----------------------------+" << endl;
    cout << "|Willkommen bei SimplexCppOPS|" << endl;
    cout << "+----------------------------+" << endl;

    while(!beenden) {
        // simple instructions for the program control
        cout << endl << "1) Simplexfile angeben" << endl;
        cout << "2) --------------------" << endl;
        cout << "x) Programm Beenden" << endl;
        cout << "Eingabe: ";

        cin >> eingabe;

        cout << endl;

        // different part of the code is executed according to the input variable
        switch (eingabe) {
            case '1':
            {
                cout << "Geben Sie den Pfad zum Simplex-File an:" << endl;
                cin >> pathtosimplex; //file path input

                cout << "Handelt es sich um ein Minimumproblem? (j/n)" << endl;
                cin >> eingabe;

                if(eingabe == 'j')
                    minimum = true;
                // loading of the text file from the path given by the user
                ifstream file(pathtosimplex);
                // n - Variablen (Spalten) , k - Nebenbedingungen (Reihen)
                if(file) {
                    int n,k;
                    file >> n >> k;

                    // Array zum Speichern der Variablen
                    double* c = new double[n];


                    for (int i = 0; i < n; ++i)
                        file >> c[i];
                    /* Minimum durch z -> min <=> -z -> max
                    if (minimum)
                        for (int i = 0; i < n; ++i)
                            c[i] *= -1;
                    */

                    //Array zum Speichern der Matrix, n+1 da wir eine zusaetzliche Spalte haben
                    double* b = new double[k];
                    double** matrice = new double*[k];
                    for (int i = 0; i < k; ++i) {
                        matrice[i] = new double[n];

                        for (int j = 0; j < n; ++j)
                            file >> matrice[i][j];

                        file >> b[i];
                    }

                    /*
                     * Ausgabe der Eingabe

                    cout << n << " " << k << endl;

                    for (int i = 0; i < k; ++i) {
                        for (int j = 0; j < n; ++j) {
                            cout << " " << matrice[i][j];
                        }
                        cout << " <= " << b[i];
                        cout << endl;
                    }

                    for (int l = 0; l < n; ++l)
                        cout << " " << c[l];

                    cout << endl << endl;

                    */

                    /* Minimum durch angabe eines primalen Problems der form */
                    if (minimum) {
                        double** tempMatrice = new double*[n];
                        double** oldMatrice = matrice;
                        // naturally we need to transpose the old matrix first
                        for (int i = 0; i < n; ++i) {
                            tempMatrice[i] = new double[k];
                            for(int j = 0; j < k; ++j)
                                tempMatrice[i][j] = oldMatrice[j][i];
                        }
                        matrice = tempMatrice;

                        for (int i = 0; i < k; ++i)
                            delete oldMatrice[i];

                        delete oldMatrice;

                        int temp = n;
                        n = k;
                        k = temp;

                        solution = lpsolve( n, b, k, matrice, c);
                        minimum = false;
                    }
                    else
                        // call of the function that solves the optimization problem
                        solution = lpsolve( n, c, k, matrice, b);

                    /// after the execution of lpsolve, the results are printed out into the console
                    cout << endl << "LOESUNGSWERTE:" << endl;
                    for(int i = 0; i < n; ++i)
                        cout << "x" << i+1 << " = " << solution[i] << endl;
                    cout << "Optimaler ZF-Wert = " << solution[n] << endl;

                    cout << "Sensitivitaetsanalyse? (j/n)" << endl;
                    eingabe = '#';
                    cin >> eingabe;

                    if (eingabe == 'j' && !minimum)
                        sensitivity(n,c,k,matrice,b);

                    delete c;
                    delete b;
                    for (int i = 0; i < k; ++i)
                        delete matrice[i];
                    delete matrice;
                }
                else {
                    // "if exception" - file path check
                    cout << "Filereader Exception: Datei gibt es nicht!" << endl;
                }
            }
                break;
            case 'x':
                cout << endl << "SimplexCppOPS wird beendet!" << endl << endl; // end of the program
                beenden = true;
                break;
            default:
                break;
        }

    }

    return 0;
}