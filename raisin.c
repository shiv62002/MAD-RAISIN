/*Shiv Patel, shiv2266, 117839807, 0203*/
/*I pledge on my honor that I have not given or recieved any unauthorized
 * assistance on this examination or assignment.*/

#include "raisin.h"
#include <stdio.h>

/*This function analyzes passed in instructions and prints them accordingly*/
unsigned short print_instruction(unsigned int instruction) {
  /*Bitwise operation (32-5=27) to aquire the first 5 bits for opcode*/
  unsigned int opcode = (instruction) >> 27;
  /*Bitwise operation (32-10=22) to aquire the next 5 bits for register 1*/
  unsigned int register1_shift = (instruction) >> 22;
  /*31 is decimal form of 11111 used for masking to get register1 values*/
  unsigned int register1 = (register1_shift & 31);
  /*Bitwise operation (32-15=17) to aquire next 5 bits for register 2*/
  unsigned int register2_shift = (instruction) >> 17;
  /*31 is decimal form of 11111 used for masking to get register1 values*/
  unsigned int register2 = (register2_shift & 31);
  /*131071 is decimal form of 11111111111111111 used for masking address*/
  unsigned int address = (instruction & 131071);

  /*checks to ensure that the function input is valid based on constraints*/
  if ((opcode < 0 || opcode > 21) || (register1 < 0 && register1 > 17) ||
      (register2 < 0 && register2 > 17) ||
      (((address % 4) != 0) && (opcode != LI)) ||
      ((opcode >= 2 && opcode <= 8) && (register1 == 16 || register1 == 17))) {
    return 0;
  }

  /*Prints approproate opcode value based on instruction*/
  if (opcode == HALT) {
    printf("halt");
  } else if (opcode == SYSCALL) {
    printf("syscall");
  } else if (opcode == ADD) {
    printf("add");
  } else if (opcode == SUB) {
    printf("sub");
  } else if (opcode == MUL) {
    printf("mul");
  } else if (opcode == QUOT) {
    printf("quot");
  } else if (opcode == MOD) {
    printf("mod");
  } else if (opcode == AND) {
    printf("and");
  } else if (opcode == OR) {
    printf("or");
  } else if (opcode == NEG) {
    printf("neg");
  } else if (opcode == NOT) {
    printf("not");
  } else if (opcode == EQL) {
    printf("eql");
  } else if (opcode == NEQ) {
    printf("neq");
  } else if (opcode == LT) {
    printf("lt");
  } else if (opcode == LE) {
    printf("le");
  } else if (opcode == GT) {
    printf("gt");
  } else if (opcode == GE) {
    printf("ge");
  } else if (opcode == MOVE) {
    printf("move");
  } else if (opcode == LW) {
    printf("lw");
  } else if (opcode == SW) {
    printf("sw");
  } else if (opcode == LI) {
    printf("li");
  } else if (opcode == BRANCH) {
    printf("branch");
  }

  /*Checks if the opcode is within bounds for values that print both registers*/
  if ((opcode >= 2 && opcode <= 8) || (opcode >= 11 && opcode <= 17)) {
    printf(" R%u", register1);
    printf(" R%u", register2);
  }

  /*Checks if opcode is in bound for values printing just 1 register*/
  if ((opcode >= 9 && opcode <= 10) || (opcode >= 18 && opcode <= 20)) {
    printf(" R%u", register1);
  }

  /*Checks for case li in opcode to print address without leading zeroes*/
  if (opcode == LI) {
    printf(" %5u", address);
  } 
  
  /*Prints address of non li cases for valid addresses with leading zeroes*/
  if ((opcode > 17) && (opcode < 22) && address % 4 == 0 && opcode != LI) {
    printf(" %05u", address);
  }

  printf("\n");
  return 1;
}

/*This function copies the program into memory while excluding extra data*/
int load_program(unsigned int memory[], const unsigned int program[],
                 unsigned int start_addr, unsigned short pgm_size,
                 unsigned short data_segment_size) {

  /*Starting index where the memory array starts getting copies from*/
  int memory_start_index = (start_addr / 4);
  /*i and j are incremental variables used in for loops*/
  int i = 0;
  int j = 0;

  /*Checks for any invalid constraints*/
  if ((start_addr > NUM_WORDS) || (start_addr % 4 != 0) ||
      (pgm_size > NUM_WORDS) || ((pgm_size - data_segment_size) < 1)) {
    return 0;
  }

  /*loops through program array to copy valyes at specific start index and
  intentionally excludes additional data values at the end of program array */
  for (i = memory_start_index;
       i < (pgm_size) + (memory_start_index); i++) {
    memory[i] = program[j++];
  }

  return 1;
}

/*Checks  validity for print_instruction function call in disassemble function*/
unsigned short check_validity(unsigned int instruction) {
  unsigned int opcode = (instruction) >> 27;
  unsigned int register1_shift = (instruction) >> 22;
  unsigned int register1 = (register1_shift & 31);
  unsigned int register2_shift = (instruction) >> 17;
  unsigned int register2 = (register2_shift & 31);
  unsigned int address = (instruction & 131071);

  /*Checks and returns zero for any invalid instructions*/
  if ((opcode < 0 || opcode > 21) || (register1 < 0 && register1 > 17) ||
      (register2 < 0 && register2 > 17) ||
      (((address % 4) != 0) && (opcode != LI)) ||
      ((opcode >= 2 && opcode <= 8) && (register1 == 16 || register1 == 17))) {
    return 0;
  }
  /*returns 1 for valid arguments*/
  return 1;
}

/*Converts machine lang to assembly lang by printing instrictions, then
prinitng the additional data values from the memory array*/
unsigned short disassemble(const unsigned int memory[], unsigned int start_addr,
                           unsigned int pgm_size,
                           unsigned int data_segment_size) {

  /*This increments the values the for loops used in this function*/
  int i;
  int memory_start_index = (start_addr / 4);

  /*Checks for invalid inputs passed into the disassemble function*/
  if (pgm_size > NUM_WORDS || memory_start_index > NUM_WORDS ||
      ((pgm_size - data_segment_size) < 1) || start_addr % 4 != 0) {
    return 0;
  }

  /*Loops through specific area of memory to check for invalid inputs for
  the print_instruction function*/
  for (i = memory_start_index;
       i < (memory_start_index + pgm_size) - (data_segment_size); i++) {
    if (check_validity(memory[i]) == 0) {
      return 0;
    }
  } 

  /*Loops through specific area of memory to print the instruction values
   derrived from the memory array */
  for (i = memory_start_index;
       i < (memory_start_index + pgm_size) - (data_segment_size); i++) {
    print_instruction(memory[i]);
  }

  /*Loops through remaining array of memory to get the data values derrived
 from the memory array*/
  for (i = (memory_start_index + pgm_size) - (data_segment_size);
       i < pgm_size + memory_start_index; i++) {
    printf("%08x\n", memory[i]);
       }
                        
  return 1;
}