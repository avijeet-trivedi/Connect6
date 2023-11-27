`timescale 1ns / 1ps

// this module will recieve windows of 6
module window_processor(    input [0:5] window_white, window_black,
						    input [5:0] marks_w, marks_b,
                            output reg t4_found_w, t3_found_w, t2_found_w, t4_found_b, t3_found_b, t2_found_b,
						    output reg [2:0] rightmost_empty_w, rightmost_empty_b

);
wire [2:0]count_b,count_w;
reg [5:0] inp_w, inp_b;
wire [2:0] outp_w, outp_b;

adder_6_bits adder_w( .inp(window_white), .out(count_w) ); 		//counts the number of white stones present in a window
	  
adder_6_bits adder_b( .inp(window_black), .out(count_b) );      //counts the number of black stones present in a window
	  
priority_encoder pw ( .in(inp_w), .out(outp_w) );
priority_encoder pb ( .in(inp_b), .out(outp_b) );

wire rival_black;
wire rival_white;

//Checking whether we have any oponent's stone in the window 

assign rival_black=|window_black;       
assign rival_white=|window_white;

always@(window_black, marks_b) begin //Black Disk
	inp_b=6'b111111;
	if(marks_b==6'd0) begin
	   if(rival_white==1) begin     // It's black's turn but white stone found_b in that window. So there can be no threat by black in that window
	       t4_found_b=1'b0;
           t3_found_b=1'b0;
		   t2_found_b=1'b0;
		   rightmost_empty_b=3'd7;     //invalid
       end										     
	   else begin    //if (rival_white==0)
	       if(count_b==4 || count_b==5)begin
					t4_found_b=1'b1;
					t3_found_b=1'b0;
			    	t2_found_b=1'b0;
			    	inp_b=window_black;
					rightmost_empty_b=outp_b;	
			end
											  
		    else if(count_b==3) begin
					t4_found_b=1'b0;
					t3_found_b=1'b1;
				    t2_found_b=1'b0;
				    inp_b=window_black;
					rightmost_empty_b=outp_b;	
		    end

	   
	       else if(count_b==2) begin
                t4_found_b=1'b0;
                t3_found_b=1'b0;
			   	t2_found_b=1'b1;
			   	inp_b=window_black;
			    rightmost_empty_b=outp_b;	
		   end
                            
		   else begin
                t4_found_b=1'b0;
                t3_found_b=1'b0;
                t2_found_b=1'b0;
                rightmost_empty_b=3'd7;
            end		                    
	   end
	end			
	else begin                 // if (marks!=6'd0)
	   t4_found_b=1'b0;
       t3_found_b=1'b0;
       t2_found_b=1'b0;
       rightmost_empty_b=3'd7;
    end													  
end				
											 
always@(window_white, marks_w) begin //White Disk
	inp_w=6'b111111;
	if(marks_w==6'd0) begin
	   if(rival_black==1) begin     // It's white's turn but black stone found  in that window. So there can be no threat by black in that window
	       t4_found_w=1'b0;
           t3_found_w=1'b0;
		   t2_found_w=1'b0;
		   rightmost_empty_w=3'd7;     //invalid
       end										     
	   else begin    //if (rival_white==0)
	       if(count_w==4 || count_w==5)begin
					t4_found_w=1'b1;
					t3_found_w=1'b0;
			    	t2_found_w=1'b0;
			    	inp_w=window_white;
					rightmost_empty_w=outp_w;	
			end
											  
		    else if(count_w==3) begin
					t4_found_w=1'b0;
					t3_found_w=1'b1;
				    t2_found_w=1'b0;
				    inp_w=window_white;
					rightmost_empty_w=outp_w;	
		    end

	   
	       else if(count_w==2) begin
                t4_found_w=1'b0;
                t3_found_w=1'b0;
			   	t2_found_w=1'b1;
			   	inp_w=window_white;
			    rightmost_empty_w=outp_w;	
		   end
                  
		   else begin
                t4_found_w=1'b0;
                t3_found_w=1'b0;
                t2_found_w=1'b0;
                rightmost_empty_w=3'd7;
            end		                    
	   end
	end			
	else begin                 // if (marks!=6'd0)
	   t4_found_w=1'b0;
       t3_found_w=1'b0;
       t2_found_w=1'b0;
       rightmost_empty_w=3'd7;
    end													  
end	

endmodule
	  