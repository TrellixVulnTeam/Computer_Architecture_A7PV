#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to print the edge list of a graph given the adjacency matrix
//void file_reader (AjacencyList)
int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
    int num_nodes = adjMatrixToList(argv[1], &adjacencyList);
    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
    for(int i=0; i<num_nodes; i++)
    {
        AdjacencyListNode* temp = &(adjacencyList[i]);
        graphNode_t source = temp->graphNode;
        while(temp->next)
        {
            if(source < (temp->next)->graphNode)
            {
                printf("%zu %zu\n", source, temp->next->graphNode);
            }
            temp = temp->next;
        }
    }
    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    freeAdjList(num_nodes, adjacencyList);
    return EXIT_SUCCESS;
}
