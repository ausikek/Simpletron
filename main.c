#include <stdio.h>
#include <stdlib.h>


// Memory Size

#define SIZE 1000

// Input/Output operations

#define READ 10
#define WRITE 11

// Load/Store operations

#define LOAD 20
#define STORE 21

// Arithmetic operations

#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

// Transfer-of-control operations

#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43


void load(int memory[], int instructionCounter);
void execute(int memory[], int* accumulator, int* instructionCounter, 
            int* instructionRegister, int* operationCode, int* operand);
void dump(int memory[], int* accumulator, int* instructionCounter, 
            int* instructionRegister, int* operationCode, int* operand);


int main(void) {

    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
    "*** Welcome to Simpletron! ***",
    "*** Please enter your program one instruction ***",
    "*** (or data word) at a time. I will type the ***",
    "*** location number and a question mark (?).  ***",
    "*** You then type the word for that location. ***",
    "*** Type the sentinel -99999 to stop entering ***",
    "*** Your Program ***");

    int memory[SIZE] = {0};
    
    int accumulator = 0;
    int instructionCounter = 0;
    int instructionRegister = 0;
    int operationCode = 0;
    int operand = 0;

    load(memory, instructionCounter);

    execute(memory, &accumulator, &instructionCounter,
           &instructionRegister, &operationCode, &operand); 

}


void load(int memory[], int instructionCounter) {
    
    int sentinel = 0;

    int input = 0;
    
    while (sentinel == 0) {

        while (1) {

            printf("%02d ? ", instructionCounter);

            scanf("%d", &input);

            if (input == -99999) {

                printf("%s\n%s\n",
                "*** Program loading complete ***",
                "*** Program execution begins ***");   

                sentinel = -1;

                break;                   

            } else if (input < -9999 || input > 9999) {

                printf("\nPlease insert a valid instruction.\n");          

            } else {
                
                memory[instructionCounter] = input;
                instructionCounter++;

                break;

            }
        }
    }
}


void execute(int memory[], int* accumulator, int* instructionCounter, 
            int* instructionRegister, int* operationCode, int* operand) {

    int sentinel = 0;

    while (sentinel == 0) {

        *instructionRegister = memory[*instructionCounter];

        *operationCode = *instructionRegister / 100;
        *operand = *instructionRegister % 100;


        switch (*operationCode) {

            case READ:

                printf("? ");    
                scanf("%d", &memory[*operand]);

                
                if (memory[*operand] < 9999 && memory[*operand] > -9999) {

                ++*instructionCounter;
                
                break;
                
                } else {

                    printf("%s\n%s\n", "*** ACCUMULATOR OVERFLOW ***", "*** Please insert a valid number ***");
                    
                    break;

                }

            case WRITE:

                printf(memory[*operand] > 0 ? "%+05d\n" : "%05d\n", memory[*operand]);
                ++*instructionCounter;

                break;

            case LOAD:

                *accumulator = memory[*operand];
                ++*instructionCounter;

                break;

            case STORE:

                memory[*operand] = *accumulator;
                ++*instructionCounter;

                break;

            case ADD:

                if (*accumulator + memory[*operand] < 9999 && *accumulator + memory[*operand] > -9999) {
                
                    *accumulator += memory[*operand];
                    ++*instructionCounter;

                    break;
                
                } else {

                    printf("*** ERROR: ACCUMULATOR OVERFLOW ***\n");
                    printf("*** Simpletron Execution abnormally terminated ***\n");

                    dump(memory, accumulator, instructionCounter,
                    instructionRegister, operationCode, operand);

                    sentinel = -1;
                    
                    break;

                }

            case SUBTRACT:

               if (*accumulator - memory[*operand] < 9999 && *accumulator - memory[*operand] > -9999) {
                
                    *accumulator -= memory[*operand];
                    ++*instructionCounter;

                    break;
                
                } else {

                    printf("*** ERROR: ACCUMULATOR OVERFLOW ***\n");
                    printf("*** Simpletron Execution abnormally terminated ***\n");

                    dump(memory, accumulator, instructionCounter,
                    instructionRegister, operationCode, operand);

                    sentinel = -1;
                    
                    break;

                }

            case DIVIDE:

                if (memory[*operand] != 0) {
                
                    *accumulator /= memory[*operand];
                    ++*instructionCounter;

                    break;
                
                } else {

                    printf("*** ERROR: DIVISION BY 0 ***\n");
                    printf("*** Simpletron Execution abnormally terminated ***\n");

                    dump(memory, accumulator, instructionCounter,
                    instructionRegister, operationCode, operand);

                    sentinel = -1;
                    
                    break;

                }

            case MULTIPLY:

                if (*accumulator * memory[*operand] < 9999 && *accumulator * memory[*operand] > -9999) {
                
                    *accumulator *= memory[*operand];
                    ++*instructionCounter;

                    break;
                
                } else {

                    printf("*** ERROR: ACCUMULATOR OVERFLOW ***\n");
                    printf("*** Simpletron Execution abnormally terminated ***\n");

                    dump(memory, accumulator, instructionCounter,
                    instructionRegister, operationCode, operand);

                    sentinel = -1;
                    
                    break;

                }

            case BRANCH:

                *instructionCounter = *operand;

                break;

            case BRANCHNEG:

                if (*accumulator < 0) {

                    *instructionCounter = *operand;
                
                } else {

                    ++*instructionCounter;

                }

                break;
            
            case BRANCHZERO:

                if (*accumulator == 0) {

                    *instructionCounter = *operand;

                } else {

                    *instructionCounter++;

                }

                break;

            case HALT:

                printf("*** Simpletron Execution Terminated ***\n");
                
                dump(memory, accumulator, instructionCounter,
                    instructionRegister, operationCode, operand);

                sentinel = -1;

                break;

        }
    }
}


void dump(int memory[], int* accumulator, int* instructionCounter, 
            int* instructionRegister, int* operationCode, int* operand) {

    printf("\n%s\n", "REGISTERS:");
    printf("%s","accumulator: ");
    printf(*accumulator > 0 ? "%+05d\n" : "%05d\n", *accumulator);
    printf("instructionCounter: %02d\n", *instructionCounter);
    printf("%s","instructionRegister: ");
    printf(*instructionRegister > 0 ? "%+05d\n" : "%05d\n", *instructionRegister);
    printf("operationCode: %02d\n", *operationCode);
    printf("operand: %02d\n", *operand);

    
    printf("\n%s\n\n", "MEMORY: ");

    
    for (size_t j = 0; j < 10; j++) {

        printf("\t%5lu", j);

    }

    
    printf("\n\n");
    
    
    for (size_t i = 0; i < SIZE; i++) {

        if (i % 10 == 0) {

            printf("%lu\t", i);

        }

        printf(memory[i] >= 0 ? "%+05d" : "%05d", memory[i]);
        printf((i+1) % 10 == 0 ? "\n" : "\t");

    }

    printf("\n");
}