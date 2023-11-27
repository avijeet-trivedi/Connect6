`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:31:12 04/08/2019 
// Design Name: 
// Module Name:    threat_analyzer 
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
module threat_analyzer(
    input clk,
    input rst,
    input analyze,
    input [0:721]board,
    output [2:0] num_t4_b,
    output [3:0] num_t3_b,
    output [4:0] num_t2_b,
    output [2:0] num_t4_w,
    output [3:0] num_t3_w,
    output [4:0] num_t2_w
    );
parameter player = 1;  //black
wire [1:0]t4_row_b[18:0],t4_col_b[18:0],t4_diag_b[26:0],t4_rev_diag_b[26:0];
wire [1:0]t3_row_b[18:0],t3_col_b[18:0],t3_diag_b[26:0],t3_rev_diag_b[26:0];
wire [1:0]t2_row_b[18:0],t2_col_b[18:0],t2_diag_b[26:0],t2_rev_diag_b[26:0];
wire [1:0]t4_row_w[18:0],t4_col_w[18:0],t4_diag_w[26:0],t4_rev_diag_w[26:0];
wire [1:0]t3_row_w[18:0],t3_col_w[18:0],t3_diag_w[26:0],t3_rev_diag_w[26:0];
wire [1:0]t2_row_w[18:0],t2_col_w[18:0],t2_diag_w[26:0],t2_rev_diag_w[26:0];
wire [37:0]section_row[18:0],section_col[18:0],section_diag[26:0],section_rev_diag[26:0]; 
//wire [4:0]diag_size;

genvar i,j;

//ROWS
generate
for(i=0;i<19;i=i+1) begin:rows
   	assign  section_row[i] = board[ 38*i: 38*i+37 ];
	section_processor  #(19) S1( clk,rst,analyze,section_row[i],t4_row_b[i],t3_row_b[i],t2_row_b[i], t4_row_w[i],t3_row_w[i],t2_row_w[i] );   
end
endgenerate

//COLUMNS
generate
for(i=0;i<19;i=i+1)  
begin  :columns
   for(j=0;j<38;j=j+2)
	begin : create_col
	  assign section_col[i][37-j] = board[2*i+19*j];
     assign section_col[i][37-j-1]	= board[ 2*i+19*j + 1];  
	end
	section_processor #(19) S2(clk,rst,analyze,section_col[i],t4_col_b[i],t3_col_b[i],t2_col_b[i], t4_col_w[i],t3_col_w[i],t2_col_w[i]);   
end
endgenerate

//DIAGONALS 
generate
for(i=0;i<27;i=i+1) begin:diag
   localparam diag_size = i<14?i+6:32-i;
   for(j=0;j<diag_size*2;j=j+2) begin :create_diag
	if (i<14) begin
	 assign section_diag[i][j+1] = board[19*j + (2*i + 10 - j)];
     assign section_diag[i][j] = board[19*j + (2*i + 11 - j)];  
	end
	else begin
	  assign section_diag[i][j+1] = board[36+38*(i-13)+19*j-j];
	  assign section_diag[i][j] = board[37+38*(i-13)+19*j-j];
	end
   end
   section_processor #(diag_size) S3(clk,rst,analyze,section_diag[i],t4_diag_b[i],t3_diag_b[i],t2_diag_b[i], t4_diag_w[i],t3_diag_w[i],t2_diag_w[i]);   
end
endgenerate

//REV_DIAGONAL
generate
for(i=0;i<27;i=i+1)
begin:rev_diag
   localparam diag_size = i<14?i+6:32-i;
   for(j=0;j<diag_size*2;j=j+2) begin : create_rev_diag
	if(i<14) begin
	 assign section_rev_diag[i][diag_size*2-j-1] = board[20*j + 37 - (2*i + 11)];
     assign section_rev_diag[i][diag_size*2-j-2] = board[20*j + 38 - (2*i + 11)];  
	end
	else begin
	 assign section_rev_diag[i][diag_size*2-j-1] = board[20*j + 38*(i-13) ];
     assign section_rev_diag[i][diag_size*2-j-2]	= board[20*j + 38*(i-13) + 1];  
	end
   end
   section_processor #(diag_size) S4(clk,rst,analyze,section_rev_diag[i],t4_rev_diag_b[i],t3_rev_diag_b[i],t2_rev_diag_b[i], t4_rev_diag_w[i],t3_rev_diag_w[i],t2_rev_diag_w[i]);   
end
endgenerate

tree_adder #(3) adder_t4_b(
                             .row0(t4_row_b[0]),
                             .row1(t4_row_b[1]),
							 .row2(t4_row_b[2]),
							 .row3(t4_row_b[3]),
							 .row4(t4_row_b[4]),
							 .row5(t4_row_b[5]),
							 .row6(t4_row_b[6]),
							 .row7(t4_row_b[7]),
							 .row8(t4_row_b[8]),
							 .row9(t4_row_b[9]),
							 .row10(t4_row_b[10]),
							 .row11(t4_row_b[11]),
							 .row12(t4_row_b[12]),
							 .row13(t4_row_b[13]),
							 .row14(t4_row_b[14]),
							 .row15(t4_row_b[15]),
							 .row16(t4_row_b[16]),
							 .row17(t4_row_b[17]),
							 .row18(t4_row_b[18]),

							 .col0(t4_col_b[0]),
                             .col1(t4_col_b[1]),
							 .col2(t4_col_b[2]),
							 .col3(t4_col_b[3]),
							 .col4(t4_col_b[4]),
							 .col5(t4_col_b[5]),
							 .col6(t4_col_b[6]),
							 .col7(t4_col_b[7]),
							 .col8(t4_col_b[8]),
							 .col9(t4_col_b[9]),
							 .col10(t4_col_b[10]),
							 .col11(t4_col_b[11]),
							 .col12(t4_col_b[12]),
							 .col13(t4_col_b[13]),
							 .col14(t4_col_b[14]),
							 .col15(t4_col_b[15]),
							 .col16(t4_col_b[16]),
							 .col17(t4_col_b[17]),
							 .col18(t4_col_b[18]),

							 .diag0(t4_diag_b[0]),
                     		 .diag1(t4_diag_b[1]),
							 .diag2(t4_diag_b[2]),
							 .diag3(t4_diag_b[3]),
							 .diag4(t4_diag_b[4]),
							 .diag5(t4_diag_b[5]),
							 .diag6(t4_diag_b[6]),
							 .diag7(t4_diag_b[7]),
							 .diag8(t4_diag_b[8]),
							 .diag9(t4_diag_b[9]),
							 .diag10(t4_diag_b[10]),
							 .diag11(t4_diag_b[11]),
							 .diag12(t4_diag_b[12]),
							 .diag13(t4_diag_b[13]),
							 .diag14(t4_diag_b[14]),
							 .diag15(t4_diag_b[15]),
							 .diag16(t4_diag_b[16]),
							 .diag17(t4_diag_b[17]),
							 .diag18(t4_diag_b[18]),
							 .diag19(t4_diag_b[19]),
							 .diag20(t4_diag_b[20]),
							 .diag21(t4_diag_b[21]),
							 .diag22(t4_diag_b[22]),
							 .diag23(t4_diag_b[23]),
							 .diag24(t4_diag_b[24]),
							 .diag25(t4_diag_b[25]),
							 .diag26(t4_diag_b[26]),
							 
							 .rev_diag0(t4_rev_diag_b[0]),
                     		 .rev_diag1(t4_rev_diag_b[1]),
							 .rev_diag2(t4_rev_diag_b[2]),
							 .rev_diag3(t4_rev_diag_b[3]),
							 .rev_diag4(t4_rev_diag_b[4]),
							 .rev_diag5(t4_rev_diag_b[5]),
							 .rev_diag6(t4_rev_diag_b[6]),
							 .rev_diag7(t4_rev_diag_b[7]),
							 .rev_diag8(t4_rev_diag_b[8]),
							 .rev_diag9(t4_rev_diag_b[9]),
							 .rev_diag10(t4_rev_diag_b[10]),
							 .rev_diag11(t4_rev_diag_b[11]),
							 .rev_diag12(t4_rev_diag_b[12]),
							 .rev_diag13(t4_rev_diag_b[13]),
							 .rev_diag14(t4_rev_diag_b[14]),
							 .rev_diag15(t4_rev_diag_b[15]),
							 .rev_diag16(t4_rev_diag_b[16]),
							 .rev_diag17(t4_rev_diag_b[17]),
							 .rev_diag18(t4_rev_diag_b[18]),
							 .rev_diag19(t4_rev_diag_b[19]),
							 .rev_diag20(t4_rev_diag_b[20]),
							 .rev_diag21(t4_rev_diag_b[21]),
							 .rev_diag22(t4_rev_diag_b[22]),
							 .rev_diag23(t4_rev_diag_b[23]),
							 .rev_diag24(t4_rev_diag_b[24]),
							 .rev_diag25(t4_rev_diag_b[25]),
							 .rev_diag26(t4_rev_diag_b[26]),
							
							 .sum(num_t4_b)

);



tree_adder #(4) adder_t3_b(

                     		 .row0(t3_row_b[0]),
                   		     .row1(t3_row_b[1]),
							 .row2(t3_row_b[2]),
							 .row3(t3_row_b[3]),
							 .row4(t3_row_b[4]),
							 .row5(t3_row_b[5]),
							 .row6(t3_row_b[6]),
							 .row7(t3_row_b[7]),
							 .row8(t3_row_b[8]),
							 .row9(t3_row_b[9]),
							 .row10(t3_row_b[10]),
							 .row11(t3_row_b[11]),
							 .row12(t3_row_b[12]),
							 .row13(t3_row_b[13]),
							 .row14(t3_row_b[14]),
							 .row15(t3_row_b[15]),
							 .row16(t3_row_b[16]),
							 .row17(t3_row_b[17]),
							 .row18(t3_row_b[18]),

							 .col0(t3_col_b[0]),
                      		 .col1(t3_col_b[1]),
							 .col2(t3_col_b[2]),
							 .col3(t3_col_b[3]),
							 .col4(t3_col_b[4]),
							 .col5(t3_col_b[5]),
							 .col6(t3_col_b[6]),
							 .col7(t3_col_b[7]),
							 .col8(t3_col_b[8]),
							 .col9(t3_col_b[9]),
							 .col10(t3_col_b[10]),
							 .col11(t3_col_b[11]),
							 .col12(t3_col_b[12]),
							 .col13(t3_col_b[13]),
							 .col14(t3_col_b[14]),
							 .col15(t3_col_b[15]),
							 .col16(t3_col_b[16]),
							 .col17(t3_col_b[17]),
							 .col18(t3_col_b[18]),

							 .diag0(t3_diag_b[0]),
                             .diag1(t3_diag_b[1]),
							 .diag2(t3_diag_b[2]),
							 .diag3(t3_diag_b[3]),
							 .diag4(t3_diag_b[4]),
							 .diag5(t3_diag_b[5]),
							 .diag6(t3_diag_b[6]),
							 .diag7(t3_diag_b[7]),
							 .diag8(t3_diag_b[8]),
							 .diag9(t3_diag_b[9]),
							 .diag10(t3_diag_b[10]),
							 .diag11(t3_diag_b[11]),
							 .diag12(t3_diag_b[12]),
							 .diag13(t3_diag_b[13]),
							 .diag14(t3_diag_b[14]),
							 .diag15(t3_diag_b[15]),
							 .diag16(t3_diag_b[16]),
							 .diag17(t3_diag_b[17]),
							 .diag18(t3_diag_b[18]),
							 .diag19(t3_diag_b[19]),
							 .diag20(t3_diag_b[20]),
							 .diag21(t3_diag_b[21]),
							 .diag22(t3_diag_b[22]),
							 .diag23(t3_diag_b[23]),
							 .diag24(t3_diag_b[24]),
							 .diag25(t3_diag_b[25]),
							 .diag26(t3_diag_b[26]),
							 
							 .rev_diag0(t3_rev_diag_b[0]),
                      		 .rev_diag1(t3_rev_diag_b[1]),
							 .rev_diag2(t3_rev_diag_b[2]),
							 .rev_diag3(t3_rev_diag_b[3]),
							 .rev_diag4(t3_rev_diag_b[4]),
							 .rev_diag5(t3_rev_diag_b[5]),
							 .rev_diag6(t3_rev_diag_b[6]),
							 .rev_diag7(t3_rev_diag_b[7]),
							 .rev_diag8(t3_rev_diag_b[8]),
							 .rev_diag9(t3_rev_diag_b[9]),
							 .rev_diag10(t3_rev_diag_b[10]),
							 .rev_diag11(t3_rev_diag_b[11]),
							 .rev_diag12(t3_rev_diag_b[12]),
							 .rev_diag13(t3_rev_diag_b[13]),
							 .rev_diag14(t3_rev_diag_b[14]),
							 .rev_diag15(t3_rev_diag_b[15]),
							 .rev_diag16(t3_rev_diag_b[16]),
							 .rev_diag17(t3_rev_diag_b[17]),
							 .rev_diag18(t3_rev_diag_b[18]),
							 .rev_diag19(t3_rev_diag_b[19]),
							 .rev_diag20(t3_rev_diag_b[20]),
							 .rev_diag21(t3_rev_diag_b[21]),
							 .rev_diag22(t3_rev_diag_b[22]),
							 .rev_diag23(t3_rev_diag_b[23]),
							 .rev_diag24(t3_rev_diag_b[24]),
							 .rev_diag25(t3_rev_diag_b[25]),
							 .rev_diag26(t3_rev_diag_b[26]),
							 
							 .sum(num_t3_b)

);


tree_adder #(5) adder_t2_b(

                      		 .row0(t2_row_b[0]),
                             .row1(t2_row_b[1]),
							 .row2(t2_row_b[2]),
							 .row3(t2_row_b[3]),
							 .row4(t2_row_b[4]),
							 .row5(t2_row_b[5]),
							 .row6(t2_row_b[6]),
							 .row7(t2_row_b[7]),
							 .row8(t2_row_b[8]),
							 .row9(t2_row_b[9]),
							 .row10(t2_row_b[10]),
							 .row11(t2_row_b[11]),
							 .row12(t2_row_b[12]),
							 .row13(t2_row_b[13]),
							 .row14(t2_row_b[14]),
							 .row15(t2_row_b[15]),
							 .row16(t2_row_b[16]),
							 .row17(t2_row_b[17]),
							 .row18(t2_row_b[18]),

							 .col0(t2_col_b[0]),
                             .col1(t2_col_b[1]),
							 .col2(t2_col_b[2]),
							 .col3(t2_col_b[3]),
							 .col4(t2_col_b[4]),
							 .col5(t2_col_b[5]),
							 .col6(t2_col_b[6]),
							 .col7(t2_col_b[7]),
							 .col8(t2_col_b[8]),
							 .col9(t2_col_b[9]),
							 .col10(t2_col_b[10]),
							 .col11(t2_col_b[11]),
							 .col12(t2_col_b[12]),
							 .col13(t2_col_b[13]),
							 .col14(t2_col_b[14]),
							 .col15(t2_col_b[15]),
							 .col16(t2_col_b[16]),
							 .col17(t2_col_b[17]),
							 .col18(t2_col_b[18]),

							 .diag0(t2_diag_b[0]),
                             .diag1(t2_diag_b[1]),
							 .diag2(t2_diag_b[2]),
							 .diag3(t2_diag_b[3]),
							 .diag4(t2_diag_b[4]),
							 .diag5(t2_diag_b[5]),
							 .diag6(t2_diag_b[6]),
							 .diag7(t2_diag_b[7]),
							 .diag8(t2_diag_b[8]),
							 .diag9(t2_diag_b[9]),
							 .diag10(t2_diag_b[10]),
							 .diag11(t2_diag_b[11]),
							 .diag12(t2_diag_b[12]),
							 .diag13(t2_diag_b[13]),
							 .diag14(t2_diag_b[14]),
							 .diag15(t2_diag_b[15]),
							 .diag16(t2_diag_b[16]),
							 .diag17(t2_diag_b[17]),
							 .diag18(t2_diag_b[18]),
							 .diag19(t2_diag_b[19]),
							 .diag20(t2_diag_b[20]),
							 .diag21(t2_diag_b[21]),
							 .diag22(t2_diag_b[22]),
							 .diag23(t2_diag_b[23]),
							 .diag24(t2_diag_b[24]),
							 .diag25(t2_diag_b[25]),
							 .diag26(t2_diag_b[26]),
							 
							 .rev_diag0(t2_rev_diag_b[0]),
                             .rev_diag1(t2_rev_diag_b[1]),
							 .rev_diag2(t2_rev_diag_b[2]),
							 .rev_diag3(t2_rev_diag_b[3]),
							 .rev_diag4(t2_rev_diag_b[4]),
							 .rev_diag5(t2_rev_diag_b[5]),
							 .rev_diag6(t2_rev_diag_b[6]),
							 .rev_diag7(t2_rev_diag_b[7]),
							 .rev_diag8(t2_rev_diag_b[8]),
							 .rev_diag9(t2_rev_diag_b[9]),
							 .rev_diag10(t2_rev_diag_b[10]),
							 .rev_diag11(t2_rev_diag_b[11]),
							 .rev_diag12(t2_rev_diag_b[12]),
							 .rev_diag13(t2_rev_diag_b[13]),
							 .rev_diag14(t2_rev_diag_b[14]),
							 .rev_diag15(t2_rev_diag_b[15]),
							 .rev_diag16(t2_rev_diag_b[16]),
							 .rev_diag17(t2_rev_diag_b[17]),
							 .rev_diag18(t2_rev_diag_b[18]),
							 .rev_diag19(t2_rev_diag_b[19]),
							 .rev_diag20(t2_rev_diag_b[20]),
							 .rev_diag21(t2_rev_diag_b[21]),
							 .rev_diag22(t2_rev_diag_b[22]),
							 .rev_diag23(t2_rev_diag_b[23]),
							 .rev_diag24(t2_rev_diag_b[24]),
							 .rev_diag25(t2_rev_diag_b[25]),
							 .rev_diag26(t2_rev_diag_b[26]),
							
							 .sum(num_t2_b)

);


tree_adder #(3) adder_t4_w(
                             .row0(t4_row_w[0]),
                             .row1(t4_row_w[1]),
							 .row2(t4_row_w[2]),
							 .row3(t4_row_w[3]),
							 .row4(t4_row_w[4]),
							 .row5(t4_row_w[5]),
							 .row6(t4_row_w[6]),
							 .row7(t4_row_w[7]),
							 .row8(t4_row_w[8]),
							 .row9(t4_row_w[9]),
							 .row10(t4_row_w[10]),
							 .row11(t4_row_w[11]),
							 .row12(t4_row_w[12]),
							 .row13(t4_row_w[13]),
							 .row14(t4_row_w[14]),
							 .row15(t4_row_w[15]),
							 .row16(t4_row_w[16]),
							 .row17(t4_row_w[17]),
							 .row18(t4_row_w[18]),

							 .col0(t4_col_w[0]),
                             .col1(t4_col_w[1]),
							 .col2(t4_col_w[2]),
							 .col3(t4_col_w[3]),
							 .col4(t4_col_w[4]),
							 .col5(t4_col_w[5]),
							 .col6(t4_col_w[6]),
							 .col7(t4_col_w[7]),
							 .col8(t4_col_w[8]),
							 .col9(t4_col_w[9]),
							 .col10(t4_col_w[10]),
							 .col11(t4_col_w[11]),
							 .col12(t4_col_w[12]),
							 .col13(t4_col_w[13]),
							 .col14(t4_col_w[14]),
							 .col15(t4_col_w[15]),
							 .col16(t4_col_w[16]),
							 .col17(t4_col_w[17]),
							 .col18(t4_col_w[18]),

							 .diag0(t4_diag_w[0]),
                     		 .diag1(t4_diag_w[1]),
							 .diag2(t4_diag_w[2]),
							 .diag3(t4_diag_w[3]),
							 .diag4(t4_diag_w[4]),
							 .diag5(t4_diag_w[5]),
							 .diag6(t4_diag_w[6]),
							 .diag7(t4_diag_w[7]),
							 .diag8(t4_diag_w[8]),
							 .diag9(t4_diag_w[9]),
							 .diag10(t4_diag_w[10]),
							 .diag11(t4_diag_w[11]),
							 .diag12(t4_diag_w[12]),
							 .diag13(t4_diag_w[13]),
							 .diag14(t4_diag_w[14]),
							 .diag15(t4_diag_w[15]),
							 .diag16(t4_diag_w[16]),
							 .diag17(t4_diag_w[17]),
							 .diag18(t4_diag_w[18]),
							 .diag19(t4_diag_w[19]),
							 .diag20(t4_diag_w[20]),
							 .diag21(t4_diag_w[21]),
							 .diag22(t4_diag_w[22]),
							 .diag23(t4_diag_w[23]),
							 .diag24(t4_diag_w[24]),
							 .diag25(t4_diag_w[25]),
							 .diag26(t4_diag_w[26]),
							 
							 .rev_diag0(t4_rev_diag_w[0]),
                     		 .rev_diag1(t4_rev_diag_w[1]),
							 .rev_diag2(t4_rev_diag_w[2]),
							 .rev_diag3(t4_rev_diag_w[3]),
							 .rev_diag4(t4_rev_diag_w[4]),
							 .rev_diag5(t4_rev_diag_w[5]),
							 .rev_diag6(t4_rev_diag_w[6]),
							 .rev_diag7(t4_rev_diag_w[7]),
							 .rev_diag8(t4_rev_diag_w[8]),
							 .rev_diag9(t4_rev_diag_w[9]),
							 .rev_diag10(t4_rev_diag_w[10]),
							 .rev_diag11(t4_rev_diag_w[11]),
							 .rev_diag12(t4_rev_diag_w[12]),
							 .rev_diag13(t4_rev_diag_w[13]),
							 .rev_diag14(t4_rev_diag_w[14]),
							 .rev_diag15(t4_rev_diag_w[15]),
							 .rev_diag16(t4_rev_diag_w[16]),
							 .rev_diag17(t4_rev_diag_w[17]),
							 .rev_diag18(t4_rev_diag_w[18]),
							 .rev_diag19(t4_rev_diag_w[19]),
							 .rev_diag20(t4_rev_diag_w[20]),
							 .rev_diag21(t4_rev_diag_w[21]),
							 .rev_diag22(t4_rev_diag_w[22]),
							 .rev_diag23(t4_rev_diag_w[23]),
							 .rev_diag24(t4_rev_diag_w[24]),
							 .rev_diag25(t4_rev_diag_w[25]),
							 .rev_diag26(t4_rev_diag_w[26]),
							
							 .sum(num_t4_w)

);



tree_adder #(4) adder_t3_w(

                     		 .row0(t3_row_w[0]),
                   		     .row1(t3_row_w[1]),
							 .row2(t3_row_w[2]),
							 .row3(t3_row_w[3]),
							 .row4(t3_row_w[4]),
							 .row5(t3_row_w[5]),
							 .row6(t3_row_w[6]),
							 .row7(t3_row_w[7]),
							 .row8(t3_row_w[8]),
							 .row9(t3_row_w[9]),
							 .row10(t3_row_w[10]),
							 .row11(t3_row_w[11]),
							 .row12(t3_row_w[12]),
							 .row13(t3_row_w[13]),
							 .row14(t3_row_w[14]),
							 .row15(t3_row_w[15]),
							 .row16(t3_row_w[16]),
							 .row17(t3_row_w[17]),
							 .row18(t3_row_w[18]),

							 .col0(t3_col_w[0]),
                      		 .col1(t3_col_w[1]),
							 .col2(t3_col_w[2]),
							 .col3(t3_col_w[3]),
							 .col4(t3_col_w[4]),
							 .col5(t3_col_w[5]),
							 .col6(t3_col_w[6]),
							 .col7(t3_col_w[7]),
							 .col8(t3_col_w[8]),
							 .col9(t3_col_w[9]),
							 .col10(t3_col_w[10]),
							 .col11(t3_col_w[11]),
							 .col12(t3_col_w[12]),
							 .col13(t3_col_w[13]),
							 .col14(t3_col_w[14]),
							 .col15(t3_col_w[15]),
							 .col16(t3_col_w[16]),
							 .col17(t3_col_w[17]),
							 .col18(t3_col_w[18]),

							 .diag0(t3_diag_w[0]),
                             .diag1(t3_diag_w[1]),
							 .diag2(t3_diag_w[2]),
							 .diag3(t3_diag_w[3]),
							 .diag4(t3_diag_w[4]),
							 .diag5(t3_diag_w[5]),
							 .diag6(t3_diag_w[6]),
							 .diag7(t3_diag_w[7]),
							 .diag8(t3_diag_w[8]),
							 .diag9(t3_diag_w[9]),
							 .diag10(t3_diag_w[10]),
							 .diag11(t3_diag_w[11]),
							 .diag12(t3_diag_w[12]),
							 .diag13(t3_diag_w[13]),
							 .diag14(t3_diag_w[14]),
							 .diag15(t3_diag_w[15]),
							 .diag16(t3_diag_w[16]),
							 .diag17(t3_diag_w[17]),
							 .diag18(t3_diag_w[18]),
							 .diag19(t3_diag_w[19]),
							 .diag20(t3_diag_w[20]),
							 .diag21(t3_diag_w[21]),
							 .diag22(t3_diag_w[22]),
							 .diag23(t3_diag_w[23]),
							 .diag24(t3_diag_w[24]),
							 .diag25(t3_diag_w[25]),
							 .diag26(t3_diag_w[26]),
							 
							 .rev_diag0(t3_rev_diag_w[0]),
                      		 .rev_diag1(t3_rev_diag_w[1]),
							 .rev_diag2(t3_rev_diag_w[2]),
							 .rev_diag3(t3_rev_diag_w[3]),
							 .rev_diag4(t3_rev_diag_w[4]),
							 .rev_diag5(t3_rev_diag_w[5]),
							 .rev_diag6(t3_rev_diag_w[6]),
							 .rev_diag7(t3_rev_diag_w[7]),
							 .rev_diag8(t3_rev_diag_w[8]),
							 .rev_diag9(t3_rev_diag_w[9]),
							 .rev_diag10(t3_rev_diag_w[10]),
							 .rev_diag11(t3_rev_diag_w[11]),
							 .rev_diag12(t3_rev_diag_w[12]),
							 .rev_diag13(t3_rev_diag_w[13]),
							 .rev_diag14(t3_rev_diag_w[14]),
							 .rev_diag15(t3_rev_diag_w[15]),
							 .rev_diag16(t3_rev_diag_w[16]),
							 .rev_diag17(t3_rev_diag_w[17]),
							 .rev_diag18(t3_rev_diag_w[18]),
							 .rev_diag19(t3_rev_diag_w[19]),
							 .rev_diag20(t3_rev_diag_w[20]),
							 .rev_diag21(t3_rev_diag_w[21]),
							 .rev_diag22(t3_rev_diag_w[22]),
							 .rev_diag23(t3_rev_diag_w[23]),
							 .rev_diag24(t3_rev_diag_w[24]),
							 .rev_diag25(t3_rev_diag_w[25]),
							 .rev_diag26(t3_rev_diag_w[26]),
							 
							 .sum(num_t3_w)

);


tree_adder #(5) adder_t2_w(

                      		 .row0(t2_row_w[0]),
                             .row1(t2_row_w[1]),
							 .row2(t2_row_w[2]),
							 .row3(t2_row_w[3]),
							 .row4(t2_row_w[4]),
							 .row5(t2_row_w[5]),
							 .row6(t2_row_w[6]),
							 .row7(t2_row_w[7]),
							 .row8(t2_row_w[8]),
							 .row9(t2_row_w[9]),
							 .row10(t2_row_w[10]),
							 .row11(t2_row_w[11]),
							 .row12(t2_row_w[12]),
							 .row13(t2_row_w[13]),
							 .row14(t2_row_w[14]),
							 .row15(t2_row_w[15]),
							 .row16(t2_row_w[16]),
							 .row17(t2_row_w[17]),
							 .row18(t2_row_w[18]),

							 .col0(t2_col_w[0]),
                             .col1(t2_col_w[1]),
							 .col2(t2_col_w[2]),
							 .col3(t2_col_w[3]),
							 .col4(t2_col_w[4]),
							 .col5(t2_col_w[5]),
							 .col6(t2_col_w[6]),
							 .col7(t2_col_w[7]),
							 .col8(t2_col_w[8]),
							 .col9(t2_col_w[9]),
							 .col10(t2_col_w[10]),
							 .col11(t2_col_w[11]),
							 .col12(t2_col_w[12]),
							 .col13(t2_col_w[13]),
							 .col14(t2_col_w[14]),
							 .col15(t2_col_w[15]),
							 .col16(t2_col_w[16]),
							 .col17(t2_col_w[17]),
							 .col18(t2_col_w[18]),

							 .diag0(t2_diag_w[0]),
                             .diag1(t2_diag_w[1]),
							 .diag2(t2_diag_w[2]),
							 .diag3(t2_diag_w[3]),
							 .diag4(t2_diag_w[4]),
							 .diag5(t2_diag_w[5]),
							 .diag6(t2_diag_w[6]),
							 .diag7(t2_diag_w[7]),
							 .diag8(t2_diag_w[8]),
							 .diag9(t2_diag_w[9]),
							 .diag10(t2_diag_w[10]),
							 .diag11(t2_diag_w[11]),
							 .diag12(t2_diag_w[12]),
							 .diag13(t2_diag_w[13]),
							 .diag14(t2_diag_w[14]),
							 .diag15(t2_diag_w[15]),
							 .diag16(t2_diag_w[16]),
							 .diag17(t2_diag_w[17]),
							 .diag18(t2_diag_w[18]),
							 .diag19(t2_diag_w[19]),
							 .diag20(t2_diag_w[20]),
							 .diag21(t2_diag_w[21]),
							 .diag22(t2_diag_w[22]),
							 .diag23(t2_diag_w[23]),
							 .diag24(t2_diag_w[24]),
							 .diag25(t2_diag_w[25]),
							 .diag26(t2_diag_w[26]),
							 
							 .rev_diag0(t2_rev_diag_w[0]),
                             .rev_diag1(t2_rev_diag_w[1]),
							 .rev_diag2(t2_rev_diag_w[2]),
							 .rev_diag3(t2_rev_diag_w[3]),
							 .rev_diag4(t2_rev_diag_w[4]),
							 .rev_diag5(t2_rev_diag_w[5]),
							 .rev_diag6(t2_rev_diag_w[6]),
							 .rev_diag7(t2_rev_diag_w[7]),
							 .rev_diag8(t2_rev_diag_w[8]),
							 .rev_diag9(t2_rev_diag_w[9]),
							 .rev_diag10(t2_rev_diag_w[10]),
							 .rev_diag11(t2_rev_diag_w[11]),
							 .rev_diag12(t2_rev_diag_w[12]),
							 .rev_diag13(t2_rev_diag_w[13]),
							 .rev_diag14(t2_rev_diag_w[14]),
							 .rev_diag15(t2_rev_diag_w[15]),
							 .rev_diag16(t2_rev_diag_w[16]),
							 .rev_diag17(t2_rev_diag_w[17]),
							 .rev_diag18(t2_rev_diag_w[18]),
							 .rev_diag19(t2_rev_diag_w[19]),
							 .rev_diag20(t2_rev_diag_w[20]),
							 .rev_diag21(t2_rev_diag_w[21]),
							 .rev_diag22(t2_rev_diag_w[22]),
							 .rev_diag23(t2_rev_diag_w[23]),
							 .rev_diag24(t2_rev_diag_w[24]),
							 .rev_diag25(t2_rev_diag_w[25]),
							 .rev_diag26(t2_rev_diag_w[26]),
							
							 .sum(num_t2_w)

);
endmodule
