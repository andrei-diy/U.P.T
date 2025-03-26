`timescale 1ns / 1ps
module cpu_tb (
    output reg clk, 
    output reset,
    output [1:0]st,
    output [1:0] st_next,
    output [9:0]PC,
    output [15:0] IR,
    output signed [15:0] X, Y, ACC,
    output [3:0] flags,
    output [8:0]stackpointer,
    output [9: 0] BADR,
    output [4:0]alu_op,
    output PC_en, CU_en,
    output hlt, bra, 
    output immediate, RD, WR, alu_en, psh, pop, mov_en
);

integer fd;

cpu DUT (.clk(clk), .bra(bra), .reset(reset), .PC_en(PC_en), .CU_en(CU_en), 
         .st(st), .st_next(st_next), .BADR(BADR), .hlt(hlt), .PC(PC),
	 .IR(IR), .flags(flags), .stackpointer(stackpointer), .alu_op(alu_op), .immediate(immediate),
	 .RD(RD), .WR(WR), .alu_en(alu_en), .psh(psh), .pop(pop), .mov_en(mov_en), .X(X), .Y(Y), .ACC(ACC));

initial begin
    clk = 1'b1;
    forever #25 clk = ~clk;
end

initial begin
    fd = $fopen("/home/mariusp/Desktop/An_3_Faculta/FIC/risc_processor/git_repo/outputs.txt", "w");
    #1000000 $fdisplay(fd, X);
    $fdisplay(fd, Y);
    $fdisplay(fd, ACC);
    #10 $fclose(fd);
    $finish;
end

endmodule
