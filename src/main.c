/*
hdbf - Hyper-Dimensional Brainfuck interpreter
Copyright (C) 2016 Dagan Martinez

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "hdbf.h"
#include "optimize.h"
#include "options.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define HDBF_VERSION "hdbf 1.3 (nonrelease-commit7)"
#define HDBF_USAGE "Usage: hdbf [options] [filename | -i cmd]\n"

int main(int argc, char *argv[])
{
	/* File Variables */
	char *filename = "";
	int filename_set = 0;

	/* Prepare options variables */
	int options = 0;
	SET_OPTIONS_VARIABLE(options);

	/* Parse arguments */
	if (argc <= 1) {
		/* No arguments */
		fprintf(stderr, "hdbf: no arguments\n" HDBF_USAGE);
		return EXIT_FAILURE;
	} else {
		int i, j;

		/* Look through arguments */
		for (i = 1; i < argc; i++) {
			if ((argv[i])[0] == '-') {
				/* Check for valid options */
				for (j = 1; argv[i][j] != '\0'; j++) {
					int new_option =
					    GET_OPTION(argv[i][j]);
					if (new_option == OPT_NONE) {
						/* Check if "--h[elp]" or "--v[ersion]" */
						if (argv[i][j] == '-'
						    && (argv[i][j + 1] ==
							'h'
							|| argv[i][j +
								   1] ==
							'v')) {
							ADD_OPTION
							    (GET_OPTION
							     (argv[i]
							      [j + 1]));
							break;
						} else {
							/* Option is invalid, abort */
							fprintf(stderr,
								"hdbf: no option `%c`\n",
								argv[i]
								[j]);
							return
							    EXIT_FAILURE;
						}
					}

					ADD_OPTION(new_option);
				}
			}

			else {
				/* Set file name */
				filename =
				    malloc(sizeof(char) *
					   (1 + strlen(argv[i])));
				for (j = 0; (argv[i])[j] != '\0'; j++)
					filename[j] = (argv[i])[j];
				filename[j] = '\0';
				filename_set = 1;
				break;
			}
		}
	}
	if (HAS_OPTION(OPT_HELP)) {
		printf(HDBF_USAGE "\n"
		       "Options:\n"
		       "\t-b\tRun regular Brainfuck\n"
		       "\t-d\tAllow debugging commands\n"
		       "\t-h\tPrint help message\n"
		       "\t-i cmd\tPass string as code\n"
		       "\t-o\tOptimize before running\n"
		       "\t-v\tDisplay version number\n");
	} else if (HAS_OPTION(OPT_VER)) {
		/* Print out version number */
		printf(HDBF_VERSION "\n");
	} else if (HAS_OPTION(OPT_STRING)) {
		/* Interpret from argument */
		if (filename_set) {
			if (HAS_OPTION(OPT_OPTIMIZE)) {
				optimize(filename, options);
			}
			run(filename, options);
		} else {
			fprintf(stderr, "hdbf: no command\n" HDBF_USAGE);
			return EXIT_FAILURE;
		}
	} else if (filename_set) {
		/* Open file for reading */
		FILE *fp;
		int fp_size;
		char *fp_contents;
		fp = fopen(filename, "rb");
		/* Check for errors */
		if (fp == NULL) {
			fprintf(stderr,
				"hdbf: file \"%s\" not found\n", filename);
			free(filename);
			return EXIT_FAILURE;
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
			optimize(fp_contents, options);
		}
		run(fp_contents, options);
		/* Free everything */
		free(fp_contents);
	} else {
		fprintf(stderr, "hdbf: no input files\n" HDBF_USAGE);
		return EXIT_FAILURE;
	}

	/* Finish */
	if (filename_set)
		free(filename);
	return EXIT_SUCCESS;
}

