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

/**
 * @brief - spusti analyzu pro BST a AVL stromy
 * vlozi data do stromu, nastavi pravdepodobnost a tiskne vysledy
 * @tparam TTree - typ stromu but BST / AVL
 * @param tree - strom ktery se ma analyzovat
 * @param data - vytazena data ze souboru (slovo, frekvence, pravdepodobnost)
 * @param treeName - je jmeno pro tisk BST / AVL
 */
template <typename TTree>
void runTreeAnalysis(TTree& tree, const InputDataExtracted& data, const std::string& treeName) {
    std::cout << "\n--- " << treeName << " tree test ---" << std::endl;
    std::cout << "Building tree...done." << std::endl;

    // vkladame slova jak byla v podasi v souboru
    for (const auto& word : data.wordsSentence) {
        tree.insert(word);
    }

    tree.setProbabilities(data.probabilityMap);     // nastavime pravdepod. na uzly

    int height = tree.getHeight();      // vypocet vysky stromu
    double averageC = tree.calculateAverageComparisons();       // spocitame prumernou hloubku

    // tisk vysledku
    std::cout << "Number of unique words: " << data.wordFrequency.size() << std::endl;
    std::cout << "Height of tree: " << height << std::endl;
    std::cout << "All words found." << std::endl;       // plati ze se vsechna slovy najdou
    std::cout << "Average search depth: " << std::fixed << std::setprecision(3) << averageC << std::endl;
}

/**
 * @brief - spusti analyzu OPT
 * funkce vola buid, ktere sestavuje optomalni strom na zaklade predem serazenych pravdepodobnosti
 * @param tree - strom ktery mam analyzovat
 * @param data - vytazena data ze souboru (slovo, frekvence, pravdepodobnost)
 */
void runOPTAnalysis(OPT& tree, const InputDataExtracted& data) {
    std::cout << "\n--- Optimal binary search tree test ---" << std::endl;
    std::cout << "Building tree...done." << std::endl;

    // vola metodu, ktera spocita root a C
    tree.build(data.sortedProbability);

    int height = tree.getHeight();      // vypocet vysky stromu
    double averageC = tree.calculateAverageComparisons();       // spocita prumernou hloubku

    // tisk vysledku
    std::cout << "Number of unique words: " << data.wordFrequency.size() << std::endl;
    std::cout << "Height of tree: " << height << std::endl;
    std::cout << "All words found." << std::endl;
    std::cout << "Average search depth: " << std::fixed << std::setprecision(3) << averageC << std::endl;
}

/**
 * @brief - hlavni funkce projektu
 * zpracuje vstupni sounor a vola analyzacni funkce a tiskne vyledky
 * @return  0 -> uspesne dokoncen, 1 -> neco je spatne
 */
int main() {
    // cesta k souboru kde jsou slova
    const std::string filename = "/Users/veronikachvostkova/CLionProjects/projektA2/Test4.txt";

    // zpracovani dat pro vsechny stromy najenou, nacte soubor, frekvenci a provdep.
    InputDataExtracted data = processInputExtracted(filename);

    // kontrola jestli je co analyzovat
    if (data.totalWord == 0) {
        std::cerr << "Žádná data ke zpracování nebo chyba souboru." << std::endl;
        return 1;
    }

    std::cout << "Number of total words (m): " << data.totalWord << std::endl;

    BST myBST;
    runTreeAnalysis(myBST, data, "Binary search");

    AVL myAVL;
    runTreeAnalysis(myAVL, data, "AVL");

    OPT myOPT;
    runOPTAnalysis(myOPT, data);

    return 0;
}
