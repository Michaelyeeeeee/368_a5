#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "post_order.h"

void writePostNode(FILE * out, TreeNode * node, int * width, int * height);

void writePostTree(FILE * out, TreeNode * node, int * width, int * height);