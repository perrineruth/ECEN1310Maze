#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "maze.h"

/* takes the basic format of the matrix struct made in class
 * and adapts it to have either 1's for walls and 0's for
 * traversable space.
 */
struct _maze {
  int rows, cols;
  int * data;
  int start[2], end[2];
};

/* add a node for the tree search of the maze. Has a pointer as 
 * a linked list to the node above, below, to the right, and to
 * the left. Also, has the parent node that made it.
 */
struct _node {
  int row, col;
  node * child;
  node * parent;
};

/* tree LIFO used to solve the maze.
 * doesn't have a head since it only needs the last node.
 */
struct _tree {
  node * tail;
};
  
// same functions from matrix getE and setE (get element & set element)
int getE(maze const * mz, int row, int col) {
  return mz->data[(col-1) * mz->rows + row - 1];
}

void setE(maze * mz, int row, int col, int val) {
  mz->data[(col-1) * mz->rows + row - 1] = val;
}

// not used but it's there in case.
int badArgs(maze const * mz, int row, int col) {
  if (!mz || !mz->data)
    return -1;
  if (row <= 0 || row > mz->rows ||
      col <= 0 || col > mz->cols)
    return -2;
  return 0;
}

/* scans through each row of the maze in order to find the
 * longest row to get the number of columns. Also the number
 * of rows is the same as the number of enters since it adds
 * an enter when saving.
 */
int mazeSize(FILE * mz, int * row, int * col){
  *row = 0; *col = 0;
  int r = 0, c = 0;    // current row and column
  char ch;             // for reading data from file
  while(fscanf(mz, "%c", &ch) != EOF){
    // get next character
    if(ch == '\n'){
      r++;   // on a new row
      c = 0; // at the beginning of the line
    }
    else{
      c++;   // otherwise has found a new column.
      if(c > *col) // check if it is the longest row.
        *col = c;
    }
  }
  if(c != 0)
    r++; // didn't end on a new line.
  // should do this automatically but mostly to verify
  *row = r;
  return 0;
}

// support function to copy over to a new maze from file
int setVals(maze * mz, FILE * fp){
  int r = 1, c = 1; // current row and column
  char ch;
  rewind(fp); // set back to the start of the file.
  while(fscanf(fp, "%c", &ch) != EOF){
    // scan character
    if(ch == '\n'){
      c = 0;
      // will be one with c++ at the end of the loop
      r++;
    }
    else if(ch == 'S' || ch == 's'){
      if(mz->start[0]) 
	// if already found a start
	// can't have 2
	return -1;
      // set a row and column of the start.
      mz->start[0] = r;
      mz->start[1] = c;
      setE(mz, r, c, 2);
    }
    else if(ch == 'E' || ch == 'e'){
      if(mz->end[0])
	// if already found an end
	return -1;
      mz->end[0] = r;
      mz->end[1] = c;
      setE(mz, r, c, 3);
    }
    else if(ch == ' ')
      // found traversable area
      setE(mz, r, c, 0);
    c++;
  }
  // otherwise all values are 1 already if not previously declared
  return 0;
}


maze * newMaze(FILE * fp) {
  int i;
  maze * mz;
  // make a maze
  if(!fp)
    return 0; // null pointer
  /* allocate a maze structure */
  mz = malloc(sizeof(maze));
  if (!mz){
    return NULL;
  }
  /* find the size of the maze file to do rows and columns
   * which also sets the size of rows and columns
   */
  mazeSize(fp, &mz->rows, &mz->cols);

  /* allocate a int array of length rows * cols */
  mz->data = malloc(mz->rows*mz->cols*sizeof(int));
  if (!mz->data) {
    free(mz);
    return NULL;
  }
  /* set all data to 1 */
  for (i = 0; i < (mz->rows)*(mz->cols); i++)
    mz->data[i] = 1;
  if(setVals(mz, fp) || !mz->start[0] || !mz->start[1]
     || !mz->end[0] || !mz->end[1]){
    // if this failed.
    free(mz->data); free(mz);
    printf("Must have exactly one start and one edge\n");
    return 0;
  }
  return mz;
}

void deleteMaze(maze * mz) {
  if (mz) {
    /* free mtx's data */
    free(mz->data);
    /* free mtx itself */
    free(mz);
  }
}

