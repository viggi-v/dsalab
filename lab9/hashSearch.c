// Assignment 7 : Find missing words in the dictionary (Hash Table)
// Authors	: 15EC250, 15EC251
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



ulong computeKey(char *word);
int DoubleHash(char** H, char *word, int M, int K,int i); 	    // TODO
void insertToHashTable(char **H, char* word, int M, int K); // TODO
int searchTable(char **H, char* word, int M, int K);        // TODO
void printHashTable(char **H, int M);

void freeArray(char **A, int SIZE);
void freeBT(NodePtr ROOT);

//-------------------------------- MAIN START -----------------------------------------------//

int main(int argc, char* argv[])
{
    char *usage = "Correct Usage : ./a.out dictionary_file input_file HT_output \n \
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

    int N, M, K;
    fscanf(dict, "%d", &N);         // Number of words
    fscanf(dict, "%d", &M);         // Number of slots
    fscanf(dict, "%d", &K);         // for calculation of 'k' during collision

    // Create a Hash Table and initialize it to EMPTY
    // It is a kind of array (size = M) of strings
    int i;
    char **HT = malloc(M * sizeof(char*));
    for(i=0; i<M; i++){
        HT[i] = (char*)malloc(MAX_WORD_SIZE);
        strcpy(HT[i], EMPTY);
    }

   
    // read dictionary word by word and insert it into HT 
    char word[MAX_WORD_SIZE];
    i = 0;
    fscanf(dict, "%s", word); 
    while(!feof(dict)){
        insertToHashTable(HT, word, M, K);  // Insert word into Hash Table
        fscanf(dict, "%s", word); 
    }

    fclose(dict);

    //-------------------------------------------------------------------------------//

    // create Trees
    NodePtr ROOT_HT = NULL;                 // To store missing words from HT search
   
    // Now read input file
    FILE *in = fopen(input, "r");
    if(in == NULL){
        printf("Text file is not loaded correctly\n"); exit(1);
    }
    
    clock_t start1, end1;

    //-------------------------- Hash Table Search -----------------------------------------------------//
    
    start1 = clock();
    int isFound;
    fscanf(in, "%s", word); 
    while(!feof(in)){
        isFound = searchTable(HT, word, M, K);
        if(isFound == 0){
            ROOT_HT = insertToTree(ROOT_HT, word);
        }
        fscanf(in, "%s", word); 
    }
    end1 = clock();
    printf("Time for Hash Search: %f seconds\n", (double)(end1-start1)/CLOCKS_PER_SEC);
  
//-------------------------------------------------------------------------------//
    
    fclose(in);

    // Save output of HT search to a file
    FILE *hout = fopen(HTout, "w");    
    if(hout == NULL){
        printf("Output didn't open correctly\n");
        exit(1);
    }

    inOrder(ROOT_HT, hout);
    fclose(hout);

    // Free the memories
    freeArray(HT, M); HT = NULL;
   

    freeBT(ROOT_HT); 
    ROOT_HT = NULL;
  
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
	else if(strcmp(ROOT->W,word)<0)
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
	inOrder(ROOT->right,f);
}




//-------------------------------------------------------------------------------//
// Function to find the numeric equivalent of a word
// Input 1  : word - the string
// Output   : Corresponding numeric value
// CAUTION  : return type is a unsigned long, not int. 
//-------------------------------------------------------------------------------//
ulong computeKey(char *word)
{
    int i, M=3;
    ulong key = 0;
    for(i=0; word[i] != '\0'; ++i){
        M += 2;
        key = key * M + word[i];
    }
    return key;
}




//-------------------------------------------------------------------------------//
// Function to find double hash of a string
// Input 1  : H - Hash Table
// Input 2  : word - the string to be inserted
// Input 3  : M - Number of slots in HT
// Input 4  : K - for calculation of k during collision
// Output   : location where string to be inserted
//-------------------------------------------------------------------------------//
int DoubleHash(char** H, char *word, int M, int K,int i)
{
 // Apply double hashing function as follows
	// H1(key) = key % M
	// H2(key) = 1 + key%K 

    ulong key = computeKey(word);
    int ans = (int)(key%M);
    if(i==0)
        return ans;
    else{
        return (ans+(i*(1+(key%K))))%M;
    }
}




//-------------------------------------------------------------------------------//
// Function to insert a string to Hash Table
// Input 1  : H - Hash Table
// Input 2  : word - the string to be inserted
// Input 3  : M - Number of slots in HT
// Input 4  : K - for calculation of k during collision
//-------------------------------------------------------------------------------//
void insertToHashTable(char **H, char* word, int M, int K)
{
    // TODO : finish the function
    // Find the numeric key of the given word
	// Apply double hashing function as follows
	// H1(key) = key % M
	// H2(key) = 1 + key%K
    // Check if that location is empty
    // if so, insert there, else apply collision resolution by double hashing
    
    int hashIndex=1;
    int loc = DoubleHash(H, word, M, K,0);
    while(strcmp(H[loc],"_")){
        loc = DoubleHash(H,word,M,K,hashIndex);
        hashIndex++;
    }  
    strcpy(H[loc],word);
}




//-------------------------------------------------------------------------------//
// Function to search a string in Hash Table
// Input 1  : H - Hash Table
// Input 2  : word - the string to be inserted
// Input 3  : M - Number of slots in HT
// Input 4  : K - for calculation of k during collision
// Output   : 1/0 - 1 if the string is present in HT, else 0
//-------------------------------------------------------------------------------//
int searchTable(char **H, char* word, int M, int K)
{
   // TODO : finish the function
    // Again, apply double hashing
    // check if the string stored in that location is same as word
    // if so, return 1, else return 0
	int hashIndex=0;
	int loc = DoubleHash(H,word,M,K,hashIndex);
	while(1){
		if(!strcmp(H[loc],word))
			return 1;
		else if(!strcmp(H[loc],"_"))
			return 0;
		hashIndex++;
		loc = DoubleHash(H,word,M,K,hashIndex);
	}
	return 0;
}




//-------------------------------------------------------------------------------//
// Function to print contents of a Hash Table
//-------------------------------------------------------------------------------//
void printHashTable(char **H, int M)
{
    int i;
    for(i=0; i<M; i++){
        printf("%s ", H[i]);
    }
    printf("\n");
}




//-------------------------------------------------------------------------------//
// Function to free the memory of HT etc.
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
