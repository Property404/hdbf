#include "optimize.h"
#include <string.h>
void optimize(char *code)
{
	unsigned int i;
	for (i = 0; code[i] != 0; i++) {
		/* Remove any matching pairs */
		if ((code[i] == '+' && code[i + 1] == '-')
		    || (code[i] == '-' && code[i + 1] == '+')
		    || (code[i] == '<' && code[i + 1] == '>')
		    || (code[i] == '>' && code[i + 1] == '<')
		    || (code[i] == '^' && code[i + 1] == 'V')
		    || (code[i] == 'V' && code[i + 1] == '^')) {

			/* Delete unnecessary section */
			unsigned int j;
			unsigned int len = strlen(code + i + 2);
			for (j = 0; j < len; j++)
				code[j + i] = code[j + i + 2];
			code[j + i] = 0;

			/* Go back 1 or 2 places */
			i -= (i > 0 ? 2 : 1);
		}
	}
}
