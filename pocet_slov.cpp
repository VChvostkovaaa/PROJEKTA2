#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

struct InputData {
    int totalWords = 0;         // celkovy pocet slov
    std::unordered_map<std::string, int> wordFrequencies;           // mapa pro unikatni slova a jejich cetnoci
};


/**
 * @brief Načte slova ze souboru, spočítá celkový počet slov a určí četnost unikátních slov.
 * * @param filename Jméno vstupního souboru (např. "Test3.txt").
 * @return InputData Struktura obsahující celkový počet slov a mapu četností.
 */
InputData processInput(const std::string& filename) {

    // Vytvoříme prázdnou strukturu, kterou budeme vyplňovat
    InputData result;

    // Otevření souboru pro čtení
    std::ifstream inputFile(filename);

    // 1. Kontrola, zda se soubor podařilo otevřít
    if (!inputFile.is_open()) {
        std::cerr << "CHYBA: Nepodařilo se otevřít soubor " << filename << std::endl;
        return result;    // kdybych dala 1 tak by to zanamenalo ze chyba je v celem kodu
    }

    // --- Proměnná pro dočasné uložení slova ---
    std::string word;

    // --- Hlavní cyklus pro čtení a počítání ---
    // delam tuhle funkci dokola dokud nejsem na konci souboru -> není tam vice slov
    while (inputFile >> word) {

        // po kazdem projetí funkce se nam pričte 1 slovo (ulozena v results)
        result.totalWords++;

        result.wordFrequencies[word]++;
        // zavisi na tom jestli slovo vidime poprve nebo ne
        // slovo poprve -> v mape jeste neexistuje -> automaticky vytvori zazman -> zvysuje z hodnoty 0 -> 1
        // slove je uz ulozene v mape –> zvysí jen hodnotu o 1
    }

    inputFile.close();

    // vysledek s daty
    return result;
}

