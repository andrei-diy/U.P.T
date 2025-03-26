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

module mux2_1 #(parameter N=16)(
  
    input [N - 1: 0] data_in0, data_in1,
    input sel,
    output [N - 1: 0] data_out
);

assign data_out = sel ? data_in1 : data_in0;

endmodule