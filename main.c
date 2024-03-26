#include <stdio.h>
#include <stdlib.h>


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
void execute();
void dump();


int main(void) {

    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
    "*** Welcome to Simpletron! ***",
    "*** Please enter your program one instruction ***",
    "*** (or data word) at a time. I will type the ***",
    "*** location number and a question mark (?).  ***",
    "*** You then type the word for that location. ***",
    "*** Type the sentinel -99999 to stop entering ***",
    "*** Your Program ***");

    int memory[100] = {0};
    
    int accumulator = 0;
    int instructionCounter = 0;
    int instructionRegister = 0;
    int operationCode = 0;
    int operand = 0;

    load(memory, instructionCounter);

    for (size_t i = 0; i < 100; i++) {

        printf("%d", memory[i]);

    }

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


