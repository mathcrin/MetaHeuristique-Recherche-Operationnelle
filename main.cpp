#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ifstream infile("Scp1.txt");
    if (!infile) {
        cerr << "Erreur: impossible d'ouvrir le fichier.\n";
        return 1;
    }

    int n, m; // n = nombre d'éléments, m = nombre d'ensembles
    infile >> n >> m;

    vector<int> costs(m); // Tableau pour stocker les coûts des sous-ensembles
    for (int i = 0; i < m; ++i) {
        infile >> costs[i];
    }

    // Matrice m x n (m lignes pour les ensembles et n colonnes pour les éléments)
    vector<vector<int>> matrix(m, vector<int>(n, 0));

    int element = 0, set_count;
    int iteration = 0; // Compteur d'itération qui désigne le nombre de couple compté 

    // Lecture des couples élément-ensembles
    while (infile >> set_count) {
        // On lit `set_count`, qui indique le nombre d'ensembles associés à cet élément
        vector<int> subsets(set_count);
        
        // Lire les indices des ensembles associés
        for (int i = 0; i < set_count; ++i) {
            infile >> subsets[i];
        }

        /* Afficher le couple : (index d'itération, set_count, liste des ensembles)
        Ce couple signigie : { 
                index d'itération : Compteur des couple trouvé  
                set_count : nombre des ensemble dans les quelle il se trouve 
                liste des ensemble :  {...}   
        }
        */
        cout << "Couple (" << iteration << ", [";
        for (int i = 0; i < set_count; ++i) {
            cout << subsets[i];
            if (i < set_count - 1) cout << ", ";
        }
        cout << "])" << endl;

        // Remplir la matrice pour chaque ensemble associé à cet élément
        for (int j = 0; j < set_count; ++j) {
            int set_idx = subsets[j]; // Convertir l'index d'ensemble en base 0
            if (set_idx >= 0 && set_idx < m && iteration < n) {
                matrix[set_idx][iteration] = costs[set_idx]; 
                /*      
                 ligne "set_idx" qui desinge l'ensemble [set_idx] {0..m}
                  la colone qui represente l'elements [iteration] {0..n} 
                */
            } else {
                cerr << "Erreur : indices hors limites - itération: " << iteration << ", set_idx: " << set_idx << endl;
            }
        }

        // Incrémenter l'index d'itération
        iteration++;
    }
    // Ouvrir un fichier pour écrire la matrice résultante
    ofstream outfile("Matrice resultante_00.txt");
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
    for (int i = 0; i < m; ++i) {
        outfile << "Sous-ensemble " << (i + 1) << " : " << costs[i] << endl;
    }

    // Fermer le fichier de sortie
    outfile.close();
    // cout<<"Pour vérifier :"<<endl ;
    // cout<< "le cout de l'ensemble 91 pour l'element 0 ="<<matrix[91][0] <<" ça doit étre égale au cout du sous ensemble = "<< costs[91]<<endl ;

    // AFFICHAGE SUR LA CONSOLE 
    /*  
        cout << "\nMatrice des couvertures m x n:\n";
        for (const auto& row : matrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
        cout<< "le nombre de couple (element - ensemble) est :"<<iteration <<endl ;
        Afficher les coûts des sous-ensembles
        for (int i = 0; i < m; ++i) {
            cout << "Le cout de sous-ensemble " << (i + 1) << " : " << costs[i] << endl;
        }
    */
    return 0;
}
