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

module stackpointer #(parameter N=9)(
    input psh, pop,
    input [N-1:0] d,
    output [N-1:0] q 
);

/*
always @(posedge clk) begin
	if(psh)
		q <= d - 1;
	else if(pop)
		q <= d + 1;
end */

assign q = psh ? (d - 1) : ( pop ? (d + 1) : d);

endmodule
