#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int rselect(int A[], int l, int r, int m); 
int partition(int A[], int l, int r); 

int sign(int x) {
    return (x > 0) - (x < 0);
}

int main(int argc, char *argv[]) {
      // The main program has two command line 
      // arguements :- filename that contains the 
      // integer numbers, number of values in the file

      // Check for correct number of command line arguements
      if(argc < 4) {
           fprintf(stderr,"Usage is %s <infile> <N> <outfile>\n",argv[0]);
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
     // Reading values to he array
     for (i = 0;i<N && !feof(fp) ; ++i)
         fscanf(fp,"%d",a+i);
 
     //close the file
     fclose (fp);

     if(i<N){
         printf("Only %d values are read from file ", i);
         N = i;
     }

     int m = (N+1)/2;
	printf("Median index is:%d\n",m-1);
     
	int med = rselect(a,0,N-1,m);
     //check the values : Uncomment only for small files
     /*
     for (i = 0;i<N  ; ++i) {
         printf("a[%d] =%3d\n", i,a[i]);
     }
     */
     
     //Write to the output file
     fp = fopen(outfile,"w"); // open output file
     if(fp == NULL) {         // check if the command was successful
           fprintf(stderr,"ERROR: Cannot open file <<%s>> \n",infile);
           exit(1);
     }
     
     //Write sorted values to output file
     fprintf(fp,"%d\n",med);
     fclose(fp);
     free(a);
}

int rselect(int A[], int l, int r, int m) 
{
	/* TODO Complete the code 
   	 * call the partition function and do a divide and conquer
	 */
	if (l>r)
return;
else
{

	int j = partition(A,l,r);
//	printf("j=%d,m=%d\n",j,m);
	if(j == m-1)
		return A[j];
	else if(j>m-1){
//		printf("coz j>m\n");
		rselect(A,0,j-1,m);
//		printf("coz j>m\n");
	}
	else if(j<m-1){	
//		printf("coz m>j\n");
		rselect(A,j+1,r,m);
//		printf("coz m>j\n");
	}
}
}

/* 
This function selects a pivot and partitions 
the data around that pivot 
*/
int partition(int A[], int l, int r)
{
 	//int piv_index = 0;
   	// TODO Complete the code for the function 
   	// First choose the pivot A[l]
   	// later modify it to median of A[l] A[r] and A[l+r/2] 
  	int pivot = A[r];
	int i,temp;
	int piv_index=l;
	for(i=l;i<r;i++){
		if(A[i]<pivot){
			//swap
			temp=A[i];
			A[i]=A[piv_index];
			A[piv_index]=temp;
			piv_index++;	
		}
	}
	temp = A[r];
	A[r] = A[piv_index];
	A[piv_index] = temp;
	return piv_index;
}
