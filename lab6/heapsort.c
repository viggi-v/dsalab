/* Assignment 6 : Heap Sort to extract the largest N numbers

AUTHORS : 15EC250, 15EC251
DATE : 5-10-2015

*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PARENT(i) ((i-1)>>1)
#define LEFT(i) ((i<<1)+1)
#define RIGHT(i) ((i<<1)+2)

void build_heap(int *A, int N);
void fix_root_violation(int *A, int i, int N);
int extract_max(int *A,  int *N);
//void swap(int*a,int*b);
int main(int argc, char *argv[]) {
      // The main program has two command line 
      // arguements :- filename that contains the 
      // integer numbers, number of values in the file

      // Check for correct number of command line arguements
      if(argc < 5) {
           fprintf(stderr,"Usage is %s <infile> <N> <r> \n",argv[0]);
           fprintf(stderr,"\t infile - file containing the numbers\n");
           fprintf(stderr,"\t      N - number of elements in the file\n");
           fprintf(stderr,"\t      r - number of max values required\n");
           fprintf(stderr,"\toutfile - output file stores order statistics\n");
           
           exit(1);
      }
 
     //Assign Command line arguements
     char *infile = argv[1];
     int N = atoi(argv[2]);
     int r = atoi(argv[3]);
     char *outfile = argv[4];
     int j;
     //Read Input File 
     int *a = NULL ; //Array to store values read from the file
     FILE *fp = fopen(infile,"r"); //Open input file
     if(fp == NULL) {             //check if opening was successful
           fprintf(stderr,"ERROR: Cannot open file <<%s>> \n",infile);
           exit(1);
     }
     //allocating memory to read the values
     a = (int*) malloc(N*sizeof(int));
     
     int i = 0;
     // Reading values to he array
     for (i = 0;i<N && !feof(fp) ; ++i)
         fscanf(fp,"%d",a+i);
 
     //close the file
     fclose (fp);

     if(i<N){
         printf("Only %d values are read from file ", i);
         N = i;
     }

     //Build the heap out of the array
     build_heap(a,N);
     
     //Write to the output file
     fp = fopen(outfile,"w"); // open output file
     if(fp == NULL) {         // check if the command was successful
           fprintf(stderr,"ERROR: Cannot open file <<%s>> \n",outfile);
           exit(1);
     }
     
     //Write sorted values to output file
     for (i = 0; i <r ; ++i )
           fprintf(fp,"%d\n",extract_max(a,&N));
/*	printf("The heap is :\n ");
	for(i=0;i<N;i++)
		printf("%d, ",a[i]);
	printf("\nThe sorted array is:\n");
	for(i=0;i<r;i++)
		printf("%d, ",extract_max(a,&N));
*/
     fclose(fp);
     free(a);
}

void swap(int*a,int*b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
/* 
   Fixes one violation that is on the root 
   fix the problem at the current node and 
   try to propagate it downwards`
*/
void fix_root_violation(int *A, int i, int N)
{	
	int max = i;
	//i is the position to be fixed 
	//N is the size of the heap
	if(i<=(N-1)/2 && LEFT(i)<N && A[LEFT(i)]>A[i]){
		//swap(&A[LEFT(i)],&A[i]);
		max = LEFT(i);
		//fix_root_violation(A,LEFT(i),N);
	}
	if(i<=(N-1)/2 && RIGHT(i)<N && A[RIGHT(i)]>A[max] ){
		//swap(&A[RIGHT(i)],&A[i]);
		max = RIGHT(i);
		//fix_root_violation(A,RIGHT(i),N);
	}
	if(max!=i){
		int temp = A[max];
		A[max] = A[i];
		A[i] = temp;
		fix_root_violation(A,max,N);
	}
	//int max = A[RIGHT(i)]>A[LEFT(i)]?RIGHT(i):LEFT(i);
}

/*
  The function builds the heap. 
  Basically you need to call the 
  fix root violation iteratively 
  (typically in a for loop) 
*/
void build_heap(int *A, int N)
{
	int temp = (N-1)/2;
	while(temp+1){
		fix_root_violation(A,temp,N);
		temp--;
	}
}

/* We need to intelligently eliminate 
   the max value.   Remove one value 
   also means reduce the size of the 
   heap N.   So reduce the value of 
   N by one 

   Remember to return the max val 
   from the function
*/
int extract_max(int *A,  int *N)
{
	int swap_pos = (*N)-1;
//	int max = A[0];
//	swap(&A[0],&A[swap_pos]);
	int temp = A[0];
	A[0] = A[swap_pos];
	A[swap_pos] = temp;
	(*N)--;
	fix_root_violation(A,0,*N);
	return temp;
}
