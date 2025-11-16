#ifndef OPT_H
#define OPT_H

#include <string>
#include <vector>
#include <unordered_map>
#include "TreeBase.h"

struct OPTNode : public BaseNode {
    /**
     * @brief - konstructo pro uzle OPT
     * @param w - slovo ulozene v uzlu
     * @param p - pravsepodobnost vykytu
     */
    OPTNode(const std::string& w, double p);
};

class OPT : public BinaryTreeBase<OPTNode> {
private:
    std::vector<std::vector<double>> C; // Tabulka cen C[i][j]
    std::vector<std::vector<int>> Root; // Tabulka kořenů Root[i][j]

    int N_size = 0; // pocet unikatnich slov

    double sumProb(int i, int j);
    void calculateDPTables(const std::vector<std::pair<std::string, double>>& data);
    OPTNode* buildTreeRecursive(int L, int R, const std::vector<std::pair<std::string, double>>& data);

public:
    OPT();
    void insert(const std::string& word) override {
        (void)word;
    }
    void build(const std::vector<std::pair<std::string, double>>& data) override;
    double calculateAverageComparisons();
};
#endif //OPT_H
