#include "optimize.h"
#include <string.h>
void optimize(char *code)
{
	unsigned int i;
	for (i = 0; i < strlen(code) - 1; i++) {
		/* Remove any matching pairs */
		if ((code[i] == '+' && code[i + 1] == '-')
		    || (code[i] == '-' && code[i + 1] == '+')
		    || (code[i] == '<' && code[i + 1] == '>')
		    || (code[i] == '>' && code[i + 1] == '<')
		    || (code[i] == '^' && code[i + 1] == 'V')
		    || (code[i] == 'V' && code[i + 1] == '^')) {
			/* Delete unnecessary section */
			strcpy(code + i, code + i + 2);
			/* Go back 1 or 2 places */
			i = i - (i > 0 ? 2 : 1);
		}
	}
}
