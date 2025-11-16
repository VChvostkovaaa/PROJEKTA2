#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> // Pro std::sort
#include <sstream>

#include "InputProcesor.h"

/**
 * @brief - zpracuje textovy soubor a vytahne uź nej data pro analyzu
 *
 * nacte soubor, spocita slova, frekvenci a pravdepodobnosst
 * @param filename - cesta k souboru
 * @return InputDataExtracted -> struktura s vytazenymi daty
 */
InputDataExtracted processInputExtracted(const std::string& filename) {
    InputDataExtracted result;

    std::cout << "Reading source file...done." << std::endl;

    // otevirani souboru
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "ERROR: Could not open file " << filename << std::endl;
        return result;
    }

    // pro cteni slov ze souboru
    std::string word;
    while (inputFile >> word) {
        // cte soubor az do konce
        while (!word.empty() && ispunct(word.back())) {
            word.pop_back();
        }
        if (!word.empty()) {
            result.totalWord++;     // pocet vsech slov
            result.wordFrequency[word]++;       // zvysuje frekvenci pro kazde slovo
            result.wordsSentence.push_back(word);       // ukadani slov do vektoru podle toho jak sli za sebou
        }
    }
    inputFile.close();

    // kontrola, ze se vsechno nacetlo
    if (result.totalWord == 0) {
        return result;
    }

    // vypocet pro pravdepodobnost p_i = f_i / m (ze zadani)
    for (const auto& pair : result.wordFrequency) {
        result.probabilityMap[pair.first] = (double)pair.second / result.totalWord;
    }

    // vytvori serazeny vektopr pro OPT strom
    result.sortedProbability = sortAndCalculateProbabilities(result.wordFrequency, result.totalWord);

    return result;
}


/**
 * @brief - sezadi slova podle frekvence a vypocíta jejich pravdepodobnest
 * vezme mapu frekvenci, spocita pravdep. a pak to seradí
 * @param freqMap - pocet vyskytu (bere to z InputDataEctracted::wordFrequency)
 * @param totalWords - celkovy pocet slov (bere to z InputDataEctracted::totalWord)
 * @return - std::vector<std::pair<std::string, double>> je to sezareny vektor dvojic -> slovo, pravdep.
*/
std::vector<std::pair<std::string, double>> sortAndCalculateProbabilities(const std::unordered_map<std::string, int>& freqMap, int totalWords) {
    std::vector<std::pair<std::string, double>> sortedData;
    if (totalWords == 0) return sortedData;

    // vypocitame pravdepodobnost a ulozime to do vektoru
    for (const auto& pair : freqMap) {
        double prob = (double)pair.second / totalWords;
        sortedData.push_back({pair.first, prob});
    }
    // pro OPT musime seradit lova abecedne
    std::sort(sortedData.begin(), sortedData.end(), [](const auto& a, const auto& b) {
        // serazovani slov
        return a.first < b.first;
    });
    return sortedData;
}