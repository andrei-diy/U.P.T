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

module instrMem #(parameter N=16)(
	input clk, rst,
	input [9:0] PC,
	output reg [N-1:0] data
);
	reg [N-1:0] memory [0:(2**10)-1];


   always @(posedge clk) begin
	if (rst != 0) begin
	    $readmemh("/home/mariusp/Desktop/An_3_Faculta/FIC/risc_processor/git_repo/instructions.mem", memory);
	end
	else begin
	    data <= memory[PC];
	end
end
		
		
endmodule