/***********************************************
DSA Lab Experiment 1:
    Sort a set of Roll number name pairs
    Input : file with roll numbers and Names
            Each line has the following form
            10EC20 ANMOL J B

    Output: File containing the roll numbers
            and names in sorted order
    
    Done on 17.08.2016 by 15EC250 and 15EC251

***********************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct {
   char RollNumber[10];
   char Name[50];
   char* ptr;
}ClassData;


void BubbleSort(ClassData A[], int n);
void SelectionSort(ClassData A[],int n);
void WriteData(ClassData A[], char* file_name,int len);
void ReadData(char* file_name,int *len, ClassData A[]);

// The main code execution
// The input file name, output file name and
// maximum number of lines from the input
// file are read from the command line
int main(int argc,char *argv[])
{
   ClassData *A = NULL;
   clock_t start,end;
   double CPU_time_used;
   if ( argc != 4 ) /* argc should be 3 for correct execution */
   {
      printf( "Use Correct arguments in %s.  The correct usage is \n", argv[0] );
      printf( "%s <input> <output> <N>\n",argv[0]);
      printf( "\t <input> - Name of the input file \n");
      printf( "\t<output> - Filename of sorted output file\n");
      printf( "\t     <N> - Maximum number of names to be read\n");
   }
   else
   {
      // Read the commandline arguments
      char* file_name_input=argv[1];
      char* file_name_output=argv[2];
      int N =atoi(argv[3]);

      //Allocation of the Array;
      A = (ClassData *) malloc(N*sizeof(ClassData));

      //Read Input Data
      ReadData(file_name_input,&N,A);

      //Sort the data
      start = clock();
      //BubbleSort(A, N);
      SelectionSort(A,N);
      end=clock();
      CPU_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
      //Write output file
      printf("The time used for execution:%f\n",CPU_time_used);
      WriteData(A, file_name_output,N);

      //release the memory
      free (A);
      return 0;
   }
}
/* Function reads the input file.
   First a roll number is read from the line.
   Whatever white space following the roll number is
   ignored. Rest of the line is treated as the name field
*/
void ReadData(char* file_name,int *len, ClassData A[])
{
   FILE* file = NULL;
   //Open the input file for reading
   file  = fopen(file_name, "r");
   if (file == NULL)
   {
      fprintf(stderr,"Cannot open <%s> for reading\n",file_name);
      exit(1);
   }

   char name[50];
   char rollno[10];

   //Read the file
   int n = 0;
   while (!feof(file))
   {
      // Read name and roll number
      fscanf(file,"%s",rollno);
      fscanf(file,"%*[ \n\t]");// TODO Find what is this command ?
      fscanf(file,"%[^\n]s\n",name);

      // copy the read information to array of structures
      strcpy(A[n].RollNumber,rollno);
      strcpy(A[n].Name,name);

      //TODO Try to understand what this line is doing
      if(feof(file) || (*len == ++n ) ) break;

      //TODO comment this line later
      //printf("Name = %s Roll number = %s\n",  name, rollno);
   }
/*
 * Print all the information in output file
 */
void WriteData(ClassData A[], char* file_name,int len)
{
   FILE* file;

   //Open the output file for writing
   file  = fopen(file_name, "w");
   if (file == NULL) {
      fprintf(stderr,"Cannot open <%s> for writing\n",file_name);
      exit(1);
   }

   //write all the data to output
   int i;
   for(i=0;i<len;i++) {
      fprintf(file,"%s %s\n", A[i].RollNumber,A[i].Name);
   }

   //close the file
   fclose(file);

}
int parseInt(char*roll){
        char*ch = roll;
        ch+=4;
        int sum=0;
        while(*ch){
                sum*=10;
                sum+=((int)*ch-48);
                ch++;
        }
        return sum;
}
// The core code to sort stuff

void BubbleSort(ClassData A[], int n)
{
        int i,j;
        for(i=0;i<n-1;i++){
                for(j=0;j<n-i-1;j++){
                        //First compare the first two chars , then the next two and only then the last three.
                        if(parseInt(A[j].RollNumber)>parseInt(A[j+1].RollNumber)){
                                //Swap
                                ClassData temp;
                                temp = A[j];
                                A[j] = A[j+1];
                                A[j+1] = temp;
                        }
                }
        }
}
void SelectionSort(ClassData A[],int n){
        int i,j,pos;
        ClassData small;
        for(i=0;i<n-1;i++){
                small = A[i];
                pos = i;
                for(j=i+1;j<n;j++){
                        if(parseInt(small.RollNumber)>parseInt(A[j].RollNumber)){
                                small = A[j];
                                pos = j ;
                        }
                }
                //Swap
                if(pos!=i){
                        A[pos] = A[i];
                        A[i] = small;
                }
        }

}