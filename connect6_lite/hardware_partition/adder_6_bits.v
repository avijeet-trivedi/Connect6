`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:12:40 04/06/2019 
// Design Name: 
// Module Name:    adder_6_bits 
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
module adder_6_bits(   input [5:0] inp,
                       output [2:0] out
     );


assign out=inp[0]+inp[1]+inp[2]+inp[3]+inp[4]+inp[5];


endmodule
