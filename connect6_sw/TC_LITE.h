//
//  evaluate_HW.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 06/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef evaluate_HW_h
#define evaluate_HW_h

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
    *(address + 0) = axi[0] ;
    *(address + 1) = axi[1] ;
    *(address + 2) = axi[2] ;
    *(address + 3) = axi[3] ;
    *(address + 4) = axi[4] ;
    *(address + 5) = axi[5] ;
    *(address + 6) = axi[6] ;
    *(address + 7) = axi[7] ;
    *(address + 8) = axi[8] ;
    *(address + 9) = axi[9] ;
    *(address + 10) = axi[10] ;
    *(address + 11) = axi[11] ;
    *(address + 12) = axi[12] ;
    *(address + 13) = axi[13] ;
    *(address + 14) = axi[14] ;
    *(address + 15) = axi[15] ;
    *(address + 16) = axi[16] ;
    *(address + 17) = axi[17] ;
    *(address + 18) = axi[18] ;
    *(address + 19) = axi[19] ;
    *(address + 20) = axi[20] ;
    *(address + 21) = axi[21] ;
    *(address + 22) = axi[22] ;
    cout<<"";
    result  = *(address + 24) ;
    
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

#endif /* evaluate_HW_h */
