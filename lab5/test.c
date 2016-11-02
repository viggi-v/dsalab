#include<stdio.h>

typedef char QData;

#include "queue.h"

void main(){
	QPtr myQ = initQ();
	printf("Initially is it empty? %s\n",isEmpty(myQ)?"yup!":"nope!");
	enqueue(myQ,'a');
	enqueue(myQ,'b');
	enqueue(myQ,'c');
	printf("\nThe contents now are:\t");
	while(!isEmpty(myQ)){
		printf("%c,",dequeue(myQ));
	}
}
