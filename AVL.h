#ifndef AVL_H
#define AVL_H

#include <string>
#include <algorithm>
#include "TreeBase.h"

/**
 *@brief - uzel pro AVL strom
 * dedi z BadeNode, pridame pole height pro balancovaní
 */
struct AVLNode : public BaseNode {
 int height;

 /**
  * @brief - konstructor pro ulez AVL
  * @param w - slovo ulozene v uzlu
  */
 AVLNode(const std::string& w);
};

/**
 * @brief - vraci aktualni vysku uzlu
 * @param node - uzel od ktereho nas vyske zajima
 * @return int - vyska stromu
 */
int getHeight(AVLNode* node);

/**
 * @brief - vypocet balancniho faktoru
 * rozdil vysek praveho a leveho podtromu
 * @param node - uzel, poroktery pocitame balancni faktor
 * @return int - balanci faktor
 */
int getBalanceFactor(AVLNode* node);

/**
 * @brief - aktualizace vysky po vlozeni nebo rotaci
 * vyska = max(vyska leveho, vyska praveho)
 * @param node - uzeů, ktery se aktualizoval
 */
void updateHeight(AVLNode* node);

/**
 * @brief - udela rotaci doprava
 * pouzije se but L-L nebo L-R rotaci
 * @param x - koren podstromu, ktery se mi rotoval
 * @return AVLNode* - korem podstromu, ktery se mi rotova
 */
AVLNode* rotateRight(AVLNode* x);
/**
 *@brief - udela rotaci doprava
 * pouzije se but R-R nebo R-L rotaci
 * @param y - koren podstromu, ktery se mi rotoval
 * @return AVLNode* - korem podstromu, ktery se mi rotova
 */
AVLNode* rotateLeft(AVLNode* y);


/**
 * @brief - dela rotaci proku je nevyvazeny
 * kontrola balancniho faktoru a vyvola jeho rotaci
 * @param node - uzel, ktery se nam ma balancovat
 * @return AVLNode* - korem vyvazeneho stromu
 */
AVLNode* balance(AVLNode* node);

class AVL : public BinaryTreeBase<AVLNode> {
private:
 AVLNode* insertRecursive(AVLNode* node, const std::string& word);

public:
 /**
  * @brief - konstructor stromu
  */
 AVL();

 /**
  * @brief - vlozeni nove slovo do AVL stromu
  * spusti rekurzi a zajicti balancovani stromu
  * @param word - slovo pro vlozeni
  */
 void insert(const std::string& word) override;

};


#endif //AVL_H
