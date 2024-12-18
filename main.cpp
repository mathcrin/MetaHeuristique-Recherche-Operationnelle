#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

bool ajouterSousEnsemble(std::vector<int>& tableau, int taille , int numeroSousEnsemble) {
    if (numeroSousEnsemble < 0 || numeroSousEnsemble >= taille-1) {
        std::cerr << "Erreur : Numero de sous-ensemble hors des limites du tableau.\n : " << numeroSousEnsemble << " taille : " << taille << "\n";
        return false;
    }

    if (tableau[numeroSousEnsemble-1] == 1) {
        std::cout << "Le sous-ensemble " << numeroSousEnsemble << " est deja present.\n";
    } else {
        tableau[numeroSousEnsemble-1] = 1;
        std::cout << "Le sous-ensemble " << numeroSousEnsemble << " a ete ajoute.\n";
    }
    return true;
}

bool retirerSousEnsemble(std::vector<int>& tableau, int taille , int numeroSousEnsemble) {
    if (numeroSousEnsemble < 0 || numeroSousEnsemble >= taille-1) {
        std::cerr << "Erreur : Numero de sous-ensemble hors des limites du tableau.\n : " << numeroSousEnsemble << " taille : " << taille << "\n";
        return false;
    }

    if (tableau[numeroSousEnsemble-1] == 0) {
        std::cout << "Le sous-ensemble " << numeroSousEnsemble << " est deja a 0.\n";
    } else {
        tableau[numeroSousEnsemble-1] = 0;
        std::cout << "Le sous-ensemble " << numeroSousEnsemble << " a ete ajoute.\n";
    }
    return true;
}

bool echangerSousEnsemble(std::vector<int>& tableau, int taille , int numeroSousEnsembleARemplacer, int numerSousEnsembleQuiRemplace) {
    return ajouterSousEnsemble(tableau, taille, numerSousEnsembleQuiRemplace) && retirerSousEnsemble(tableau, taille, numeroSousEnsembleARemplacer);
}

vector<int> constructSolution(const vector<vector<int>>& matrix, int n, int m) {
    vector<int> solution(m, -1); // Initialiser la solution avec -1
    vector<int> covered(n, 0); // Tableau qui sert à stocker les éléments déjà couverts

    // Parcourir les colonnes de la matrice
    for (int j = 0; j < n; ++j) {
        // Parcourir les lignes de la matrice
        for (int i = 0; i < m; ++i) {
            // Si l'élément est couvert par l'ensemble i et que l'ensemble i n'est pas encore utilisé
            if (matrix[i][j] >= 1 && covered[j] == 0) {
                solution[i] = 1; // Ajouter l'ensemble i à la solution
                covered[j] = 1; // Marquer l'élément i comme ajouter à la solution
                break; // Passer à la colonne suivante
            }
        }
    }
    //véirifer si la solution est valide ou non, si la somme des éléments couverts est égale à n
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += covered[i];
    }
    if (sum != n) {
        cerr << "Erreur: la solution n'est pas valide.\n";
        printf("Les elements non couverts sont : ");
        for (int i = 0; i < n; ++i) {
            if (covered[i] == 0) {
                printf("\n | Elements %d ", i);
            }
        }
        printf("\nListe des elements dans covered : \n");
        for (int i = 0; i < n; ++i) {
            printf("\n| Elements %d  : %d ", i, covered[i]);
        }
    }

    return solution;
}

//Fonction qui calcule le coût total de la solution
int calculerCout(const vector<int>& solution, const vector<int>& costs) {
    int totalCost = 0;
    for (size_t i = 0; i < solution.size(); ++i) {
        if (solution[i] == 1) { // Si l'ensemble est sélectionné
            totalCost += costs[i];
        }
    }
    return totalCost;
}

