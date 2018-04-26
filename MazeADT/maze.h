#ifndef MAZE_H_
#define MAZE_H_

// file types for maze.c
// maze which is a matrix of the maze itself
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

tree * plantTree(maze * mz);
/* Makes a tree for the maze solver
 * works as a linked list (LIFO)
 */

int newNode(maze * mz, int r, int c, node * parent);
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
#endif
