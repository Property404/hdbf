#ifndef HEADER_OPTIONS
#define HEADER_OPTIONS 1
	/* Define __option_var__ as pointer to the variable declared as
	   the option variable */
#define SET_OPTIONS_VARIABLE(a) int* __option_var__=&a;

	/* return 'n' from options if exists */
#define HAS_OPTION(n) ((int)((*__option_var__)&n))

	/* Remove 'n' from options */
#define RM_OPTION(n) ((HAS_OPTION(n)?*__option_var__^=n:*__option_var__))

	/* Add 'n' to options */
#define ADD_OPTION(n) ((n>0?*__option_var__|=n:RM_OPTION(-n)));


	/* List of possible options 
	   Values are by powers of 2 */
#define OPT_NONE (0)		/* Empty option */
#define OPT_OPTIMIZE (1<<0)	/* Optimize HDBF code before interpreting */
#define OPT_HELP (1<<1)		/* Display help message (do not interpret) */
#define OPT_PUREBF (1<<2)	/* Interpret Brainfuck instead of HDBF */
#define OPT_VER (1<<3)		/* Show version number */
#define OPT_DEBUG (1<<4)	/* Allow debug commands */
#define OPT_STRING (1<<5)	/* Lets argument string run as code instead of file */


	/* Get option from option code */
#define GET_OPTION(n) (\
	n=='h'?OPT_HELP:\
	n=='o'?OPT_OPTIMIZE:\
	n=='b'?OPT_PUREBF:\
	n=='v'?OPT_VER:\
	n=='d'?OPT_DEBUG:\
	n=='i'?OPT_STRING:\
	OPT_NONE)
#endif
