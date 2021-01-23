#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
int main(int argc, char* argv[])
{

    FILE* matrix_a_fp = fopen(argv[1], "r");
    if (!matrix_a_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    FILE* matrix_b_fp = fopen(argv[2], "r");
    if (!matrix_b_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
/**buff: string buffer to read in strings
c1: number of rows of the matrix
length_a_m: number of columns in the matrix**/


//Initilize the matrix_a[] from file "matrix_a.txt"
    char buff[256];
    fscanf(matrix_a_fp, "%s", buff);
    int r1= atoi(buff);
    int** matrix_a = malloc( r1 * sizeof(int*) );
    fscanf(matrix_a_fp, "%s", buff);
    int c1 = atoi(buff);
    for ( unsigned char i=0; i<r1; i++ ) {
        matrix_a[i] = malloc( c1 * sizeof(int) );
    }
    for(int row=0; row<r1; row++)
    {
        for(int col=0; col<c1; col++)
        {
            fscanf(matrix_a_fp, "%s", buff);
            matrix_a[row][col] = atoi(buff);
        }
    }
    //Initilize the matrix_b[] from file "matrix_b.txt"
    fscanf(matrix_b_fp, "%s", buff);
    int r2 = atoi(buff);
    int** matrix_b = malloc( r2 * sizeof(int*) );
    fscanf(matrix_b_fp, "%s", buff);
    int c2 = atoi(buff);
    for ( unsigned char i=0; i<r2; i++ ) {
        matrix_b[i] = malloc( c2 * sizeof(int) );
    }
    for(int row=0; row<r2; row++)
    {
        for(int col=0; col<c2; col++)
        {
            fscanf(matrix_b_fp, "%s", buff);
            matrix_b[row][col] = atoi(buff);
        }
    }


    int temp = 0;
    for(int i=0; i<r1; i++)
    {
        for(int j=0; j<c2; j++)
        {
            for(int k=0; k<c1; k++)
            {
                temp = temp+matrix_a[i][k]*matrix_b[k][j];
            }
            printf("%d ", temp);
            temp = 0;
        }
    }
    printf("\n");
    fclose(matrix_a_fp);
    fclose(matrix_b_fp);

    for ( unsigned char i=0; i<r1; i++ ) {
        free( matrix_a[i] );
    }
    free( matrix_a );
        for ( unsigned char i=0; i<r2; i++ ) {
        free( matrix_b[i] );
    }
    free( matrix_b );

    return 0;

}

