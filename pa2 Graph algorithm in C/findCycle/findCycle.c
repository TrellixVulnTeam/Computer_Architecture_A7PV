#include "../graphutils.h"

// A program to find a cycle in a directed graph

// You may use DFS or BFS as needed
/* ... */
bool find_cycle (AdjacencyListNode*, size_t, graphNode_t*, graphNode_t current, graphNode_t parent, graphNode_t*);
int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    /* ... */

    bool isCyclic = false;
    graphNode_t* parents;
    graphNode_t* endpoint = malloc(sizeof(graphNode_t));
    for (unsigned source=0; source<graphNodeCount; source++) {
        
        parents = calloc( graphNodeCount, sizeof(graphNode_t) );
        for (size_t i=0; i<graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited; i.e., node not yet connected to MST.
    }
        //printf("start a new find\n");
        bool flag = find_cycle(adjacencyList, graphNodeCount, parents, source, source, endpoint);
        if(isCyclic != flag)
        {
            isCyclic = true;
            break;
        }
        free(parents);
    }

    if (!isCyclic) { printf("DAG\n"); }
    else
    {
        int i = *endpoint, j = 0;
        int answer[graphNodeCount];
        answer[0] = *endpoint;
        while(parents[i] != *endpoint)
        {
            j++;
            answer[j] = parents[i];
            i = parents[i];
        }
        for(; j>=0; j--)
        {
            printf("%d ", answer[j]);
        }
        printf("\n");
        free(parents);
    }
    free(endpoint);
    freeAdjList ( graphNodeCount, adjacencyList );
    return EXIT_SUCCESS;
}

bool find_cycle (AdjacencyListNode* adjacencyList, size_t graphNodeCount, graphNode_t* parents, graphNode_t current, graphNode_t parent, graphNode_t* endpoint)
{
    if(parents[current] != -1)
    {
        // printf("find cycle, ");
        // printf("parent is %zu, current is %zu\n", parent, current);
        parents[current] = parent;
        *endpoint = current;
        return 1;
    }
    else
    {
        parents[current] = parent;
        // printf("parent is %zu, child is %zu\n", parent, current);
    
        AdjacencyListNode* next = adjacencyList[current].next;
        while(next)
        {
            // printf("The next one is %zu\n", next->graphNode);
            bool flag = find_cycle(adjacencyList, graphNodeCount, parents, next->graphNode, current, endpoint);
            if(flag==1)
            {
                return flag;
            }
            else
            {
                parents[next->graphNode] = -1;
                next = next->next;
            }
        }
    }
    return 0;
}
