#include "post_order.h"
#include "tree.h"

/*
prints a single node
inputs
    node - node to be printed
*/
void printNode(TreeNode * node){
    if(!node) return;
    if(node->cutType == 'L'){
        printf("%d(%d,%d)\n", node->label, node->width, node->height);
    } else {
        printf("%c\n", node->cutType);
    }
}

/*
prints tree in post-order
inputs
    node - root of tree to be printed
*/
void printTree(TreeNode * node){
    if(!node) return;
    printTree(node->left);
    printNode(node);
    printTree(node->right);
}