#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[]) {

    // SETUP

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    double value;
    fscanf(fp, "%lf", &value);

    // the reference solution ('the easy way')
    // you are not allowed to print from this casted 'ref_bits' variable below
    // but, it is helpful for validating your solution
    unsigned long int ref_bits = *(unsigned long int*) &value;
    //printf("%lu\n", ref_bits);

    // THE SIGN BIT
    bool sign = value<0.0;
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ))); // validate your result against the reference

    // THE EXP FIELD
    // find the exponent E such that the fraction will be a canonical fraction:
    // 1.0 <= fraction < 2.0
    //double fraction = sign ? -value : value;

    signed short trial_exp=(1<<(EXP_SZ-1))-1; // start by assuming largest possible exp (before infinity)
    // do trial division until the proper exponent E is found
    /* ... */
    double quotient = 0;
    while((quotient >=2 && trial_exp >=-1022)|| (quotient <1 && trial_exp >=-1022))
    {
        quotient = sign ? -(value / pow(2, trial_exp)) : (value / pow(2, trial_exp));
        trial_exp--;
    }
    //printf("%d\n", trial_exp+1);
    trial_exp++;
    unsigned short bias = (1<<(EXP_SZ-1))-1;
    signed short exp = trial_exp + bias;
    if(trial_exp == -1022 && quotient <1)
    {
        exp = 0;
    }
    else
    {
        quotient -= 1;
    }
    
    for ( int exp_index=EXP_SZ-1; 0<=exp_index; exp_index-- ) {
        bool exp_bit = 1&exp>>exp_index;
        printf("%d",exp_bit);
        assert (exp_bit == (1&ref_bits>>(exp_index+FRAC_SZ))); // validate your result against the reference
    }
    printf("_");
    // you get partial credit by getting the exp field correct
    // even if you print zeros for the frac field next
    // you should be able to pass test cases 0, 1, 2, 3

    // THE FRAC FIELD
    // prepare the canonical fraction such that:
    // 1.0 <= fraction < 2.0
    /* ... */
    //printf("quotient is %f\n", quotient);
    bool frac_array[FRAC_SZ+1]; // one extra LSB bit for rounding
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        frac_array[frac_index] = false; // frac set to zero to enable partial credit
        /* ... */
        quotient = quotient*2;
        if(quotient >= 1)
        {
            frac_array[frac_index] = true;
            quotient--;
        }
        //printf("%d", frac_array[frac_index]);
        
    }
    //putchar('\n');
    // rounding
    /* ... */
    bool carry = frac_array[0];
    int frac_index = 1;
    while(frac_array[frac_index] && carry)
    {
        frac_array[frac_index] = false;
        frac_index++;
    }

    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
        assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }
    fclose(fp);
    return EXIT_SUCCESS;

}
