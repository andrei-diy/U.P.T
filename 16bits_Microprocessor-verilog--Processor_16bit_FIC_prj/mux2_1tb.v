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

module mux2_1tb(
  output reg [15 :0] data_in1, data_in0,
  output reg sel,
  output [15: 0] data_out
);

mux2_1 DUT
  ( .data_in1(data_in1),
    .data_in0(data_in0),
    .sel(sel),
    .data_out(data_out)
  
  );

integer i;
initial begin 
  {sel, data_in1, data_in0} = 33'd0;
end 

initial begin
  #50 sel = 1'b1;
  #50 sel = 1'b0;  
end

initial begin
  #25 data_in1 = 16'd5;
   data_in0 = 16'd4;
  #30 data_in1 = 16'd6;
    data_in0 = 16'd7;
end

endmodule