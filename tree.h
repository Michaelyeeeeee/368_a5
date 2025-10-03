#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    char val;
    struct StackNode * next;
} StackNode;

typedef struct TreeNode {
    char val;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;

typedef struct Stack {
    struct StackNode * head;
} Stack;

typedef struct Tree {
    struct TreeNode * head;
} Tree;
