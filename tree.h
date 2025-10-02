#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    char cut;
    struct Node * left;
    struct Node * right;
} Node;

typedef struct Stack {
    struct Node * head;
} Stack;
