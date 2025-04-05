
/*!
* \file binary_tree.c
* \brief File implementing the binary Huffman tree structure as studied in Huffman coding practical work
*/

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"



static void printCode(char cod[CODESIZEMAX], int size_code, float pb)
{
   int i;
   printf("le code dont la proba. est  %5.3f est: ",pb);
   for (i=0;i<size_code;i++) 
   	printf(" %c", cod[i]);
   printf("\n");
}

nodeTree * newNodeTree(float p, nodeTree * l, nodeTree * r) {
    nodeTree * newNode = (nodeTree *)malloc(sizeof(nodeTree));
    if (newNode == NULL) {
        printf("Error allocating a new node.\n");
        return NULL;
    }
    newNode->left = l;
    newNode->right = r;
    newNode->proba = p;
    return newNode;
}

void deleteNodeTree(nodeTree * n) {
    free((void*) n);
}

nodeTree * buildParentNode(nodeTree *l, nodeTree *r) {
    return newNodeTree(l->proba + r->proba, l, r);
}

void printCodewords(binary_tree t) {
    static char cod[CODESIZEMAX];  // Static array to persist between recursive calls
    static int size_code = 0;      // Static variable to track current depth

    // If tree is empty
    if (t == NULL) {
        return;
    }

    // If we reach the leaf, print all the code stocked and return
    if (t->left == NULL && t->right == NULL) {
        printCode(cod, size_code, t->proba);
        return;
    }

    // Traverse left
    if (t->left) {
        cod[size_code] = '0';      // Add '0' to code
        size_code++;               // Increment depth
        printCodewords(t->left);   // Recursive call
        size_code--;               // Backtrack: remove last digit
    }

    // Traverse right
    if (t->right) {
        cod[size_code] = '1';      // Add '1' to code
        size_code++;               // Increment depth
        printCodewords(t->right);  // Recursive call
        size_code--;              // Backtrack: remove last digit
    }
}

