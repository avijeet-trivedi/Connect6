`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.01.2020 04:20:02
// Design Name: 
// Module Name: board_gen
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


module board_gen(
    input [0:721] board,
    input [0:31] location,
    input clock, reset_h, upgrade,
    output reg analyze,
    output [0:721] board_final
    );
    
    reg  [0:721] board_mov = 722'd0 ;
    
    assign board_final = board_mov | board ;
    
    wire [9:0] index1 = 2*((10'd19*{5'd0,location[0:4]})+ {5'd0,location[5:9]}) ;
    wire [9:0] index2 = 2*((10'd19*{5'd0,location[22:26]})+ {5'd0,location[27:31]}) ;
    
    always@(posedge clock) begin
        if (reset_h) begin
            analyze <= 1'b1 ;
            board_mov <= 722'd0 ;
        end
        else begin
            analyze <= 1'b0 ;
            board_mov[index1 + !location[10]] <= upgrade ;
            board_mov[index2 + !location[10]] <= upgrade ;
        end
    end


endmodule
