#include <stdio.h>
#include <stdlib.h>
#include "coordinates.h"

/* usage: ./a5 input.po out_post.txt */
int main(int argc, char **argv){
    if(argc != 5){
        fprintf(stderr, "usage: %s input.po out_post.txt dim.txt\n", argv[0]);
        return 1;
    }

    // retrieve filenames from command line arguments
    const char *infile = argv[1];
    const char *outpost = argv[2];
    const char *outdim = argv[3];
    const char *outcoord = argv[4];

    Stack s;
    /* readFile in your tree.c expects char * in some versions; cast to match signature */
    Tree *t = readFile((char *)infile, &s);
    if(!t){
        fprintf(stderr, "Failed to read tree from '%s'\n", infile);
        return 2;
    }
    // write the post-order traversal to outpost
    FILE *fpost = fopen(outpost, "w");
    if(!fpost){
        perror("fopen outpost");
        freeTree(t);
        freeStack(&s);
        return 3;
    }
    writeTree(fpost, t->head);
    fclose(fpost);

    // write the dimensions to outdim
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

    // write the coordinates to outcoord
    FILE * fcoord = fopen(outcoord, "w");
    if(!fcoord){
        perror("fopen outcoord");
        freeTree(t);
        freeStack(&s);
        return 5;
    }
    printAllCoords(t->head, fcoord);
    fclose(fcoord); 

    freeTree(t);
    freeStack(&s);
    return 0;
}