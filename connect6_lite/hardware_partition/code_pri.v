`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:38:12 04/05/2019 
// Design Name: 
// Module Name:    code_pri 
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


module code_pri #
    (
    parameter integer num_elements = 14
    )
    
    (   
    input [0:num_elements-1] section,              //this module basically acts as a priority ecoder
    output active,                    			  //gives priority to the leftmost position
	output reg [3:0] leftmost_element
    );
	  
assign active = section==0?(1'b0):(1'b1);    

integer i;
always@(section)          //return the leftmost element
    begin
	leftmost_element= 4'b0000;
	for (i=num_elements-1;i>=0;i=i-1)
		begin
	    if (section[i] == 1'b1)
		leftmost_element = i;
		end					
    end 
endmodule
