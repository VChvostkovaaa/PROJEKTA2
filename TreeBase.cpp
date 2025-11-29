#include <unordered_map>
#include "TreeBase.h"

/**
 * @brief - rekurzivně počítá výšku stromu
 */
int calculateHeightRecursive(BaseNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(calculateHeightRecursive(node->left),
                        calculateHeightRecursive(node->right));
}

/**
 * @brief - rekurzivně prochází strom a nastavuje uzlům jejich pravděpodobnosti z mapy
 */
void setProbabilitiesRecursive(BaseNode* node, const std::unordered_map<string, double>& probMap) {
    if (node == nullptr) {
        return;
    }
    // najdeme pravděpodobnost pro slovo v aktuálním uzlu
    auto it = probMap.find(node->word);
    if (it != probMap.end()) {
        node->probability = it-> second;
    }
    // pokračujeme na potomky
    setProbabilitiesRecursive(node->left, probMap);
    setProbabilitiesRecursive(node->right, probMap);
}

/**
 * @brief - rekurzivně počítá průměrnou hloubku vyhledávání
 * Vzorec: suma(p_i * hloubka_i)
 */
double calculateAverageRecursive(BaseNode* node, int depth) {
    if (node == nullptr) {
        return 0.0;
    }
    // hloubka pro výpočet ceny
    double c_i = (double)depth + 1.0;
    // aktuální příspěvek do celkové ceny
    double currentContribution = c_i * node->probability;

    // Celková cena stromu
    return currentContribution
           + calculateAverageRecursive(node->left, depth + 1)
           + calculateAverageRecursive(node->right, depth + 1);
}
