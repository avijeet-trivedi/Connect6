//
//  TC_NO.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 06/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef TC_NO_h
#define TC_NO_h

inline int evaluate_no(char board[19][19], player turn){

    int start, end ;
    XTime_GetTime(&t_elapse);
    start =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    
    t_cnt trt_p ;
    t_cnt trt_o ;
    
    // Calculating threat horizontally
    // i is row no.
    // j is col no.
    for(int i=0 ;i<19;i++){
        //horizontal sections
        unsigned char section_p[19] ;
        unsigned char section_o[19] ;
        for(int l=0 ; l<19 ; l++){
            section_p[l] = board[i][l] ;
            section_o[l] = board[i][l] ;
        }
        
        // Counting in order t4 --> t3 --> t2
        
        //FOR BLACK
        //t4 & t5
        for (int j=0 ; j<14;j++){
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            
            for (int m=0 ; m<6 ; m++){
                if ( section_p[j+m] == turn.o || section_p[j+m] == 'r' ){
                    b_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                else if (section_p[j+m] == '_') sec_pos = &section_p[j+m] ;
                
                else if (section_p[j+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 4 || b_cnt == 5){
                *sec_pos = 'r' ;
                trt_p.t4++ ;
            }
        }
        
        //t3
        for (int j=0 ; j<14;j++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[j+m] == turn.o || section_p[j+m] == 'r' ) {
                    b_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_p[j+m] == '_') sec_pos = &section_p[j+m] ;
                
                else if (section_p[j+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 3){
                *sec_pos = 'r' ;
                trt_p.t3++ ;
            }
        }
        
        //t2
        for (int j=0 ; j<14;j++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[j+m] == turn.o || section_p[j+m] == 'r' ) {
                    b_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_p[j+m] == '_') sec_pos = &section_p[j+m] ;
                
                else if (section_p[j+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 2){
                *sec_pos = 'r' ;
                trt_p.t2++ ;
            }
        }
        
        //FOR WHITE
        //t4 & t5
        for (int j=0 ; j<14;j++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            
            for (int m=0 ; m<6 ; m++){
                if ( section_o[j+m] == turn.p || section_o[j+m] == 'r' ){
                    w_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if (section_o[j+m] == '_') sec_pos = &section_o[j+m] ;
                
                else if (section_o[j+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 4 || w_cnt == 5){
                *sec_pos = 'r' ;
                trt_o.t4++ ;
            }
        }
        
        //t3
        for (int j=0 ; j<14;j++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[j+m] == turn.p || section_o[j+m] == 'r' ) {
                    w_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_o[j+m] == '_') sec_pos = &section_o[j+m] ;
                
                else if (section_o[j+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 3){
                *sec_pos = 'r' ;
                trt_o.t3++ ;
            }
        }
        
        //t2
        for (int j=0 ; j<14;j++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[j+m] == turn.p || section_o[j+m] == 'r' ) {
                    w_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                else if ( section_o[j+m] == '_') sec_pos = &section_o[j+m] ;
                
                else if (section_o[j+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 2){
                *sec_pos = 'r' ;
                trt_o.t2++ ;
            }
        }
    }
    
    //calculating threat Vertically
    //i is row no.
    //j is col no.
    for(int j=0 ;j<19;j++){
        //vertical sections
        unsigned char section_p[19] ;
        unsigned char section_o[19] ;
        for(int l=0 ; l<19 ; l++){
            section_p[l] = board[l][j] ;
            section_o[l] = board[l][j] ;
        }
        //we will count in order t5 --> t4 --> t2 --> t1
        
        
        //FOR BLACK
        //t4 & t5
        for (int i=0 ; i<14 ; i++){
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[i+m] == turn.o || section_p[i+m] == 'r' ){
                    b_cnt = 0 ;
                    i = i+m ;
                    break ;
                    
                }
                else if (section_p[i+m] == '_') sec_pos = &section_p[i+m] ;
                
                else if (section_p[i+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 4 || b_cnt == 5){
                *sec_pos = 'r' ;
                trt_p.t4++ ;
            }
        }
        
        //t3
        for (int i=0 ; i<14;i++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[i+m] == turn.o || section_p[i+m] == 'r' ) {
                    b_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_p[i+m] == '_') sec_pos = &section_p[i+m] ;
                
                else if (section_p[i+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 3){
                *sec_pos = 'r' ;
                trt_p.t3++ ;
            }
        }
        
        //t2
        for (int i=0 ; i<14;i++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[i+m] == turn.o || section_p[i+m] == 'r' ) {
                    b_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_p[i+m] == '_') sec_pos = &section_p[i+m] ;
                
                else if (section_p[i+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 2){
                *sec_pos = 'r' ;
                trt_p.t2++ ;
            }
        }
        
        //FOR WHITE
        //t4 & t5
        for (int i=0 ; i<14;i++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[i+m] == turn.p || section_o[i+m] == 'r' ){
                    w_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if (section_o[i+m] == '_') sec_pos = &section_o[i+m] ;
                
                else if (section_o[i+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 4 || w_cnt == 5){
                *sec_pos = 'r' ;
                trt_o.t4++ ;
            }
        }
        
        //t3
        for (int i=0 ; i<14;i++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[i+m] == turn.p || section_o[i+m] == 'r' ) {
                    w_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_o[i+m] == '_') sec_pos = &section_o[i+m] ;
                
                else if (section_o[i+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 3){
                *sec_pos = 'r' ;
                trt_o.t3++ ;
            }
        }
        
        //t2
        for (int i=0 ; i<14;i++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[i+m] == turn.p || section_o[i+m] == 'r' ) {
                    w_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                else if ( section_o[i+m] == '_')sec_pos = &section_o[i+m] ;
                
                else if (section_o[i+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 2){
                *sec_pos = 'r' ;
                trt_o.t2++ ;
            }
        }
    }
    
    //calculating threat diagonally 135 degree
    //i is row no.
    // j is col no.
    
    int j = 13 ;
    int i = 0 ;
    int len ;
    while (i<14){
        //length of diagonal
        if (j!=0) len = 19 - j ;
        else len = 19 - i ;
        
        unsigned char section_p[len] ;
        unsigned char section_o[len] ;
        
        for(int l=0 ; l<len ; l++){
            section_p[l] = board[i+l][j+l] ;
            section_o[l] = board[i+l][j+l] ;
        }
        //we will count in order t5 --> t4 --> t2 --> t1
        
        
        //FOR BLACK
        //t4 & t5
        for (int k=0 ; k<len-5 ; k++){
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            
            for (int m=0 ; m<6 ; m++){
                if ( section_p[k+m] == turn.o || section_p[k+m] == 'r' ){
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                else if (section_p[k+m] == '_') sec_pos = &section_p[k+m] ;
                
                else if (section_p[k+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 4 || b_cnt == 5){
                *sec_pos = 'r' ;
                trt_p.t4++ ;
            }
        }
        
        //t3
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[k+m] == turn.o || section_p[k+m] == 'r' ) {
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p[k+m] == '_') sec_pos = &section_p[k+m] ;
                
                else if (section_p[k+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 3){
                *sec_pos = 'r' ;
                trt_p.t3++ ;
            }
        }
        
        //t2
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[k+m] == turn.o || section_p[k+m] == 'r' ) {
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p[k+m] == '_') sec_pos = &section_p[k+m] ;
                
                else if (section_p[k+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 2){
                *sec_pos = 'r' ;
                trt_p.t2++ ;
            }
        }
        
        //FOR WHITE
        //t4 & t5
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[k+m] == turn.p || section_o[k+m] == 'r' ){
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if (section_o[k+m] == '_') sec_pos = &section_o[k+m] ;
                
                else if (section_o[k+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 4 || w_cnt == 5){
                *sec_pos = 'r' ;
                trt_o.t4++ ;
            }
        }
        
        //t3
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[k+m] == turn.p || section_o[k+m] == 'r' ) {
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o[k+m] == '_') sec_pos = &section_o[k+m] ;
                
                else if (section_o[k+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 3){
                *sec_pos = 'r' ;
                trt_o.t3++ ;
            }
        }
        
        //t2
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[k+m] == turn.p || section_o[k+m] == 'r' ) {
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o[k+m] == '_') sec_pos = &section_o[k+m] ;
                
                else if (section_o[k+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 2){
                *sec_pos = 'r' ;
                trt_o.t2++ ;
            }
        }
        
        if (j!=0) j = j - 1 ;
        else i = i + 1 ;
    }
    
    
    
    //calculating threat diagonally 45 degree
    //i is row no.
    // j is col no.
    
    j = 0 ;
    i = 5 ;
    while (j<14){
        //length of diagonal
        if (i!=18) len = i + 1 ;
        else len = 19-j ;
        
        unsigned char section_p[len] ;
        unsigned char section_o[len] ;
        
        for(int l=0 ; l<len ; l++){
            section_p[l] = board[i-l][j+l] ;
            section_o[l] = board[i-l][j+l] ;
        }
        //we will count in order t5 --> t4 --> t2 --> t1
        
        
        //FOR BLACK
        //t4 & t5
        for (int k=0 ; k<len-5 ; k++){
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[k+m] == turn.o || section_p[k+m] == 'r' ){
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if (section_p[k+m] == '_')sec_pos = &section_p[k+m] ;
                
                else if (section_p[k+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 4 || b_cnt == 5){
                *sec_pos = 'r' ;
                trt_p.t4++ ;
            }
        }
        
        //t3
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[k+m] == turn.o || section_p[k+m] == 'r' ) {
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p[k+m] == '_') sec_pos = &section_p[k+m] ;
                
                else if (section_p[k+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 3){
                *sec_pos = 'r' ;
                trt_p.t3++ ;
            }
        }
        
        //t2
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p[k+m] == turn.o || section_p[k+m] == 'r' ) {
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p[k+m] == '_') sec_pos = &section_p[k+m] ;
                
                else if (section_p[k+m] == turn.p ) b_cnt++ ;
            }
            
            if (b_cnt == 2){
                *sec_pos = 'r' ;
                trt_p.t2++ ;
            }
        }
        
        //FOR WHITE
        //t4 & t5
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            
            for (int m=0 ; m<6 ; m++){
                if ( section_o[k+m] == turn.p || section_o[k+m] == 'r' ){
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if (section_o[k+m] == '_') sec_pos = &section_o[k+m] ;
                
                else if (section_o[k+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 4 || w_cnt == 5){
                *sec_pos = 'r' ;
                trt_o.t4++ ;
            }
        }
        
        //t3
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[k+m] == turn.p || section_o[k+m] == 'r' ) {
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o[k+m] == '_') sec_pos = &section_o[k+m] ;
                
                else if (section_o[k+m] == turn.o ) w_cnt++ ;
            }
            
            if (w_cnt == 3){
                *sec_pos = 'r' ;
                trt_o.t3++ ;
            }
        }
        
        //t2
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o[k+m] == turn.p || section_o[k+m] == 'r' ) {
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if (section_o[k+m] == '_') sec_pos = &section_o[k+m] ;
                
                else if (section_o[k+m] == turn.o) w_cnt++ ;
            }
            
            if (w_cnt == 2){
                *sec_pos = 'r' ;
                trt_o.t2++ ;
            }
        }
        
        if (i!=18) i = i + 1 ;
        else j = j + 1 ;
    }

    XTime_GetTime(&t_elapse);
    end =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
    eval_time += (end - start) ;
    
    return W4*(trt_p.t4 - trt_o.t4) + W3*(trt_p.t3 - trt_o.t3) + W2*(trt_p.t2 - trt_o.t2) ;
}

#endif /* TC_NO_h */
