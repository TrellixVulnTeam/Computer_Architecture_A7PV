#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // first, read the number
    signed short int input;
    fscanf(fp, "%hd", &input); // note how the 'h' modifier shortens the %d to half size

    // print bits; you will see this kind of for loop often in this assignment
    // for ( int digit=15; 0<=digit; digit-- ) {
    //     bool char_val = 0b1 & input>>digit; // shift and mask
    //     printf("%d",char_val);
    // }
    // printf("\n");

    // useful hints for printing uppercase hexadecimal
    //printf("The character value of '0' = %c\n",65);
    // printf("The character value of 'A' = %d\n",'A');
    int sum = 0;
    for( int digit=15; digit>=0; digit--)
    {
        int char_val = 0b1 & input>>digit;
        sum += char_val<<(digit%4);
        if(digit%4 == 0)
        {
            if(sum >= 10)
            {
                sum += 7;
            }
            printf("%c", sum+48);
            sum = 0;
        }

    }
    fclose(fp);

    return EXIT_SUCCESS;

}
