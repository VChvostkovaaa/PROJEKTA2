#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> // Pro std::sort
#include <sstream>
#include <cctype> // Pro ispunct

#include "InputProcesor.h"

/**
 * @brief - hlavní funkce pro zpracování vstupního souboru.
 * Načte soubor, spočítá frekvence, pravděpodobnosti a připraví všechna potřebná data.
 * @param filename - cesta ke vstupnímu textovému souboru.
 * @return - struktura InputDataExtracted naplněná všemi relevantními daty.
 */
InputDataExtracted processInputExtracted(const std::string& filename) {
    // prázdná struktura, kterou budeme postupně plnit
    InputDataExtracted result;

    std::cout << "Reading source word...done." << std::endl;

    //  otevřít soubor pro čtení
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "CHYBA: Nepodarilo se otevrit soubor " << filename << std::endl;
        return result;
    }

    std::string word;
    // Cyklus pro čtení slov ze souboru
    while (inputFile >> word) {
        result.totalWord++;
        result.wordFrequency[word]++; // zvýšení počtu výskytů slova, pokud neexistuje slovo není v mapě, vytvoří se
        // přidáme slovo do vektoru, abychom zachovali původní pořadí
        result.wordsSentence.push_back(word);
    }
    inputFile.close();

    if (result.totalWord == 0) {
        return result;
    }

    // projdeme mapu frekvencí a pro každé slovo vypočítáme jeho pravděpodobnost
    for (const auto& pair : result.wordFrequency) {
        result.probabilityMap[pair.first] = (double)pair.second / result.totalWord;
    }

    // vytvoří abecedně seřazený seznam, pro potřeby OPT stromu
    result.sortedProbability = sortAndCalculateProbabilities(result.wordFrequency, result.totalWord);

    return result;
}

bool compare(const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
    return a.first < b.first;
}


/**
 * @brief - pomocná funkce, která vezme mapu frekvencí a vytvoří z ní abecedně seřazený
 * vektor -> slovo, pravděpodobnost
 * @param freqMap - mapa frekvencí slov
 * @param totalWords - celkový počet slov v textu
 * @return - abecedně seřazený vektor párů připravený pro OPT strom
 */
std::vector<std::pair<std::string, double>> sortAndCalculateProbabilities(const std::unordered_map<std::string, int>& freqMap, int totalWords) {
    std::vector<std::pair<std::string, double>> sortedData;
    if (totalWords == 0) return sortedData;

    // Převedeme mapu frekvencí na vektor párů
    for (const auto& pair : freqMap) {
        double prob = (double)pair.second / totalWords;
        sortedData.push_back({pair.first, prob});
    }
    
    // seřadíme vektor abecedně podle slov
    std::sort(sortedData.begin(), sortedData.end(), compare);
    
    return sortedData;
}
