#include "Benchmark.h"
#include "RedBlackTree.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// ================================================
// MESURE DU TEMPS D'EXECUTION
// ================================================

template <typename Function>
double mesurerTemps(Function operation) {

    auto debut = high_resolution_clock::now();

    operation();

    auto fin = high_resolution_clock::now();

    return duration<double, nano>(fin - debut).count();
}

// ================================================
// EXECUTION DES TESTS
// ================================================

void executerTests(int N, mt19937& generateur) {

    // Generer les valeurs
    vector<int> valeurs(N);

    for (int i = 0; i < N; i++)
        valeurs[i] = i + 1;

    // Melanger les valeurs
    shuffle(valeurs.begin(), valeurs.end(), generateur);

    // Valeurs utilisees pour les tests
    int valeurRecherchee = valeurs[N / 2];
    int valeurSupprimee = valeurs[N / 3];

    cout << "\n";
    cout << "============================================================\n";
    cout << "              COMPARAISON DES ARBRES RED-BLACK\n";
    cout << "============================================================\n";

    cout << "Nombre de valeurs N : " << N << "\n\n";

    cout << left
         << setw(20) << "Implementation"
         << setw(16) << "Operation"
         << setw(16) << "Valeur"
         << "Temps (ns)\n";

    cout << "------------------------------------------------------------\n";

    // ============================================
    // FROM SCRATCH
    // ============================================

    RedBlackTree arbre;

    double tempsInsertion = mesurerTemps([&]() {

        for (int v : valeurs)
            arbre.insertion(v);
    });

    bool trouve = false;

    double tempsRecherche = mesurerTemps([&]() {

        trouve = arbre.recherche(valeurRecherchee);
    });

    bool supprime = false;

    double tempsSuppression = mesurerTemps([&]() {

        supprime = arbre.suppression(valeurSupprimee);
    });

    cout << fixed << setprecision(2);

    cout << left
         << setw(20) << "From Scratch"
         << setw(16) << "Insertion"
         << setw(16) << N
         << tempsInsertion << "\n";

    cout << left
         << setw(20) << "From Scratch"
         << setw(16) << "Recherche"
         << setw(16) << valeurRecherchee
         << tempsRecherche << "\n";

    cout << left
         << setw(20) << "From Scratch"
         << setw(16) << "Suppression"
         << setw(16) << valeurSupprimee
         << tempsSuppression << "\n";

    cout << "------------------------------------------------------------\n";

    // ============================================
    // STD::MAP
    // ============================================

    map<int, int> arbreMap;

    double tempsInsertionMap = mesurerTemps([&]() {

        for (int v : valeurs)
            arbreMap.insert({v, v});
    });

    bool trouveMap = false;

    double tempsRechercheMap = mesurerTemps([&]() {

        trouveMap =
            (arbreMap.find(valeurRecherchee) != arbreMap.end());
    });

    bool supprimeMap = false;

    double tempsSuppressionMap = mesurerTemps([&]() {

        supprimeMap = (arbreMap.erase(valeurSupprimee) > 0);
    });

    cout << left
         << setw(20) << "std::map"
         << setw(16) << "Insertion"
         << setw(16) << N
         << tempsInsertionMap << "\n";

    cout << left
         << setw(20) << "std::map"
         << setw(16) << "Recherche"
         << setw(16) << valeurRecherchee
         << tempsRechercheMap << "\n";

    cout << left
         << setw(20) << "std::map"
         << setw(16) << "Suppression"
         << setw(16) << valeurSupprimee
         << tempsSuppressionMap << "\n";

    cout << "============================================================\n";

    // ============================================
    // VERIFICATION DES RESULTATS
    // ============================================

    if (!trouve || !trouveMap ||
        !supprime || !supprimeMap) {

        cerr << "ERREUR : une operation a echoue !\n";
    }
}
