/*!
* \file main.c
* \brief main program to build a Huffman tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <float.h>

#include "binary_tree.h"

int main() {
    float pb[] = {0.11, 0.01, 0.09, 0.3, 0.05, 0.15, 0.22, 0.07};
    int nb = sizeof(pb)/sizeof(pb[0]);

    nodeTree * root = NULL;

    /* to be completed */

    // Create an array of leaf nodes
    nodeTree* nodes[nb];
    for (int i = 0; i < nb; i++) {
        nodes[i] = newNodeTree(pb[i], NULL, NULL);
    }


    return 0;
}
