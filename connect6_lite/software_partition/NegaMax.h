//
//  NegaMax.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 07/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef NegaMax_h
#define NegaMax_h

int NegaMax(char board[19][19], int depth, int alpha, int beta, player turn){
   
    Node_count++ ;
    
    if(depth==0){
      leaf_nodes++;
      return evaluate(board, turn);
    }
    
    // Fill Stack with max. of LIMIT no. of Moves and returns the no. of Moves
    unsigned long move_count = move_selector(board, turn);
    
    // Return zero if there is a tie
    if (move_count == 0 ) return 0;
    
    if (move_count == 1 && p_win){
        Stack.pop() ;
        p_win = false ;
        return MAX-1 ;
    }
    
    Move m;
    int BestVal = MIN;
    player Nxturn = (turn.isBlack) ? white : black ;
    
#if (OPTIMISATION==2)
    int r_max_prev = r_max;
    int r_min_prev = r_min;
    int c_max_prev = c_max;
    int c_min_prev = c_min;
#endif
    
#if (NO==1)
    if(depth>=NO_MAX_DEPTH && move_count>NO_MAX_MOV){
        MV mov_val[NO_MAX_MOV] ;
        move_ordering(board, mov_val, NO_MAX_MOV, turn) ;
    }
#endif
    
    while (move_count!=0){
        // Make a Move
        m = Stack.top();
        board[m.row[0]] [m.col[0]] = turn.p ;
        board[m.row[1]] [m.col[1]] = turn.p ;
        
#if (OPTIMISATION==2)
        r_max = min(max(max(m.row[0]+TRUNC_INCR,m.row[1]+TRUNC_INCR), r_max),18);
        r_min = max(min(min(m.row[0]-TRUNC_INCR,m.row[1]-TRUNC_INCR), r_min),0);
        c_max = min(max(max(m.col[0]+TRUNC_INCR, m.col[1]+TRUNC_INCR), c_max),18);
        c_min = max(min(min(m.col[0]-TRUNC_INCR, m.col[1]-TRUNC_INCR), c_min),0);
#endif
        
        BestVal = max(BestVal, -NegaMax(board, depth-1, -beta, -alpha, Nxturn));
        
#if (OPTIMISATION==2)
        r_max = r_max_prev;
        r_min = r_min_prev;
        c_max = c_max_prev;
        c_min = c_min_prev;
#endif
        
        // Undo the moves
        board[m.row[0]] [m.col[0]] = '_' ;
        board[m.row[1]] [m.col[1]] = '_' ;
        
        alpha = max(alpha, BestVal);
        if (alpha >= beta) {
            MTStack(move_count) ;
            break ;
        }
        Stack.pop() ;
        move_count--;
    }
    return BestVal;
}

#endif /* NegaMax_h */
