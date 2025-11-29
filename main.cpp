#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "BST.h"
#include "AVL.h"
#include "OPT.h"
#include "TreeBase.h"
#include "InputProcesor.h"

using std::string;
using std::vector;

/**
 * @brief - spusti analyzu pro BST a AVL stromy
 * vlozi data do stromu, nastavi pravdepodobnost a tiskne vysledky
 * @param tree - strom ktery se ma analyzovat
 * @param data - vytazena data ze souboru (slovo, frekvence, pravdepodobnost)
 * @param treeName - je jmeno pro tisk BST / AVL
 */
void runTreeAnalysis(BinaryTreeBase& tree, const InputDataExtracted& data, const string& treeName) {
    cout << "\n--- " << treeName << " tree test ---" << endl;
    cout << "Building tree...done." << endl;
    // vkládáme slova, jak byla v pořadí v souboru
    for (const auto& word : data.wordsSentence) {
        tree.insert(word);
    }

    // nastavíme pravděpodobnosti na uzly
    tree.setProbabilities(data.probabilityMap);

    //Výpočet výšky stromu
    int height = tree.getHeight();

    // výpočet průměrné hloubky
    double averageC = tree.calculateAverageComparisons();

    // tisk výsledků
    cout << "Number of unique words: " << data.wordFrequency.size() << endl;
    cout << "Height of tree: " << height << endl;
    cout << "All words found." << endl;
    cout << "Average search depth: " << fixed << setprecision(3) << averageC << endl;
}

/**
 * @brief - spustí analýzu pro OPT strom
 * @param tree - strom, který se má analyzovat
 * @param data - data ze souboru (slovo, frekvence, pravděpodobnost)
 */
void runOPTAnalysis(OPT& tree, const InputDataExtracted& data) {
    cout << "\n--- Optimal binary search tree test ---" << endl;
    cout << "Building tree...done." << endl;

    // zavolá metodu, který vypočítá C a Root
    tree.build(data.sortedProbability);

    // výpočet výšky stromu
    int height = tree.getHeight();

    // spočítáme průměrnou hloubku vyhledávání
    double averageC = tree.calculateAverageComparisons();

    // tisk výsledků
    cout << "Number of unique words: " << data.wordFrequency.size() << endl;
    cout << "Height of tree: " << height << endl;
    cout << "All words found." << endl;
    cout << "Average search depth: " << fixed << setprecision(3) << averageC << endl;
}

/**
 * @brief - hlavní funkce projektu. Zpracuje vstupní soubor, volá analyzační funkce a tiskne výsledky
 * @return 0 při úspěšném dokončení, 1 při chybě
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file_path>" << endl;
        return 1;
    }
    // cesta k souboru
    const string filename = argv[1];

    // zpracování vstupního souboru
    InputDataExtracted data = processInputExtracted(filename);

    // kontrola, zda máme nějaká data
    if (data.totalWord == 0) {
        cerr << "No words found in the input file or file is empty." << endl;
        return 1; // Chyba
    }

    cout << "Number of total words (m): " << data.totalWord << endl;

    BST myBST;
    runTreeAnalysis(myBST, data, "Binary search");

    AVL myAVL;
    runTreeAnalysis(myAVL, data, "AVL");
    OPT myOPT;
    runOPTAnalysis(myOPT, data);

    return 0; // Všechno v pořádku
}
