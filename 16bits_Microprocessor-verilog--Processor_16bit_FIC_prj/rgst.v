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

module rgst #(parameter N=16)(
    input clk, rst, en,
    input [N-1:0]resetval,
    input [N-1:0] d,
    output reg [N-1:0] q 
);

always @(posedge clk) begin
	if(rst != 0)
		q <= resetval;
	else if(en)
		q <= d;
end

endmodule