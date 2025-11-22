#include "OPT.h"
#include "TreeBase.h"
#include "InputProcesor.h"
#include <iostream>
#include <algorithm>
#include <limits> // Potřebné pro std::numeric_limits

/**
 * @brief Konstruktor pro uzel optimálního stromu.
 * @param word Slovo, které se má do uzlu uložit.
 * @param p Pravděpodobnost výskytu tohoto slova.
 */
OPTNode::OPTNode(const std::string& word, double p) {
    this -> word = word;
    this -> left = nullptr;
    this -> right = nullptr;
    this -> probability = p;
}

/**
 * @brief - základní konstruktor pro celý OPT strom
 */
OPT::OPT() : BinaryTreeBase<OPTNode>() {
    this -> N_size = 0; // na začátku je velikost 0
}

/**
 * @brief - pomocná funkce pro sečtení pravděpodobností
 * @param i - začáteční index
 * @param j - konečný index
 * @param data - vektor slovo, pravděpodobnost
 * @return - součet pravděpodobností slov od indexu i do j
 */
double sumProbDirect(int i, int j, const std::vector<std::pair<std::string, double>>& data) {
    double sum = 0.0;
    // iterujeme od indexu i-1 do j-1, protože vektor 'data' je 0-indexovaný
    for(int k = i-1; k < j; k++) {
        if(k  >= 0 && k < data.size()) {
            sum += data[k].second;
        }
    }
    return sum;
}

/**
 * @brief -rekurzivní funkce pro sestavení stromu na základě vyplněné tabulky 'Root'
 * @param L -levá hranice aktuálního podstromu
 * @param R -pravá hranice aktuálního podstromu
 * @param data -původní data (slova a pravděpodobnosti)
 * @return -ukazatel na kořen nově vytvořeného podstromu
 */
OPTNode* OPT::buildTreeRecursive(int L, int R, const std::vector<std::pair<std::string, double>>& data) {
    // pokud je levá hranice větší než pravá, znamená to prázdný podstrom
    if (R < L) return nullptr;

    int k_index = Root[L][R];   // z Root zjistíme index korene

    // vytvoříme nový uzel pro tento kořen
    const auto& wordData = data[k_index - 1];
    OPTNode* node = new OPTNode(wordData.first, wordData.second);

    // rekurzivně sestavíme levý a pravý podstrom
    // levý podstrom je pro prvky od L do k_index-1.
    node -> left = buildTreeRecursive(L, k_index - 1, data);
    // pravý podstrom je pro prvky od k_index+1 do R.
    node -> right = buildTreeRecursive(k_index + 1, R, data);

    return node;
}

/**
 * @brief - hlavní metoda dynamického programování pro výpočet tabulek C a Root
 * inspirace z knihy:LEVITIN, Anany., 2012. Introduction to the Design and Analysis of Algorithms. 3rd ed. Boston: Pearson. ISBN 978-0-13-231681-1
 * @param data - vstupní data seřazená abecedně
 */
void OPT::calculateDPTables(const std::vector<std::pair<std::string, double>>& data) {
    int n = data.size();
    this -> N_size = n;

    // připravíme 2D tabulky C (ceny) a Root (kořeny)
    // velikost n+2 a n+1 je pro zjednodušení práce s indexy od 1 do n
    C.assign(n + 2, std::vector<double>(n + 2, 0.0));
    Root.assign(n + 1, std::vector<int>(n + 1, 0));

    // pro podstromy délky 1
    for (int i = 1; i <= n; i++) {
        C[i][i] = data[i-1].second; // cena je pravděpodobnost jediného prvku
        Root[i][i] = i; // koren je ten prvek
    }

    // pro podstromy délky větší než 1
    // d je délka podstromi
    for (int d = 1; d <= n - 1; d++) {
        // i je začáteční index podstromu
        for (int i = 1; i <= n - d; i++) {
            int R = i + d; // R je konečný index podstromu
            double minval = 10000000.0; // máme tak velké mminimum, protože portěbujeme zajisti, že hned při prvním porovní to neprekročíme
            int kmin = 0; // zde si budeme ulkádat nejlepší kořen

            for (int k = i; k <= R; k++) {
                double cost = C[i][k - 1] + C[k + 1][R];    // součet cen levého a pravého podstromu

                // pokud je cost menší, aktualizujeme minimum
                if (cost < minval) {
                    minval = cost;
                    kmin = k;
                }
            }

            // uložíme si nejlepší nalezený kořen pro podstrom
            Root[i][R] = kmin;

            double sum_probs_direct = sumProbDirect(i, R, data);    // součet pravděpodobností od i do R

            C[i][R] = minval + sum_probs_direct;    //minimanlní cena + součet pravděpodobností
        }
    }
}

/**
 * @brief - veřejná metoda, která spustí celý proces stavby OPT stromu
 * @param data - vstupní data seřazená abecedně
 */
void OPT::build(const std::vector<std::pair<std::string, double> > &data) {
    calculateDPTables(data);
    root = buildTreeRecursive(1, data.size(), data);
    // na zakladě tabulky Root sestavíme strom
}

/**
 * @brief - vrací průměrnou hloubku vyhledávání pro OPT strom
 * @return - průměrná hloubka vyhledávání
 */
double OPT::calculateAverageComparisons() {
    if (N_size == 0 || C.empty()) return 0.0;
    return C[1][N_size];
}