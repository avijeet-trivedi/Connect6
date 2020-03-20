//
//  evaluate.h
//  C6_Final
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef evaluate_h
#define evaluate_h

int evaluate(uchar board[19][19]){
    leaf_nodes++;
    
    auto start = high_resolution_clock::now();
    
    t_cnt trt_b ;
    t_cnt trt_w ;
    
    //calculating threat horizontally
    //i is row no.
    // j is col no.
    for(int i=0 ;i<19;i++){
        //horizontal sections
        unsigned char section_b[19] ;
        unsigned char section_w[19] ;
        for(int l=0 ; l<19 ; l++){
            section_b[l] = board[i][l] ;
            section_w[l] = board[i][l] ;
        }
        
        // Counting in order t4 --> t3 --> t2
        
        
        //FOR BLACK
        //t4 & t5
        for (int j=0 ; j<14;j++){
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            
            for (int m=0 ; m<6 ; m++){
                if ( section_b[j+m] == 'W' || section_b[j+m] == 'r' ){
                    b_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                else if (section_b[j+m] == '_') sec_pos = &section_b[j+m] ;
                
                else if (section_b[j+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 4 || b_cnt == 5){
                *sec_pos = 'r' ;
                trt_b.t4++ ;
            }
        }
        
        //t3
        for (int j=0 ; j<14;j++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[j+m] == 'W' || section_b[j+m] == 'r' ) {
                    b_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_b[j+m] == '_') sec_pos = &section_b[j+m] ;
                
                else if (section_b[j+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 3){
                *sec_pos = 'r' ;
                trt_b.t3++ ;
            }
        }
        
        //t2
        for (int j=0 ; j<14;j++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[j+m] == 'W' || section_b[j+m] == 'r' ) {
                    b_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_b[j+m] == '_') sec_pos = &section_b[j+m] ;
                
                else if (section_b[j+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 2){
                *sec_pos = 'r' ;
                trt_b.t2++ ;
            }
        }
        
        //FOR WHITE
        //t4 & t5
        for (int j=0 ; j<14;j++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            
            for (int m=0 ; m<6 ; m++){
                if ( section_w[j+m] == 'B' || section_w[j+m] == 'r' ){
                    w_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if (section_w[j+m] == '_') sec_pos = &section_w[j+m] ;
                
                else if (section_w[j+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 4 || w_cnt == 5){
                *sec_pos = 'r' ;
                trt_w.t4++ ;
            }
        }
        
        //t3
        for (int j=0 ; j<14;j++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[j+m] == 'B' || section_w[j+m] == 'r' ) {
                    w_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_w[j+m] == '_') sec_pos = &section_w[j+m] ;
                
                else if (section_w[j+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 3){
                *sec_pos = 'r' ;
                trt_w.t3++ ;
            }
        }
        
        //t2
        for (int j=0 ; j<14;j++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[j+m] == 'B' || section_w[j+m] == 'r' ) {
                    w_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                else if ( section_w[j+m] == '_') sec_pos = &section_w[j+m] ;
                
                else if (section_w[j+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 2){
                *sec_pos = 'r' ;
                trt_w.t2++ ;
            }
        }
    }
    
    //calculating threat Vertically
    //i is row no.
    //j is col no.
    for(int j=0 ;j<19;j++){
        //vertical sections
        unsigned char section_b[19] ;
        unsigned char section_w[19] ;
        for(int l=0 ; l<19 ; l++){
            section_b[l] = board[l][j] ;
            section_w[l] = board[l][j] ;
        }
        //we will count in order t5 --> t4 --> t2 --> t1
        
        
        //FOR BLACK
        //t4 & t5
        for (int i=0 ; i<14 ; i++){
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[i+m] == 'W' || section_b[i+m] == 'r' ){
                    b_cnt = 0 ;
                    i = i+m ;
                    break ;
                    
                }
                else if (section_b[i+m] == '_') sec_pos = &section_b[i+m] ;
                
                else if (section_b[i+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 4 || b_cnt == 5){
                *sec_pos = 'r' ;
                trt_b.t4++ ;
            }
        }
        
        //t3
        for (int i=0 ; i<14;i++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[i+m] == 'W' || section_b[i+m] == 'r' ) {
                    b_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_b[i+m] == '_') sec_pos = &section_b[i+m] ;
                
                else if (section_b[i+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 3){
                *sec_pos = 'r' ;
                trt_b.t3++ ;
            }
        }
        
        //t2
        for (int i=0 ; i<14;i++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[i+m] == 'W' || section_b[i+m] == 'r' ) {
                    b_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_b[i+m] == '_') sec_pos = &section_b[i+m] ;
                
                else if (section_b[i+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 2){
                *sec_pos = 'r' ;
                trt_b.t2++ ;
            }
        }
        
        //FOR WHITE
        //t4 & t5
        for (int i=0 ; i<14;i++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[i+m] == 'B' || section_w[i+m] == 'r' ){
                    w_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if (section_w[i+m] == '_') sec_pos = &section_w[i+m] ;
                
                else if (section_w[i+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 4 || w_cnt == 5){
                *sec_pos = 'r' ;
                trt_w.t4++ ;
            }
        }
        
        //t3
        for (int i=0 ; i<14;i++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[i+m] == 'B' || section_w[i+m] == 'r' ) {
                    w_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_w[i+m] == '_') sec_pos = &section_w[i+m] ;
                
                else if (section_w[i+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 3){
                *sec_pos = 'r' ;
                trt_w.t3++ ;
            }
        }
        
        //t2
        for (int i=0 ; i<14;i++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[i+m] == 'B' || section_w[i+m] == 'r' ) {
                    w_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                else if ( section_w[i+m] == '_')sec_pos = &section_w[i+m] ;
                
                else if (section_w[i+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 2){
                *sec_pos = 'r' ;
                trt_w.t2++ ;
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
        
        unsigned char section_b[len] ;
        unsigned char section_w[len] ;
        
        for(int l=0 ; l<len ; l++){
            section_b[l] = board[i+l][j+l] ;
            section_w[l] = board[i+l][j+l] ;
        }
        //we will count in order t5 --> t4 --> t2 --> t1
        
        
        //FOR BLACK
        //t4 & t5
        for (int k=0 ; k<len-5 ; k++){
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            
            for (int m=0 ; m<6 ; m++){
                if ( section_b[k+m] == 'W' || section_b[k+m] == 'r' ){
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                else if (section_b[k+m] == '_') sec_pos = &section_b[k+m] ;
                
                else if (section_b[k+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 4 || b_cnt == 5){
                *sec_pos = 'r' ;
                trt_b.t4++ ;
            }
        }
        
        //t3
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[k+m] == 'W' || section_b[k+m] == 'r' ) {
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_b[k+m] == '_') sec_pos = &section_b[k+m] ;
                
                else if (section_b[k+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 3){
                *sec_pos = 'r' ;
                trt_b.t3++ ;
            }
        }
        
        //t2
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[k+m] == 'W' || section_b[k+m] == 'r' ) {
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_b[k+m] == '_') sec_pos = &section_b[k+m] ;
                
                else if (section_b[k+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 2){
                *sec_pos = 'r' ;
                trt_b.t2++ ;
            }
        }
        
        //FOR WHITE
        //t4 & t5
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[k+m] == 'B' || section_w[k+m] == 'r' ){
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if (section_w[k+m] == '_') sec_pos = &section_w[k+m] ;
                
                else if (section_w[k+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 4 || w_cnt == 5){
                *sec_pos = 'r' ;
                trt_w.t4++ ;
            }
        }
        
        //t3
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[k+m] == 'B' || section_w[k+m] == 'r' ) {
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_w[k+m] == '_') sec_pos = &section_w[k+m] ;
                
                else if (section_w[k+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 3){
                *sec_pos = 'r' ;
                trt_w.t3++ ;
            }
        }
        
        //t2
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[k+m] == 'B' || section_w[k+m] == 'r' ) {
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_w[k+m] == '_') sec_pos = &section_w[k+m] ;
                
                else if (section_w[k+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 2){
                *sec_pos = 'r' ;
                trt_w.t2++ ;
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
        
        unsigned char section_b[len] ;
        unsigned char section_w[len] ;
        
        for(int l=0 ; l<len ; l++){
            section_b[l] = board[i-l][j+l] ;
            section_w[l] = board[i-l][j+l] ;
        }
        //we will count in order t5 --> t4 --> t2 --> t1
        
        
        //FOR BLACK
        //t4 & t5
        for (int k=0 ; k<len-5 ; k++){
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[k+m] == 'W' || section_b[k+m] == 'r' ){
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if (section_b[k+m] == '_')sec_pos = &section_b[k+m] ;
                
                else if (section_b[k+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 4 || b_cnt == 5){
                *sec_pos = 'r' ;
                trt_b.t4++ ;
            }
        }
        
        //t3
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[k+m] == 'W' || section_b[k+m] == 'r' ) {
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_b[k+m] == '_') sec_pos = &section_b[k+m] ;
                
                else if (section_b[k+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 3){
                *sec_pos = 'r' ;
                trt_b.t3++ ;
            }
        }
        
        //t2
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int b_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_b[k+m] == 'W' || section_b[k+m] == 'r' ) {
                    b_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_b[k+m] == '_') sec_pos = &section_b[k+m] ;
                
                else if (section_b[k+m] == 'B' ) b_cnt++ ;
            }
            
            if (b_cnt == 2){
                *sec_pos = 'r' ;
                trt_b.t2++ ;
            }
        }
        
        //FOR WHITE
        //t4 & t5
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            
            for (int m=0 ; m<6 ; m++){
                if ( section_w[k+m] == 'B' || section_w[k+m] == 'r' ){
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if (section_w[k+m] == '_') sec_pos = &section_w[k+m] ;
                
                else if (section_w[k+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 4 || w_cnt == 5){
                *sec_pos = 'r' ;
                trt_w.t4++ ;
            }
        }
        
        //t3
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[k+m] == 'B' || section_w[k+m] == 'r' ) {
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_w[k+m] == '_') sec_pos = &section_w[k+m] ;
                
                else if (section_w[k+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 3){
                *sec_pos = 'r' ;
                trt_w.t3++ ;
            }
        }
        
        //t2
        for (int k=0 ; k<len-5;k++){
            int w_cnt = 0 ;
            unsigned char* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_w[k+m] == 'B' || section_w[k+m] == 'r' ) {
                    w_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_w[k+m] == '_') sec_pos = &section_w[k+m] ;
                
                else if (section_w[k+m] == 'W' ) w_cnt++ ;
            }
            
            if (w_cnt == 2){
                *sec_pos = 'r' ;
                trt_w.t2++ ;
            }
        }
        
        if (i!=18) i = i + 1 ;
        else j = j + 1 ;
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    eval_time += duration.count() ;
    
    return W4*(trt_b.t4 - trt_w.t4) + W3*(trt_b.t3 - trt_w.t3) + W2*(trt_b.t2 - trt_w.t2) ;
}

#endif /* evaluate_h */
