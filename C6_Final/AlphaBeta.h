//
//  AlphaBeta.h
//  C6_Final
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef AlphaBeta_h
#define AlphaBeta_h

int AlphaBeta(uchar board[19][19], int depth, int alpha, int beta, bool turn){
    
    Node_count++ ;
    
    if(depth==0) return evaluate(board);
    
    // Fill Stack with max. of LIMIT no. of Moves and returns the no. of Moves
    unsigned long move_count = move_selector(board, turn);
    
    // Return zero if there is a tie
    if (move_count == 0 ){
        return 0;
    }
    
    // MAXIMIZERS TURN (BLACK)
    if (turn){
        if (move_count == 1 && b_win){
            Stack.pop() ;
            b_win = false ;
            return MAX ;
        }
        
        Move m;
        
#if (OPTIMISATION==2)
        u16 r_max_prev = r_max;
        u16 r_min_prev = r_min;
        u16 c_max_prev = c_max;
        u16 c_min_prev = c_min;
#endif
        
#if (NO==1)
        if(depth>=NO_MAX_DEPTH && move_count>NO_MAX_MOV){
            MV mov_val[NO_MAX_MOV] ;
            
            for (int i=0 ; i<NO_MAX_MOV ; i++){
                m =  Stack.top() ;
                board[m.row[0]] [m.col[0]] = 'B' ;
                board[m.row[1]] [m.col[1]] = 'B' ;
                mov_val[i].m = m;
                mov_val[i].Val = evaluate(board);
                board[m.row[0]] [m.col[0]] = '_' ;
                board[m.row[1]] [m.col[1]] = '_' ;
                Stack.pop() ;
            }
            
            sort(mov_val, mov_val+NO_MAX_MOV, Compare_Value_B);
            
            for (int i=0 ; i<NO_MAX_MOV ; i++){
                Stack.push(mov_val[i].m) ;
            }
        }
#endif
        
        while (move_count!=0){
            // Make a Move
            m = Stack.top();
            board[m.row[0]] [m.col[0]] = 'B' ;
            board[m.row[1]] [m.col[1]] = 'B' ;

#if (OPTIMISATION==2)
            r_max = min(max(max(m.row[0]+2,m.row[1]+2), r_max),18);
            r_min = max(min(min(m.row[0]-2,m.row[1]-2), r_min),0);
            c_max = min(max(max(m.col[0]+2, m.col[1]+2), c_max),18);
            c_min = max(min(min(m.col[0]-2, m.col[1]-2), c_min),0);
#endif

            alpha = max(alpha,AlphaBeta(board, depth-1, alpha, beta, !turn));

#if (OPTIMISATION==2)
            r_max = r_max_prev;
            r_min = r_min_prev;
            c_max = c_max_prev;
            c_min = c_min_prev;
#endif

            // Undo the moves
            board[m.row[0]] [m.col[0]] = '_' ;
            board[m.row[1]] [m.col[1]] = '_' ;
            
            if (alpha >= beta) {
                MTStack(move_count) ;
                break ;
            }
            Stack.pop() ;
            move_count--;
        }
        return alpha;
    }
    
    // If this minimizer's move
    else{
        if (move_count == 1 && w_win){
            Stack.pop() ;
            w_win = false ;
            return MIN ;
        }
        
        Move m ;
        
#if (OPTIMISATION==2)
        u16 r_max_prev = r_max;
        u16 r_min_prev = r_min;
        u16 c_max_prev = c_max;
        u16 c_min_prev = c_min;
#endif
        
#if (NO==1)
        if(depth>=NO_MAX_DEPTH && move_count>NO_MAX_MOV){
            MV mov_val[NO_MAX_MOV] ;
            
            for (int i=0 ; i<NO_MAX_MOV ; i++){
                m =  Stack.top() ;
                board[m.row[0]] [m.col[0]] = 'W' ;
                board[m.row[1]] [m.col[1]] = 'W' ;
                mov_val[i].m = m;
                mov_val[i].Val = evaluate(board);
                board[m.row[0]] [m.col[0]] = '_' ;
                board[m.row[1]] [m.col[1]] = '_' ;
                Stack.pop() ;
            }
            
            sort(mov_val, mov_val+NO_MAX_MOV, Compare_Value_W);
            
            for (int i=0 ; i<NO_MAX_MOV ; i++){
                Stack.push(mov_val[i].m) ;
            }
        }
#endif

        while (move_count!=0){
            // Make a Move
            m = Stack.top();
            board[m.row[0]] [m.col[0]] = 'W' ;
            board[m.row[1]] [m.col[1]] = 'W' ;

#if (OPTIMISATION==2)
            r_max = min(max(max(m.row[0]+2,m.row[1]+2), r_max),18);
            r_min = max(min(min(m.row[0]-2,m.row[1]-2), r_min),0);
            c_max = min(max(max(m.col[0]+2, m.col[1]+2), c_max),18);
            c_min = max(min(min(m.col[0]-2, m.col[1]-2), c_min),0);
#endif

            beta = min(beta,AlphaBeta(board, depth-1, alpha, beta, !turn));

#if (OPTIMISATION==2)
            r_max = r_max_prev;
            r_min = r_min_prev;
            c_max = c_max_prev;
            c_min = c_min_prev;
#endif
            
            // Undo the moves
            board[m.row[0]] [m.col[0]] = '_' ;
            board[m.row[1]] [m.col[1]] = '_' ;
            
            if (alpha >= beta){
                MTStack(move_count) ;
                break ;
            }
            Stack.pop() ;
            move_count--;
        }
        return beta;
    }
}

#endif /* AlphaBeta_h */
