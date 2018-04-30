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
  if(!fp){
    printf("Error reading file\n");
    return 1;}
  maze * m = newMaze(fp); // make the maze
  if(!m){
    printf("Error creating maze\n");
    return 1;}
  fclose(fp);
  tree * tr;
  tr = plantTree(m);
  if(!tr){
    printf("Error creating tree\n");
    return 1;}
  if(!findSol(tr,m)){// try updating maze. If findSol==0, no solution was found.
    assert(printPrettyMaze(m)); 
    printf("No solution found\n");
    return 0;
  }
  //printMaze(m); assert(m); //Prints the maze using maze matrix stored values.
  assert(printPrettyMaze(m)); //Prints a User-friendly version of the maze.
  deleteMaze(m);
  freeTree(tr);
  return 0;
}