int printMaze(maze const * mz) {
  int row, col;

  if (!mz) return -1;

  for (row = 1; row <= mz->rows; row++) {
    for (col = 1; col <= mz->cols; col++) {
      /* Print the wall as 1 if there's
       * a wall and 0 otherwise.
       * surrounds each number by 2
       * spaces.                        */
      printf(" %d ", getE(mz, row, col));
    }
    /* separate rows by newlines */
    printf("\n");
  }
  // say where it starts and ends.
  printf("starts at row: %d col: %d\n",mz->start[0],mz->start[1]);
  printf("ends at row: %d col: %d\n",mz->end[0],mz->end[1]);
  return 0;
}




// tree functions

tree * plantTree(maze * mz){ //plant a tree... make a forest
  // check for null pointers and allocate data.
  if(!mz) return NULL;
  tree * tr;
  // allocate a tree.
  tr = malloc(sizeof(tree));
  if(!tr) return NULL;
  // allocate a node to be the current tail.
  node * n;
  n = malloc(sizeof(node));
  if(!n) return NULL;
  // set it to be at the start of the maze.
  n->row = mz->start[0];
  n->col = mz->start[1];
  n->parent = 0;
  //set the tree to the tail and return it.
  tr->tail = n;
  return tr;
}

/* Creates a new node in the depth first search
 */
int newNode(int r, int c, tree * tr, maze * mz){
  if(!tr) return 0;
  if(r <= 0 || r <= 0) return 0;
  // allocate the new node.
  node * n;
  n = malloc(sizeof(node));
  if(!n) return 0; // bad allocation
  n->row = r;
  n->col = c;
  //it's parent is the last in the 
  n->parent = tr->tail;
  tr->tail = n;
  setE(mz, r, c, -2); //sets the new element as the current path in the maze as well.
  return 1;
}

/* A function that deletes the node at the end of the
 * tree/LIFO and moves the tail up.
 */
int deleteNode(tree * tr, maze * mz){
  if(!tr) return 0;
  if(!tr->tail) return 0; // in case it tries to free something bad...
  // a node to reference the tail.
  node * n;
  n = tr->tail;
  setE(mz, n->row, n->col, -1); //no longer in the
  // tree goes up one in the list
  tr->tail = n->parent;
  // free the node
  free(n);
  return 1;
}

/* Takes the end of the depth first search.
 * Removes each node from the end and getting 
 * each parent.
 */
int freeTree(tree * tr){
  if(!tr) return 0;
  node * n;
  node * nprev;
  n = tr->tail;
  nprev = n;
  while(n){
    // go up the tree deleting nodes
    n = n->parent;
    free(nprev);
    nprev = n;
  }
  // free the tree now that the nodes are free.
  free(tr);
  return 1;
}
/*
 * Return Value Legend:
 *  0 = Next Step Taken
 * -1 = No Solution
 *  1 = Solution Found!
 */
int stepPath(tree * tr,maze * mz){
  node * n;
  n=tr->tail;
   int N,E,W,S;
  //Obtain Maze values for each direction
  E=getE(mz,n->row,n->col+1);
  S=getE(mz,n->row+1,n->col);
  W=getE(mz,n->row,n->col-1);
  N=getE(mz,n->row-1,n->col);

  //Check for Solution Value
  if(N==3 || E==3 || W==3 || S==3)
    return 1;

  //Check for Open Paths and Follow
  if (!E){ //East
    newNode(n->row,n->col+1,tr,mz);
    return 0;
  }
  if(!S){//South
    newNode(n->row+1,n->col,tr,mz);
    return 0;
  }
  if(!W){//West
    newNode(n->row,n->col-1,tr,mz);
    return 0;
  }
  if(!N){//North
    newNode(n->row-1,n->col,tr,mz);
    return 0;
  }
  
  //If no open paths found
  if(!n->parent) //No parent nodes found. Returned to Start.
    return -1;
  deleteNode(tr,mz);
  return 0;
}
    
int findSol(tree * tr, maze * mz){
  if(!tr || !mz) return 0;
  int n = 0;
  while(!(n = stepPath(tr, mz)));
  // keep stepping the path until there is or isn't a solution
  if(n == 1) return 1; // found a solution
  if(n == -1) return 0; // no solution
  return 0; // unexpected return value...
}
    
