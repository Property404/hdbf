#ifndef HEADER_BINARYTREE
#    define HEADER_BINARYTREE 1
/* Binary tree node */
struct Leaf {
	struct Leaf *right;
	struct Leaf *left;
	char value;
	int *coord;		/* List of coordinates */
	int dim;		/* # Of coordinates. should be AT LEAST 1 */
};

/* Find matching leaf, make new one if it doesn't exist*/
struct Leaf *traverse(struct Leaf *root, int *bcoord, int bdim);

/* Free entire tree*/
void deleteTree(struct Leaf *root);
#endif
