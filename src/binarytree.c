#include <stdlib.h>
#include "binarytree.h"

/* Compare Leaf's coordinates (NOT VALUE) */
static int compare(struct Cell a, int *bcoord, int bdim)
{
	int i;

	/* Compare up to the first zero */
	for (i = 0; i < (a.dim > bdim ? bdim : a.dim); i++) {
		if (a.coord[i] != bcoord[i]) {
			return (a.coord[i] > bcoord[i]) ? 1 : -1;
		}
	}

	/* Compare from the first zero onwards */
	for (; i < (a.dim > bdim ? a.dim : bdim); i++) {
		if ((a.dim > bdim ? a.coord[i] : bcoord[i]) != 0) {
			return ((a.dim > bdim) ? 1 : -1);
		}
	}
	return 0;
}

void deleteWorld(struct Cell *root)
{
	/* Keep deleting until all leaves are gone
	 ** Does not delete root */
	while (root->right != NULL || root->left != NULL) {
		if (root->right != NULL) {
			if (root->right->left == NULL
			    && root->right->right == NULL) {
				/* Delete leaf to the right */
				free(root->right->coord);
				free(root->right);
				root->right = NULL;
			} else {
				/* Traverse starting at right */
				deleteWorld(root->right);
			}
		}
		if (root->left != NULL) {
			if (root->left->left == NULL
			    && root->left->right == NULL) {
				/* Delete leaf to the left */
				free(root->left->coord);
				free(root->left);
				root->left = NULL;
			} else {
				/* Traverse starting at left */
				deleteWorld(root->left);
			}
		}
	}
}

/* traverse/insert cell into world */
struct Cell *traverseWorld(struct Cell *root, int *bcoord, int bdim)
{
	int i;
	int difference = compare(*root, bcoord, bdim);
	if (difference == 0) {
		return root;
	} else if (difference > 0) {
		if (root->right == NULL) {
			/* Create leaf rightwise */
			root->right = malloc(sizeof(struct Cell));
			root->right->value = 0;
			root->right->coord = malloc(sizeof(int) * bdim);
			/* Hard copy bcoord */
			for (i = 0; i < bdim; i++)
				root->right->coord[i] = bcoord[i];
			root->right->dim = bdim;
			root->right->right = NULL;
			root->right->left = NULL;
			return root->right;
		} else {
			/* Recurse rightwise */
			return traverseWorld(root->right, bcoord, bdim);
		}
	} else {
		if (root->left == NULL) {
			/* Create cell leftwise */
			root->left = malloc(sizeof(struct Cell));
			root->left->value = 0;
			root->left->coord = malloc(sizeof(int) * bdim);
			/* Hard copy bcoord */
			for (i = 0; i < bdim; i++)
				root->left->coord[i] = bcoord[i];
			root->left->dim = bdim;
			root->left->right = NULL;
			root->left->left = NULL;
			return root->left;
		} else {
			/* Recurse leftwise */
			return traverseWorld(root->left, bcoord, bdim);
		}
	}
}
