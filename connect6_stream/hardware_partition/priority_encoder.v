`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:18:25 04/10/2019 
// Design Name: 
// Module Name:    priority_encoder 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module priority_encoder(   input [0:5] in,
                           output reg [2:0] out
    );
	 
	 
	 always@(in)
	  begin
	    if(in[5]==0)
			  out= 3'd5;
	    else if(in[4]==0)
           out=3'd4;
        else if(in[3]==0)
           out=3'd3;
     	else if(in[2]==0)
           out=3'd2;		  
		else if(in[1]==0)
           out=3'd1;
	    else if(in[0]==0)
           out=3'd0;		 
	    else
		     out=3'd7;
	  end


endmodule
