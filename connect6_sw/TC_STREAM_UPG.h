//
//  TC_STREAM_UPG.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 07/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef TC_STREAM_UPG_h
#define TC_STREAM_UPG_h

inline void send_board(char board[19][19], player turn){
    int start_hw, start, end ;
    
    XTime_GetTime(&t_elapse);
    start =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    
    unsigned int axi[23] = {0} ;
    unsigned int x = 0;
    unsigned int counter = 22 ;
    
    for (int i=18 ; i>=0 ; i--){
        for (int j=18 ; j>=0 ; j--){
            if(board[i][j] == turn.p) axi[counter] |= (1 << (2*x+1) ) ;
            
            else if(board[i][j] == turn.o) axi[counter] |= (1 << (2*x) ) ;
            
            x = x + 1 ;
            if(x==16) {
                counter-- ;
                x=0 ;
            }
        }
    }
    
    axi[0] |= 1<<18 ;
    
    XTime_GetTime(&t_elapse);
    start_hw =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    
    Xil_DCacheFlushRange((UINTPTR)axi, 4*NUM_OF_REGISTER);     // Flush the SrcBuffer before the DMA transfer
    XAxiDma_SimpleTransfer(&AxiDma,(UINTPTR) axi, 4*NUM_OF_REGISTER, XAXIDMA_DMA_TO_DEVICE);
    
    
    XTime_GetTime(&t_elapse);
    end =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    hw_time += (end - start_hw) ;
    eval_time += (end - start) ;
    
}

inline int send_move(int row1, int col1, int row2, int col2, bool turn){

    int start, end, start_hw, end_hw ;
    XTime_GetTime(&t_elapse);
    start =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    
    unsigned int location = 0 ;
    unsigned int t4_p = 0 , t3_p = 0 , t2_p = 0 , t4_o = 0, t3_o = 0, t2_o = 0 ;
    unsigned int result ;
    
    location = (row1<<27) | (col1<<22) | (row2<<5) |(col2)| (turn<<21) ;
    
    XTime_GetTime(&t_elapse);
    start_hw =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    
    *(address) = location ;
    cout<<"";
    result = *(address + 1) ;
    
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

#endif /* TC_STREAM_UPG_h */
