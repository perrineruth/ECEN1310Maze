#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "maze.h"

int main(){
  printf("give the name of a text file\n");
  FILE * fp;
  char str[128];
  if(scanf("%127s", str) != 1)
    printf("Malformed input\n"); // shouldn't get this but here anyways
  fp = fopen(str, "r"); // read designated fileprint
  maze * m = newMaze(fp); // make the maze
  tree * tr;
  tr = plantTree(m);
  findSol(tr,m); // try updating maze
  fclose(fp);
  printMaze(m); assert(m);
  printPrettyMaze(m); assert(m);
  deleteMaze(m);
  freeTree(tr);
  return 0;
}
