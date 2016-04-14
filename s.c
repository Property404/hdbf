#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

#define inc_dpointer if((++dpointer)>=dim)coord=realloc(coord,++dim)
#define dec_dpointer --dpointer
#define inc_wpointer wpointer++;coord[dpointer]=wpointer;cell=traverse(root,coord,dim)
#define dec_wpointer --wpointer;coord[dpointer]=wpointer;cell=traverse(root,coord,dim)
#define inc_cell cell->value++
#define dec_cell cell->value--
#define out_cell printf("%c",cell->value)


void run(const char* code){
	/* Set up interpretation variables */
	int wpointer=0;/* world pointer */
	int dpointer=0;/* dimensional pointer */
	int dim=1; /* Number of dimensions working with*/
	int* coord=malloc(dim);coord[dim-1]=0; /* current coordinates*/
	int* loopqueue=malloc(0);/* loop list*/
	char* buffer=malloc(1);//So it doesn't fail on `free`
	int loops=0; /* Number of loops*/
	int offness=-1;//Indicates offness (value is -1 or location of loop)
	
	/* Set up binary tree */
	struct Leaf* root=malloc(sizeof(struct Leaf));
	root->right=NULL;
	root->left=NULL;
	root->value=0;
	root->coord=malloc(dim);root->coord[0]=0;
	root->dim=dim;
	struct Leaf* cell=root;
	
	/* Start interpretation */
	unsigned int i;int v;
	for (i=0;i<strlen(code);i++){
		if(offness==-1 || code[i]==']' || code[i]=='['){
			switch(code[i]){
				case '[':
					// Increment size of loop queue
					loops++;
					
					// Safely reallocate memory
					buffer=realloc(loopqueue,loops*sizeof(int));
					if(buffer==NULL){
							fprintf(stderr,"Memory allocation error\n");
							exit(1);
					}
					memcpy(buffer,loopqueue,(loops-1)*sizeof(int));
					loopqueue=malloc(loops*sizeof(int));
					memcpy(loopqueue,buffer,loops*sizeof(int));
					loopqueue[loops-1]=i;

					// Check if need to turn off
					if(offness==-1 && cell->value==0){
						offness=i;
					}
					break;
				case ']':
					// Store last loopqueue value before deleting it
					v = loopqueue[loops-1];
					
					// Delete last loopqueue value
					loops--;
					buffer=realloc(loopqueue,loops);
					memcpy(buffer,loopqueue,sizeof(int)*loops);
					loopqueue=malloc(sizeof(int)*loops);
					memcpy(loopqueue,buffer,sizeof(int)*loops);
					
					// Turn on if necessary
					if(offness!=-1){
						if(offness==v)offness=-1;
					}else{
						// Go back to matching `[`
						i=v-1;
					}
					break;
				case '+':
					inc_cell;
					break;
				case '-':
					dec_cell;
					break;
				case '^':
					inc_dpointer;
					break;
				case 'V':
					dec_dpointer;
					break;
				case '>':
					inc_wpointer;
					break;
				case '<':
					dec_wpointer;
					break;
				case '.':
					out_cell;
					break;
			}
		}
	}
	printf("\nCoordinates{");
	for(signed i=0;i<dim;i++){printf("%s%d",(i==0?"":","),coord[i]);}
	printf("}\n");
	/*Free stuff*/
	free(coord);
	free(loopqueue);
	free(buffer);
	/*TODO: delete binary tree*/
}

int main(){
	run("^++++++++++>---^--->>>VV>++++++++[-<+++++++++>]<.>>+>-[+]++>++>+++[>[->+++<<+++>]<<]>-----.>->+++..+++.>-.<<+[>[+>+]>>]<--------------.>>.+++.------.--------.>+.>+.");
	return 0;
}