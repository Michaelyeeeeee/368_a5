#include "post_order.h"
/*
prints a single node
inputs
    node - node to be printed
*/
void writeNode(FILE * out, TreeNode * node){
    if(!out || !node) return;
    if(node->cutType == 'L'){
        fprintf(out, "%d(%d,%d)\n", node->label, node->width, node->height);
    } else {
        fprintf(out, "%c\n", node->cutType);
    }
}

/*
prints tree in pre-order
inputs
    node - root of tree to be printed
*/
void writeTree(FILE * out, TreeNode * node){
    if(!out || !node) return;
    writeNode(out, node);
    writeTree(out, node->left);
    writeTree(out, node->right);
}