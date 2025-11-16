#include "OPT.h"
#include "TreeBase.h"
#include "InputProcesor.h"
#include <iostream>
#include <algorithm>


OPTNode::OPTNode(const std::string& w, double p) {
    this -> word = w;
    this -> left = nullptr;
    this -> right = nullptr;
    this -> probability = p;
}

OPT::OPT() : BinaryTreeBase<OPTNode>() {
    this -> N_size = 0;
}

double sumProbDirect(int i, int j, const std::vector<std::pair<std::string, double>>& data) {
    double sum = 0.0;
    //interujeme od indexi i-1 do j-1, protze 'data' je 0-indexovane
    for(int k = i-1; k < j; k++) {
        if(k>=0 && k < data.size()) {
            sum += data[k].second;
        }
    }
    return sum;
}

OPTNode* OPT::buildTreeRecursive(int L, int R, const std::vector<std::pair<std::string, double>>& data) {
    if (R < L) return nullptr;

    // Index kořene je uložen v DP tabulce (Indexy jsou 1-založené)
    int k_index = Root[L][R];

    // Data v 'data' jsou 0-založená, k_index je 1-založený
    const auto& wordData = data[k_index - 1];

    OPTNode* node = new OPTNode(wordData.first, wordData.second);

    // Rekurzivní volání
    node -> left = buildTreeRecursive(L, k_index - 1, data);
    node -> right = buildTreeRecursive(k_index + 1, R, data);

    return node;
}

// V SOUBORU OPT.cpp, uvnitř metody OPTTree::calculateDPTables:

void OPT::calculateDPTables(const std::vector<std::pair<std::string, double>>& data) {
    int n = data.size();
    this->N_size = n;

    // SumP již neexistuje!
    C.assign(n + 2, std::vector<double>(n + 2, 0.0));
    Root.assign(n + 1, std::vector<int>(n + 1, 0));

    // Krok 1: Inicializace délky 1
    for (int i = 1; i <= n; i++) {
        C[i][i] = data[i-1].second; // P[i]
        Root[i][i] = i;
    }

    // Krok 2-4: Iterace DP
    for (int d = 1; d <= n - 1; d++) {
        for (int i = 1; i <= n - d; i++) {
            int R = i + d;
            double minval = std::numeric_limits<double>::infinity();
            int kmin = 0;

            for (int k = i; k <= R; k++) {
                double cost = C[i][k - 1] + C[k + 1][R];

                if (cost < minval) {
                    minval = cost;
                    kmin = k;
                }
            }

            Root[i][R] = kmin;

            // Tady používáme NOVOU PŘÍMOU FUNKCI:
            double sum_probs_direct = sumProbDirect(i, R, data);

            C[i][R] = minval + sum_probs_direct; // C[i, j] ← minval + sum
        }
    }
}

void OPT::build(const std::vector<std::pair<std::string, double> > &data) {
    calculateDPTables(data);
    root = buildTreeRecursive(1, data.size(), data);
}


double OPT::calculateAverageComparisons() {
    if (N_size == 0 || C.empty()) return 0.0;
    // Celková minimální cena je vždy uložena v C[1][N]
    return C[1][N_size];
}

