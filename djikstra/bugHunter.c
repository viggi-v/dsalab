/****************************
 * Graph Program
 * 09-20-2016
 * Vighnesh Velayudhan :)
 ****************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INT_MAX 100000

/*
 * The code reads the file and stores the map in a graph.
 * More precisely, in an adjacency list
 * vertex represents a city,
 * graph represents a map,
 * weight represents the distance between two cities.
 */
typedef struct vertex{
    int name;
    int weight;
    struct vertex*next;
}Vertex,*VertexPtr;

typedef struct{
    VertexPtr head;
}Neighbour,*NeighbourPtr;

typedef struct{
    int V;
    NeighbourPtr neighbourArray;
}Graph,*GraphPtr;

VertexPtr makeVertex(int name,int weight){
    VertexPtr newVertex = (VertexPtr) malloc(sizeof(Vertex));
    newVertex->name = name;
    newVertex->weight = weight;
    newVertex->next = NULL;
    return newVertex;
}
GraphPtr makeGraph(int V){
    int i;
    GraphPtr newGraph = (GraphPtr) malloc(sizeof(Graph));
    newGraph->V=V;
    newGraph->neighbourArray = (NeighbourPtr) malloc(V*sizeof(Neighbour));
    for(i=0;i<V;i++)
        newGraph->neighbourArray[i].head = NULL;
    return newGraph;
}
/*
 * We have a graph as a structure with two members:
 * 1. The number of elements in the graph
 * 2. A list of all the elements in the map(it is named as neighborArray and a little confusing)
 *      Each element neighborArray is another array of cities which are directly connected to that city, and weight being the distance between them
 */
void addEdge(GraphPtr graph, int src,int destination,int distance){
    VertexPtr newVertex = makeVertex(destination,distance);
    newVertex->next = graph->neighbourArray[src].head;
    graph->neighbourArray[src].head = newVertex;
    /*
     * If i and j are connected so are j and i...
     */
    VertexPtr backVertex = makeVertex(src,distance);
    backVertex->next = graph->neighbourArray[destination].head;
    graph->neighbourArray[destination].head = backVertex;
}

void printGraph(GraphPtr graph,int V){
    int i=0;
    VertexPtr temp;
    while(i<V){
        printf("\nThe neighbours of vertex %d are:\n",i);
        temp = graph->neighbourArray[i].head;
        while(temp){
            printf("%d (%d),",temp->name,temp->weight);
            temp = temp->next;
        }
        i++;
    }
    printf("\n");
}
int findClosestCity(int*distances,int*visitedSet,int count){
    int i=0,min_dist=INT_MAX,min_pos=-1;
    while(i<count){
        if(!*(visitedSet+i)){
            if(*(distances+i)<min_dist){
                min_dist = *(distances+i);
                min_pos = i;
            }
        }
        i++;
    }
    return min_pos;
}
int dijkstra(GraphPtr graph, int src,int dest,int V){
    int*distances = (int*) malloc(V*sizeof(int));
    int*visitedSet = (int*) malloc(V*sizeof(int));
    int i,dist;
    /*
     * Setting all nodes as unvisited and all distances to infinity
     */
    for(i=0;i<V;i++){
        *(visitedSet+i)=0;
        *(distances+i) = INT_MAX;
    }
    *(distances+src)=0;
    //For isolated elements
    if(graph->neighbourArray[dest].head==NULL || graph->neighbourArray[src].head==NULL)
        return -1;
    for(i=0;i<V;i++){
      int current_vertex = findClosestCity(distances,visitedSet,V);
      if(current_vertex == -1)
        break;
      int present_distance_from_src = *(distances+current_vertex);
      VertexPtr temp = graph->neighbourArray[current_vertex].head;
      while(temp!=NULL){
        if(!*(visitedSet+temp->name)){
            //It is unvisited
            if(*(distances+temp->name)>(present_distance_from_src+temp->weight)){
                //Yippee!! found a shorter length
                *(distances+temp->name) = present_distance_from_src+temp->weight;
            }
        }
        temp=temp->next;
      }
      visitedSet[current_vertex] = 1 ;
    }
    dist = *(distances+dest);
    free(visitedSet);
    free(distances);
    return dist;
}
int fakedijkstra(GraphPtr graph, int src,int dest,int V){
    int*distances = (int*) malloc(V*sizeof(int));
    int*visitedSet = (int*) malloc(V*sizeof(int));
    int i,dist;
    /*
     * Setting all nodes as unvisited and all distances to infinity
     */
    for(i=0;i<V;i++){
        *(visitedSet+i)=0;
        *(distances+i) = INT_MAX;
    }
    *(distances+src)=0;
    if(graph->neighbourArray[dest].head==NULL || graph->neighbourArray[src].head==NULL)
        return -1;
    for(i=0;i<V;i++){
      //This caused the second bug, it gives the city with least index in case of a tie.
      int current_vertex = findClosestCity(distances,visitedSet,V);

      if(current_vertex == -1)
        break;
      int present_distance_from_src = *(distances+current_vertex);
      VertexPtr temp = graph->neighbourArray[current_vertex].head;
      while(temp!=NULL){
        if(!*(visitedSet+temp->name)){
            //It is unvisited
            if(*(distances+temp->name)==INT_MAX){
                //We update only for unvisited:P
                //This is the bug...
                *(distances+temp->name) = present_distance_from_src+temp->weight;
            }
        }
        temp=temp->next;
      }
      visitedSet[current_vertex] = 1; //Marks visited
    }
    dist = *(distances+dest);
    free(visitedSet);
    free(distances);
    return dist;
    }

void main(){
    char fileName[20],temp,op='y';
    FILE* file;
    int adjMat[20][20],i,j,src,dest,V=0,dist,fakedist;
    printf("Enter the file to open:");
    scanf("%s",fileName);
    file = fopen(fileName,"r");
    if(file==NULL)
    {
        printf("File couldnt be acceced.");
        exit(0);
    }
    fscanf(file,"%d",&V);
    for(i=0;i<V && !feof(file);i++)
        for(j=0;j<V && !feof(file);j++)
            fscanf(file,"%d",&adjMat[i][j]);
    GraphPtr myGraph = makeGraph(V);
    for(i=0;i<V;i++){
        for(j=i;j<V;j++){
            if(adjMat[i][j])
                addEdge(myGraph,i,j,adjMat[i][j]);
        }
    }
    while(op!='n'){
            printf("Enter p to visualize the map\nEnter r to test the code\nEnter n to quit\n");
            scanf("\n%c",&op);
            if(op=='n') return;
            if(op=='p'){
                printGraph(myGraph,V);
                continue;
            }
            else if(op=='r'){
                printf("\nEnter a source:");
                scanf("%d",&src);
                printf("Enter the destination:");
                scanf("%d",&dest);
                if(src<0 || src>=V || dest<0 || dest>=V)
                {
                printf("Invalid input");
                exit(1);
                }
                dist=dijkstra(myGraph,src,dest,V);
                fakedist = fakedijkstra(myGraph,src,dest,V);
                if(dist==fakedist){
                        // :P
                    if(dist==-1)
                        printf("Isolated Element, no short path\n");
                    else
                        printf("The shortest distance between %d and %d is %d\n",src,dest,fakedist);

                }
                else
                    printf("Congrats! You have found a bug.\n The shortest distance between %d and %d :\n With Buggy algorithm:%d\nActual Distance:%d\n",src,dest,fakedist,dist);
            }
            else
                printf("Invalid option\n");
    }
    fclose(file);
    free(myGraph);
}
