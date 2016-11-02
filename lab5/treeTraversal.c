/* Objective    : Write a program to perform tree traversal
                : Level Order Using Queue data structure
		: Pre-Order,In-order, Post-Order Traversal
		: To find the Height of the given tree.
		
Assumptions     : consider a binary tree structure already given

Author         : Aparna P.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct tnode {
char data;
struct tnode * left;
struct tnode * right;
}TreeNode, *TreeNodePtr;

typedef TreeNodePtr QData ;

#include "queue.h"
#define MaxWordSize 1


TreeNodePtr buildTree(FILE * in) 
{
	char c;
		
	if(feof(in)) return NULL;
	
	fscanf(in, "%c", &c); 
	if(c =='@') return NULL;
	TreeNodePtr p = (TreeNodePtr) malloc(sizeof(TreeNode));
	p->data=c;
	p->left = buildTree(in);
	p->right = buildTree(in);
	return p;
} //end buildTree




void levelOrder(TreeNodePtr root){
	// Edit the queue.h file
	// Complete the Level Order Traversal using the Queue Data structure.
	// Print the node data in Level Order. 	
	QPtr tempQ = initQ();
	TreeNodePtr tempNode;
	tempNode = root;
	while(tempNode!=NULL){
		printf("%c ",tempNode->data);
		if(tempNode->left!=NULL)
			enqueue(tempQ,tempNode->left);
		if(tempNode->right!=NULL)
			enqueue(tempQ,tempNode->right);
		if(!isEmpty(tempQ))
			tempNode = dequeue(tempQ);
		else 
			tempNode=NULL;
		}
		
}//end level order 


void preOrder(TreeNodePtr root) 
{
	//Perform pre-order traversal to print the data.
	if(root==NULL)
		return;
	printf("%c ",root->data);
	preOrder(root->left);
	preOrder(root->right);
} //end pre-order




void inOrder(TreeNodePtr root) 
{
	//Perform In-order traversal to print the data.
	if(root==NULL)
                return;
        inOrder(root->left);
        printf("%c ",root->data);
	inOrder(root->right);

} //end In-order


void postOrder(TreeNodePtr root) 
{
	if(root==NULL)
                return;
        postOrder(root->left);
        postOrder(root->right);
	printf("%c ",root->data);
	//Perform pre-order traversal to print the data.
} //end pre-order


int findHeight(TreeNodePtr root)
{
	if(root==NULL)return -1;
	int left = findHeight(root->left);
	int right = findHeight(root->right);
	if(left>right)
		return left+1;
	return right+1;
}


int main(int argv, char* argc[]){

	char* infile = argc[1];
	FILE* in = fopen(infile, "r");
	if(in == NULL){
        	printf("Invalid Input File\n");
        	exit(1);
    	}
    

	TreeNodePtr root=buildTree(in);
	int ht=0;

	printf("\nLevel Order Traversal of the given tree:  \n");

	levelOrder (root);

	printf("\n\nPre-Order Traversal of the given tree:  \n");
	preOrder (root);

	printf("\n\nIn-Order Traversal of the given tree:  \n");
	inOrder (root);

	printf("\n\nPost-Order Traversal of the given tree:  \n");
	postOrder (root);

	printf("\n");

	ht=findHeight(root);
	printf("\n The height of the tree is: %d \n",ht);
	fclose(in);                 // Close the input file
}




