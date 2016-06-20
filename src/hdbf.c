#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdbf.h"
#include "binarytree.h"
#include "options.h"

void run(const char *code, int options)
{
	/* Set up interpretation variables */
	unsigned int dpointer = 0;	/* dimensional pointer */
	unsigned int dim = 1;	/* Number of dimensions working with */
	int *coord = malloc(sizeof(int) * dim);	/* current coordinates */
	int *loopqueue = malloc(sizeof(int));	/* loop list */
	char *buffer = malloc(sizeof(char));	/* alloc now so it doesn't fail on `free` */
	int loops = 0;		/* Number of loops */
	int offness = -1;	/* Indicates offness (value is -1 or location of loop) */

	/* World variables */
	struct Cell *root = malloc(sizeof(struct Cell));
	struct Cell *cell = root;

	/* Loop and temporary variables */
	unsigned int i;
	unsigned int v;

	/* Performance enhancing variables */
	int com_buffer = 0;	/* Command buffer */

	/* Set up options */
	SET_OPTIONS_VARIABLE(options);

	/* Set initial coordinates */
	coord[0] = 0;

	/* Set up binary tree */
	root->right = NULL;
	root->left = NULL;
	root->value = 0;
	root->coord = malloc(sizeof(int) * dim);
	root->coord[0] = 0;
	root->dim = dim;

	/* Start interpretation */
	for (i = 0; code[i] != '\0'; i++) {
		if (offness == -1 || code[i] == ']' || code[i] == '[') {
			switch (code[i]) {
			case '[':
				/* Increment size of loop queue */
				loops++;

				/* Safely reallocate memory */
				free(buffer);
				buffer = malloc(loops * sizeof(int));
				if (buffer == NULL) {
					fprintf(stderr,
						"hdbf: runtime error: memory allocation error\n");
					exit(EXIT_FAILURE);
				}
				memcpy(buffer, loopqueue,
				       (loops - 1) * sizeof(int));
				free(loopqueue);
				loopqueue = malloc(loops * sizeof(int));
				memcpy(loopqueue, buffer,
				       loops * sizeof(int));

				/* Error if out of bounds */
				if (loops <= 0) {
					fprintf(stderr,
						"hdbf: runtime error: loops below bounds\n");
					exit(EXIT_FAILURE);
				}

				loopqueue[loops - 1] = i;

				/* Check if need to turn off */
				if (offness == -1 && cell->value == 0) {
					offness = i;
				}
				break;
			case ']':
				/* Store last loopqueue value before deleting it */
				v = loopqueue[loops - 1];

				/* Delete last loopqueue value */
				loops--;
				free(buffer);
				buffer = malloc(sizeof(int) * loops);
				memcpy(buffer, loopqueue,
				       sizeof(int) * loops);
				free(loopqueue);
				loopqueue = malloc(sizeof(int) * loops);
				memcpy(loopqueue, buffer,
				       sizeof(int) * loops);

				/* Turn on if necessary */
				if (offness != -1) {
					if (offness == (signed) v)
						offness = -1;
				} else {
					/* Go back to matching `[` */
					i = v - 1;
				}
				break;
			case '+':
				/* Increase value of cell */
				com_buffer = 1;
				while (code[i + 1] == '+') {
					com_buffer++;
					i++;
				}
				cell->value += com_buffer;
				break;
			case '-':
				/* Decrease value of cell */
				com_buffer = 1;
				while (code[i + 1] == '-') {
					com_buffer++;
					i++;
				}
				cell->value -= com_buffer;
				break;
			case '^':
				if (!HAS_OPTION(OPT_PUREBF)) {
					/* Increase dimensional pointer */
					if ((++dpointer) >= dim) {
						dim++;
						free(buffer);
						buffer =
						    malloc(sizeof(int) *
							   dim);
						for (v = 0; v < dim; v++) {
							buffer[v] =
							    coord[v];
						}
						free(coord);
						coord =
						    malloc(sizeof(int) *
							   dim);
						for (v = 0; v < dim; v++) {
							coord[v] =
							    buffer[v];
						}
						coord[dim - 1] = 0;
					}
				}
				break;
			case 'V':
				/* Decrease dimentional pointer */
				if (!HAS_OPTION(OPT_PUREBF)) {
					--dpointer;
				}
				break;
			case '>':
				com_buffer = 1;
				while (code[i + 1] == '>') {
					com_buffer++;
					i++;
				}
				/* Go in positive direction of current vector */
				coord[dpointer] += com_buffer;
				cell = traverseWorld(root, coord, dim);
				break;
			case '<':
				com_buffer = 1;
				while (code[i + 1] == '<') {
					com_buffer++;
					i++;
				}
				/* Go in negative direction of current vector */
				coord[dpointer] -= com_buffer;
				cell = traverseWorld(root, coord, dim);
				break;
			case '.':
				putchar(cell->value);
				break;
			case ',':
				cell->value = getchar();
				break;
			case '?':
				/* Print out coordinates if debugging is on */
				if (HAS_OPTION(OPT_DEBUG)) {
					printf("[(");
					for (v = 0; v < dim; v++) {
						printf("%d%c", coord[v],
						       (v ==
							dim -
							1) ? ')' : ',');
					}
					printf("]\n");
				}
				break;
			case '#':
				/* Print out cell if debugging is on */
				if (HAS_OPTION(OPT_DEBUG)) {
					printf("{(");
					for (v = 0;
					     v < (unsigned) (cell->dim);
					     v++) {
						printf("%d%c",
						       cell->coord[v],
						       (v == (unsigned)
							(cell->dim -
							 1)) ? ')' : ',');
					}
					printf("=%d}\n", cell->value);
				}
				break;
			}
		}
	}

	/* Free stuff */
	deleteWorld(root);
	free(root->coord);
	free(root);
	free(coord);
	free(loopqueue);
	free(buffer);
}
