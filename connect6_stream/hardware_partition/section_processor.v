`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:18:27 04/10/2019 
// Design Name: 
// Module Name:    section_processor 
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

module section_processor #
   (
	parameter integer section_size = 19
    )
   (
	input clk, rst, start, 	 		  
	input [section_size*2-1:0] section,
	output [1:0] num_t4_b, num_t3_b, num_t2_b, num_t4_w, num_t3_w, num_t2_w 
    );
    
    wire [0:5] window_b [0:section_size-6], window_w [0:section_size-6];
	
	wire [0:section_size-6] t4_found_b, t3_found_b, t2_found_b, t4_found_w, t3_found_w, t2_found_w ;
	wire [4-1 : 0] current_num_window_b, current_num_window_w ;
	wire [3-1 : 0] current_window_position_b, current_window_position_w ;
	
	//Marks
	wire [0 : section_size-1] marks_b, marks_w ;
	wire [2:0] pos_to_mark_b [0 :section_size-6], pos_to_mark_w [0 :section_size-6] ;
	wire rst_marks ; 
	reg update_marks_b, update_marks_w ;
	
	//Priority encoders
	
	wire t4_pending_b, t3_pending_b, t2_pending_b, t4_pending_w, t3_pending_w, t2_pending_w ;
	wire [4-1 : 0] window_num_t4_b, window_num_t3_b, window_num_t2_b, window_num_t4_w, window_num_t3_w, window_num_t2_w ;
		
	//Threat counters	
	reg inc_t4_b, inc_t3_b, inc_t2_b ;
	reg inc_t4_w, inc_t3_w, inc_t2_w ;

	//FSM
	localparam IDLE = 1'b0, PROCESSING = 1'b1 ; 	
	reg  current_state_b, current_state_w ;
	reg next_state_b,next_state_w ;

	//Process all the section in parallel
	//integer j ;
	genvar i,j ;
	generate
	for ( i=0 ; i<=(section_size-6) ; i=i+1)
		begin :loop1
		for (j=0 ; j <= 6-1 ; j=j+1)
			begin :loop2
			assign window_b[i][j] = section[(section_size*2-1)-i*2-j*2];
			assign window_w[i][j] = section[(section_size*2-1)-i*2-j*2-1];
			end
		window_processor WP (window_w[i] , window_b[i] , marks_w[i:i+5], marks_b[i:i+5], t4_found_w[i], t3_found_w[i], t2_found_w[i], t4_found_b[i], t3_found_b[i], t2_found_b[i], pos_to_mark_w[i], pos_to_mark_b[i]);
	    end 
	endgenerate	


//Select the leftmost window where a threat was found
	code_pri #(section_size-5) cod_t4_b  (t4_found_b, t4_pending_b, window_num_t4_b);
	code_pri #(section_size-5) cod_t3_b  (t3_found_b, t3_pending_b, window_num_t3_b);
	code_pri #(section_size-5) cod_t2_b  (t2_found_b, t2_pending_b, window_num_t2_b);
	
	code_pri #(section_size-5) cod_t4_w  (t4_found_w, t4_pending_w, window_num_t4_w);
	code_pri #(section_size-5) cod_t3_w  (t3_found_w, t3_pending_w, window_num_t3_w);
	code_pri #(section_size-5) cod_t2_w  (t2_found_w, t2_pending_w, window_num_t2_w);
	
//Muxes to locate the current mark to write
	assign current_num_window_b = t4_pending_b == 1'b1 ? window_num_t4_b : t3_pending_b == 1'b1 ? window_num_t3_b: window_num_t2_b;
	assign current_window_position_b = t4_pending_b == 1'b1 ? pos_to_mark_b[window_num_t4_b] : t3_pending_b == 1'b1 ? pos_to_mark_b[window_num_t3_b] : pos_to_mark_b[window_num_t2_b];
	marks_updater #(section_size) marks_updater_b (clk, rst_marks, update_marks_b, current_num_window_b, current_window_position_b, marks_b);
	
	assign current_num_window_w = t4_pending_w == 1'b1 ? window_num_t4_w : t3_pending_w == 1'b1 ? window_num_t3_w: window_num_t2_w;
	assign current_window_position_w = t4_pending_w == 1'b1 ? pos_to_mark_w[window_num_t4_w] : t3_pending_w == 1'b1 ? pos_to_mark_w[window_num_t3_w] : pos_to_mark_w[window_num_t2_w];
	marks_updater #(section_size) marks_updater_w (clk, rst_marks, update_marks_w, current_num_window_w, current_window_position_w, marks_w);

	assign rst_marks = rst || start ;
					
	counter t4_counter_b (clk, rst, start, inc_t4_b, num_t4_b);
	counter t3_counter_b (clk, rst, start, inc_t3_b, num_t3_b);
	counter t2_counter_b (clk, rst, start, inc_t2_b, num_t2_b);	
	
	counter t4_counter_w (clk, rst, start, inc_t4_w, num_t4_w);
	counter t3_counter_w (clk, rst, start, inc_t3_w, num_t3_w);
	counter t2_counter_w (clk, rst, start, inc_t2_w, num_t2_w);	


	//Control FSM
	always @(current_state_b, start, t4_pending_b, t3_pending_b, t2_pending_b)
	begin
		//Defaults		
		update_marks_b = 1'b0;
		inc_t4_b = 1'b0;
		inc_t3_b = 1'b0;
		inc_t2_b = 1'b0;		
		next_state_b = current_state_b;	  
		case (current_state_b)
			IDLE :	if (start == 1'b1)
					next_state_b = PROCESSING;
					
			
			PROCESSING :
				//Update threats count
				if (t4_pending_b == 1'b1)
					begin
					inc_t4_b =1'b1;
					update_marks_b = 1'b1;
					end
				else if (t3_pending_b == 1'b1)
					begin
					inc_t3_b = 1'b1;
					update_marks_b = 1'b1;
					end
				else if (t2_pending_b == 1'b1) 
					begin
					inc_t2_b = 1'b1;
					update_marks_b = 1'b1;
					end
				//Section explored
		  	    else next_state_b = IDLE;
		endcase;
	end  
	
	
	always @(current_state_w, start, t4_pending_w, t3_pending_w, t2_pending_w)
	begin
		//Defaults		
		update_marks_w = 1'b0;
		inc_t4_w = 1'b0;
		inc_t3_w = 1'b0;
		inc_t2_w = 1'b0;		
		next_state_w = current_state_w;	  
		case (current_state_w)
			IDLE :	if (start == 1'b1)
					next_state_w = PROCESSING;
			PROCESSING :
				//Update threats count
				if (t4_pending_w == 1'b1)
					begin
					inc_t4_w =1'b1;
					update_marks_w = 1'b1;
					end
				else if (t3_pending_w == 1'b1)
					begin
					inc_t3_w = 1'b1;
					update_marks_w = 1'b1;
					end
				else if (t2_pending_w == 1'b1) 
					begin
					inc_t2_w = 1'b1;
					update_marks_w = 1'b1;
					end
				//Section explored
		  	    else next_state_w = IDLE;
		endcase;
	end  


	always @(posedge clk, posedge rst)
	begin
		if (rst == 1'b1)	begin
		      current_state_b <= IDLE;
		      current_state_w <= IDLE;
		end

		else begin
		      current_state_b <= next_state_b;
		      current_state_w <= next_state_w;
        end
	end
	
endmodule	

