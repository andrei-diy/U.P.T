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

module SEU_tb
( output reg[8:0]number,
  output reg en,
  output [15:0]rezultat
);
SEU DUT(.NR(number),        //  9 biti din  din intructiune, bitul cu nr 8 repr semnul
        .enable(en),
        .result(rezultat)); // output bloc SEU (pe 16 biti) 
integer i;
 initial begin
   {number,en} = 10'd0;
   for (i=0; i<1024; i= i+1)begin
     #10 {number,en}=i;   // 000000000 -nr pozitiv si en =0
                          // 000000000 -nr pozitiv si en =1
                          // .......................
                          // 000000101 -nr si en =0
                          // .......................
                          // 10 0000 000 -nr negativ si en =0
                          // 10 0000 000 -nr negativ si en =1 
   end
end
endmodule