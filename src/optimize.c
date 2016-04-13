#include "optimize.h"
#include <string.h>
#include <stdio.h>
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
			unsigned int j;
			unsigned int l=strlen(code+i+2);
			for(j=0;j<l;j++)
				code[j+i]=code[j+i+2];
			code[j+i]=0;
			/* Go back 1 or 2 places */
			i = i - (i > 0 ? 2 : 1);
		}
	}
}
