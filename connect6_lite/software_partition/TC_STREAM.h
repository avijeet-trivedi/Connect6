//
//  TC_STREAM.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 07/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef TC_STREAM_h
#define TC_STREAM_h

int evaluate(char board[19][19], player turn){
    
    int start_hw, end_hw, start, end ;
    XTime_GetTime(&t_elapse);
    start =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    
    unsigned int axi[23] = {0}  ;
    unsigned int x = 0;
    unsigned int counter = 22 ;
    unsigned int result = 0 ;
    unsigned int t4_p = 0 , t3_p = 0 , t2_p = 0 , t4_o = 0, t3_o = 0, t2_o = 0 ;
    
    for (int i=18 ; i>=0 ; i--){
        for (int j=18 ; j>=0 ; j--){
            if (board[i][j] == turn.p) axi[counter] |= (1 << (2*x+1) ) ;
            
            else if (board[i][j] == turn.o) axi[counter] |= (1 << (2*x) ) ;
            
            x = x + 1 ;
            if(x==16) {
                counter-- ;
                x=0 ;
            }
        }
    }
    
    XTime_GetTime(&t_elapse);
    start_hw =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    
    Xil_DCacheFlushRange((UINTPTR)axi, 4*NUM_OF_REGISTER);     // Flush the SrcBuffer before the DMA transfer
    XAxiDma_SimpleTransfer(&AxiDma,(UINTPTR) axi, 4*NUM_OF_REGISTER, XAXIDMA_DMA_TO_DEVICE);
    
    cout<<"";
    cout<<"";
    cout<<"";
    cout<<"";
    cout<<"";
    cout<<"";
    
    result = *(address+1) ;
    
    XTime_GetTime(&t_elapse);
    end_hw =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    hw_time += (end_hw - start_hw) ;
    
    t4_p = 7 & (result) ;
    t3_p = 15 & (result>>3) ;
    t2_p = 31 & (result>>7) ;
    t4_o = 7 & (result>>12) ;
    t3_o = 15 & (result>>15) ;
    t2_o = 31 & (result>>19) ;
    
    XTime_GetTime(&t_elapse);
    end =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    eval_time += (end - start) ;
    
    return W4*(t4_p - t4_o) + W3*(t3_p - t3_o) + W2*(t2_p - t2_o) ;
}

#endif /* TC_STREAM_h */
