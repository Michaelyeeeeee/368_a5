#include "tree.h"

/*
Converts inputs in file to tree using a stack
inputs 
    filename - name of file
    stack - stack used for creating tree
returns completed tree
*/
Tree * readFile(char * filename, Stack * stack){
    if(!filename || !stack) return NULL;
    FILE *f = fopen(filename, "r");
    if(!f) return NULL;

    initStack(stack);

    char line[10000];
    while(fgets(line, sizeof(line), f) != NULL){
        char *p = line;

        /* if V or H, pop two nodes and create cut node */
        if((p[0] == 'V' || p[0] == 'H')){
            TreeNode * r = pop(stack); /* right subtree */
            TreeNode * l = pop(stack); /* left subtree */
            if(!l || !r){
                /* malformed: push back any popped nodes and cleanup */
                if(r) push(stack, r);
                if(l) push(stack, l);
                fclose(f);
                return NULL;
            }
            TreeNode *node = createCutNode(p[0]);
            if(!node){ fclose(f); return NULL; }
            node->left = l;
            node->right = r;
            push(stack, node);
        } else {
            /* try to parse leaf format: "%d(%d,%d)" */
            int label, w, h;
            // line by line in string line
            int nmatched = sscanf(p, "%d(%d,%d)", &label, &w, &h);
            if(nmatched == 3){
                TreeNode *leaf = createLeafNode(label, w, h);
                if(!leaf){ fclose(f); return NULL; }
                push(stack, leaf);
            } else {
                printf("Malformed line: %s\n", line);
                fclose(f);
                return NULL;
            }
        }
    }

    fclose(f);

    /* After processing, stack should have exactly one TreeNode (the root) */
    TreeNode * root = pop(stack);
    if(!isEmpty(stack)){
        while(!isEmpty(stack)){
            TreeNode *t = pop(stack);
            freeTreeNode(t);
        }
        if(root) freeTreeNode(root);
        return NULL;
    }

    Tree * tree = (Tree *)malloc(sizeof *tree);
    if(!tree){
        freeTreeNode(root);
        return NULL;
    }
    tree->head = root;
    return tree;
}

/*
initializes stack
inputs
    stack - stack of nodes
*/
void initStack(Stack * s){
    if(!s) return;
    s->head = NULL;
}
/*
removes head from stack
inputs
    stack - stack of nodes
returns value of removed head
*/
TreeNode * pop(Stack * s){
    if(!s || !s->head) return NULL;
    StackNode *top = s->head;
    TreeNode *tn = top->tn;
    s->head = top->next;
    free(top);
    return tn;
}

/*
adds node to head of stack
inputs
    stack - stack of nodes
    node - node to be added to stack
returns new stack
*/
StackNode * push(Stack * stack, TreeNode * tn){
    StackNode * node = (StackNode *)malloc(sizeof(StackNode));
    if(!node) return NULL;
    node->tn = tn;
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
int isEmpty(Stack *s){
    return (s == NULL || s->head == NULL);
}

/*
creates leaf node
inputs
    label - label of leaf node
    w - width of leaf node
    h - height of leaf node
*/
TreeNode * createLeafNode(int label, int w, int h){
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    if(!n) return NULL;
    n->cutType = 'L';
    n->label = label;
    n->width = w;
    n->height = h;
    n->left = n->right = NULL;
    return n;
}

/*
creates cut node
inputs
    cut - type of cut (V or H)
*/
TreeNode * createCutNode(char cut){
    if(cut != 'V' && cut != 'H') return NULL;
    TreeNode *n = (TreeNode *)malloc(sizeof(*n));
    if(!n) return NULL;
    n->cutType = cut;
    n->label = 0;
    n->width = n->height = 0;
    n->left = n->right = NULL;
    return n;
}

/*
frees stack
inputs
    stack - stack of nodes
*/
void freeStack(Stack *s){
    if(!s) return;
    StackNode *curr = s->head;
    while(curr){
        StackNode *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    /* do not free the TreeNodes pointed to by stack (they belong to the tree) */
    s->head = NULL;
}

/*
frees tree nodes recursively
inputs
    node - node to be freed
*/
void freeTreeNode(TreeNode * node){
    if(!node) return;
    freeTreeNode(node->left);
    freeTreeNode(node->right);
    free(node);
}

/*
frees entire tree
inputs
    tree - tree to be freed
*/
void freeTree(Tree * tree){
    if(!tree) return;
    freeTreeNode(tree->head);
    free(tree);
}
