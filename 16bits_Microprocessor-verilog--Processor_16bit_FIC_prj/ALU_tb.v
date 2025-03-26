`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Team: 
// Member: 
// 
// Create Date:    13:38 10/12/2022 
// Module Name:    Control_Unit 
// Project Name:   Pocket_Calculator_Processor
//
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module ALU_tb(
 output reg  [15:0] A,  
 output reg  [15:0] B,
 output reg  enable,
 output reg[ 5:0] opcode, 
 
 output [15:0] Result,  
 output [ 3:0] flags
    );

`include "alu_ops.v"
    
ALU DUT(.A(A),
        .B(B),
        .enable(enable),
        .opcode(opcode),
        .Result(Result),
        .flags(flags));

initial begin

#10 enable = 1;opcode = `ALU_ADD;
#10 A = 10; B = 1;
#10 opcode = `ALU_SUB;
#10 opcode = `ALU_LSR;
#10 opcode = `ALU_LSL;
#10 opcode = `ALU_RSR;
#10 opcode = `ALU_RSL;
#10 opcode = `ALU_MUL;
#10 opcode = `ALU_DIV;
#10 opcode = `ALU_MOD;
#10 opcode = `ALU_AND;
#10 opcode = `ALU_OR;
#10 opcode = `ALU_XOR;
#10 opcode = `ALU_CMP;
#10 opcode = `ALU_TST;
#10 opcode = `ALU_NOT;
#10 opcode = `ALU_INC;
#10 opcode = `ALU_DEC;
#10 opcode = `ALU_NOP;
end

endmodule