#include "tree.h"

/*
Converts inputs in file to tree using a stack
inputs 
    filename - name of file
    stack - stack used for creating tree
returns completed tree
*/
Tree * readFile(char * filename, Stack * stack){
    FILE * f = fopen(filename, 'r');
    if(!f) return;

    Tree * tree = (Tree *)malloc(sizeof(Tree));
    // tracks which node is non number
    Tree * prevLeft = NULL;
    TreeNode * prevRight = NULL;
    char c;
    while(fgets(c, 1, f) != NULL){
        if(c == 'V' || c == 'H'){
            // pop top 2 in stack
            // add popped nodes to tree
            char a = pop(stack); // right node
            char b = pop(stack); // left node
            TreeNode * nodeC = createNode(c); // current node
            // both left and right are numbers
            if(a != 'V' && a != 'H' && b != 'V' && b != 'H'){
                TreeNode * prevRight = createNode(a);
                TreeNode * prevLeft = createNode(b);
                nodeC->left = prevLeft;
                nodeC->right = prevRight;
                prevLeft = NULL;
                prevRight = NULL;
            }
            // right node is number, current node becomes left child of next node
            else if(a != 'V' && a != 'H'){
                TreeNode * prevRight = createNode(a);
                nodeC->left = prevLeft;
                nodeC->right = prevRight;
                prevLeft = nodeC;
                prevRight = NULL;
            }
            // left node is number, current node becomes right child of next node
            else if(b != 'V' && b != 'H'){
                TreeNode * prevLeft = createNode(b);
                nodeC->left = prevLeft;
                nodeC->right = prevRight;
                prevLeft = NULL;
                prevRight = nodeC;
            }
            // both left and right are non numbers, current node becomes right child of next node
            else{
                nodeC->left = prevLeft;
                nodeC->right = prevRight;
                prevLeft = NULL;
                prevRight = nodeC;
            }
            stack->head = push(stack, c);
        }
        else{
            // add node to stack
            stack->head = push(stack, c);
        }
    }
    tree->head = (prevLeft) ? prevLeft : prevRight;
    return tree;
}

/*
removes head from stack
inputs
    stack - stack of nodes
returns value of removed head
*/
char pop(Stack * stack){
    if(!stack->head) return NULL;
    StackNode * next = stack->head->next;
    char val = stack->head->val;
    free(stack->head);
    stack->head = next;
    return val;
}

/*
adds node to head of stack
inputs
    stack - stack of nodes
    node - node to be added to stack
returns new stack
*/
StackNode * push(Stack * stack, char c){
    StackNode * node = (StackNode *)malloc(sizeof(StackNode));
    node->val = c;
    node->next = stack->head;
    stack->head = node;
    return stack->head;
}

/*
checks if stack is empty
inputs
    stack - stack of nodes
returns 0 for empty, 1 for not empty
*/
int isEmpty(Stack * stack){
    if(!stack->head) return 1;
    return 0;
}

TreeNode * createNode(char c){
    TreeNode * node = (TreeNode *)malloc(sizeof(node));
    node->val = c;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void freeStack(Stack * stack){
    if(!stack) return;
    StackNode * curr = stack->head;
    while(curr){
        StackNode * temp = curr->next;
        free(curr);
        curr = temp;
    }
    free(stack);
}
void freeTreeNode(TreeNode * node){
    if(!node) return;
    freeTreeNode(node->left);
    freeTreeNode(node->right);
    free(node);
}

void freeTree(Tree * tree){
    freeTreeNode(tree->head);
    free(tree);
}
