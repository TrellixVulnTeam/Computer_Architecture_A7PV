#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP
    //fscanf()
    // first, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[8]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", &buff);
        minuend[i] = 0b1 & buff;
    }

    // notice that you are reading two different lines; caution with reading
    /* ... */
    fscanf(fp, "%c", &buff);
    // second, read the subtrahend (number to subtract)
    bool subtrahend[8]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", &buff);
        subtrahend[i] = 0b1 & buff;
    }

    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND
    // Negate the subtrahend
    // flip all bits
    /* ... */
    for(int i=0; i<8; i++)
    {
        subtrahend[i] = !subtrahend[i];
    }

    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i=0; i<8; i++) { // iterate from LSB to MSB
        /* ... */
        bool temp = subtrahend[i];
        subtrahend[i] = subtrahend[i] ^ carry;
        carry = carry && temp;
    }

    // Add the minuend and the negated subtrahend
    bool difference[8];
    carry = false;
    /* ... */
    for(int i=0; i<8; i++)
    {
        bool temp = carry;
        carry = (subtrahend[i] && minuend[i]) || (subtrahend[i] && carry) || (minuend[i] && carry);
        difference[i] = subtrahend[i] ^ minuend[i] ^ temp;
    }
    //print the difference bit string
    for(int i=7; i>=0; i--)
    {
        printf("%d",difference[i]);
    }
    fclose(fp);
    return EXIT_SUCCESS;

}
