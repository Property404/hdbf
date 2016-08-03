#ifndef HEADER_BINARYTREE
#define HEADER_BINARYTREE 1
/*
	The HDBF World is represented as a binary tree
	Each cell is a node/leaf in the tree(referred to as "World")
	The first cell is referred to as "root"(relative term)
*/

struct Cell {
	struct Cell *right;
	struct Cell *left;
	char value;		/* Value of cell */
	int *coord;		/* List of coordinates */
	int dim;		/* # Of coordinates. should be AT LEAST 1 */
};

/* Find matching cell, make new one if it doesn't exist */
struct Cell *traverseWorld(struct Cell *root, int *bcoord, int bdim);

/* Free entire world except root */
void deleteWorld(struct Cell *root);
#endif
