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

module dataMem #(parameter N=16) (
	input clk, WR, RD, psh, pop, rst,
	input [8:0] address,
	input [N-1:0] data_in,
	input [8:0]stackpointer,
	output reg [N-1:0] data_out
);
reg [N-1:0] memory [0:(2**9)-1];
integer i;	

always @(posedge clk) begin
    if(rst) begin
	for(i = 0; i <= 2**9-1; i = i + 1)
	    memory[i] = 0;
    end
    
    if(WR)
	memory[address] = data_in;
    if(RD)
	data_out = memory[address];
    if(psh)
	memory[stackpointer] = data_in;
    if(pop)
	data_out = memory[stackpointer + 1];
end

endmodule