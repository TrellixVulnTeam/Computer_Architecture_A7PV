#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Struct to hold the expected close brace character and a pointer to the next element.
struct element {
    char close;
    struct element* next;
};

int main(int argc, char* argv[])
{

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    bool balanced = true;
    char buff;
    struct element* top = malloc(sizeof(struct element)); //top is the pointer pointing to the head of the stack
    top->next = NULL; 
    while ( fscanf(fp, "%c", &buff)==1 ) {


    //push function of the stack
        if(buff == '<')
        {
            struct element* current = malloc(sizeof(struct element));
            current->close = '>';
            current->next = top->next;
            top->next = current;
        }
        else if (buff == '(')
        {
            struct element* current = malloc(sizeof(struct element));
            current->close = ')';
            current->next = top->next;
            top->next = current;
        }
        else if (buff == '[')
        {
            struct element* current = malloc(sizeof(struct element));
            current->close = ']';
            current->next = top->next;
            top->next = current;
        }
        else if (buff == '{')
        {
            struct element* current = malloc(sizeof(struct element));
            current->close = '}';
            current->next = top->next;
            top->next = current;
        }
    
    //pop function of the stack

        else if(buff == '>' || buff == '}' || buff == ']' || buff == ')')
        {
            struct element* temp = top;
            struct element* f;
            while(temp->next != NULL && buff != temp->next->close)
            {
                temp = temp->next;
            }
            if(temp->next == NULL)
            {
                balanced = false;
                break;
            }
            f = temp->next;
            temp->next = temp->next->next;
            free(f);
        }
       
    }


     struct element* temp;
     while(top != NULL)
     {
         temp = top;
         top = top->next;
         if(top != NULL)
         {
            balanced = false;
            //printf("%c ", top->close);
         }
         free(temp);
     }
     //printf ("\n");

    printf ( balanced ? "yes" : "no" );
    fclose(fp);
    return 0;
}
