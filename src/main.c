#include "hdbf.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc<2){
		/* No arguments*/
		fprintf(stderr,"hdbf: no input file\n");
		exit(1);
	}else{
		/* Open file for reading*/
		FILE* fp;
		int fp_size;
		char* fp_contents;
		fp=fopen(argv[1],"rb");
		
		/* Check for errors*/
		if(fp==NULL){
			fprintf(stderr,"hdbf: <%s> not found\n",argv[1]);
			exit(1);
		}
		
		/* Get size*/
		fseek(fp,0,SEEK_END);
		fp_size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		
		/* Read file*/
		fp_contents=malloc((sizeof(char)+1)*fp_size);
		fp_contents[fp_size]='\0'; /* Terminate with null*/
		fread(fp_contents,1,fp_size,fp);
		fclose(fp);
		
		/* Interpret source code*/
		run(fp_contents);
		
		/* Free source code*/
		free(fp_contents);
	}
	return 0;
}
