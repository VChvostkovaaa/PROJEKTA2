#ifndef OPT_H
#define OPT_H

#include <string>
#include <vector>
#include <unordered_map>
#include "TreeBase.h"

using namespace std;

struct OPTNode : public BaseNode {
    /**
     * @brief - konstructo pro uzle OPT
     * @param w - slovo ulozene v uzlu
     * @param p - pravsepodobnost vykytu
     */
    OPTNode(const string& w, double p);
};

class OPT : public BinaryTreeBase<OPTNode> {
private:
    vector<vector<double>> C; // Tabulka cen C[i][j]
    vector<vector<int>> Root; // Tabulka kořenů Root[i][j]

    int N_size = 0; // pocet unikatnich slov

    double sumProb(int i, int j);

    void calculateDPTables(const vector<pair<string, double>>& data);

    OPTNode* buildTreeRecursive(int L, int R, const vector<pair<string, double>>& data);

public:
    OPT();
    void insert(const string& word) {
        (void)word;
    }

    void build(const vector<pair<string, double>>& data);

    double calculateAverageComparisons();
};
#endif //OPT_H