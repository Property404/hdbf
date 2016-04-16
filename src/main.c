#include "hdbf.h"
#include "optimize.h"
#include "options.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	/* File Variables */
	char *filename;
	int filename_set = 0;

	/* Prepare options variables */
	int options = 0;
	SET_OPTIONS_VARIABLE(options);

	if (argc <= 1) {
		/* No arguments */
		fprintf(stderr, "hdbf: no arguments");
		exit(1);
	} else {
		int i, j;

		/* Look through arguments */
		for (i = 1; i < argc; i++) {
			if (argv[i][0] == '-') {
				/* Check for valid options */
				for (j = 1; argv[i][j] != '\0'; j++) {
					int new_option =
					    GET_OPTION(argv[i][j]);
					if (new_option == OPT_NONE) {
						/* Option is invalid, abort */
						fprintf(stderr,
							"hdbf: no option `%c`",
							argv[i][j]);
						return 1;
					}
					ADD_OPTION(new_option);
				}
			} else {
				/* Set file name */
				filename =
				    malloc(sizeof(char) * strlen(argv[i]));
				strcpy(filename, argv[i]);
				if (!HAS_OPTION(OPT_HELP))
					filename_set = 1;
				break;
			}
		}
	}
	if (HAS_OPTION(OPT_HELP)) {
		printf("Usage: hdbf [options] filename\n\n"
		       "Options:\n"
		       "\t-h\tPrint help message\n"
		       "\t-o\tOptimize before running\n"
		       "\t-u\tDo not optimize(default)\n"
		       "\t-b\tRun regular Brainfuck\n");
	} else if (filename_set) {
		/* Open file for reading */
		FILE *fp;
		int fp_size;
		char *fp_contents;
		fp = fopen(filename, "rb");

		/* Check for errors */
		if (fp == NULL) {
			fprintf(stderr, "hdbf: file \"%s\" not found\n",
				filename);
			free(filename);
			return 1;
		}

		/* Get size */
		fseek(fp, 0, SEEK_END);
		fp_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		/* Read file */
		fp_contents = malloc((sizeof(char) + 1) * fp_size);
		fp_contents[fp_size] = '\0';	/* Terminate with null */
		fread(fp_contents, 1, fp_size, fp);
		fclose(fp);

		/* Interpret source code */
		if (HAS_OPTION(OPT_OPTIMIZE)) {
			optimize(fp_contents);
		}
		run(fp_contents, options);

		/* Free everything */
		free(fp_contents);
		free(filename);
	} else {
		fprintf(stderr, "hdbf: no input files");
		return 1;
	}

	return 0;
}
