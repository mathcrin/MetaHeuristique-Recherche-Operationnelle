#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int main() {
    ifstream infile("Scp1.txt");
    if (!infile) {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
        return 1;
    }

    int n, m; // n = nombre d'ensembles, m = nombre d'éléments
    infile >> n >> m;

    vector<int> costs(m); // Tableau pour stocker les coûts des sous-ensembles
    for (int i = 0; i < m; ++i) {
        infile >> costs[i];
    }

    // Matrice m x n (m lignes pour les ensembles et n colonnes pour les elements )
    vector<vector<int>> matrix(m, vector<int>(n, 0));

    string line;
    int element, set_count, subset;

    // Lecture des couples élément-ensembles
    while (infile >> element >> set_count) {
        vector<int> subsets(set_count);
        for (int i = 0; i < set_count; ++i) {
            infile >> subsets[i];
        }

        // Mettez 1 dans la matrice pour chaque couple (élément, sous-ensemble)
        for (int j = 0; j < set_count; ++j) {
            int set_idx = subsets[j] - 1; // Les indices des ensembles commencent à 1 dans le fichier
            if (element > 0 && element <= n && set_idx >= 0 && set_idx < m) {
                matrix[element - 1][set_idx] = 1;
            } else {
                cerr << "Erreur : indices hors limites - element: " << element << ", set_idx: " << set_idx << endl;
            }
        }
    }

    // Ouvrir un fichier pour écrire la matrice résultante
    ofstream outfile("output_matrix2.txt");
    if (!outfile) {
        cerr << "Erreur: impossible d'ouvrir le fichier de sortie.\n";
        return 1;
    }

    // Écrire la matrice dans le fichier
    outfile << "Matrice des couvertures m x n:\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            outfile << val << " ";
        }
        outfile << endl;
    }

    // Écrire les coûts des sous-ensembles dans le fichier
    outfile << "\nCoûts des sous-ensembles:\n";
    for (int i = 0; i < n; ++i) {
        outfile << "Sous-ensemble " << (i + 1) << " : " << costs[i] << endl;
    }

    // Fermer le fichier de sortie
    outfile.close();

    cout << "La matrice résultante et les coûts des sous-ensembles ont été écrits dans 'output_matrix.txt'.\n";

    return 0;
}
