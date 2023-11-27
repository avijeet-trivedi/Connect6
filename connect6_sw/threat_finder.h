//
//  threat_finder.h
//  C6 NegaScout
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef threat_finder_h
#define threat_finder_h

void threat_finder(uchar board[19][19], player turn){
    
    auto start = high_resolution_clock::now();
    
    int  len_hs = c_max-c_min+1;
    int  num_hs = r_max-r_min+1;
    
    int  len_vs = r_max-r_min+1 ;
    int  num_vs = c_max-c_min+1 ;
    
    int  num_diag = r_max-r_min + c_max-c_min - 9 ;
    
    // Horizontal Sections
    uchar  section_p_hs[num_hs][len_hs] ;
    uchar  section_o_hs[num_hs][len_hs] ;
    
    // Vertical Sections
    uchar  section_p_vs[num_vs][len_vs] ;
    uchar  section_o_vs[num_vs][len_vs] ;
    
    // Diagonal Sections (135 degree)
    uchar  section_p_rev_diag[num_diag][min(len_vs,len_hs)] ;
    uchar  section_o_rev_diag[num_diag][min(len_vs,len_hs)] ;
    
    // Diagonal Sections (45 degree)
    uchar  section_p_diag[num_diag][min(len_vs,len_hs)] ;
    uchar  section_o_diag[num_diag][min(len_vs,len_hs)] ;
    
    // T4 BLACK [PLAYER]
    
    // Making Horizontal Sections
    // Calculating t4 threat of the player in that sections
    
    // i is row no.
    // j is col no.
    for(int  i=0 ; i<num_hs ; i++){
        for(int  l=0 ; l<len_hs ; l++){
            section_p_hs[i][l] = board[r_min+i][c_min+l] ;
            section_o_hs[i][l] = board[r_min+i][c_min+l] ;
        }
        
        for (int j=0 ; j<len_hs-5 ; j++){                               //threats in the window for PLAYER
            int p_cnt  = 0 ;
            int trt_pos1 = -20 ;
            int trt_pos2 = -20 ;
            uchar* sec_pos = 0 ;
            int count = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p_hs[i][j+m] == turn.o || section_p_hs[i][j+m] == 'r' ) {
                    p_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_p_hs[i][j+m] == '_'){
                    sec_pos = &section_p_hs[i][j+m] ;
                    count++;
                    if(count == 1) trt_pos1 = (19*(r_min+i))+c_min+j+m  ;
                    else if (count == 2) trt_pos2 = (19*(r_min+i))+c_min+j+m  ;
                }
                
                else if (section_p_hs[i][j+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 4 || p_cnt == 5){
                *sec_pos = 'r' ;
                t4_p.push(trt_pos1) ;                          //position translator
                t4_p.push(trt_pos2) ;                          //position translator
                return;
            }
        }
    }
    
    // Making Vertical Sections
    // Calculating t4 threat of the player in that sections
    
    // i is row no.
    // j is col no.
    for(int  j=0 ; j<num_vs ; j++){
        for(int  l=0 ; l<len_vs ; l++){
            section_p_vs[j][l] = board[r_min+l][c_min+j] ;
            section_o_vs[j][l] = board[r_min+l][c_min+j] ;
        }
        
        for (int i=0 ; i<len_vs-5 ; i++){                 //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos1 = -20 ;
            int trt_pos2 = -20 ;
            uchar* sec_pos = 0 ;
            int count = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p_vs[j][i+m] == turn.o || section_p_vs[j][i+m] == 'r' ) {
                    p_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                else if ( section_p_vs[j][i+m] == '_'){
                    sec_pos = &section_p_vs[j][i+m] ;
                    count++ ;
                    if (count == 1) trt_pos1 = 19*(r_min+i+m)+(c_min+j) ;
                    else if (count == 2) trt_pos2 = 19*(r_min+i+m)+(c_min+j) ;
                }
                
                else if (section_p_vs[j][i+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 4 || p_cnt == 5){
                *sec_pos = 'r' ;
                t4_p.push(trt_pos1) ;                          //position translator
                t4_p.push(trt_pos2) ;                          //position translator
                return;
            }
        }
    }
    
    // Making Reverse diagonal Sections (135 degree)
    // Calculating t4 threat of the player in that sections
    
    int  j_max, i_max, i_min, i, j ;
    j_max = c_max ;
    i_max = r_min+5;
    j = c_max-5 ;
    i = r_min;
    for (int  num = 0 ; num < num_diag ; num++){
        int  len = min(i_max-i+1,j_max-j+1) ;
        for(int  l=0 ; l<len ; l++){
            section_p_rev_diag[num][l] = board[i+l][j+l] ;
            section_o_rev_diag[num][l] = board[i+l][j+l] ;
        }
        
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos1 = -20 ;
            int trt_pos2 = -20 ;
            uchar* sec_pos = 0 ;
            int count = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p_rev_diag[num][k+m] == turn.o || section_p_rev_diag[num][k+m] == 'r' ) {
                    p_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p_rev_diag[num][k+m] == '_'){
                    sec_pos = &section_p_rev_diag[num][k+m] ;
                    count++;
                    if (count == 1) trt_pos1 = 19*(i+k+m)+j+k+m  ;
                    else if (count == 2) trt_pos2 = 19*(i+k+m)+j+k+m  ;
                }
                
                else if (section_p_rev_diag[num][k+m] == turn.p) p_cnt++ ;
            }
            
            if (p_cnt == 4 || p_cnt == 5){
                *sec_pos = 'r' ;
                t4_p.push(trt_pos1) ;                          //position translator
                t4_p.push(trt_pos2) ;                          //position translator
                return;
            }
        }
        if (j!=c_min) j-- ;
        else i++ ;
        if(i_max!=r_max) i_max++ ;
        else j_max-- ;
    }
    
    
    // Making Diagonal Sections (45 degree) and Calculating t4 threat of the player in that sections also
    j = c_min ;
    i = r_min + 5 ;
    i_min = r_min ;
    j_max = c_min + 5 ;
    for (int  num = 0 ; num< num_diag ; num++){
        int  len = min(i-i_min+1,j_max-j+1);
        for(int  l=0 ; l<len ; l++){
            section_p_diag[num][l] = board[i-l][j+l] ;
            section_o_diag[num][l] = board[i-l][j+l] ;
        }
        
        //FOR BLACK
        //t4 & t5
        for (int  k=0 ; k<len-5;k++){                               //threats in the window for WHITE
            int p_cnt  = 0 ;
            int trt_pos1 = -20 ;
            int trt_pos2 = -20 ;
            uchar* sec_pos = 0 ;
            int count = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p_diag[num][k+m] == turn.o || section_p_diag[num][k+m] == 'r' ) {
                    p_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p_diag[num][k+m] == '_'){
                    sec_pos = &section_p_diag[num][k+m] ;
                    count++;
                    if(count == 1) trt_pos1 = 19*(i-k-m)+j+k+m ;
                    else if (count == 2) trt_pos2 = 19*(i-k-m)+j+k+m ;
                }
                
                else if (section_p_diag[num][k+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 4 || p_cnt == 5){
                *sec_pos = 'r' ;
                t4_p.push(trt_pos1) ;                          //position translator
                t4_p.push(trt_pos2) ;                          //position translator
                return;
            }
        }
        if (i!=r_max) i++ ;
        else j++;
        if (j_max!=c_max) j_max++;
        else i_min++;
    }
    
    // T4 WHITE [OPPONENT]
    
    int  t4_opponent = 0 ;
    
    // Horizontal Sections : Calculating t4 threat of the opponent
    // i is row no.
    // j is col no.
    for(int i=0 ; i<num_hs ; i++){
        
        for (int  j=0 ; j<len_hs-5 ;j++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_hs[i][j+m] == turn.p || section_o_hs[i][j+m] == 'r' ) {
                    o_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_o_hs[i][j+m] == '_'){
                    sec_pos = &section_o_hs[i][j+m] ;
                    trt_pos = (19*(r_min+i))+c_min+j+m  ;
                }
                
                else if (section_o_hs[i][j+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 4 || o_cnt == 5){
                *sec_pos = 'r' ;
                t4_o.push(trt_pos) ;                          //position translator
                t4_opponent++;
                if(t4_opponent==2) return;
            }
        }
    }
    
    // Vertical Sections : Calculating t4 threat of the opponent
    // i is row no.
    // j is col no.
    for(int  j=0 ; j<num_vs ; j++){
        
        for (int  i=0 ; i<len_vs-5;i++){
            int o_cnt = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_vs[j][i+m] == turn.p || section_o_vs[j][i+m] == 'r' ) {
                    o_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_o_vs[j][i+m] == '_'){
                    sec_pos = &section_o_vs[j][i+m] ;
                    trt_pos = 19*(r_min+i+m)+(c_min+j)   ;
                }
                
                else if (section_o_vs[j][i+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 4 || o_cnt == 5){
                *sec_pos = 'r' ;
                t4_o.push(trt_pos) ;                          //position translator
                t4_opponent++;
                if(t4_opponent==2) return;
            }
        }
    }
    
    // Rev_diagonal Sections (135 degree) : Calculating t4 threat of the opponent
    j_max = c_max ;
    i_max = r_min+5;
    j = c_max-5 ;
    i = r_min;
    for (int  num = 0 ; num < num_diag ; num++){
        int  len = min(i_max-i+1,j_max-j+1) ;
        //FOR WHITE
        //t4 & t5
        for (int  k=0 ; k<len-5;k++){
            int o_cnt = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_rev_diag[num][k+m] == turn.p || section_o_rev_diag[num][k+m] == 'r' ) {
                    o_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o_rev_diag[num][k+m] == '_'){
                    sec_pos = &section_o_rev_diag[num][k+m] ;
                    trt_pos = 19*(i+k+m)+j+k+m  ;
                }
                
                else if (section_o_rev_diag[num][k+m] == turn.o) o_cnt++ ;
            }
            
            if (o_cnt == 4 || o_cnt == 5){
                *sec_pos = 'r' ;
                t4_o.push(trt_pos) ;                          //position translator
                t4_opponent++;
                if(t4_opponent==2) return;
            }
        }
        if (j!=c_min) j-- ;
        else i++ ;
        if(i_max!=r_max) i_max++ ;
        else j_max-- ;
    }
    
    
    // Diagonal Sections (45 degree) : Calculating t4 threat of the opponent
    j = c_min ;
    i = r_min + 5 ;
    i_min = r_min ;
    j_max = c_min + 5 ;
    for (int  num = 0 ; num<num_diag ; num++){
        int  len = min(i-i_min+1,j_max-j+1);
        
        for (int  k=0 ; k<len-5;k++){
            int o_cnt = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o_diag[num][k+m] == turn.p || section_o_diag[num][k+m] == 'r' ) {
                    o_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                else if ( section_o_diag[num][k+m] == '_'){
                    sec_pos = &section_o_diag[num][k+m] ;
                    trt_pos = 19*(i-k-m)+j+k+m ;
                }
                else if (section_o_diag[num][k+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 4 || o_cnt == 5){
                *sec_pos = 'r' ;
                t4_o.push(trt_pos) ;                          //position translator
                t4_opponent++;
                if(t4_opponent==2) return;
            }
        }
        if (i!=r_max) i++ ;
        else j++;
        if (j_max!=c_max) j_max++;
        else i_min++;
    }
    
    
    // Calculating threat in following order : t3-->t2-->t1
    
    // Horizontal Sections
    // i is row no.
    // j is col no.
    for(int i=0 ; i<num_hs ; i++){
        // BLACK [PLAYER]
        
        // t3
        for (int j=0 ; j<len_hs-5 ;j++){                               //threats in the window for black
            int p_cnt = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_p_hs[i][j+m] == turn.o || section_p_hs[i][j+m] == 'r' ) {
                    p_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_p_hs[i][j+m] == '_'){
                    count++;
                    if (count == 3){
                        sec_pos = &section_p_hs[i][j+m] ;
                        trt_pos  = (19*(r_min+i))+c_min+j+m ;
                    }
                    
                }
                else if (section_p_hs[i][j+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 3){
                *sec_pos = 'r' ;
                t3_p.push(trt_pos) ;                          //position translator
            }
        }
        
        //t2
        for (int j=0 ; j<len_hs-5 ;j++){                               //threats in the window for black
            int p_cnt = 0 ;
            int trt_pos1 = 0 ;
            int trt_pos2 = 0 ;
            uchar* sec_pos = 0 ;
            int count = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_p_hs[i][j+m] == turn.o || section_p_hs[i][j+m] == 'r' ) {
                    p_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_p_hs[i][j+m] == '_'){
                    count++ ;
                    if (count == 3) trt_pos1 = (19*(r_min+i))+c_min+j+m  ;
                    else if (count == 4) {
                        sec_pos = &section_p_hs[i][j+m] ;
                        trt_pos2 = (19*(r_min+i))+c_min+j+m  ;
                    }
                }
                
                else if (section_p_hs[i][j+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 2){
                *sec_pos = 'r' ;
                t2_p.push(trt_pos1) ;                          //position translator
                t2_p.push(trt_pos2) ;                          //position translator
            }
        }
        
        //t1
        for (int j=0 ; j<len_hs-5 ;j++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_p_hs[i][j+m] == turn.o || section_p_hs[i][j+m] == 'r' ) {
                    p_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_p_hs[i][j+m] == '_'){
                    count++ ;
                    if(count==5) {
                        sec_pos = &section_p_hs[i][j+m] ;
                        trt_pos = (19*(r_min+i))+c_min+j+m  ;
                    }
                }
                else if (section_p_hs[i][j+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 1){
                *sec_pos = 'r' ;
                t1_p.push(trt_pos) ;                          //position translator
            }
        }
        
        // WHITE [OPPONENT]
        
        // t3
        for (int j=0 ; j<len_hs-5 ; j++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_hs[i][j+m] == turn.p || section_o_hs[i][j+m] == 'r' ) {
                    o_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_o_hs[i][j+m] == '_'){
                    count++ ;
                    if(count == 3) {
                        sec_pos = &section_o_hs[i][j+m] ;
                        trt_pos = (19*(r_min+i))+c_min+j+m  ;
                    }
                }
                
                else if (section_o_hs[i][j+m] == turn.o) o_cnt++ ;
            }
            
            if (o_cnt == 3){
                *sec_pos = 'r' ;
                t3_o.push(trt_pos) ;                          //position translator
            }
        }
        
        //t2
        for (int  j=0 ; j<len_hs-5 ;j++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_hs[i][j+m] == turn.p || section_o_hs[i][j+m] == 'r' ) {
                    o_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_o_hs[i][j+m] == '_'){
                    count++ ;
                    if(count==4) {
                        sec_pos = &section_o_hs[i][j+m] ;
                        trt_pos = (19*(r_min+i))+c_min+j+m  ;
                    }
                }
                else if (section_o_hs[i][j+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 2){
                *sec_pos = 'r' ;
                t2_o.push(trt_pos) ;                          //position translator
            }
        }
        
        // t1
        for (int j=0 ; j<len_hs-5 ; j++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o_hs[i][j+m] == turn.p || section_o_hs[i][j+m] == 'r' ) {
                    o_cnt = 0 ;
                    j = j+m ;
                    break ;
                }
                
                else if ( section_o_hs[i][j+m] == '_'){
                    count++ ;
                    if(count==5) {
                        sec_pos = &section_o_hs[i][j+m] ;
                        trt_pos = (19*(r_min+i))+c_min+j+m  ;
                    }
                }
                else if (section_o_hs[i][j+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 1){
                *sec_pos = 'r' ;
                t1_o.push(trt_pos) ;                          //position translator
            }
        }
    }
    
    // Vertical Sections
    
    // i is row no.
    // j is col no.
    for(int j=0 ; j<num_vs ; j++){
        // BLACK [PLAYER]
        
        // t3
        for (int i=0 ; i<len_vs-5 ; i++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p_vs[j][i+m] == turn.o || section_p_vs[j][i+m] == 'r' ) {
                    p_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_p_vs[j][i+m] == '_'){
                    count++ ;
                    if(count==3){
                        sec_pos = &section_p_vs[j][i+m] ;
                        trt_pos = 19*(r_min+i+m)+(c_min+j)   ;
                    }
                    
                }
                else if (section_p_vs[j][i+m] == turn.p) p_cnt++ ;
            }
            
            if (p_cnt == 3){
                *sec_pos = 'r' ;
                t3_p.push(trt_pos) ;                          //position translator
            }
        }
        
        // t2
        for (int i=0 ; i<len_vs-5;i++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos1 = 0 ;
            int trt_pos2 = 0 ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p_vs[j][i+m] == turn.o || section_p_vs[j][i+m] == 'r' ) {
                    p_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                else if ( section_p_vs[j][i+m] == '_'){
                    count++;
                    if (count == 3) trt_pos1 = 19*(r_min+i+m)+(c_min+j) ;
                    else if (count == 4) {
                        sec_pos = &section_p_vs[j][i+m] ;
                        trt_pos2 = 19*(r_min+i+m)+(c_min+j)   ;
                    }
                }
                else if (section_p_vs[j][i+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 2){
                *sec_pos = 'r' ;
                t2_p.push(trt_pos1) ;                          //position translator
                t2_p.push(trt_pos2) ;                          //position translator
                
            }
        }
        
        // t1
        for (int  i=0 ; i<len_vs-5;i++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p_vs[j][i+m] == turn.o || section_p_vs[j][i+m] == 'r' ) {
                    p_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_p_vs[j][i+m] == '_'){
                    count++ ;
                    if (count==5) {
                        sec_pos = &section_p_vs[j][i+m] ;
                        trt_pos = 19*(r_min+i+m)+(c_min+j)   ;
                    }
                }
                else if (section_p_vs[j][i+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 1){
                *sec_pos = 'r' ;
                t1_p.push(trt_pos) ;                          //position translator
            }
        }
        
        // WHITE [OPPONENT]
        
        // t3
        for (int  i=0 ; i<len_vs-5;i++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_vs[j][i+m] == turn.p || section_o_vs[j][i+m] == 'r' ) {
                    o_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_o_vs[j][i+m] == '_'){
                    count ++ ;
                    if (count==3){
                        sec_pos = &section_o_vs[j][i+m] ;
                        trt_pos = 19*(r_min+i+m)+(c_min+j) ;
                    }
                }
                
                else if (section_o_vs[j][i+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 3){
                *sec_pos = 'r' ;
                t3_o.push(trt_pos) ;                          //position translator
            }
        }
        
        // t2
        for (int i=0 ; i<len_vs-5;i++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_vs[j][i+m] == turn.p || section_o_vs[j][i+m] == 'r' ) {
                    o_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_o_vs[j][i+m] == '_'){
                    count++ ;
                    if (count==4){
                        sec_pos = &section_o_vs[j][i+m] ;
                        trt_pos = 19*(r_min+i+m)+(c_min+j)   ;
                    }
                }
                
                else if (section_o_vs[j][i+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 2){
                *sec_pos = 'r' ;
                t2_o.push(trt_pos) ;                          //position translator
            }
        }
        
        // t1
        for (int i=0 ; i<len_vs-5;i++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_vs[j][i+m] == turn.p || section_o_vs[j][i+m] == 'r' ) {
                    o_cnt = 0 ;
                    i = i+m ;
                    break ;
                }
                
                else if ( section_o_vs[j][i+m] == '_' ){
                    count++;
                    if (count==5){
                        sec_pos = &section_o_vs[j][i+m] ;
                        trt_pos = 19*(r_min+i+m)+(c_min+j)   ;
                    }
                }
                else if (section_o_vs[j][i+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 1){
                *sec_pos = 'r' ;
                t1_o.push(trt_pos) ;                          //position translator
            }
        }
    }
    
    // Calculating threat diagonally 135 degree
    // i is row no.
    // j is col no.
    j_max = c_max ;
    i_max = r_min+5;
    j = c_max-5 ;
    i = r_min;
    for (int  num = 0 ; num < num_diag ; num++){
        int  len = min(i_max-i+1,j_max-j+1) ;
        
        // BLACK [PLAYER]
        
        // t3
        for (int  k=0 ; k<len-5;k++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_p_rev_diag[num][k+m] == turn.o || section_p_rev_diag[num][k+m] == 'r' ) {
                    p_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p_rev_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 3) {
                        sec_pos = &section_p_rev_diag[num][k+m] ;
                        trt_pos = 19*(i+k+m)+j+k+m  ;
                    }
                    
                }
                else if (section_p_rev_diag[num][k+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 3){
                *sec_pos = 'r' ;
                t3_p.push(trt_pos) ;                          //position translator
            }
        }
        
        // t2
        for (int  k=0 ; k<len-5;k++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos1 = 0 ;
            int trt_pos2 = 0 ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_p_rev_diag[num][k+m] == turn.o || section_p_rev_diag[num][k+m] == 'r' ) {
                    p_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p_rev_diag[num][k+m] == '_'){
                    count++;
                    if (count == 3) trt_pos1 = 19*(i+k+m)+j+k+m ;
                    if (count == 4) {
                        sec_pos = &section_p_rev_diag[num][k+m] ;
                        trt_pos2 = 19*(i+k+m)+j+k+m  ;
                    }
                    
                }
                else if (section_p_rev_diag[num][k+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 2){
                *sec_pos = 'r' ;
                t2_p.push(trt_pos1) ;                          //position translator
                t2_p.push(trt_pos2) ;                          //position translator
                
            }
        }
        
        // t1
        for (int  k=0 ; k<len-5;k++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_p_rev_diag[num][k+m] == turn.o || section_p_rev_diag[num][k+m] == 'r' ) {
                    p_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p_rev_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 5) {
                        sec_pos = &section_p_rev_diag[num][k+m] ;
                        trt_pos = 19*(i+k+m)+j+k+m  ;
                    }
                }
                
                else if (section_p_rev_diag[num][k+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 1){
                *sec_pos = 'r' ;
                t1_p.push(trt_pos) ;                          //position translator
            }
        }
        
        // WHITE [OPPONENT]
        
        // t3
        for (int  k=0 ; k<len-5 ; k++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_rev_diag[num][k+m] == turn.p || section_o_rev_diag[num][k+m] == 'r' ) {
                    o_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o_rev_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 3) {
                        sec_pos = &section_o_rev_diag[num][k+m] ;
                        trt_pos = 19*(i+k+m)+j+k+m  ;
                    }
                }
                
                else if (section_o_rev_diag[num][k+m] == turn.o ) o_cnt++ ;
            }
            if (o_cnt == 3){
                *sec_pos = 'r' ;
                t3_o.push(trt_pos) ;                          //position translator
            }
        }
        
        //t2
        for (int  k=0 ; k<len-5;k++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_rev_diag[num][k+m] == turn.p || section_o_rev_diag[num][k+m] == 'r' ) {
                    o_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                else if ( section_o_rev_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 4) {
                        sec_pos = &section_o_rev_diag[num][k+m] ;
                        trt_pos = 19*(i+k+m)+j+k+m  ;
                    }
                }
                else if ( section_o_rev_diag[num][k+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 2){
                *sec_pos = 'r' ;
                t2_o.push(trt_pos) ;                          //position translator
            }
        }
        
        // t1
        for (int  k=0 ; k<len-5;k++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_rev_diag[num][k+m] == turn.p || section_o_rev_diag[num][k+m] == 'r' ) {
                    o_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o_rev_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 5) {
                        sec_pos = &section_o_rev_diag[num][k+m] ;
                        trt_pos = 19*(i+k+m)+j+k+m ;
                    }
                }
                else if (section_o_rev_diag[num][k+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 1){
                *sec_pos = 'r' ;
                t1_o.push(trt_pos) ;                          //position translator
            }
        }
        
        if (j!=c_min) j-- ;
        else i++ ;
        if(i_max!=r_max) i_max++ ;
        else j_max-- ;
    }
    
    // Calculating threat diagonally 45 degree
    
    // i is row no.
    // j is col no.
    j = c_min ;
    i = r_min + 5 ;
    i_min = r_min ;
    j_max = c_min + 5 ;
    for (int num = 0 ; num<num_diag ; num++){
        
        int  len = min(i-i_min+1,j_max-j+1);
        // BLACK [PLAYER]
        
        // t3
        for (int  k=0 ; k<len-5;k++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_p_diag[num][k+m] == turn.o || section_p_diag[num][k+m] == 'r' ) {
                    p_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p_diag[num][k+m] == '_'){
                    count++ ;
                    if (count==3) {
                        sec_pos = &section_p_diag[num][k+m] ;
                        trt_pos = 19*(i-k-m)+j+k+m ;
                    }
                    
                }
                else if (section_p_diag[num][k+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 3){
                *sec_pos = 'r' ;
                t3_p.push(trt_pos) ;                          //position translator
            }
        }
        
        // t2
        for (int k=0 ; k<len-5;k++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos1 = 0 ;
            int trt_pos2 = 0 ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_p_diag[num][k+m] == turn.o || section_p_diag[num][k+m] == 'r' ) {
                    p_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_p_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 3) trt_pos1 = 19*(i-k-m)+j+k+m ;
                    if (count == 4) {
                        sec_pos = &section_p_diag[num][k+m] ;
                        trt_pos2 = 19*(i-k-m)+j+k+m ;
                    }
                }
                
                else if (section_p_diag[num][k+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 2){
                *sec_pos = 'r' ;
                t2_p.push(trt_pos1) ;                          //position translator
                t2_p.push(trt_pos2) ;                          //position translator
            }
        }
        
        // t1
        for (int  k=0 ; k<len-5;k++){                               //threats in the window for black
            int p_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_p_diag[num][k+m] == turn.o || section_p_diag[num][k+m] == 'r' ) {
                    p_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                else if ( section_p_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 5) {
                        sec_pos = &section_p_diag[num][k+m] ;
                        trt_pos = 19*(i-k-m)+j+k+m ;
                    }
                }
                else if (section_p_diag[num][k+m] == turn.p ) p_cnt++ ;
            }
            
            if (p_cnt == 1){
                *sec_pos = 'r' ;
                t1_p.push(trt_pos) ;                          //position translator
            }
        }
        
        // WHITE [OPPONENT]
        
        // t3
        for (int  k=0 ; k<len-5 ; k++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o_diag[num][k+m] == turn.p || section_o_diag[num][k+m] == 'r' ) {
                    o_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 3) {
                        sec_pos = &section_o_diag[num][k+m] ;
                        trt_pos = 19*(i-k-m)+j+k+m ;
                    }
                }
                
                else if (section_o_diag[num][k+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 3){
                *sec_pos = 'r' ;
                t3_o.push(trt_pos) ;                          //position translator
            }
        }
        
        // t2
        for (int  k=0 ; k<len-5;k++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int m=0 ; m<6 ; m++){
                if ( section_o_diag[num][k+m] == turn.p || section_o_diag[num][k+m] == 'r' ) {
                    o_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 4) {
                        sec_pos = &section_o_diag[num][k+m] ;
                        trt_pos = 19*(i-k-m)+j+k+m ;
                    }
                }
                else if (section_o_diag[num][k+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 2){
                *sec_pos = 'r' ;
                t2_o.push(trt_pos) ;                          //position translator
                
            }
        }
        
        // t1
        for (int  k=0 ; k<len-5;k++){
            int o_cnt  = 0 ;
            int trt_pos ;
            uchar* sec_pos = 0 ;
            int count  = 0 ;
            for (int  m=0 ; m<6 ; m++){
                if ( section_o_diag[num][k+m] == turn.p || section_o_diag[num][k+m] == 'r' ) {
                    o_cnt = 0 ;
                    k = k+m ;
                    break ;
                }
                
                else if ( section_o_diag[num][k+m] == '_'){
                    count++ ;
                    if (count == 5) {
                        sec_pos = &section_o_diag[num][k+m] ;
                        trt_pos = 19*(i-k-m)+j+k+m ;
                    }
                }
                else if (section_o_diag[num][k+m] == turn.o ) o_cnt++ ;
            }
            
            if (o_cnt == 1){
                *sec_pos = 'r' ;
                t1_o.push(trt_pos) ;                          //position translator
            }
        }
        if (i!=r_max) i++ ;
        else j++;
        if (j_max!=c_max) j_max++;
        else i_min++;
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    TA_time += duration.count() ;
}

#endif /* threat_finder_h */
