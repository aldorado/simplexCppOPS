#include "utilities.h"
#include "simplex.h"

using namespace std;

int main() {

    string pathtosimplex;
    char eingabe = '#';
    bool beenden = false;

    cout << endl
         << "+----------------------------+" << endl;
    cout << "|Willkommen bei SimplexCppOPS|" << endl;
    cout << "+----------------------------+" << endl;

    while(!beenden) {

        cout << endl << "1) Simplexfile angeben" << endl;
        cout << "2) --------------------" << endl;
        cout << "x) Programm Beenden" << endl;
        cout << "Eingabe: ";

        cin >> eingabe;

        cout << endl;

        switch (eingabe) {
            case '1':
            {
                cout << "Geben Sie den Pfad zum Simplex-File an:" << endl;
                cin >> pathtosimplex;

                ifstream file(pathtosimplex);
                // n - Variablen (Spalten) , k - Nebenbedingungen (Reihen)
                if(file) {
                    int n,k;
                    file >> n >> k;

                    // Array zum Speichern der Variablen
                    double* c = new double[n];

                    for (int i = 0; i < n; ++i)
                        file >> c[i];


                    //Array zum Speichern der Matrix, n+1 da wir eine zusaetzliche Spalte haben
                    double* b = new double[k];
                    double** matrice = new double*[k];
                    for (int i = 0; i < k; ++i) {
                        matrice[i] = new double[n];

                        for (int j = 0; j < n; ++j)
                            file >> matrice[i][j];

                        file >> b[i];
                    }

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

                    double* solution = lpsolve( n, c, k, matrice, b);
/*
                    cout << endl << "LOESUNGSWERTE:" << endl;
                    for(int i = 0; i < n; ++i)
                        cout << "x" << i+1 << " = " << solution[i] << endl;
                    cout << "Optimaler ZF-Wert = " << solution[n] << endl;
*/
                }
                else {
                    cout << "Filereader Exception: Datei gibt es nicht!" << endl;
                }
            }
                break;
            case 'x':
                cout << endl << "SimplexCppOPS wird beendet!";
                beenden = true;
                break;
            default:
                break;
        }

    }

    return 0;
}