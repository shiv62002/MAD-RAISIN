/* (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

/* DO NOT MODIFY THIS FILE OR YOUR CODE WILL NOT COMPILE ON THE SUBMIT
 * SERVER. */

#define NUM_BYTES (64 * 1024)
#define BYTES_PER_WORD 4
#define NUM_WORDS (NUM_BYTES / BYTES_PER_WORD)
enum register_name {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9,
                    R10, R11, R12, R13, R14, R15, R16, R17};
enum opcode_name {HALT, SYSCALL, ADD, SUB, MUL, QUOT, MOD, AND, OR, NEG,
                  NOT, EQL, NEQ, LT, LE, GT, GE, MOVE, LW, SW, LI, BRANCH};

unsigned short print_instruction(unsigned int instruction);
int load_program(unsigned int memory[], const unsigned int program[],
                 unsigned int start_addr, unsigned short pgm_size,
                 unsigned short data_segment_size);
unsigned short disassemble(const unsigned int memory[],
                           unsigned int start_addr, unsigned int pgm_size,
                           unsigned int data_segment_size);
