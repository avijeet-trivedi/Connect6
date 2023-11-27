//
//  AlphaBeta.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 07/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef AlphaBeta_h
#define AlphaBeta_h

int AlphaBeta(char board[19][19], int depth, int alpha, int beta, player turn){
    
    Node_count++ ;
    
    if(depth==0){
        leaf_nodes++;
        return evaluate(board, black);
    }
    
    // Fill Stack with max. of LIMIT no. of Moves and returns the no. of Moves
    unsigned long move_count = move_selector(board, turn);
    
    // Return zero if there is a tie
    if (move_count == 0){
        return 0;
    }
    
#if (NO==1)
    if(depth>=NO_MAX_DEPTH && move_count>NO_MAX_MOV){
        MV mov_val[NO_MAX_MOV] ;
        move_ordering(board, mov_val, NO_MAX_MOV, turn) ;
    }
#endif
    
#if (OPTIMISATION==2)
    int r_max_prev = r_max;
    int r_min_prev = r_min;
    int c_max_prev = c_max;
    int c_min_prev = c_min;
#endif
    
    // MAXIMIZERS TURN (BLACK)
    if (turn.isBlack){
        if (move_count == 1 && p_win){
            Stack.pop() ;
            p_win = false ;
            return MAX-1 ;
        }
        
        Move m;
        int BestVal=MIN;
        
        while (move_count!=0){
            // Make a Move
            m = Stack.top();
            board[m.row[0]] [m.col[0]] = 'B' ;
            board[m.row[1]] [m.col[1]] = 'B' ;
            
#if (OPTIMISATION==2)
            r_max = min(max(max(m.row[0]+TRUNC_INCR,m.row[1]+TRUNC_INCR), r_max),18);
            r_min = max(min(min(m.row[0]-TRUNC_INCR,m.row[1]-TRUNC_INCR), r_min),0);
            c_max = min(max(max(m.col[0]+TRUNC_INCR, m.col[1]+TRUNC_INCR), c_max),18);
            c_min = max(min(min(m.col[0]-TRUNC_INCR, m.col[1]-TRUNC_INCR), c_min),0);
#endif
            
            BestVal = max(BestVal, AlphaBeta(board, depth-1, alpha, beta, white));
            
#if (OPTIMISATION==2)
            r_max = r_max_prev;
            r_min = r_min_prev;
            c_max = c_max_prev;
            c_min = c_min_prev;
#endif
            
            // Undo the moves
            board[m.row[0]] [m.col[0]] = '_' ;
            board[m.row[1]] [m.col[1]] = '_' ;
            
            alpha = max(alpha,BestVal);
            if (alpha >= beta) {
                MTStack(move_count) ;
                break ;
            }
            Stack.pop() ;
            move_count--;
        }
        return BestVal;
    }
    
    // If this minimizer's move
    else{
        if (move_count == 1 && p_win){
            Stack.pop() ;
            p_win = false ;
            return MIN+1 ;
        }
        
        Move m ;
        int BestVal= MAX;
        
        while (move_count!=0){
            // Make a Move
            m = Stack.top();
            board[m.row[0]] [m.col[0]] = 'W' ;
            board[m.row[1]] [m.col[1]] = 'W' ;
            
#if (OPTIMISATION==2)
            r_max = min(max(max(m.row[0]+TRUNC_INCR,m.row[1]+TRUNC_INCR), r_max),18);
            r_min = max(min(min(m.row[0]-TRUNC_INCR,m.row[1]-TRUNC_INCR), r_min),0);
            c_max = min(max(max(m.col[0]+TRUNC_INCR, m.col[1]+TRUNC_INCR), c_max),18);
            c_min = max(min(min(m.col[0]-TRUNC_INCR, m.col[1]-TRUNC_INCR), c_min),0);
#endif
            
            BestVal = min(BestVal, AlphaBeta(board, depth-1, alpha, beta, black));
            
#if (OPTIMISATION==2)
            r_max = r_max_prev;
            r_min = r_min_prev;
            c_max = c_max_prev;
            c_min = c_min_prev;
#endif
            
            // Undo the moves
            board[m.row[0]] [m.col[0]] = '_' ;
            board[m.row[1]] [m.col[1]] = '_' ;
            
            beta=min(beta, BestVal);
            if (alpha >= beta){
                MTStack(move_count) ;
                break ;
            }
            Stack.pop() ;
            move_count--;
        }
        return BestVal;
    }
}

#endif /* AlphaBeta_h */
