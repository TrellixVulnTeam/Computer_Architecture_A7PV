#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    char buff;
    unsigned long int binary = 0;
    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", &buff);
        binary += (buff-'0')<<i;
        //printf("%lu\n", binary);
    }

    //float number = *(float *)&binary; // you are not allowed to do this.

    /*sign*/
    bool sign = (binary >> (EXP_SZ+FRAC_SZ))% 2 ;
    // E
    unsigned short exp = (binary - (sign<<(EXP_SZ+FRAC_SZ)))>>FRAC_SZ;
    int e;
    double m;
    if(exp == 0)
    {
        e = 1-127;
        m = (binary - (sign<<(EXP_SZ+FRAC_SZ)) - (exp<<(FRAC_SZ)))/ pow(2, FRAC_SZ);
        //m = (binary<<9)/pow(2, FRAC_SZ);
    }
    else
    {
        e = exp - 127;
        m = ((binary - (sign<<(EXP_SZ+FRAC_SZ)) - (exp<<(FRAC_SZ))) + (1<<(FRAC_SZ))) / pow(2, FRAC_SZ);
    }

    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( m, e );
    number = sign ? -number : number;
    printf("%e\n", number);

    fclose(fp);
    return EXIT_SUCCESS;

}
