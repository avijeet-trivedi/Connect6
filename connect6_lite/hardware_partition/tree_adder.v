`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:35:41 04/12/2019 
// Design Name: 
// Module Name:    tree_adder 
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
module tree_adder #(parameter output_size = 5  )(
                            input [1:0]  row0,
                     		input [1:0]  row1,
							input [1:0]  row2,
							input [1:0]  row3,
							input [1:0]  row4,
							input [1:0]  row5,
							input [1:0]  row6,
							input [1:0]  row7,
							input [1:0]  row8,
							input [1:0]  row9,
							input [1:0]  row10,
							input [1:0]  row11,
							input [1:0]  row12,
							input [1:0]  row13,
							input [1:0]  row14,
							input [1:0]  row15,
							input [1:0]  row16,
							input [1:0]  row17,
							input [1:0]  row18,
							
							input [1:0]  col0,
                     		input [1:0]  col1,
							input [1:0]  col2,
							input [1:0]  col3,
							input [1:0]  col4,
							input [1:0]  col5,
							input [1:0]  col6,
							input [1:0]  col7,
							input [1:0]  col8,
							input [1:0]  col9,
							input [1:0]  col10,
							input [1:0]  col11,
							input [1:0]  col12,
							input [1:0]  col13,
							input [1:0]  col14,
							input [1:0]  col15,
							input [1:0]  col16,
							input [1:0]  col17,
							input [1:0]  col18,
							
							input [1:0]  diag0,
                    	  	input [1:0]  diag1,
							input [1:0]  diag2,
							input [1:0]  diag3,
							input [1:0]  diag4,
							input [1:0]  diag5,
							input [1:0]  diag6,
							input [1:0]  diag7,
							input [1:0]  diag8,
							input [1:0]  diag9,
							input [1:0]  diag10,
							input [1:0]  diag11,
							input [1:0]  diag12,
							input [1:0]  diag13,
							input [1:0]  diag14,
							input [1:0]  diag15,
							input [1:0]  diag16,
							input [1:0]  diag17,
							input [1:0]  diag18,
							input [1:0]  diag19,
							input [1:0]  diag20,
							input [1:0]  diag21,
							input [1:0]  diag22,
							input [1:0]  diag23,
							input [1:0]  diag24,
							input [1:0]  diag25,
							input [1:0]  diag26,
							
							input [1:0]  rev_diag0,
                            input [1:0]  rev_diag1,
							input [1:0]  rev_diag2,
							input [1:0]  rev_diag3,
							input [1:0]  rev_diag4,
							input [1:0]  rev_diag5,
							input [1:0]  rev_diag6,
							input [1:0]  rev_diag7,
							input [1:0]  rev_diag8,
							input [1:0]  rev_diag9,
							input [1:0]  rev_diag10,
							input [1:0]  rev_diag11,
							input [1:0]  rev_diag12,
							input [1:0]  rev_diag13,
							input [1:0]  rev_diag14,
							input [1:0]  rev_diag15,
							input [1:0]  rev_diag16,
							input [1:0]  rev_diag17,
							input [1:0]  rev_diag18,
							input [1:0]  rev_diag19,
							input [1:0]  rev_diag20,
							input [1:0]  rev_diag21,
							input [1:0]  rev_diag22,
							input [1:0]  rev_diag23,
							input [1:0]  rev_diag24,
							input [1:0]  rev_diag25,
							input [1:0]  rev_diag26,
							
							output  [output_size-1:0] sum
    );

wire [output_size-1:0] extended_row0 ;
wire [output_size-1:0] extended_row1 ; 
wire [output_size-1:0] extended_row2 ;
wire [output_size-1:0] extended_row3 ;
wire [output_size-1:0] extended_row4 ;
wire [output_size-1:0] extended_row5 ; 
wire [output_size-1:0] extended_row6 ;
wire [output_size-1:0] extended_row7 ;
wire [output_size-1:0] extended_row8 ;
wire [output_size-1:0] extended_row9 ;
wire [output_size-1:0] extended_row10 ;
wire [output_size-1:0] extended_row11 ;
wire [output_size-1:0] extended_row12 ;
wire [output_size-1:0] extended_row13 ;
wire [output_size-1:0] extended_row14 ;
wire [output_size-1:0] extended_row15 ;
wire [output_size-1:0] extended_row16 ;
wire [output_size-1:0] extended_row17 ;
wire [output_size-1:0] extended_row18 ;

wire [output_size-1:0] extended_col0 ;
wire [output_size-1:0] extended_col1 ;
wire [output_size-1:0] extended_col2 ;
wire [output_size-1:0] extended_col3 ;
wire [output_size-1:0] extended_col4 ;
wire [output_size-1:0] extended_col5 ;
wire [output_size-1:0] extended_col6 ;
wire [output_size-1:0] extended_col7 ;
wire [output_size-1:0] extended_col8 ;
wire [output_size-1:0] extended_col9 ;
wire [output_size-1:0] extended_col10 ;
wire [output_size-1:0] extended_col11 ;
wire [output_size-1:0] extended_col12 ;
wire [output_size-1:0] extended_col13 ;
wire [output_size-1:0] extended_col14 ;
wire [output_size-1:0] extended_col15 ;
wire [output_size-1:0] extended_col16 ;
wire [output_size-1:0] extended_col17 ;
wire [output_size-1:0] extended_col18 ;

wire [output_size-1:0] extended_diag0 ;
wire [output_size-1:0] extended_diag1 ;
wire [output_size-1:0] extended_diag2 ;
wire [output_size-1:0] extended_diag3 ;
wire [output_size-1:0] extended_diag4 ;
wire [output_size-1:0] extended_diag5 ; 
wire [output_size-1:0] extended_diag6 ;
wire [output_size-1:0] extended_diag7 ;
wire [output_size-1:0] extended_diag8 ;
wire [output_size-1:0] extended_diag9 ;
wire [output_size-1:0] extended_diag10 ;
wire [output_size-1:0] extended_diag11 ;
wire [output_size-1:0] extended_diag12 ;
wire [output_size-1:0] extended_diag13 ;
wire [output_size-1:0] extended_diag14 ;
wire [output_size-1:0] extended_diag15 ;
wire [output_size-1:0] extended_diag16 ;
wire [output_size-1:0] extended_diag17 ;
wire [output_size-1:0] extended_diag18 ;
wire [output_size-1:0] extended_diag19 ;
wire [output_size-1:0] extended_diag20 ;
wire [output_size-1:0] extended_diag21 ;
wire [output_size-1:0] extended_diag22 ;
wire [output_size-1:0] extended_diag23 ;
wire [output_size-1:0] extended_diag24 ;
wire [output_size-1:0] extended_diag25 ;
wire [output_size-1:0] extended_diag26 ;
wire [output_size-1:0] extended_rev_diag0 ;
wire [output_size-1:0] extended_rev_diag1 ;
wire [output_size-1:0] extended_rev_diag2 ;
wire [output_size-1:0] extended_rev_diag3 ;
wire [output_size-1:0] extended_rev_diag4 ;
wire [output_size-1:0] extended_rev_diag5 ;
wire [output_size-1:0] extended_rev_diag6 ;
wire [output_size-1:0] extended_rev_diag7 ;
wire [output_size-1:0] extended_rev_diag8 ;
wire [output_size-1:0] extended_rev_diag9 ;
wire [output_size-1:0] extended_rev_diag10 ;
wire [output_size-1:0] extended_rev_diag11 ;
wire [output_size-1:0] extended_rev_diag12 ;
wire [output_size-1:0] extended_rev_diag13 ;
wire [output_size-1:0] extended_rev_diag14 ;
wire [output_size-1:0] extended_rev_diag15 ;
wire [output_size-1:0] extended_rev_diag16 ;
wire [output_size-1:0] extended_rev_diag17 ;
wire [output_size-1:0] extended_rev_diag18 ;
wire [output_size-1:0] extended_rev_diag19 ;
wire [output_size-1:0] extended_rev_diag20 ;
wire [output_size-1:0] extended_rev_diag21 ;
wire [output_size-1:0] extended_rev_diag22 ;
wire [output_size-1:0] extended_rev_diag23 ;
wire [output_size-1:0] extended_rev_diag24 ;
wire [output_size-1:0] extended_rev_diag25 ;
wire [output_size-1:0] extended_rev_diag26 ;

assign extended_row0 [output_size-1:2] = 0 ;
assign extended_row1 [output_size-1:2] = 0 ; 
assign extended_row2 [output_size-1:2] = 0 ;
assign extended_row3 [output_size-1:2] = 0 ;
assign extended_row4 [output_size-1:2] = 0 ;
assign extended_row5 [output_size-1:2] = 0 ; 
assign extended_row6 [output_size-1:2] = 0 ;
assign extended_row7 [output_size-1:2] = 0 ;
assign extended_row8 [output_size-1:2] = 0 ;
assign extended_row9 [output_size-1:2] = 0 ;
assign extended_row10 [output_size-1:2] = 0 ;
assign extended_row11 [output_size-1:2] = 0 ;
assign extended_row12 [output_size-1:2] = 0 ;
assign extended_row13 [output_size-1:2] = 0 ;
assign extended_row14 [output_size-1:2] = 0 ;
assign extended_row15 [output_size-1:2] = 0 ;
assign extended_row16 [output_size-1:2] = 0 ;
assign extended_row17 [output_size-1:2] = 0 ;
assign extended_row18 [output_size-1:2] = 0 ;

assign extended_col0 [output_size-1:2] = 0 ;
assign extended_col1 [output_size-1:2] = 0 ;
assign extended_col2 [output_size-1:2] = 0 ;
assign extended_col3 [output_size-1:2] = 0 ;
assign extended_col4 [output_size-1:2] = 0 ;
assign extended_col5 [output_size-1:2] = 0 ;
assign extended_col6 [output_size-1:2] = 0 ;
assign extended_col7 [output_size-1:2] = 0 ;
assign extended_col8 [output_size-1:2] = 0 ;
assign extended_col9 [output_size-1:2] = 0 ;
assign extended_col10 [output_size-1:2] = 0 ;
assign extended_col11 [output_size-1:2] = 0 ;
assign extended_col12 [output_size-1:2] = 0 ;
assign extended_col13 [output_size-1:2] = 0 ;
assign extended_col14 [output_size-1:2] = 0 ;
assign extended_col15 [output_size-1:2] = 0 ;
assign extended_col16 [output_size-1:2] = 0 ;
assign extended_col17 [output_size-1:2] = 0 ;
assign extended_col18 [output_size-1:2] = 0 ;

assign extended_diag0 [output_size-1:2] = 0 ;
assign extended_diag1 [output_size-1:2] = 0 ;
assign extended_diag2 [output_size-1:2] = 0 ;
assign extended_diag3 [output_size-1:2] = 0 ;
assign extended_diag4 [output_size-1:2] = 0 ;
assign extended_diag5 [output_size-1:2] = 0 ; 
assign extended_diag6 [output_size-1:2] = 0 ;
assign extended_diag7 [output_size-1:2] = 0 ;
assign extended_diag8 [output_size-1:2] = 0 ;
assign extended_diag9 [output_size-1:2] = 0 ;
assign extended_diag10 [output_size-1:2] = 0 ;
assign extended_diag11 [output_size-1:2] = 0 ;
assign extended_diag12 [output_size-1:2] = 0 ;
assign extended_diag13 [output_size-1:2] = 0 ;
assign extended_diag14 [output_size-1:2] = 0 ;
assign extended_diag15 [output_size-1:2] = 0 ;
assign extended_diag16 [output_size-1:2] = 0 ;
assign extended_diag17 [output_size-1:2] = 0 ;
assign extended_diag18 [output_size-1:2] = 0 ;
assign extended_diag19 [output_size-1:2] = 0 ;
assign extended_diag20 [output_size-1:2] = 0 ;
assign extended_diag21 [output_size-1:2] = 0 ;
assign extended_diag22 [output_size-1:2] = 0 ;
assign extended_diag23 [output_size-1:2] = 0 ;
assign extended_diag24 [output_size-1:2] = 0 ;
assign extended_diag25 [output_size-1:2] = 0 ;
assign extended_diag26 [output_size-1:2] = 0 ;
assign extended_rev_diag0 [output_size-1:2] = 0 ;
assign extended_rev_diag1 [output_size-1:2] = 0 ;
assign extended_rev_diag2 [output_size-1:2] = 0 ;
assign extended_rev_diag3 [output_size-1:2] = 0 ;
assign extended_rev_diag4 [output_size-1:2] = 0 ;
assign extended_rev_diag5 [output_size-1:2] = 0 ;
assign extended_rev_diag6 [output_size-1:2] = 0 ;
assign extended_rev_diag7 [output_size-1:2] = 0 ;
assign extended_rev_diag8 [output_size-1:2] = 0 ;
assign extended_rev_diag9 [output_size-1:2] = 0 ;
assign extended_rev_diag10 [output_size-1:2] = 0 ;
assign extended_rev_diag11 [output_size-1:2] = 0 ;
assign extended_rev_diag12 [output_size-1:2] = 0 ;
assign extended_rev_diag13 [output_size-1:2] = 0 ;
assign extended_rev_diag14 [output_size-1:2] = 0 ;
assign extended_rev_diag15 [output_size-1:2] = 0 ;
assign extended_rev_diag16 [output_size-1:2] = 0 ;
assign extended_rev_diag17 [output_size-1:2] = 0 ;
assign extended_rev_diag18 [output_size-1:2] = 0 ;
assign extended_rev_diag19 [output_size-1:2] = 0 ;
assign extended_rev_diag20 [output_size-1:2] = 0 ;
assign extended_rev_diag21 [output_size-1:2] = 0 ;
assign extended_rev_diag22 [output_size-1:2] = 0 ;
assign extended_rev_diag23 [output_size-1:2] = 0 ;
assign extended_rev_diag24 [output_size-1:2] = 0 ;
assign extended_rev_diag25 [output_size-1:2] = 0 ;
assign extended_rev_diag26 [output_size-1:2] = 0 ;

assign extended_row0 [1:0] = row0 ;
assign extended_row1 [1:0] = row1 ; 
assign extended_row2 [1:0] = row2 ;
assign extended_row3 [1:0] = row3 ;
assign extended_row4 [1:0] = row4 ;
assign extended_row5 [1:0] = row5 ; 
assign extended_row6 [1:0] = row6 ;
assign extended_row7 [1:0] = row7 ;
assign extended_row8 [1:0] = row8 ;
assign extended_row9 [1:0] = row9 ;
assign extended_row10 [1:0] = row10 ;
assign extended_row11 [1:0] = row11 ;
assign extended_row12 [1:0] = row12 ;
assign extended_row13 [1:0] = row13 ;
assign extended_row14 [1:0] = row14 ;
assign extended_row15 [1:0] = row15 ;
assign extended_row16 [1:0] = row16 ;
assign extended_row17 [1:0] = row17 ;
assign extended_row18 [1:0] = row18 ;

assign extended_col0 [1:0] = col0 ;
assign extended_col1 [1:0] = col1 ; 
assign extended_col2 [1:0] = col2 ;
assign extended_col3 [1:0] = col3 ;
assign extended_col4 [1:0] = col4 ;
assign extended_col5 [1:0] = col5 ; 
assign extended_col6 [1:0] = col6 ;
assign extended_col7 [1:0] = col7 ;
assign extended_col8 [1:0] = col8 ;
assign extended_col9 [1:0] = col9 ;
assign extended_col10 [1:0] = col10 ;
assign extended_col11 [1:0] = col11 ;
assign extended_col12 [1:0] = col12 ;
assign extended_col13 [1:0] = col13 ;
assign extended_col14 [1:0] = col14 ;
assign extended_col15 [1:0] = col15 ;
assign extended_col16 [1:0] = col16 ;
assign extended_col17 [1:0] = col17 ;
assign extended_col18 [1:0] = col18 ;

assign extended_diag0 [1:0] = diag0 ;
assign extended_diag1 [1:0] = diag1 ; 
assign extended_diag2 [1:0] = diag2 ;
assign extended_diag3 [1:0] = diag3 ;
assign extended_diag4 [1:0] = diag4 ;
assign extended_diag5 [1:0] = diag5 ; 
assign extended_diag6 [1:0] = diag6 ;
assign extended_diag7 [1:0] = diag7 ;
assign extended_diag8 [1:0] = diag8 ;
assign extended_diag9 [1:0] = diag9 ;
assign extended_diag10 [1:0] = diag10 ;
assign extended_diag11 [1:0] = diag11 ;
assign extended_diag12 [1:0] = diag12 ;
assign extended_diag13 [1:0] = diag13 ;
assign extended_diag14 [1:0] = diag14 ;
assign extended_diag15 [1:0] = diag15 ;
assign extended_diag16 [1:0] = diag16 ;
assign extended_diag17 [1:0] = diag17 ;
assign extended_diag18 [1:0] = diag18 ;
assign extended_diag19 [1:0] = diag19 ;
assign extended_diag20 [1:0] = diag20 ;
assign extended_diag21 [1:0] = diag21 ;
assign extended_diag22 [1:0] = diag22 ;
assign extended_diag23 [1:0] = diag23 ;
assign extended_diag24 [1:0] = diag24 ;
assign extended_diag25 [1:0] = diag25 ;
assign extended_diag26 [1:0] = diag26 ;

assign extended_rev_diag0 [1:0] = rev_diag0 ;
assign extended_rev_diag1 [1:0] = rev_diag1 ; 
assign extended_rev_diag2 [1:0] = rev_diag2 ;
assign extended_rev_diag3 [1:0] = rev_diag3 ;
assign extended_rev_diag4 [1:0] = rev_diag4 ;
assign extended_rev_diag5 [1:0] = rev_diag5 ; 
assign extended_rev_diag6 [1:0] = rev_diag6 ;
assign extended_rev_diag7 [1:0] = rev_diag7 ;
assign extended_rev_diag8 [1:0] = rev_diag8 ;
assign extended_rev_diag9 [1:0] = rev_diag9 ;
assign extended_rev_diag10 [1:0] = rev_diag10 ;
assign extended_rev_diag11 [1:0] = rev_diag11 ;
assign extended_rev_diag12 [1:0] = rev_diag12 ;
assign extended_rev_diag13 [1:0] = rev_diag13 ;
assign extended_rev_diag14 [1:0] = rev_diag14 ;
assign extended_rev_diag15 [1:0] = rev_diag15 ;
assign extended_rev_diag16 [1:0] = rev_diag16 ;
assign extended_rev_diag17 [1:0] = rev_diag17 ;
assign extended_rev_diag18 [1:0] = rev_diag18 ;
assign extended_rev_diag19 [1:0] = rev_diag19 ;
assign extended_rev_diag20 [1:0] = rev_diag20 ;
assign extended_rev_diag21 [1:0] = rev_diag21 ;
assign extended_rev_diag22 [1:0] = rev_diag22 ;
assign extended_rev_diag23 [1:0] = rev_diag23 ;
assign extended_rev_diag24 [1:0] = rev_diag24 ;
assign extended_rev_diag25 [1:0] = rev_diag25 ;
assign extended_rev_diag26 [1:0] = rev_diag26 ;

assign sum     =  extended_row0 +  extended_col0 +  extended_diag0 +  extended_rev_diag0 +
	              extended_row1 +  extended_col1 +  extended_diag1 +  extended_rev_diag1 +
	              extended_row2 +  extended_col2 +  extended_diag2 +  extended_rev_diag2 +
	              extended_row3 +  extended_col3 +  extended_diag3 +  extended_rev_diag3 +
	              extended_row4 +  extended_col4 +  extended_diag4 +  extended_rev_diag4 +
	              extended_row5 +  extended_col5 +  extended_diag5 +  extended_rev_diag5 +
	              extended_row6 +  extended_col6 +  extended_diag6 +  extended_rev_diag6 +
	              extended_row7 +  extended_col7 +  extended_diag7 +  extended_rev_diag7 +
	              extended_row8 +  extended_col8 +  extended_diag8 +  extended_rev_diag8 +
	              extended_row9 +  extended_col9 +  extended_diag9 +  extended_rev_diag9 +
	              extended_row10 + extended_col10 + extended_diag10 + extended_rev_diag10 +
	              extended_row11 + extended_col11 + extended_diag11 + extended_rev_diag11 +
	              extended_row12 + extended_col12 + extended_diag12 + extended_rev_diag12 +
	              extended_row13 + extended_col13 + extended_diag13 + extended_rev_diag13 +
	              extended_row14 + extended_col14 + extended_diag14 + extended_rev_diag14 +
	              extended_row15 + extended_col15 + extended_diag15 + extended_rev_diag15 +
	              extended_row16 + extended_col16 + extended_diag16 + extended_rev_diag16 +
	              extended_row17 + extended_col17 + extended_diag17 + extended_rev_diag17 +
	              extended_row18 + extended_col18 + extended_diag18 + extended_rev_diag18 +
								                    extended_diag19 + extended_rev_diag19 +
	                                                extended_diag20 + extended_rev_diag20 +
	                                                extended_diag21 + extended_rev_diag21 +
	                                                extended_diag22 + extended_rev_diag22 +
	                                                extended_diag23 + extended_rev_diag23 +
	                                                extended_diag24 + extended_rev_diag24 +
	                                                extended_diag25 + extended_rev_diag25 +
	                                                extended_diag26 + extended_rev_diag26;

endmodule



