#ifndef INPUTPROCESOR_H
#define INPUTPROCESOR_H

#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief - struktura pro uchování všech dat ze vstupního souboru
 * Slouží jako kontejner
 */
struct InputDataExtracted {
  int totalWord = 0;  // celkový počet slov v textu
  
  std::unordered_map<std::string, int> wordFrequency; // (slovo, frekvence)

  std::vector<std::string> wordsSentence; // všechna slova v pořadí

  std::unordered_map<std::string, double> probabilityMap; // (slovo, pravdepodobnost)

  std::vector<std::pair<std::string, double>> sortedProbability; // abecedne uspořádané (slovo, pravdepodobnost)
};


InputDataExtracted processInputExtracted(const std::string& filename);


std::vector<std::pair<std::string, double>> sortAndCalculateProbabilities(const std::unordered_map<std::string, int>& freqMap, int totalWords);

#endif //INPUTPROCESOR_H