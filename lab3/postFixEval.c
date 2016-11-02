// Assignment 4 - Postfix Evaluation
// Objective : Evaluate a postfix expression using Stack
//              
//===========================================================
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef int StackData ;

#include "stack.h"

int main(int argv, char* argc[]){
    char* infile = argc[1];
    FILE* IN = fopen(infile, "r");
    if(IN == NULL){
        printf("Invalid Input File\n");
        exit(1);
    }
    
    char c;
    int a, b;

// initialze the stack and the stack pointer

   StackPtr sp=initStack();

    c = fgetc(IN);

    // Read characters one-by-one
    while(!feof(IN)){
        if(c == ' ' || c == '\r' || c == '\n'); // Do nothing
	
	else if(isdigit(c)){
		//printf("It is a digit, %d\n",c-'0');
		push(sp,c-'0');
	}
	else{
		b = pop(sp);
		a = pop(sp);
		//printf("%d%c%d\n",a,c,b);
		switch(c){
			case '+' : push(sp,a+b);
				   break;
			case '-' : push(sp,a-b);
                                   break;
			case '*' : push(sp,a*b);
                                   break;
			case '/' : push(sp,a/b);
                                   break;
		}
		
	}
        c = fgetc(IN);
    } //end while       
   

// Finally stack contains the result. Pop it out
    a = pop(sp);
    printf("final result: %d \n", a);            
    fclose(IN);
}

