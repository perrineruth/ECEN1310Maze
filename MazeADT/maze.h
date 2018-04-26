#ifndef MAZE_H_
#define MAZE_H_

typedef struct _maze maze;
typedef struct _node node;
typedef struct _tree tree;

maze * newMaze(FILE * mz);
/* creates a maze from a text file.
 * places 0's for spaces as traversable
 * space and 1 everywhere else takes a
 * start at character 's' and ends at 
 * the character 'e'
 */

void deleteMaze(maze * mz);
// frees the memory stored by maze

int printMaze(maze const * mz);
/* prints the maze in boolean form
 * as well as the coordinates of the
 * start and end points
 */

node * initNode(maze * mz);
node * newNode(maze * mz, int r, int c, node * parent);
// makes a new node.
#endif
