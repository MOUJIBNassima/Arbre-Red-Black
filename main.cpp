#include <iostream>
#include <vector>
#include <random>

#include "Benchmark.h"

using namespace std;

int main() {

    // Les differentes tailles de test
    vector<int> tailles = {
        1000,
        10000,
        100000,
        1000000
    };

    // Generateur aleatoire
    mt19937 generateur(42);

    cout << "============================================\n";
    cout << "       PROJET ARBRE RED-BLACK EN C++\n";
    cout << "============================================\n";

    // Executer les tests pour chaque taille
    for (int N : tailles) {

        executerTests(N, generateur);
    }

    cout << "\nTous les tests sont termines !\n";

    return 0;
}
