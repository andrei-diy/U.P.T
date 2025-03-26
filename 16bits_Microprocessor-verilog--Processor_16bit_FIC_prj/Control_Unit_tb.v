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
module Control_Unit_tb(
	output reg [5:0]opcode,
	output reg clk, rst,
	output reg [3:0] flags,
	output [4:0]alu_op,
	output immediate, bra, RD, WR, alu_en, psh, pop, hlt, mov_en
    );

`include "opcodes.v"
`include "alu_ops.v"

Control_Unit DUT (
	.opcode(opcode),
	.clk(clk),
	.rst(rst),
	.flags(flags),
	.immediate(immediate),
	.alu_op(alu_op),
	.bra(bra),
	.RD(RD),
	.WR(WR),
	.alu_en(alu_en),
	.psh(psh),
	.pop(pop),
	.hlt(hlt),
	.mov_en(mov_en)
); 


initial begin
  clk = 1'b0;
  forever #25 clk = ~clk;
end

initial begin
  	flags = 4'b1010;
  	#30 opcode = `BRZ;
	#50 opcode = `BRN;
	#50 opcode = `BRC;
	#50 opcode = `BRO;
	#50 opcode = `BRA;
	#50 opcode = `JMP;
	#50 opcode = `RET;
	#50 opcode = `LDR;
	#50 opcode = `STR;
	#50 opcode = `ADDXY;
	#50 opcode = `SUBXY;
	#50 opcode = `LSRXY;
	#50 opcode = `LSLXY;
	#50 opcode = `RSRXY;
	#50 opcode = `RSLXY;
	#50 opcode = `MULXY;
	#50 opcode = `DIVXY;
	#50 opcode = `MODXY;
	#50 opcode = `ANDXY;
	#50 opcode = `ORXY;
	#50 opcode = `XORXY;
	#50 opcode = `CMPXY;
	#50 opcode = `TSTXY;
	#50 opcode = `NOTXY;
	#50 opcode = `ADDRI;
	#50 opcode = `SUBRI;
	#50 opcode = `LSRRI;
	#50 opcode = `LSLRI;
	#50 opcode = `RSRRI;
	#50 opcode = `RSLRI;
	#50 opcode = `MULRI;
	#50 opcode = `DIVRI;
	#50 opcode = `MODRI;
	#50 opcode = `ANDRI;
	#50 opcode = `ORRI;
	#50 opcode = `XORRI;
	#50 opcode = `CMPRI;
	#50 opcode = `TSTRI;
	#50 opcode = `NOTRI;
	#50 opcode = `INC;
	#50 opcode = `DEC;
	#50 opcode = `MOVR;
	#50 opcode = `MOVI;
	#50 opcode = `PSH;
	#50 opcode = `POP;
	#50 opcode = `NOP;
	#50 opcode = `HLT;
end

endmodule