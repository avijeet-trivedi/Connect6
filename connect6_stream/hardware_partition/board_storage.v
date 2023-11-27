`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10.01.2020 19:22:21
// Design Name: 
// Module Name: board_storage
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

module board_storage ( 
          input wire clk,rst,
          input wire new_data,
          input wire [31:0] data,
          output wire [721:0] board,
          output reg analyze_normal, reset_normal, 
          output wire upgrade
    );


    
   reg [31:0] slv_reg0, slv_reg1, slv_reg2, slv_reg3, slv_reg4, slv_reg5, slv_reg6, slv_reg7, slv_reg8, slv_reg9, slv_reg10, slv_reg11, slv_reg12, slv_reg13, slv_reg14, slv_reg15, slv_reg16, slv_reg17, slv_reg18, slv_reg19, slv_reg20, slv_reg21, slv_reg22 ;
    
   reg [4:0] count = 0 ;
    
	always @(posedge clk) 
	begin
      if (rst) begin
          count <= 0;
      	  slv_reg0 <= 0;
	      slv_reg1 <= 0;
	      slv_reg2 <= 0;
	      slv_reg3 <= 0;
	      slv_reg4 <= 0;
	      slv_reg5 <= 0;
	      slv_reg6 <= 0;
	      slv_reg7 <= 0;
	      slv_reg8 <= 0;
	      slv_reg9 <= 0;
	      slv_reg10 <= 0;
	      slv_reg11 <= 0;
	      slv_reg12 <= 0;
	      slv_reg13 <= 0;
	      slv_reg14 <= 0;
	      slv_reg15 <= 0;
	      slv_reg16 <= 0;
	      slv_reg17 <= 0;
	      slv_reg18 <= 0;
	      slv_reg19 <= 0;
	      slv_reg20 <= 0;
	      slv_reg21 <= 0;
	      slv_reg22 <= 0;
	      analyze_normal <= 0;
	      reset_normal <= 0;
	  end          
			
	  else begin  
	     if (new_data) begin 
	          analyze_normal <= 0;
	          reset_normal <= 0;
	          case (count)
	          5'd0: begin 
	                   slv_reg0 <= data; 
	                   count <= count + 5'd1 ;
	                   reset_normal <= 1'b1 ;
	                end
              5'd1: begin
                        slv_reg1 <= data; 
                        count <= count + 5'd1 ;
                    end
              5'd2: begin 
                        slv_reg2 <= data;
                        count <= count + 5'd1 ;
                    end
              5'd3: begin
                        slv_reg3 <= data; 
                        count <= count + 5'd1 ;
                    end
              5'd4: begin
                        slv_reg4 <= data; 
                        count <= count + 5'd1 ;
                    end
              5'd5: begin 
                        slv_reg5 <= data; 
                        count <= count + 5'd1 ;
                    end
              5'd6: begin
                        slv_reg6 <= data; 
                        count <= count + 5'd1 ;
                    end
              5'd7: begin
                        slv_reg7 <= data; 
                        count <= count + 5'd1 ;
                    end 
              5'd8: begin
                        slv_reg8 <= data; 
                        count <= count + 5'd1 ;
                    end 
              5'd9: begin
                        slv_reg9 <= data; 
                        count <= count + 5'd1 ;
                    end
             5'd10: begin
                        slv_reg10 <= data; 
                        count <= count + 5'd1 ;
                    end
              5'd11: begin
                        slv_reg11 <= data; 
                        count <= count + 5'd1 ;
                    end
              5'd12: begin
                        slv_reg12 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd13: begin
                        slv_reg13 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd14: begin  
                        slv_reg14 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd15: begin
                        slv_reg15 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd16: begin
                        slv_reg16 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd17: begin
                        slv_reg17 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd18: begin  
                        slv_reg18 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd19: begin  
                        slv_reg19 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd20: begin 
                        slv_reg20 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd21: begin      
                        slv_reg21 <= data; 
                        count <= count + 5'd1 ;
                     end
              5'd22: begin
                        slv_reg22 <= data; 
                        count <= 0 ;
                        analyze_normal <= 1'b1;
                     end
              default : begin 
                        analyze_normal <= 0;
	                    reset_normal <= 0;
	                    end
              endcase
         end
         else begin
            analyze_normal <= 0;
	        reset_normal <= 0;
         end 
      end 
     end
     
    assign board = {slv_reg0[17:0], slv_reg1, slv_reg2, slv_reg3, slv_reg4, slv_reg5, slv_reg6, slv_reg7, slv_reg8, slv_reg9, slv_reg10, slv_reg11, slv_reg12, slv_reg13, slv_reg14, slv_reg15, slv_reg16, slv_reg17, slv_reg18, slv_reg19, slv_reg20, slv_reg21, slv_reg22};
   
	assign upgrade = slv_reg0[18] ;
endmodule
