#ifndef TREEBASE_H
#define TREEBASE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> // Pro std::max
#include <utility>   // Pro std::pair

using namespace std;

struct InputDataExtracted;

/**
 * @brief základní struktura pro uzel stromu
 * Definuje společné vlastnosti, které mají všechny uzly ve všech typech stromů
 */
struct BaseNode {
    string word;
    BaseNode *left = nullptr;
    BaseNode *right = nullptr;
    double probability = 0.0;
    int height = 1;
    
    // Virtuální destruktor je důležitý pro správné uvolnění paměti
    // při práci s polymorfismem (kdy držíme ukazatel na BaseNode,
    // ale ve skutečnosti je to třeba AVLNode).
    virtual ~BaseNode() = default;
};

template<class TNode>
int calculateHeightRecursive(TNode* node);

template<class TNode>
void setProbabilitiesRecursive(TNode* node, const unordered_map<string, double>& probMap);

template<class TNode>
double calculateAverageRecursive(TNode* node, int depth);


/**
 * @brief - základní třída pro všechny binární vyhledávací stromy
 * Definuje společné rozhraní a sdílí kód pro analytické funkce
 * Použití šablony <class TNode> umožňuje této třídě pracovat s různými typy uzlů
*/
template<class TNode>
class BinaryTreeBase {
protected:
    // každý strom má kořen, který je přístupný pro potomky
    TNode* root;

public:
    // konstruktor vytvoří prázdný strom
    BinaryTreeBase() : root(nullptr) {}

    // tyto funkce jsou stejné pro všechny stromy
    // výska stromu
    int getHeight() {
        return calculateHeightRecursive(root);
    }

    // pravdepodobnosti uzlu
    void setProbabilities(const unordered_map<string, double>& probMap) {
        setProbabilitiesRecursive(root, probMap);
    }

    // průměrná hloubka vyhledávání
    double calculateAverageComparisons() {
        return calculateAverageRecursive(root, 0);
    }

    // zavolání destruktoru pro správné uvolnění paměti
    virtual ~BinaryTreeBase() = default;

    // Tyto metody mohou být implementovány

    /**
     * @brief - metoda pro vložení slova
     * '= 0' znamená, že BST a AVL si musí implementovat vlastní verzi této metody
     */
    virtual void insert(const string& word) = 0;

    /**
     * @brief - sestavení stromu najednou
     * Používá se pro OPT strom
     */
    virtual void build(const vector<pair<string, double>>& data) {
        (void)data; // prázdná implementace na nevyužitý parametr
    }
};

/**
 * @brief - rekurzivně počítá výšku stromu
 */
template<class TNode>
int calculateHeightRecursive(TNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(calculateHeightRecursive((TNode*)(node -> left)),
                        calculateHeightRecursive((TNode*)(node -> right)));
}

/**
 * @brief - rekurzivně prochází strom a nastavuje uzlům jejich pravděpodobnosti z mapy
 */
template<class TNode>
void setProbabilitiesRecursive(TNode* node, const unordered_map<string, double>& probMap) {
    if (node == nullptr) {
        return;
    }
    // najdeme pravděpodobnost pro slovo v aktuálním uzlu
    auto it = probMap.find(node -> word);
    if (it != probMap.end()) {
        node->probability = it -> second;
    }
    // pokračujeme na potomky
    setProbabilitiesRecursive((TNode*)(node -> left), probMap);
    setProbabilitiesRecursive((TNode*)(node -> right), probMap);
}

/**
 * @brief - rekurzivně počítá průměrnou hloubku vyhledávání
 * Vzorec: suma(p_i * hloubka_i)
 */
template<class TNode>
double calculateAverageRecursive(TNode* node, int depth) {
    if (node == nullptr) {
        return 0.0;
    }
    // hloubka pro výpočet ceny
    double c_i = (double)depth + 1.0;
    // aktuální příspěvek do celkové ceny
    double currentContribution = c_i * node -> probability;

    // Celková cena stromu
    return currentContribution
           + calculateAverageRecursive((TNode*)(node -> left), depth + 1)
           + calculateAverageRecursive((TNode*)(node -> right), depth + 1);
}

#endif //TREEBASE_H