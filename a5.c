#include <stdio.h>
#include <stdlib.h>
#include "post_order.h"

/* usage: ./a5 input.po out_post.txt */
int main(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "usage: %s input.po out_post.txt\n", argv[0]);
        return 1;
    }

    const char *infile = argv[1];
    const char *outpost = argv[2];

    Stack s;
    /* readFile in your tree.c expects char * in some versions; cast to match signature */
    Tree *t = readFile((char *)infile, &s);
    if(!t){
        fprintf(stderr, "Failed to read tree from '%s'\n", infile);
        return 2;
    }

    FILE *fpost = fopen(outpost, "w");
    if(!fpost){
        perror("fopen outpost");
        freeTree(t);
        freeStack(&s);
        return 3;
    }

    writeTree(fpost, t->head);

    fclose(fpost);
    freeTree(t);
    freeStack(&s);
    return 0;
}