#include <stdio.h>
#include <stdlib.h>
#include "dimensions.h"

/* usage: ./a5 input.po out_post.txt */
int main(int argc, char **argv){
    if(argc != 4){
        fprintf(stderr, "usage: %s input.po out_post.txt dim.txt\n", argv[0]);
        return 1;
    }

    const char *infile = argv[1];
    const char *outpost = argv[2];
    const char *outdim = argv[3];

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

    FILE *fdim = fopen(outdim, "w");
    if(!fdim){
        perror("fopen outdim");
        freeTree(t);
        freeStack(&s);
        return 4;
    }
    int width = 0, height = 0;
    writePostTree(fdim, t->head, &width, &height);
    fclose(fdim);

    freeTree(t);
    freeStack(&s);
    return 0;
}