// Fonction de recherche tabou
vector<int> rechercheTabou(const vector<vector<int>>& matrix, const vector<int>& costs, int maxIter, int tabouSize) {
    int m = matrix.size();
    int n = matrix[0].size();

    // Générer une solution initiale avec la fonction constructSolution
    vector<int> solution = constructSolution(matrix, n, m);
    int bestCost = calculerCout(solution, costs);
    vector<int> bestSolution = solution;

    // Liste tabou pour empêcher des mouvements récents
    unordered_set<string> tabouList;

    // Générateur de nombres aléatoires pour explorer des solutions voisines
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, m - 1);

    for (int iter = 0; iter < maxIter; ++iter) {
        printf("1");
        vector<int> currentSolution = bestSolution;
        string move = "";

        // Explorer un voisin aléatoire
        int ensembleARemplacer = dis(gen);
        int ensembleQuiRemplace = dis(gen);

        // Effectuer l'échange
        if (echangerSousEnsemble(currentSolution, m, ensembleARemplacer, ensembleQuiRemplace)) {
            // Générer un identifiant pour le mouvement
            move = to_string(ensembleARemplacer) + "-" + to_string(ensembleQuiRemplace);
            printf("2");
            // Calculer le coût de la solution courante
            int currentCost = calculerCout(currentSolution, costs);

            // Vérifier si le mouvement est tabou
            if (tabouList.find(move) == tabouList.end() || currentCost < bestCost) {
                printf("3");
                solution = currentSolution;
                if (currentCost < bestCost) {
                    bestCost = currentCost;
                    bestSolution = solution;
                }

                // Ajouter le mouvement à la liste tabou
                if (tabouList.size() >= static_cast<size_t>(tabouSize)) {
                    tabouList.erase(tabouList.begin()); // Retirer le plus ancien mouvement
                }
                tabouList.insert(move);
            }
            printf("4");
            // Afficher l'état à chaque itération (facultatif)
            cout << "Iteration " << iter + 1 << " : Cout actuel = " << currentCost
                 << ", Meilleur cout = " << bestCost << endl;
        }else {
            cerr << "Erreur: echangerSousEnsemble a echoue.\n";
        }
        currentSolution.clear();
        currentSolution.shrink_to_fit();

    }

    return bestSolution;
}

// Fonction pour vérifier si la solution est satisfiable en parcourant la matrice et en vérifiant si chaque élément est couvert
bool isStatisfiable(const vector<int> &solution, const vector<vector<int>>& matrix) {
    int n = matrix[0].size();
    int m = matrix.size();
    vector<int> covered(n, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] >= 1 && covered[j] == 0) {
                covered[j] = 1;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += covered[i];
    }
    return sum == n;

}

void loadMatrices(const string& filename, vector<vector<int>>& matrix, vector<int>& costs, int& n, int& m) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Erreur: impossible d'ouvrir le fichier " << filename << ".\n";
        return;
    }

    infile >> n >> m; // Lire les dimensions n et m

    costs.resize(m);
    for (int i = 0; i < m; ++i) {
        infile >> costs[i]; // Lire les coûts des ensembles
    }

    matrix.assign(m, vector<int>(n, 0)); // Initialiser la matrice m x n

    int set_count, iteration = 0;
    while (infile >> set_count) {
        vector<int> subsets(set_count);
        for (int i = 0; i < set_count; ++i) {
            infile >> subsets[i]; // Lire les indices des ensembles
        }

        for (int j = 0; j < set_count; ++j) {
            int set_idx = subsets[j];
            if (set_idx >= 0 && set_idx < m && iteration < n) {
                matrix[set_idx][iteration] = costs[set_idx];
            } else {
                cerr << "Erreur : indices hors limites - itération: " << iteration << ", set_idx: " << set_idx << endl;
            }
        }
        iteration++;
        if (iteration >= n) {
            break; // Stop if iteration exceeds the number of elements
        }
    }
}


int main() {
    string filename = "Scp1.txt";
    vector<vector<int>> matrix;
    vector<int> costs;
    int n, m;

    // Charger les matrices à partir du fichier
    loadMatrices(filename, matrix, costs, n, m);

    // Exemple : utiliser les matrices pour résoudre le problème
    int maxIter = 100;   // Nombre maximal d'itérations
    int tabouSize = 10;  // Taille de la liste tabou

    vector<int> bestSolution = rechercheTabou(matrix, costs, maxIter, tabouSize);

    cout << "\nMeilleure solution trouvee :\n";
    for (size_t i = 0; i < bestSolution.size(); ++i) {
        cout << "Sous-ensemble " << i + 1 << " : " << bestSolution[i] << endl;
    }

    return 0;
}
