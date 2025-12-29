# MAD Raisin CPU Simulator

## Project Description
This project implements a simple processor simulator in C by developing an assembler that interprets and executes instructions defined by the MAD Raisin CPU, a pre-existing 32-bit architecture. Each instruction word contains an opcode, up to two register operands, and a memory address or immediate value. The simulator reads these 32-bit words from memory, decodes their fields using bitwise operations, and performs the corresponding actions to emulate CPU behavior.

## How It Works
- The assembler loads binary instruction words into memory.
- Bit masks and shifts are used to extract:
  - the **opcode** (operation to perform)
  - up to **two registers** (used as operands depending on the instruction)
  - an **address / immediate value** (for memory-based instructions)
- Opcodes are mapped to processor functions, which update registers and memory to simulate execution flow.

## Skills Demonstrated
- Low-level C programming
- Bitwise manipulation and masking
- Parsing binary instruction formats
- Simulated processor execution
- UNIX-based development workflow
- Efficient code editing with Emacs

## Key Takeaways
This project highlights my ability to:
- Interpret and execute assembly-like instructions  
- Scan binary values and extract data using bit operators  
- Manage arrays and memory during instruction execution  
- Build a working processor simulation in C within a UNIX environment
