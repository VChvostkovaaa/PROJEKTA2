#ifndef BST_H
#define BST_H

#include "TreeBase.h"

using std::string;

/**
 * @brief - struktura reprezentující uzel BST
 * Dědí všechny vlastnosti ze základní struktury BaseNode
 */
struct BSTNode : public BaseNode {

  /**
   * @brief - konstruktor pro vytvoření nového uzlu BST
   * @param w - slovo, které bude v uzlu uloženo
   */
   BSTNode(const string& w);
};


class BST : public BinaryTreeBase {
private:
  BSTNode* insertRecursive(BSTNode* node, const string& word);

public:
  /**
   * @brief Konstruktor pro vytvoření prázdného BST stromu.
   */
  BST();

  void insert(const string& word);

};
#endif //BST_H