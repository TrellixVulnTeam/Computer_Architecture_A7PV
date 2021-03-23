#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    //float value = *(float *) &binary; // you are not allowed to do this.
    //unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP
    unsigned int multiplier = 0, multiplicand = 0;
    char buffer;
    // first, read the binary number representation of multiplier
    /* ... */
    for(int i=EXP_SZ+FRAC_SZ; i>=0; i--)
    {
        fscanf(fp, "%c", &buffer);
        multiplier += (buffer & 0b1)*pow(2,i);
    }
    // notice that you are reading two different lines; caution with reading
    /* ... */
    fscanf(fp, "%c", &buffer);
    // first, read the binary number representation of multiplcand
    /* ... */
    for(int i=EXP_SZ+FRAC_SZ; i>=0; i--)
    {
        fscanf(fp, "%c", &buffer);
        multiplicand += (buffer & 0b1)*pow(2,i);
    }
    
    float product = *(float *) &multiplier * *(float *) &multiplicand; // you are not allowed to print from this.
    unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.
    //printf("%f\n", product);
    // SIGN
    /* ... */
    bool sign_1 = (multiplier >> (EXP_SZ + FRAC_SZ )) & 0b1;
    // printf("sign 1 is %d\n", sign_1);
    bool sign_2 = (multiplicand >> (EXP_SZ + FRAC_SZ)) & 0b1;
    // printf("sign 2 is %d\n", sign_2);
    bool sign = (sign_1 && !sign_2) || (sign_2 && !sign_1);
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ)));

    // EXP
    // get the exp field of the multiplier and multiplicand
    /* ... */
    unsigned short exp1 = (multiplier - (sign_1<<(EXP_SZ+FRAC_SZ)))>>FRAC_SZ;
    unsigned short exp2 = (multiplicand - (sign_2<<(EXP_SZ+FRAC_SZ)))>>FRAC_SZ;
    //printf("exp1 is %u, exp2 is %u\n", exp1, exp2);
    // add the two exp together
    /* ... */
    unsigned exp = exp1 + exp2;
    // subtract bias
    /* ... */
    exp = exp - 127;

    // FRAC
    // get the frac field of the multiplier and multiplicand
    /* ... */
    unsigned long frac1 = (multiplier - (sign_1<<(EXP_SZ+FRAC_SZ)) - (exp1<<FRAC_SZ));
    unsigned long frac2 = (multiplicand - (sign_2<<(EXP_SZ+FRAC_SZ)) - (exp2<<FRAC_SZ));
    //printf("frac1 is %lu, frac2 is %lu\n", frac1, frac2);
    // assuming that the input numbers are normalized floating point numbers, add back the implied leading 1 in the mantissa
    /* ... */
    frac1 = frac1 + (1<<FRAC_SZ);
    frac2 = frac2 + (1<<FRAC_SZ);
    //printf("frac1 is %lu, frac2 is %lu\n", frac1, frac2);
    // multiply the mantissas
    /* ... */
    unsigned long frac = frac1 * frac2;
    // overflow and normalize
    unsigned long int overflow = (frac >> (2*FRAC_SZ));
    //printf("overflow is %lu\n", overflow);
    /* ... */
    exp = exp + (overflow/2);
    //frac = frac - (overflow<<(2*(FRAC_SZ)));
    frac = frac >> (FRAC_SZ+overflow/2-1);
    // rounding
    /* ... */
    unsigned int carry = frac & 0b1;
    //printf("carry is %u\n", carry);
    frac = frac >> 1;
    frac = frac + carry;
    // frac = frac + (carry<<(FRAC_SZ+1));
    // frac = frac >> (FRAC_SZ+1);
    // move decimal point
    /* ... */

    // PRINTING
    // print exp
    for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&exp>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    }
    printf("_");

    // // print frac
    for ( int bit_index=FRAC_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&frac>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index)));
    }

    fclose(fp);
    return(EXIT_SUCCESS);

}
