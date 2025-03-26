`timescale 1ns / 1ps

module PC_INC(
  input clk, rst, PC_increment,
  input [9:0]next_PC,
  output reg [9 : 0]PC
);

always @(posedge clk) begin
  if(rst != 0) begin
    PC <= 0;
  end
  else if(PC_increment == 1) begin
    PC <= next_PC;
  end
end

endmodule
