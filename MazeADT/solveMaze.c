#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "maze.h"

int main(){
  printf("give the name of a text file\n");
  FILE * fp;
  char str[128];
  if(scanf("%127s", str) != 1)
    printf("Malformed input\n");       // shouldn't get this but here anyways
  fp = fopen(str, "r");                // read designated filename to a pointer
  if(!fp){                             // did not find a file
    printf("Error reading file\n");
    return -1;}
  maze * m = newMaze(fp);              // make the maze
  if(!m){                              // did not make a maze
    printf("Error creating maze\n");
    fclose(fp);                        // free the file pointer before exiting
    return -1;}
  fclose(fp);                          // free the pointer
  tree * tr;
  tr = plantTree(m);                   // make a tree for the maze solver
  if(!tr){
    printf("Error creating tree\n");
    deleteMaze(m);                     // free the matrix fp is already closed
    return -1;}
  if(!findSol(tr,m)){
    // try updating maze. If findSol==0, no solution was found.
    assert(printPrettyMaze(m)); 
    printf("No solution found\n");
    return 0;
  }
  freeTree(tr);
  //printMaze(m); assert(m);           //Prints the maze using maze matrix stored values.
  if(!printPrettyMaze(m)){             //Prints a User-friendly version of the maze.
    deleteMaze(m);
    assert(0);}                        // already found an error just needs to free m first
  return 0;
}
