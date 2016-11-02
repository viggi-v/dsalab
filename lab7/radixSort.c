/* Assignment 7 : Perform radix sort using counting sort

AUTHORS : 
DATE : 

*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void radixSort(int *A, int N);
void countSort(int*, int, int);


int main(int argc, char *argv[]) {
      // The main program has two command line 
      // arguements :- filename that contains the 
      // integer numbers, number of values in the file

      // Check for correct number of command line arguements
      if(argc < 4) {
           fprintf(stderr,"Usage is %s <infile> <N> \n",argv[0]);
           fprintf(stderr,"\t infile - file containing the numbers\n");
           fprintf(stderr,"\t      N - number of elements in the file\n");
           fprintf(stderr,"\toutfile - output file stores order statistics\n");
           
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

	radixSort(a,N);
	printf("done\n");
     //Write to the output file
   	fp = fopen(outfile,"w"); // open output file
     if(fp == NULL) {         // check if the command was successful
           fprintf(stderr,"ERROR: Cannot open file <<%s>> \n",outfile);
           exit(1);
     }
     
     //Write sorted values to output file
     for (i = 0; i <N ; ++i )
           fprintf(fp,"%d\n",a[i]);
     fclose(fp);
     free(a);
}
void countSort(int *A, int n, int exponent){
	int counts[10],i;
	int *answer = (int*)malloc(n*sizeof(int));
	for(i=0;i<10;i++)
		counts[i]=0;
	for(i=0;i<n;i++){
		counts[(A[i]/exponent)%10]++;
	}
	//updating into modified array
	for(i=1;i<10;i++){
		counts[i]+= counts[i-1];
	}
	for(i=n-1;i>=0;i--){
		answer[counts[(A[i]/exponent)%10]-1] = A[i];
		counts[(A[i]/exponent)%10]--;
	}
	for(i=0;i<n;i++){
		A[i] = answer[i];
	}
	free(answer);
}
int maximum(int*a,int n){
	int i=0;
	int max=a[i];
	while(i<n){
		if(max<a[i])
			{	
			max=a[i];
			}	
		i++;
	}
	return max;	
}
void radixSort(int *A, int n)
{
	int max = maximum(A,n);
	int i;
	printf("Calling countSort\n");
	for(i=1;max/i>0;i*=10){
		countSort(A,n,i);
	}
}

 

