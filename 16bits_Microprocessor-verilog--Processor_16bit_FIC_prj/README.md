# PCP

## Theme:

### **General Purpose Processor - Pocket Calculator**

<br />
<br />

# Project Technical Specifications:

## Components:

- 2 general purpose registers: X, Y
- 1 accumulator A
- ALU
- Control Unit
- Instruction and Data memory (Including Stack)
- Sign Extend Unit
- Processor registers: PC, SP, Flag

## Sizes:

- Registers:
    - 16-bit Accumulator
    - 2 of 16-bit general purpose (GP) registers: X and Y
    - 4-bit Flag register: Zero, Negative, Carry, Overflow
    - 16-bit stack pointer
    - 6-bit Program Counter
- Instructions:
    - 16-bit instruction size
        - 6-bit op-code
        - 1-bit Register address
        - 9-bit Immediate size ( [-256:255] )
- Word:
    - 16-bit word size
- Stack:
    
    Grows inverse in memory
    

## Instructions:

### Memory instructions:

- Load
- Store

| Opcode | Register Address | Immediate |
| --- | --- | --- |
| 6 bit | 1 bit | 9 bit |

### Branch instructions:

- BRZ = brach if zero
- BRN = branch if negative
- BRC = branch if carry
- BRO = branch if overflow
- BRA = branch always (unconditional branch)
- JMP = call procedure
- RET = return from procedure

| Opcode | Address |
| --- | --- |
| 6 bit | 10 bit |

### ALU:

- ADD
- SUB
- LSR
- LSL
- RSR
- RSL
- MOV
- MUL
- DIV
- MOD
- AND
- OR
- XOR
- NOT
- CMP
- TST
- INC
- DEC

| Opcode | Register Address | Immediate |
| --- | --- | --- |
| 6 bit | 1 bit | 9 bit |

## Additional operations:

- Logarithm
- Factorial
- Module
- Sin