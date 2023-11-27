`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/05/2019 11:30:22 PM
// Design Name: 
// Module Name: marks_updater
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


module marks_updater #
    (
    parameter section_size = 19 
    )
    
    (
    input clk,
    input reset,
    input update,
    input [3:0] num_window,
    input [2:0] window_position,
    output [0:section_size-1] marks
    );
	 
integer i;
reg [0:section_size-1] marks_new;
wire [0:section_size-1] current_marks;

always@(*)
    begin
    for(i=0; i<section_size; i=i+1)
        begin
        if(i == num_window + window_position)
            marks_new[i] = 1'b1;
        else
            marks_new[i] = current_marks[i];
        end
    end    
    
reg_marks #(section_size) reg_marks1 (clk, reset, update, marks_new, current_marks);

assign marks = current_marks;
  
endmodule
