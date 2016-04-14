#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"


/* Compare Leaf's coordinates (NOT VALUE) */
static int compare(struct Leaf a, int* bcoord,int bdim){
	int i;
	for(i=0;i<(a.dim>bdim?bdim:a.dim);i++){
		if(a.coord[i]!=bcoord[i]) return a.coord[i]>bcoord[i]?1:-1;
	}
	for(;i<(a.dim>bdim?a.dim:bdim);i++){
		if(a.dim>bdim?a.coord[i]:bcoord[i]!=0)return (a.dim>bdim?1:-1);
	}
	return 0;
}

void deleteTree(struct Leaf* root){
	while(root->right!=NULL || root->left!=NULL){
		if(root->right!=NULL){
			if(root->right->left==NULL && root->right->right==NULL){
				free(root->right->coord);
				free(root->right);
				root->right=NULL;
			}else{
				deleteTree(root->right);
			}
		}
		if(root->left!=NULL){
			if(root->left->left==NULL && root->left->right==NULL){
				free(root->left->coord);
				free(root->left);
				root->left=NULL;
			}else{
				deleteTree(root->left);
			}
		}
	}
}

/* traverse/insert into binary tree*/
struct Leaf* traverse(struct Leaf* root,int* bcoord, int bdim){
	int i;
	if(compare(*root,bcoord,bdim)==0){
		return root;
	}else if(compare(*root,bcoord,bdim)>0){
		if(root->right==NULL){
			/* Create leaf rightwise*/
			root->right = malloc(sizeof(struct Leaf));
			root->right->value=0;
			root->right->coord=malloc(sizeof(int)*bdim);
			/* Hard copy bcoord*/
			for(i=0;i<bdim;i++)root->right->coord[i]=bcoord[i];
			root->right->dim=bdim;
			root->right->right=NULL;
			root->right->left=NULL;
			return root->right;
		}else{
			/* Recurse rightwise*/
			return traverse(root->right,bcoord,bdim);
		}
	}else{
		if(root->left==NULL){
			/* Create leaf leftwise*/
			root->left = malloc(sizeof(struct Leaf));
			root->left->value=0;
			root->left->coord=malloc(sizeof(int)*bdim);
			/* Hard copy bcoord*/
			for(i=0;i<bdim;i++)root->left->coord[i]=bcoord[i];
			root->left->dim=bdim;
			root->left->right=NULL;
			root->left->left=NULL;
			return root->left;
		}else{
			/* Recurse leftwise*/
			return traverse(root->left,bcoord,bdim);
		}
	}
}
