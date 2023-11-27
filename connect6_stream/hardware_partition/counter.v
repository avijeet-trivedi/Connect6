`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:26:02 04/08/2019 
// Design Name: 
// Module Name:    counter 
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
module counter #
    (
    parameter integer size = 1 
    )
    (
     input clk,rst,rst2,inc,
     output [size:0] count
    );

 
reg [size:0]CS, NS;

assign count = CS;

always @(posedge clk)
begin
  if (rst)
     CS <= 0;
  else
     CS <= NS;  
end   

always @*
begin
  if (rst2)
     NS = 0;
  else if (inc)
     NS = CS+1;
  else
     NS = CS;	  
end
	

endmodule
