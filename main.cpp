#include "utilities.h"
#include "simplex.h"

using namespace std;

int main() {

    string pathtosimplex;
    char eingabe = '#';
    bool beenden = false;

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
                Tableau t = filereader(pathtosimplex);
                double* solution = lpsolve(t);
                cout << endl << "LOESUNGSWERTE:" << endl;
                for(int i = 0; i < t.getN(); ++i)
                    cout << "x" << i+1 << " = " << solution[i] << endl;
                cout << "Optimaler ZF-Wert = " << solution[t.getN()] << endl;
            }
                break;
            case 'x':
                beenden = true;
                break;
            default:
                break;
        }

    }

    return 0;
}