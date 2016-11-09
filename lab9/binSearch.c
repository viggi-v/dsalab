// Assignment 7 : Find missing words in the dictionary (binary /linear Search)
// Authors	: 
// Date 	:

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_SIZE 75
#define EMPTY "_"

typedef unsigned long ulong;

// Node of a tree {No need of parent pointer}
typedef struct node{
    char *W;
    struct node* left;
    struct node* right;
}Node, *NodePtr;



// Finish all TODO marked functions; Check at end of file for function definition
NodePtr makeNode(char *word);
NodePtr insertToTree(NodePtr ROOT, char *word); 			// TODO
void inOrder(NodePtr ROOT, FILE *f);            			// TODO

int binarySearch(char **BSA, int low, int high, char *word);
int linearSearch(char **A, int N, char *word);

void freeArray(char **A, int SIZE);
void freeBT(NodePtr ROOT);


    //-------------------------------- MAIN START -----------------------------------------------//

int main(int argc, char* argv[])
{
    char *usage = "Correct Usage : ./a.out dictionary_file input_file output_file \n \
Example : ./a.out dict_1.txt ex_1.txt HTout.txt \n";

    if (argc < 4){
        printf("%s", usage);
        exit(1);
    }

    // Read command line arguments
    char *dictionary = argv[1];     // dictionary file
    char *input = argv[2];          // Input file
    char *HTout = argv[3];          // Output file

    // Read Dictionary File
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL){
        printf("Dictionary file is not read correctly\n");
        exit(1);
    }
    int i;
    int N, M, K;
    fscanf(dict, "%d", &N);         // Number of words
    fscanf(dict, "%d", &M);         // Number of slots
    fscanf(dict, "%d", &K);         // for calculation of 'k' during collision

   
    // Similarly, create a Binary Search Array of size N
    char **BSA = malloc(N * sizeof(char*));
    for(i=0; i<N; i++){
        BSA[i] = (char*)malloc(MAX_WORD_SIZE);
        strcpy(BSA[i], EMPTY);
    }

    // read dictionary word by word and insert it into HT and BSA
    char word[MAX_WORD_SIZE];
    i = 0;
    fscanf(dict, "%s", word); 
    while(!feof(dict)){
        strcpy(BSA[i++], word);             // Insert word to BSA and increment 'i'
        fscanf(dict, "%s", word); 
    }

    fclose(dict);

//-------------------------------------------------------------------------------//
    // create Trees
  
    NodePtr ROOT_BSA = NULL;                // To store missing words from BSA search
    NodePtr ROOT_LS = NULL;                 // To store missing words from Linear search

    // Now read input file
    FILE *in = fopen(input, "r");
    if(in == NULL){
        printf("Text file is not loaded correctly\n"); exit(1);
    }
    
    clock_t start1, end1;

    int isFound;
	//-------------------------- Binary Search -----------------------------------------------------//
    fseek(in, 0, SEEK_SET);
    start1 = clock();
    	
	fscanf(in, "%s", word); 
    while(!feof(in)){
        isFound = binarySearch(BSA, 0, N-1, word);
        if(isFound == 0)
            ROOT_BSA = insertToTree(ROOT_BSA, word);
        fscanf(in, "%s", word); 
    }


    end1 = clock();
    printf("Time for Binary Search: %f seconds\n", (double)(end1-start1)/CLOCKS_PER_SEC);

  
    //-------------------------------------------------------------------------------//

    //--------------------------------- Linear Search ---------------------------------------------//

    // Linear search only if file size is small
    // Otherwise it will take long time
    size_t SIZE = ftell(in);
    if(SIZE < 15000){
        fseek(in, 0, SEEK_SET);
        start1 = clock();
       	
	fseek(in, 0, SEEK_SET);
        start1 = clock();
        fscanf(in, "%s", word); 
        while(!feof(in)){
            isFound = linearSearch(BSA, N, word);
            if(isFound == 0)
                ROOT_LS = insertToTree(ROOT_LS, word);
            fscanf(in, "%s", word); 
        }
        end1 = clock();
        printf("Time for Linear Search: %f seconds\n", (double)(end1-start1)/CLOCKS_PER_SEC);

      
    }
    //-------------------------------------------------------------------------------//

    fclose(in);

    // Save output of HT search to a file
    FILE *hout = fopen(HTout, "w");    
    if(hout == NULL){
        printf("Output didn't open correctly\n");
        exit(1);
    }

    inOrder(ROOT_BSA, hout);
   // inOrder(ROOT_LS, hout);
    fclose(hout);

    // Free the memories
    freeArray(BSA, N); BSA = NULL;

    freeBT(ROOT_BSA); ROOT_BSA = NULL;
    if(ROOT_LS != NULL){
        freeBT(ROOT_LS); ROOT_LS = NULL;
    }
}

