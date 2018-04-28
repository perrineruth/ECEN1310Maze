#ifndef MAZE_H_
#define MAZE_H_

// file types for maze.c
// maze which is a matrix of the maze itself.
typedef struct _maze maze;
// node in the tree linked list.
typedef struct _node node;
// linked list attempting a path to solve the maze.
typedef struct _tree tree;

maze * newMaze(FILE * mz);
/* creates a maze from a text file.
 * places 0's for spaces as traversable
 * space and 1 everywhere else takes a
 * start at character 's' and ends at 
 * the character 'e'
 * code for each maze value:
 * 0  = space that is still traversable
 * 1  = wall
 * -1 = already explored but not in current path
 * -2 = in current path
 */

void deleteMaze(maze * mz);
// frees the memory stored by maze

int printMaze(maze const * mz);
/* prints the maze in integer form
 * as well as the coordinates of the
 * start and end points
 */
int printPrettyMaze(maze const * mz);
//Calls printMaze in a more User-friendly view.

int * printSol(); // function not yet implemented
// like print maze but nicer form.

tree * plantTree(maze * mz);
/* Makes a tree for the maze solver
 * works as a linked list (LIFO)
 */

int freeTree(tree * tr);
/* frees the nodes in tree as well as the tree itself.
 */

int newNode(int r, int c, tree * tr, maze * mz);
/* makes a new node and adds it to the tree.
 * then sets the new node to -2 in the corresponding
 * location in the maze to say it's in the explored path.
 */

int deleteNode(tree * tr, maze * mz);
/* takes a node from the end of the tree
 * and sets it to -1 in the corresponding maze
 * element (explored but not in current path)
 * and then deletes the node and backtracks.
 */

int stepPath(tree * tr, maze * mz);
/* Checks the last node of the tree FIFO and adds
 * an element or goes back to thhe parent if possible.
 * returns 0 if it did this, 1 if it found a solution,
 * and -1 if it explored all possible locations.
 */

int findSol(tree * tr, maze * mz);
/* A function that continues by stepping through
 * the maze until a solution is found, or until
 * it realizes there is no solution.
 * returns 0 if there is no solution or has bad input
 * or 1 if it found a solution.
 * sets up the maze data to be printed as well.
 */
#endif
