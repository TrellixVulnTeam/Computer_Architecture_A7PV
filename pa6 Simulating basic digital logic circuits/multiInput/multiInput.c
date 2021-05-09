#define  _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#define NAME_SIZE 16

// Reverse linked list node of Boolean variable and Boolean value pairs
typedef struct var {
    char name[NAME_SIZE];
    bool val;
    struct var* prev;
} var_t;


// PROCESS A SINGLE ROW OF CIRCUIT FILE DESCRIBING A GATE TO FIND OUTPUT NAME AND VALUE
void findOutVarNameVal (
    var_t* varList,
    char* gateLine,
    char** outName,
    bool* outVal
) {

    char inName0[NAME_SIZE];
    char gate[5];
    int inputs = -1;
    //printf("%s\n\n",gateLine);
    char tempName[NAME_SIZE];
    if ( sscanf(gateLine, "NOT %s %s\n", inName0, tempName)==2 ) {
        // It is a NOT gate
        // printf("NOT %s %s\n", inName0, outName);
        *outName = tempName;
        bool inVal=false;

        // Traverse varList to look for existing value
        var_t* curr = varList;
        while (curr) {
            // https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
            if ( strcmp(curr->name, inName0)==0 ) {
                inVal = curr->val;
                break;
            }
            curr = curr->prev;
        }

        *outVal = !inVal;

    } else{
        // It is not a NOT gate
        sscanf(gateLine, "%s %d ", gate, &inputs);
        char delim[] = " ";
        //printf("number of inputs is %d\n", inputs);
        // strtok(gateLine, delim);
        char* temp = gateLine;
        strtok_r(temp, delim, &temp);
        strtok_r(temp, delim, &temp);
        char** inName = malloc(sizeof(char*)*inputs);
        for(int i=0; i<inputs; i++)
        {

            inName[i] = strtok_r(temp, delim, &temp);
            //printf("inName %d is %s\n", i, inName[i]);
            // //sscanf(gateLine, "%s %d %s", inName[i]);
            // //printf("inName %d is %s\n", i, inName[i]);

        }
        // sscanf(gateLine, "%s\n", outName);
        *outName = strtok_r(temp, "\n", &temp);
        
        //printf("outname is %s\n", outName);


        bool inVal[inputs];
        var_t* curr = varList;
        while(curr)
        {
            for(int i=0; i<inputs; i++)
            {
                if(strcmp(curr->name, inName[i])==0)
                {
                    inVal[i] = curr->val;
                    //printf("inName %s is matched, inVal is %d\n", inName[i], inVal[i]);
                }
            }
            curr = curr->prev;
        }

            if(strcmp(gate, "AND")==0)
            {
                *outVal = inVal[0];
                for(int i=1; i<inputs; i++)
                {
                    *outVal = *outVal && inVal[i];
                }
            }
            else if(strcmp(gate, "NAND")==0)
            {
                *outVal = inVal[0];
                for(int i=1; i<inputs; i++)
                {
                    *outVal = *outVal && inVal[i];
                }
                *outVal = !(*outVal);
            }
            else if(strcmp(gate, "OR")==0)
            {
                *outVal = inVal[0];
                for(int i=1; i<inputs; i++)
                {
                    *outVal = *outVal || inVal[i];
                }
            }
            else if(strcmp(gate, "NOR")==0)
            {
                *outVal = inVal[0];
                for(int i=1; i<inputs; i++)
                {
                    *outVal = *outVal || inVal[i];
                }
                *outVal = !(*outVal);
            }     
            else
            {
                perror("invalid line describing gate in circuit file\n");
                exit(EXIT_FAILURE);                
            }
            free(inName);
            //printf("outName is %s, outVal is %d\n", *outName, *outVal);

    }
}