//-------------------------------- MAIN END -----------------------------------------------//


//-------------------------------- FUNCTIONS -----------------------------------------------//
// Function to create a node for the tree
// Input - A string
// Output - A Pointer to the node
//-------------------------------------------------------------------------------//

NodePtr makeNode(char *word){
    NodePtr np = malloc(sizeof(Node));
    np->W = malloc(strlen(word)+1);         // +1 to accomodate '\0' at end
    strcpy(np->W, word);
    np->left = NULL;
    np->right = NULL;
    return np;
}



//-------------------------------------------------------------------------------//
// Function to insert a node to a Binary Search Tree
// Input 1 : ROOT - Root of the tree
// Input 2 : word - a string to be inserted
// Output  : Return the new root of the tree
//-------------------------------------------------------------------------------//
NodePtr insertToTree(NodePtr ROOT, char *word)
{
    // TODO : finish this function
    // Create a new node for word
    // Find its location to insert in BST and insert
    // Return the ROOT 
    // Don't forget it while calling the function in main
        if(ROOT==NULL){
                ROOT = makeNode(word);
                return ROOT;
        }
        if(!strcmp(ROOT->W,word))
                return ROOT;
        else if(strcmp(ROOT->W,word)<1)
                ROOT->right = insertToTree(ROOT->right,word);
        else
                ROOT->left = insertToTree(ROOT->left,word);
        return ROOT;
}


//-------------------------------------------------------------------------------//
// Function for inOrder traversal of the BST
// Instead of printing to the screen, it is written to a file
// Input 1 : ROOT - root of the BST
// Input 2 : f - file pointer to save the data
//-------------------------------------------------------------------------------//

void inOrder(NodePtr ROOT, FILE *f){
    //TODO : finish the function
    // Recursively traverse through the tree via inOrder
    // Instead of printing the word, write it to f
    // Use this : fprintf(f, "%s\n", ROOT->W);
        if(!ROOT)
                return;
        inOrder(ROOT->left,f);
        fprintf(f,"%s\n",ROOT->W);
//       	printf(".");
	inOrder(ROOT->right,f);
}


//-------------------------------------------------------------------------------/(
// Function for iterative binary search in a sorted array
// Input 1 : BSA - Array of strings
// Input 2 : low - starting index of the array
// Input 3 : high - ending index of the array (Carefull !!)
// Input 4 : word - the string to be searched
// Output  : 1/0 - 1 if string is found in array, else 0
//-------------------------------------------------------------------------------//
int binarySearch(char **BSA, int low, int high, char *word)
{
    //Complete Binary search algorithm
	
	/*if(low>high)
		return 0;
	*/
	int mid = (low+high)/2;
	while(low<=high){
		mid = (low+high)/2;
		if(!strcmp(BSA[mid],word))
	                return 1;
		else if(strcmp(BSA[mid],word)>0)
			high = mid-1;
		else
			low = mid+1;
	
	}
	return 0;
	/*
	if(!strcmp(BSA[mid],word))
		return 1;
	else if(strcmp(BSA[mid],word)<0)
		return binarySearch(BSA,low,mid-1,word);
	else return binarySearch(BSA,mid+1,high,word);
	*/
}




//-------------------------------------------------------------------------------//
// Function for the exhaustive searching in an array
// Input 1  : A - Array of strings
// Input 2  : N - Size of the array
// Input 3  : word - string to be searched
// Output  : 1/0 - 1 if string is found in array, else 0
//-------------------------------------------------------------------------------//
int linearSearch(char **A, int N, char *word)
{
    //Complete Linear Search Algorithm
	int i;
	for(i=0;i<N;i++)
		if(!strcmp(A[i],word))
			return 1;
	return 0;
}


//-------------------------------------------------------------------------------//
// Function to free the memory of HT, BSA etc.
//-------------------------------------------------------------------------------//
void freeArray(char **A, int SIZE)
{
    int i;
    for(i=0; i<SIZE; ++i){
        free(A[i]);
        A[i] = NULL;
    }
    free(A);
    A = NULL;
}

//-------------------------------------------------------------------------------//
// Free the Binary Tree memory
//-------------------------------------------------------------------------------//

void freeBT(NodePtr ROOT)
{
    if(ROOT == NULL)
        return;

    if(ROOT->left != NULL){
        freeBT(ROOT->left);
        ROOT->left = NULL;
    }

    if(ROOT->right != NULL){
        freeBT(ROOT->right);
        ROOT->right = NULL;
    }
    
    free(ROOT->W);
    ROOT->W = NULL;
    free(ROOT);
}
