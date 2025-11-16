#ifndef INPUTPROCESOR_H
#define INPUTPROCESOR_H

#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief - struktura pro ulozeni a drzini vsech informci, ktere vytahneme ze vstupniho souboru
 */
struct InputDataExtracted {
  int totalWord = 0;  // celkovy pocet slov, ktere jsme nasli v souboru
  std::unordered_map<std::string, int> wordFrequency;  // zaznamenava pocet vyskytu urciteho slova -> frekvence
  std::vector<std::string> wordsSentence;  // udrzi poradi slov jak sli v souboru za sebou
  std::unordered_map<std::string, double> probabilityMap;  // pravdepodobnobnost vyskytu kazdeho slova
  std::vector<std::pair<std::string, double>> sortedProbability;  // sezrazeny seznam slov a jejich poravdepodobnost -> od nejvetsiho po nejmensi
};


/**
 * @brief - zpracujeme vstupni soubor, vypocitame cetnost a pravdepodobnosti vsech slov
 * @param filename - cesta k souboru
 * @return processInputExtracted - struktura s nactenymi a vypocitanymi daty
*/
InputDataExtracted processInputExtracted(const std::string& filename);

/**
 * @brief - sezadi slova podle frekvence a vypocíta jejich pravdepodobnest
 * vezme mapu frekvenci, spocita pravdep. a pak to seradí
 * @param freqMap - pocet vyskytu (bere to z InputDataEctracted::wordFrequency)
 * @param totalWords - celkovy pocet slov (bere to z InputDataEctracted::totalWord)
 * @return - std::vector<std::pair<std::string, double>> je to sezareny vektor dvojic -> slovo, pravdep.
 */
std::vector<std::pair<std::string, double>> sortAndCalculateProbabilities(const std::unordered_map<std::string, int>& freqMap, int totalWords);

#endif //INPUTPROCESOR_H
