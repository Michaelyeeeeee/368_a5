#include "coordinates.h"

/*
prints coordinates of a single node
inputs
    node - node to be printed
    x - x coordinate of bottom-left corner of node
    y - y coordinate of bottom-left corner of node
    out - file to print to
*/
void printCoord(TreeNode * node, int x, int y, FILE * out){
    if(!node) return;
    if(node->cutType == 'L'){
        fprintf(out, "%d((%d,%d)(%d,%d))\n", node->label, node->width, node->height, x, y);
    } else if(node->cutType == 'V'){
        printCoord(node->left, x, y, out);
        printCoord(node->right, x + node->left->width, y, out);
    } else if(node->cutType == 'H'){
        printCoord(node->left, x, y + node->right->height, out);
        printCoord(node->right, x, y, out);
    }
}

/*
prints coordinates of all leaf nodes
inputs
    node - root of tree
    out - file to print to
*/
void printAllCoords(TreeNode * node, FILE * out){
    if(!node) return;
    printCoord(node, 0, 0, out);
}