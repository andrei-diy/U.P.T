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

module ALU(
 input  [15:0] A, // reg 
 input  [15:0] B, // reg sau immediate
 input  enable,
 input  [4:0]opcode, 
 
 output reg [15:0] Result,  
 output reg [ 3:0] flags
    );
    
reg [16:0] aux = 17'd0;
reg [15:0] R; 
reg cmp_enable = 0;
reg [15:0]BB;
integer i;

`include "alu_ops.v"

`define Z	3
`define N	2
`define C	1
`define O	0

always @(*)
begin 
 if(enable)
 begin
   aux = 17'd0;
   flags = 4'd0;
  
   case(opcode)
   `ALU_ADD: begin 
    	      aux = A + B;
	      if(!A[15] && !B[15] && aux[15]) flags[`O] = 1;
              if(A[15] && B[15] && !aux[15]) flags[`O] = 1;
	      cmp_enable = 0;
             end
   `ALU_SUB: begin 
              if(B[15]) BB = ~(B-1); // TRANSFORMAM B in nr pozitiv  pt cazul a - -b = a +  b  
                   else BB = (~B)+1; // TRANSFORMAM B in nr negativ  pt cazul a - +b = a + -b 
              aux = A + BB;
              if(!A[15] && !BB[15] && (aux[15]==1)) flags[`O] = 1;
              if( A[15] &&  BB[15] &&!(aux[15]==1)) flags[`O] = 1;
	      cmp_enable = 0;
             end      
   `ALU_LSR: begin 
              aux = A;
              aux = aux >> B;
	      cmp_enable = 0;
	     end
   `ALU_LSL: begin
             aux = A;
             aux = aux << B;
	      cmp_enable = 0;
             end 
          
   `ALU_RSR: begin
             aux = A;
             R = B;
             while(R>0)
              begin 
                aux[16] = A[0];
                aux = aux >> 1;
                R = R - 1;
              end
	      cmp_enable = 0;
             end
   `ALU_RSL: begin
             aux = A;
             R = B;
             while(R>0)
              begin 
                aux = aux << 1;
                aux[0] = aux[16];
                R = R - 1;
              end
	      cmp_enable = 0;
             end
   `ALU_MUL: begin 
              aux = A * B;
	      if(aux / A != B) flags[`O] = 1;
	      cmp_enable = 0;
	      end
   `ALU_DIV: begin 
              aux = A / B;
	      if(B == 16'b0) begin
		aux = 16'b1111111111111111;
	        flags[`O] = 1;
	      end
	      cmp_enable = 0;
             end
   `ALU_MOD: begin 
              aux = A % B;
	      cmp_enable = 0;
             end
   `ALU_AND: begin 
              aux = A & B;
	      cmp_enable = 0;
             end
   `ALU_OR: begin 
              aux = A | B;
	      cmp_enable = 0;
             end 
   `ALU_XOR: begin 
              aux = A ^ B;
	      cmp_enable = 0;
             end
   `ALU_CMP: begin         //flag [ zero, neg, carry, overflow ]
              cmp_enable = 1'b1;
              if(B[15]) BB = ~(B-1); // TRANSFORMAM B in nr pozitiv  pt cazul a - -b = a +  b  
                   else BB = (~B)+1; // TRANSFORMAM B in nr negativ  pt cazul a - +b = a + -b 
              aux = A + BB;
              if(!A[15] && !BB[15] && (aux[15]==1)) flags[`O] = 1;
              if( A[15] &&  BB[15] &&!(aux[15]==1)) flags[`O] = 1;
             end
   `ALU_TST: begin 
              // N/A
	      cmp_enable = 0;
             end
   `ALU_NOT: begin 
              aux = ~A;
	      cmp_enable = 0;
             end
   `ALU_INC: begin 
              aux = A + 1;
	      cmp_enable = 0;
             end
   `ALU_DEC: begin 
              aux = A - 1;
	      cmp_enable = 0;
             end
   `ALU_LOG2: begin
	       aux = 0;
	       for(i = 0; 2**i <= A; i = i + 1)
	        aux = i;
	       if(A[15] == 1 || A == 0) begin
		aux = 16'b1111111111111111;
	       end
	      cmp_enable = 0;
	     end
   `ALU_MODULE: begin
	       aux = A;
	       if(A[15] == 1'b1) begin
		aux = ~A + 1'b1;
	       end
	      cmp_enable = 0;
	     end
   `ALU_FACTRL: begin
	       aux = 1;
	       for(i = 1; i <= A; i = i + 1)
		  aux = aux * i;
	       if(A[15] == 1'b1)begin //pentru factorial de numere negative
		  aux = 16'b1111111111111111;
	       end
	      cmp_enable = 0;
	     end
   `ALU_NOP: begin 
              // no operation needed
	      cmp_enable = 0;
             end                                                                                     
   endcase
   if(cmp_enable == 0)
	Result = aux[15:0];
   if(aux[16]==1) flags[`C] = 1;   // carry
   if(aux[15:0] == 16'd0) flags[`Z] = 1;     // zero
   if(aux[15]==1) flags[`N] = 1;      // negative
 end
end
endmodule
