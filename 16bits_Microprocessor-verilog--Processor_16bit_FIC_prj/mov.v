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

module mov(
    input [15:0] data_acc,
    input [15:0] data_imm,
    input sel_imm, en,
    output reg [15:0] data_out
);

always @(*)begin
  if(en)begin
    case (sel_imm)
      1'b0: data_out = data_acc;
      1'b1: data_out = data_imm;
    endcase

  end
end
endmodule