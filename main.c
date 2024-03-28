#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Memory Size

#define SIZE 1000

// Input/Output operations

#define READ 0x0001
#define WRITE 0x0002
#define NEWLINE 0x0003

// Load/Store operations

#define LOAD 0x0004
#define STORE 0x0005

// Arithmetic operations

#define ADD 0x0006
#define SUBTRACT 0x0007
#define DIVIDE 0x0008
#define MULTIPLY 0x0009
#define MODULUS 0x000A
#define EXPONENTIATION 0x000B

// Transfer-of-control operations

#define BRANCH 0x000C
#define BRANCHNEG 0X000D
#define BRANCHZERO 0x000E
#define HALT 0x000F


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
    "*** Type the sentinel 0xFDEAD to stop entering ***",
    "*** Your Program ***");

    int memory[SIZE] = {0};
    
    int accumulator = 0x0;
    int instructionCounter = 0x0;
    int instructionRegister = 0x0;
    int operationCode = 0x0;
    int operand = 0x0;

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

            scanf("%x", &input);

            if (input == 0xFDEAD) {

                printf("%s\n%s\n",
                "*** Program loading complete ***",
                "*** Program execution begins ***");   

                sentinel = -1;

                break;                   

            } else if (input < -0xF3E7 || input > 0xF3E7) {

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

        *operationCode = *instructionRegister / 0x1000;
        *operand = *instructionRegister % 0x1000;


        switch (*operationCode) {

            case READ:

                printf("? ");    
                scanf("%d", &memory[*operand]);

                
                if (memory[*operand] < 2147483647 && memory[*operand] > -2147483648) {

                    ++*instructionCounter;
                    
                    break;
                
                } else {

                    printf("%s\n%s\n", "*** INTEGER OVERFLOW ***", 
                                    "*** Please insert a valid number ***");
                    
                    break;

                }

            case WRITE:

                printf(memory[*operand] > 0 ? "%+05d\n" : "%05d\n", memory[*operand]);

                ++*instructionCounter;

                break;

            case NEWLINE:

                printf("\n");
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

                if (*accumulator + memory[*operand] < 2147483647 && *accumulator + memory[*operand] > -2147483648) {
                
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

               if (*accumulator - memory[*operand] < 2147483647 && *accumulator - memory[*operand] > -2147483648) {
                
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

                if (*accumulator * memory[*operand] < 2147483647 && *accumulator * memory[*operand] > -2147483648) {
                
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

            case MODULUS:

            if (memory[*operand] != 0) {
                
                    *accumulator %= memory[*operand];
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

            case EXPONENTIATION:

                if (pow(*accumulator, memory[*operand]) < 2147483647 && pow(*accumulator, memory[*operand]) > -2147483648) {

                    *accumulator = (int) pow(*accumulator, memory[*operand]);
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

            default:

                if (*instructionCounter < 1000) {
                    
                    printf("*** Instruction not found, skipping to the next instruction... ***\n");
                    ++*instructionCounter;

                    break;
                
                } else {

                    printf("*** ERROR: SEGMENTATION FAULT (MEMORY OUT OF BOUNDS) ***\n");
                    printf("*** Simpletron execution abnormally terminated ***\n");

                    dump(memory, accumulator, instructionCounter,
                    instructionRegister, operationCode, operand);

                sentinel = -1;

                break;

                }
        }
    }
}


void dump(int memory[], int* accumulator, int* instructionCounter, 
            int* instructionRegister, int* operationCode, int* operand) {

    printf("\n%s\n", "REGISTERS:");
    printf("%s","accumulator: ");
    printf(*accumulator > 0 ? "%05x\n" : "%05x\n", *accumulator);
    printf("instructionCounter: %02d\n", *instructionCounter);
    printf("%s","instructionRegister: ");
    printf(*instructionRegister > 0 ? "%05x\n" : "%05x\n", *instructionRegister);
    printf("operationCode: %02d\n", *operationCode);
    printf("operand: %02d\n", *operand);

    
    printf("\n%s\n\n", "MEMORY: ");

    
    for (size_t j = 0; j < 10; j++) {

        printf("\t%10lu", j);

    }

    
    printf("\n\n");
    
    
    for (size_t i = 0; i < SIZE; i++) {

        if (i % 10 == 0) {

            printf("%lu\t", i);

        }

        printf(memory[i] >= 0 ? "0x%08x" : "%08x", memory[i]);
        printf((i+1) % 10 == 0 ? "\n" : "\t");

    }

    printf("\n");
}