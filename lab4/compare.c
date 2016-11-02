/***********************************************
 *        Compare.c
 * To compare the execution time of Insertion sort and mergesort.
 * The Mergesort function call is commented off
 * Done by 15EC250,15EC251 
 * This is to see if you would actually open this code :)
 * #just_curious
 **********************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void merge_sort(int *A, int N);
void merge_arrays(int *B, int *C, int *A, int Nb, int Nc, int Na);
void insertion_sort(int*A,int N);
int main(int argc, char *argv[]) {
      // The main program has two command line 
      // arguements :- filename that contains the 
      // integer numbers, number of values in the file
	clock_t start,end;
        double CPU_time_used;
      // Check for correct number of command line arguements
      if(argc < 4) {
           fprintf(stderr,"Usage is %s <infile> <N>\n",argv[0]);
           fprintf(stderr,"\t infile - name of the file that contains the numbers\n");
           fprintf(stderr,"\t      N - number of elements in the file\n");
           fprintf(stderr,"\toutfile - output file that stores sorted numbers\n");
           exit(1);
      }
 
     //Assign Command line arguements
     char *infile = argv[1];
     int N = atoi(argv[2]);
     char *outfile = argv[3];
     
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
     // Reading values to the array
     for (i = 0;i<N && !feof(fp) ; ++i)
         fscanf(fp,"%d",a+i);
 
     //close the file
     fclose (fp);

     if(i<N){
         printf("Only %d values are read from file ", i);
         N = i;
     }
     start = clock();
     //merge_sort(a,N);
	insertion_sort(a,N);
     end = clock();
	CPU_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("\nThe time taken for execution = %f\n",CPU_time_used);
     //check the values : Uncomment only for small files
     /*for (i = 0;i<N  ; ++i) {
         printf("a[%d] =%3d\n", i,a[i]);
     }*/
     
     //Write to the output file
     fp = fopen(outfile,"w"); // open output file
     if(fp == NULL) {         // check if the command was successful
           fprintf(stderr,"ERROR: Cannot open file <<%s>> \n",infile);
           exit(1);
     }
     
     //Write sorted values to output file
     for (i = 0;i<N  ; ++i)
         fprintf(fp,"%d\n",a[i]);
     fclose(fp);

     free(a);
}


//------------------------------------------
// This is the recursive merge sort function
// input is the array "a" and its size N 
//------------------------------------------
void merge_sort(int *A, int N){

   if(N<2) return;

   int *B = NULL,*C = NULL;  //Sub arrays for recursive calls
   int i; //loop variable

   //Split array size into two almost equal halves
   // start - (midpnt-1) in B and 
   // midpnt - last value in C
   int midpnt = N/2; // Remember Integer division :) 
   int Nb = midpnt ; // number of elements in B
   int Nc = N - midpnt; // rest of the elements in C
   
   //Nb and Nc are same if N is even
   //else they differ by 1
   B = (int *) malloc(Nb*sizeof(int));
   C = (int *) malloc(Nc*sizeof(int));
   
   //TODO Split the array into two equal halves
   //Copy the first Nb elements to B
   //next Nc elements to C

   for(i=0;i<N;i++){
	if(i<Nb)
		*(B+i) = *(A+i);
	else
		*(C+i-Nb) = *(A+i);
	}

   //TODO Do recursive sorting on arrays B and C
   merge_sort(B,Nb);
   merge_sort(C,Nc);
	
   //Merge those sorted arrays to one
   merge_arrays(B, C, A, Nb, Nc, N);

   free(B);
   free(C);
}

/* 
    The following function merges the sorted 
    arrays B (of size Nb) and C (size Nc) to 
    a single array A 
*/
void merge_arrays(int *B, int *C, int *A, int Nb, int Nc, int Na)
{
     // TODO Complete the code
	int i=0,j=0,k=0;
	while( k<Na && i<Nb && j<Nc){
		if(*(B+i) < *(C+j))
			{
			*(A+k) = *(B+i);
			i++;
			}
		else    {
			*(A+k) = *(C+j);
			j++;
			}
		k++;
	}
	if((i<Nb)&&(j>=Nc))
		for(;i<Nb;i++,k++)
			*(A+k) = *(B+i);
	else if((j<Nc)&&(i>=Nb))
		for(;j<Nc;j++,k++)
			*(A+k) = *(C+j);	 
}
void insertion_sort(int*A,int N){
	int i,j;
	int hole,key;
	for(i=1;i<N;i++){
		hole = i;
		key = A[i];
		while( hole>0 && key<A[hole-1]){
			A[hole] = A[hole-1];
			hole--;
		}
		if(hole!=i)
			A[hole] = key;
	}
}
	
