#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct bstNode node;
struct bstNode {
    int val;
    struct bstNode* l_child;
    struct bstNode* r_child;
};
void inorder (node*);
void insert (node* , int new_val);


int main(int argc, char* argv[])
{
    FILE* fp = fopen(argv[1], "r");
    if (!fp) 
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    node* root = malloc(sizeof(node));
    root->l_child = NULL;
    root->r_child = NULL;
    char buff[256];
    if (fscanf(fp, "%s", buff)!=EOF)
    {
        root->val = atoi(buff);
    }

    while ( fscanf(fp, "%s", buff)!=EOF ) 
    {
        insert(root, atoi(buff));
    }
    inorder(root);
    fclose(fp);
    return 0;
}

//The print and release function to print in reverse inorder
void inorder (node* nd)
{
    if(nd!=NULL)
    {
        inorder(nd->r_child);
        printf("%d ", nd->val);
        inorder(nd->l_child);
        free(nd);
    }
}

//The insert function to insert a node
void insert (node* nd, int new_val)
{
        if(nd->l_child == NULL&&nd->val > new_val)
        {
            node* leaf = malloc(sizeof(node));
            leaf->val = new_val;
            leaf->l_child = NULL;
            leaf->r_child = NULL;
            nd->l_child = leaf;
        }
        else if(nd->r_child == NULL&&nd->val < new_val)
        {
            node* leaf = malloc(sizeof(node));
            leaf->val = new_val;
            leaf->l_child = NULL;
            leaf->r_child = NULL;
            nd->r_child = leaf;           
        }
    
    else
    {
        if(nd->val > new_val)
        {
            insert(nd->l_child, new_val);
        }
        else if(nd->val < new_val)
        {
            insert(nd->r_child, new_val);
        }
        return;
    }
    
} 
