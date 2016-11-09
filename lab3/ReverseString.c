/* Objective    : Write a program to perform string reversal using stack
		
Assumptions     : Stack is added as header.

Author         : Aparna P.

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// StackData is used in stack.h
typedef char StackData ;

#include "stack.h"


//To-Do- Complete the function to reverse the string using stack
char * reverseString(char *cp, int count)
{
	printf("In Reverse String fun");
	StackPtr stringStack = initStack();
	char* returnArray = (char*)malloc(count*sizeof(char));
	int i=0;
	while(*cp){
		push(stringStack,*cp);
		cp++;
	}
	printf("Starting to pop");
	//popping
	while(!isEmpty(stringStack)){
		*(returnArray+i) = pop(stringStack);
		printf("popping %d\n",i);
		i++;
	}
	printf("POP Complete");
	return returnArray;
}
int count_str(char*c){
	int i=0;
	while(*c){
		i++;
		c++;	
	}
	return i;
}


int main(){

	char *cp, a;
	char val[100];
	
	cp=val;
	int i=0, count=0;	
   
	printf("\nEnter the string. Terminating char is 0 :\n");

	// Input the charcters or string 
	scanf("%s",cp);	
	count = count_str(cp);	    
	cp = reverseString(cp,count);	
	
	printf("\nReversed string is \n%s",cp);
   	printf("\n") ;
	free(cp);
}



