#ifndef TREEBASE_H
#define TREEBASE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> // Pro std::max
#include <utility>   // Pro std::pair

using std::string;
using std::vector;

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


int calculateHeightRecursive(BaseNode* node);


void setProbabilitiesRecursive(BaseNode* node, const std::unordered_map<string, double>& probMap);


double calculateAverageRecursive(BaseNode* node, int depth);


/**
 * @brief - základní třída pro všechny binární vyhledávací stromy
 * Definuje společné rozhraní a sdílí kód pro analytické funkce
 * Použití šablony <class TNode> umožňuje této třídě pracovat s různými typy uzlů
*/

class BinaryTreeBase {
protected:
    // každý strom má kořen, který je přístupný pro potomky
    BaseNode* root;

public:
    // konstruktor vytvoří prázdný strom
    BinaryTreeBase() : root(nullptr) {}

    // tyto funkce jsou stejné pro všechny stromy
    // výska stromu
    int getHeight() {
        return calculateHeightRecursive(root);
    }

    // pravdepodobnosti uzlu
    void setProbabilities(const std::unordered_map<string, double>& probMap) {
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
    virtual void build(const vector<std::pair<string, double>>& data) {
        (void)data; // prázdná implementace na nevyužitý parametr
    }
};

#endif //TREEBASE_H