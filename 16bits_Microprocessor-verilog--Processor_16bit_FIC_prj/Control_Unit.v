`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:52 09/12/2022 
// Design Name: 
// Module Name:    Control_Unit 
// Project Name:   Pocket_Calculator_Processor
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module Control_Unit(
	input [15:0]IR,
	input clk, rst, CU_en,
	input [3:0]flags,
	output reg [4:0]alu_op,
	output reg immediate, bra, RD, WR, alu_en, psh, pop, hlt, mov_en,
	output reg [8:0]imm_value,
	output reg ir9sel, ir0sel,
	output reg [9:0]BADR
    );

`include "opcodes.v"
`include "alu_ops.v"

`define Z	3
`define N	2
`define C	1
`define O	0

always @(posedge clk) begin
  imm_value = IR[8:0];
  ir9sel = IR[9];
  ir0sel = IR[0];
  BADR = IR[9:0];
  if (rst != 0) begin
    		bra = 0;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	else if(CU_en == 1'b1) begin
  case(IR[15:10])
	`BRA: begin 
		bra = 1;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`BRZ: begin
		bra = flags[`Z];
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`BRN: begin
		bra = flags[`N];
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`BRC: begin
		bra = flags[`C];
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end 
	`BRO: begin
		bra = flags[`O];
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end  
	`JMP: begin
		bra = 1;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`RET: begin
     		bra = 1;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`LDR: begin
		bra = 0;
		immediate = 0;
		alu_en = 0;
		RD = 1;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`STR: begin
		bra = 0;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 1;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`ADDXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_ADD;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`SUBXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_SUB;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`LSRXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_LSR;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`LSLXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_LSL;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`RSRXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_RSR;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`RSLXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_RSL;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
	end
	`MULXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_MUL;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`DIVXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_DIV;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`MODXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_MOD;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`ANDXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_AND;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`ORXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_OR;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`XORXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_XOR;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`CMPXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_CMP;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`TSTXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_TST;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`NOTXY: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_NOT;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`ADDRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_ADD;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`SUBRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_SUB;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`LSRRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_LSR;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`LSLRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_LSL;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`RSRRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_RSR;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`RSLRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_RSL;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`MULRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_MUL;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`DIVRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_DIV;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`MODRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_MOD;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`ANDRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_AND;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`ORRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_OR;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`XORRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_XOR;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`CMPRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_CMP;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`TSTRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_TST;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`NOTRI: begin
		bra = 0;
		immediate = 1;
		alu_en = 1;
		alu_op = `ALU_NOT;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`INC: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_INC;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`DEC: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_DEC;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`LOG2: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_LOG2;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`MODULE: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_MODULE;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`FACTRL: begin
		bra = 0;
		immediate = 0;
		alu_en = 1;
		alu_op = `ALU_FACTRL;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`MOVR: begin
		bra = 0;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 1;
	end
	`MOVI: begin
		bra = 0;
		immediate = 1;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 1;
	end
	`PSH: begin
		bra = 0;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 1;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`POP: begin
		bra = 0;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 1;
		hlt = 0;
		mov_en = 0;
	end
	`NOP: begin
		bra = 0;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 0;
		mov_en = 0;
	end
	`HLT: begin
		bra = 1;
		immediate = 0;
		alu_en = 0;
		RD = 0;
		WR = 0;
		psh = 0;
		pop = 0;
		hlt = 1;
		mov_en = 0;
	end
  endcase
end

end

endmodule















