/* Objective    : To create Stack package that performs functions

Initialize Stack 	I/P:NIL 			        O/P:StackPtr
Push StackData 		I/P:StackPtr & StackData 	O/P:Void 
Pop Stack 		    I/P:StackPtr 			    O/P:StackData
IsEmpty Stack		I/P:StackPtr			    O/P:int

StackData defined in application.
Author         : Aparna P.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	StackData val;
	struct node * next;
}NodeType, *NodePtr;


typedef struct{
	NodePtr top;
}StackType, *StackPtr;


// Stack will embed the top of stack(top)
StackPtr initStack() {
	StackPtr sp = (StackPtr) malloc(sizeof(StackType));
	sp->top = NULL;
	return sp;
}


int isEmpty(StackPtr sp) {
	return (sp->top == NULL);
}

// To Do
// Complete the push function by creating the node and updating top.
void push(StackPtr sp, StackData data) {
	NodePtr newNode = (NodePtr) malloc(sizeof(NodeType));
	newNode->val = data;
	newNode->next = sp->top;
	sp->top = newNode;
} //end push




//To Do-Peek function returns the value at the top without poping the value 
// Before performing peek check if the stack is empty
StackData peek(StackPtr sp){
	if(sp->top)
		return sp->top->val;
	return ;	
} 

//end peek



//To Do- Pop the value from the stack. free the memory/node after poping
// Before performing pop check if the stack is empty
StackData pop(StackPtr sp) {
	if(sp->top == NULL){
		return ;
	}
	else{
		NodePtr poppedNode = sp->top;
		StackData poppedData = poppedNode->val;
		sp->top = poppedNode->next;
		free(poppedNode);
		return poppedData;
	}
} //end pop