// PRINT A SINGLE ROW OF THE TRUTH TABLE GIVEN INITIAL ASSIGNMENTS TO CIRCUIT INPUTS
void printTruthTableRow (
    FILE* circuit_fp,
    size_t circuitInputBits // Vector of Boolean assignments for input bits
) {

    // Record input variable names
    size_t circuitInputCount;
    assert ( fscanf(circuit_fp, "INPUTVAR %ld ", &circuitInputCount)==1 );
    var_t* inputs = calloc( circuitInputCount, sizeof(var_t) ); // We use an array of var_t here
    for ( size_t i=0; i<circuitInputCount; i++ )
        assert ( fscanf(circuit_fp, "%s", inputs[i].name)==1 );
    assert ( fscanf(circuit_fp, "\n")==0 );

    // Record output variable names
    size_t circuitOutputCount;
    assert ( fscanf(circuit_fp, "OUTPUTVAR %ld ", &circuitOutputCount)==1 );
    var_t* outputs = calloc( circuitOutputCount, sizeof(var_t) ); // We use an array of var_t here
    for ( size_t i=0; i<circuitOutputCount; i++ )
        assert ( fscanf(circuit_fp, "%s", outputs[i].name)==1 );
    assert ( fscanf(circuit_fp, "\n")==0 );

    // Reversed linked list of variable structs
    var_t* varList = NULL;
    // Initialize the list with initial assignments to input variables
    for ( size_t i=0; i<circuitInputCount; i++ ) {
        var_t* temp = calloc( 1, sizeof(var_t) );
        // https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
        strcpy(temp->name, inputs[i].name);
        temp->val = 0b1 & circuitInputBits>>i; // Each bit in input bits
        temp->prev = varList;
        varList = temp;
    }

    // Read the rest of the circuit file consisting of gates line by line
    char* line = NULL;
    size_t len = 0;
    char* outName;
    // free(outName);
    while(getline(&line, &len, circuit_fp)!=-1)
    {
    // https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline--

    // THIS IS CURRENTLY SET UP TO READ A CIRCUIT FILE LINE FOR A SINGLE GATE
    /* ... */
    //assert ( getline(&line, &len, circuit_fp)!=-1 );

    //char* outName = malloc(NAME_SIZE*sizeof(char));
    bool outVal=false;
    findOutVarNameVal( varList, line, &outName, &outVal );
    //printf("outName is %s, outval is \n", *outName);
    // Record this gate's outputs
    var_t* temp = calloc( 1, sizeof(var_t) );
    // https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
    strcpy(temp->name, outName);
    //printf("outName is %s, outval is \n", outName);
    //free(outName);
    temp->val = outVal;
    temp->prev = varList;
    varList = temp;
    free(line);
    line = NULL;
    len = 0;
    }
    /* ... */

    // Print the truth table
    for ( size_t i=0; i<circuitInputCount; i++ ) {
        var_t* curr = varList;
        while (curr) {
            if ( strcmp(curr->name, inputs[i].name)==0 ) {
                printf ( "%d ", curr->val );
                break;
            }
            curr = curr->prev;
        }
    }
    for ( size_t i=0; i<circuitOutputCount; i++ ) {
        var_t* curr = varList;
        while (curr) {
            if ( strcmp(curr->name, outputs[i].name)==0 ) {
                printf ( "%d ", curr->val );
                break;
            }
            curr = curr->prev;
        }
    }
    printf("\n");

    free(line);
    while (varList) {
        // printf ( "\n%s %d", varList->name, varList->val );
        var_t* temp = varList;
        varList = varList->prev;
        free(temp);
    }
    free(outputs);
    free(inputs);
}


int main(int argc, char* argv[]) {

    if (argc!=2) {
        printf("Usage: ./basicGates <circuit_file>\n");
        exit(EXIT_FAILURE);
    }

    // Open circuit file
    FILE* circuit_fp = fopen(argv[1], "r");
    if (!circuit_fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    // Peak at the input count so we know how many rows in the truth table
    size_t circuitInputCount;
    assert ( fscanf(circuit_fp, "INPUTVAR %ld ", &circuitInputCount)==1 );

    // CURRENTLY SET UP TO PRINT JUST TWO ROWS OF THE TRUTH TABLE

    // // Rewind circuit file for each truth table line
    // rewind(circuit_fp);
    // printTruthTableRow (circuit_fp, 0);

    // // Rewind circuit file for each truth table line
    // rewind(circuit_fp);
    // printTruthTableRow (circuit_fp, 1);
    for(int i=0; i<pow(2,circuitInputCount); i++)
    {
        rewind(circuit_fp);
        printTruthTableRow (circuit_fp, i);
    }

    fclose(circuit_fp);
    exit(EXIT_SUCCESS);
}
