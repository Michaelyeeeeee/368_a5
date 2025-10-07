#include "dimensions.h"

/*
prints a single node in post-order with dimensions
inputs
    node - node to be printed
    width - pointer to width variable to store width of node
    height - pointer to height variable to store height of node
*/
void writePostNode(FILE * out, TreeNode * node, int * width, int * height){
    if(!out || !node) return;
    if(node->cutType == 'L'){
        fprintf(out, "%d(%d,%d)\n", node->label, node->width, node->height);
    } else {
        *width = (node->cutType == 'V') ? (node->left->width + node->right->width) : fmax(node->left->width, node->right->width);
        node->width = *width;
        *height = (node->cutType == 'H') ? (node->left->height + node->right->height) : fmax(node->left->height, node->right->height);
        node->height = *height;
        fprintf(out, "%c(%d,%d)\n", node->cutType, *width, *height);
    }
}

/*
prints tree in post-order with dimensions
inputs
    node - root of tree to be printed
    width - pointer to width variable to store width of tree
    height - pointer to height variable to store height of tree
*/
void writePostTree(FILE * out, TreeNode * node, int * width, int * height){
    if(!out || !node) return;
    writePostTree(out, node->left, width, height);
    writePostTree(out, node->right, width, height);
    writePostNode(out, node, width, height);
}