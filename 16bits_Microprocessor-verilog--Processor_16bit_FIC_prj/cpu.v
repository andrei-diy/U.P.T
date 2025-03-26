`timescale 1ns / 1ps
module cpu (
    input clk, 
    output bra,
    output reg reset, PC_en, CU_en,
    output reg [1:0]st,
    output reg [1:0] st_next,
    output [9: 0] BADR,
    output hlt,
    output [9:0]PC,
    output [15:0] IR,
    output [3:0] flags,
    output [4:0]alu_op,
    output immediate, RD, WR, alu_en, psh, pop, mov_en,
    output [8:0]stackpointer,
    output [15:0]X, Y, ACC
);

localparam RESET = 2'd0;
localparam FETCH = 2'd1;
localparam DECODE = 2'd2;
localparam EXECUTE = 2'd3;

wire [9 : 0] out_hlt;
wire [9 : 0] next_PC;
wire [8 : 0] next_stackpointer;
wire [8:0] imm_value;
wire ir9sel;
wire ir0sel;
wire [15: 0] out_mov;
wire [15 : 0] seu_res;
wire [15 : 0] alu_in1;
wire [15 : 0] reg2;
wire [15 : 0] alu_in2;
wire [15: 0] out_mem;
wire [15:0] demux_in;

// initializam modulele

mux2_1 #(10) HLT_MUX  (.sel(hlt), .data_in0(BADR), .data_in1(PC), .data_out(out_hlt));
mux2_1 #(10) BRA_MUX  (.sel(bra), .data_in0(PC + 10'b1), .data_in1(out_hlt), .data_out(next_PC));
rgst #(10) PC_INC ( .clk(clk), .rst(reset), .en(PC_en), .d(next_PC), .q(PC), .resetval(10'b0));
instrMem #(16) INSTR_MEM (.clk(clk), .rst(reset), .PC(PC), .data(IR));
Control_Unit CU (.IR(IR), .clk(clk), .rst(rst), .flags(flags), .alu_op(alu_op), .immediate(immediate),
                 .bra(bra), .RD(RD), .WR(WR), .alu_en(alu_en), .psh(psh), .pop(pop),
                 .hlt(hlt), .mov_en(mov_en), .CU_en(CU_en), .imm_value(imm_value), .ir9sel(ir9sel), .ir0sel(ir0sel), .BADR(BADR));
SEU SE (.NR(imm_value), .result(seu_res));
mux2_1 #(16) REG1 (.sel(ir9sel), .data_in0(X), .data_in1(Y), .data_out(alu_in1));
mux2_1 #(16) REG2 (.sel(ir0sel), .data_in0(X), .data_in1(Y), .data_out(reg2));
mux2_1 #(16) ALU_IN (.sel(immediate), .data_in0(reg2), .data_in1(seu_res), .data_out(alu_in2));
ALU ARITHMETICLOGICUNIT (.A(alu_in1), .B(alu_in2), .enable(alu_en), .opcode(alu_op), .Result(ACC), .flags(flags));
mov MOVE (.data_acc(ACC), .data_imm(seu_res), .sel_imm(immediate), .en(mov_en), .data_out(out_mov));
mux2_1 #(16) MOV_OR_MEM (.sel(RD | pop), .data_in0(out_mov), .data_in1(out_mem), .data_out(demux_in));
dataMem #(16) DATA_MEM (.clk (clk), .rst(reset), .WR(WR), .RD(RD), .address(imm_value), .data_in(alu_in1), .data_out(out_mem),
			.stackpointer(stackpointer), .psh(psh & (PC_en & (~CU_en))), .pop(pop & (PC_en & (~CU_en))));
demux MEM_DEMUX (.data_in(demux_in), .sel(ir9sel), .en(RD | mov_en | pop), .data_out0(X), .data_out1(Y));
stackpointer #(9) SP (.psh(psh), .pop(pop), .d(stackpointer), .q(next_stackpointer));
rgst #(9) STACKP (.clk(clk), .rst(reset), .en((psh | pop) & PC_en), .d(next_stackpointer), .q(stackpointer), .resetval(9'd511));


always @(posedge clk) begin
    st = st_next;
end

always @(posedge clk) begin
    st_next = RESET;
    case (st) 
	RESET: begin
	       reset = 1;
	       PC_en = 0;
               CU_en = 1;
	       st_next = FETCH;
	       end
	FETCH: begin
	       reset = 0;
	       PC_en = 0;
               CU_en = 0;
	       st_next = DECODE;
	       end
	DECODE: begin
		reset = 0;
		PC_en = 0;
		CU_en = 1;
		if(bra == 1'b1)
		    st_next = FETCH;
		else
		    st_next = EXECUTE;
		end
	EXECUTE: begin
		 reset = 0;
		 PC_en = 1;
                 CU_en = 0;
		 st_next = FETCH;
		 end
    endcase
end


endmodule
