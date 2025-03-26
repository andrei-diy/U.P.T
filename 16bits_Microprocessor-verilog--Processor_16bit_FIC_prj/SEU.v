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

module SEU( 
 input [8:0]NR,
 //input enable,
 output [15:0]result   
 );
 
/*
 reg [7:0]aux;
 reg [15:0]buff;
 
always @ (enable)
begin
  if(enable) begin
    if( NR[8] == 0 )
        begin
        result = {8'd0, NR[7:0]};  
        end
    else if( NR[8] == 1 && NR[7:0] != 0)
        begin
           aux = ~NR[7:0];           //complementam bitii
           buff = {8'b11111111,aux}; //punem masca pt nr negative
           result = buff + 1;        // adunam 1 pt complement de 2       
        end
    else result = 16'd0;
    end
end
endmodule */


assign result = NR[8] ? {8'b11111111,NR[7:0]} : {8'd0, NR[7:0]};

endmodule 
