#ifndef AVL_H
#define AVL_H

#include <string>
#include <algorithm>
#include "TreeBase.h"

using namespace std;

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
 AVLNode(const string& w);
};


int getHeight(AVLNode* node);

int getBalanceFactor(AVLNode* node);

void updateHeight(AVLNode* node);

AVLNode* rotateRight(AVLNode* x);

AVLNode* rotateLeft(AVLNode* y);

AVLNode* balance(AVLNode* node);

class AVL : public BinaryTreeBase<AVLNode> {
private:
 AVLNode* insertRecursive(AVLNode* node, const string& word);

public:

 AVL();


 void insert(const string& word);

};


#endif //AVL_H