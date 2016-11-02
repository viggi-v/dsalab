/* Objective    : To create Queue package that performs functions

Initialize Queue  	I/P:NIL 		O/P:QPtr
Enqueue QData 		I/P:QPtr & QData 	O/P:Void 
Dequeue Queue 		I/P:QPtr 		O/P: QData
IsEmpty Queue		I/P:QPtr		O/P:int

QData defined in application.
Author         : Aparna P.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	QData val;
	struct node * next;
}NodeType, *NodePtr;


typedef struct{
	NodePtr front, rear;
}QType, *QPtr;



QPtr initQ() {
	//Complete the function to Initialise Queue
	QPtr newQueue = (QPtr) malloc(sizeof(QType));
	newQueue->front = NULL;
	newQueue->rear  = NULL;
	return newQueue;
}


int isEmpty(QPtr qp) {
	if(qp->front==NULL || qp->rear==NULL)
		return 1;
	else
		return 0;
}


void enqueue(QPtr qp, QData data) {
	NodePtr newNode = (NodePtr) malloc(sizeof(NodeType));
	newNode->val = data;
	newNode->next = NULL;
	if(isEmpty(qp)){
		qp->front = newNode;
		qp->rear  = newNode;
	}
	else{
		qp->rear->next = newNode;
		qp->rear = qp->rear->next;
	}
} //end enqueue


QData dequeue(QPtr qp) {
	if(isEmpty(qp)){
		return NULL;
	}
	else{
		QData temp = qp->front->val;
		NodePtr tempNode = qp->front;
		qp->front = qp->front->next;
		free(tempNode);
		return temp;
	}
} //end dequeue
