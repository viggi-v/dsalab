/* Assignment 4 - Infix to Postfix conversion using Stack
  done by 15EC250, 15EC251     
  ===========================================================
*/ 
#include <stdio.h>
#include <stdlib.h>

// only symbols are to pushed to the stack.
typedef char StackData ;

#include "stack.h"


int precedence(char c)
{
   if(c=='#') return -1;
   if(c=='(') return 0;
   if(c=='+' || c== '-') return 3;
   if(c=='*' || c== '/') return 5;
}

int isInteger(char ch){
	if(ch>='0'&& ch<='9'){
		return (int)ch-'0';
	}
	return -1;
}
int isOperator(char ch){
	switch(ch){
		case '+' : 
		case '-' : 
		case '/' : 
		case '*' : return 1;
		default : return 0;
	}
}
void print_stack(StackPtr sp){
	printf("The stack is:\n");
	while(!isEmpty(sp)){
		printf("%c ",pop(sp));
	}
}
StackPtr reverse(StackPtr sp){
	StackPtr ans = initStack();
	while(isEmpty(sp)){
		push(ans,pop(sp));
	}
	return ans;
}
int main(int argv, char* argc[]){
	char* infile = argc[1];
    	FILE* IN = fopen(infile, "r");
   	if(IN == NULL){
        	printf("Invalid Input File\n");
        	exit(1);
    	}
	    
    	char c,post[100],dump;
    	char * cp;	
    	cp=post;
    	int len, res;

   	StackPtr sp=initStack();
	StackPtr temp = initStack(); 
    	push(temp,'#');
	c = fgetc(IN);
    
	int i=0;
    	// Read character-by-character
   	while(!feof(IN)){
        	if(c == ' ' || c == '\r' || c == '\n'); // Do nothing
	
	//To Do: Complete the logic for infix to PostFix conversion using stack
        // ------------------------------------------------
		if(c=='('){
			push(temp,c);
		}
		else if(c==')'){
			while(peek(temp)!='('){
				push(sp,pop(temp));
	
			}
			
			dump = pop(temp);
		}
        	else if(isInteger(c)!=-1){
			push(sp,c);
			
		} 
		else if(isOperator(c)){
			while(precedence(peek(temp))>=precedence(c)){
				push(sp,pop(temp));
				
			}
			push(temp,c);
		}           

        // -----------------------------------------------
	c = fgetc(IN);
   	}//end while

	while(!isEmpty(temp))
		push(sp,pop(temp));
	dump = pop(sp);

	
	print_stack(sp);


//To print the postfix expression from char array. 
//len is to be obtained from previous loop

    /*printf("\n The postfix expresion is  \n");            
    for(i=0;i<len;i++)
	printf("%c",cp[i]);
     printf("\n");
	*/

    fclose(IN);
}

