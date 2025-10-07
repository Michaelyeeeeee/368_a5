#include "coordinates.h"

void printCoord(TreeNode * node, int x, int y, FILE * out){
    if(!node) return;
    if(node->cutType == 'L'){
        fprintf(out, "%d((%d,%d)(%d,%d))\n", node->label, node->width, node->height, x, y);
    } else if(node->cutType == 'V'){
        printCoord(node->left, x, y, out);
        printCoord(node->right, x + node->left->width, y, out);
    } else if(node->cutType == 'H'){
        printCoord(node->left, x, node->right->height, out);
        printCoord(node->right, x, y, out);
    }
}

void printAllCoords(TreeNode * node, FILE * out){
    if(!node) return;
    printCoord(node, 0, 0, out);
}