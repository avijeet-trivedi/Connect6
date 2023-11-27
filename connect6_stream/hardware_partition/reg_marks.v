`timescale 1ns / 1ps


//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/05/2019 06:57:45 PM
// Design Name: 
// Module Name: reg_marks
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module reg_marks(
    input clk,
    input rst,
    input ld,
    input [0:section_size-1] din,
    output [0:section_size-1] dout
    );

parameter section_size = 19;

reg [0:section_size-1] cs,ns1; 

always@(posedge clk)
begin
    if (rst == 1'b1) 
    cs <= 0;
    else 
    cs <= ns1; 
end

always@(*) 
begin
if (ld == 1'b1) ns1 <= din;
else ns1 <= cs;
end

assign dout = cs;

endmodule
