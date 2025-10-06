#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TreeNode {
    char cutType;
    int label;
    int width;
    int height;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;

typedef struct StackNode {
    TreeNode * tn;
    struct StackNode * next;
} StackNode;

typedef struct Stack {
    struct StackNode * head;
} Stack;

typedef struct Tree {
    struct TreeNode * head;
} Tree;

void initStack(Stack *s);
void freeStack(Stack *s);
int isEmpty(Stack *s);
StackNode * push(Stack *s, TreeNode *tn);
TreeNode * pop(Stack *s);
TreeNode * createLeafNode(int label, int w, int h);
TreeNode * createCutNode(char cut);

void freeTree(Tree * tree);
void freeTreeNode(TreeNode * node);

Tree * readFile(char * filename, Stack * stack);
