#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to solve a maze that may contain cycles using BFS

// BFS requires using a queue data structure
typedef struct QueueNode {
    graphNode_t graphNode;
    struct QueueNode* next;
} QueueNode;

struct Queue {
    struct QueueNode* front; // front (head) of the queue
    struct QueueNode* back; // back (tail) of the queue
};
typedef struct Queue Queue;

// Append a new QueueNode to the back of the Queue
struct Queue enqueue ( struct Queue queue, graphNode_t graphNode ) {
    /* ... */
    QueueNode* newnode = malloc(sizeof(QueueNode));
    newnode->graphNode = graphNode;
    newnode->next = NULL;
    if(queue.back)
    {
        queue.back->next = newnode;
        queue.back = newnode;
    }
    else
    {
        queue.back = newnode;
        queue.front = newnode;
    }

    return queue;
}

// Remove a QueueNode from the front of the Queue
graphNode_t dequeue ( Queue* queue ) {
    /* ... */
    graphNode_t node = queue->front->graphNode;
    QueueNode* temp = queue->front;
    if(queue->front == queue->back)
    {
        queue->back = NULL;
    }
    queue->front = temp->next;
    free(temp);
    return node;
}

int main ( int argc, char* argv[] ) {

    // First, read the query file to get the source and target nodes in the maze
    /* ... */
    FILE *fp = fopen(argv[2],"r");
    if(!fp)
    {
        perror("fopen failed");
        return 1;
    }
    graphNode_t current, target, source;
    fscanf(fp, "%ld", &source);
    fscanf(fp, "%ld", &target);
    current = source; 
    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    /* ... */
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    // USE A QUEUE TO PERFORM BFS
    Queue queue = { .front=NULL, .back=NULL };

    // An array that keeps track of who is the parent node of each graph node we visit
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited
    }
    /* ... */

    while ( current != target ) {

        // so long as we haven't found the target node yet, iterate through the adjacency list
        // add each neighbor that has not been visited yet (has no parents) to the queue of nodes to visit
        /* ... */
        //AdjacencyListNode* neighbor = (adjacencyList[current]).next;
        //while(adjacencyList[current])
        AdjacencyListNode* neighbor = adjacencyList[current].next;
        while(neighbor)
        {
            if(parents[neighbor->graphNode] == -1)
            {
                queue = enqueue(queue, neighbor->graphNode);
                parents[neighbor->graphNode] = current;
            }
            neighbor = neighbor->next;
        }
        // Visit the next node at the front of the queue of nodes to visit
        /* ... */
        if(queue.front)
        {
            //printf("queue front is %zu\n", queue.front->graphNode);
            current = dequeue(&queue);
        }
        else
        {
            break;
        }
    }

    // Now that we've found the target graph node, use the parent array to print maze solution
    // Print the sequence of edges that takes us from the source to the target node
    /* ... */
    if(parents[target] == -1)
    {
        printf("There is no path from %zu to %zu\n", source, target);
    }
    else 
    {
        while(parents[current] != source)
        {
            printf("%zu %zu\n", current, parents[current]);
            current = parents[current];
        }
        printf("%zu %zu\n", current, parents[current]);
    }
    // free any queued graph nodes that we never visited because we already solved the maze
    while ( queue.front ) {
        dequeue(&queue);
    }
    free (parents);
    freeAdjList ( graphNodeCount, adjacencyList );

    return EXIT_SUCCESS;
}
