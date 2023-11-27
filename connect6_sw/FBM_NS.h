//
//  FBM_NS.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 07/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef FBM_NS_h
#define FBM_NS_h

Move findBestMove(char board[19][19], player turn){
    
    // Depth of the TREE
    int depth = DEPTH ;
    
    // Fill Stack with max. of LIMIT no. of Moves and returns the no. of Moves
    unsigned long move_count = move_selector(board, turn);

    Move bestMove ;
    
    if (move_count == 1){
        bestMove = Stack.top() ;
        Stack.pop() ;
        return bestMove;
    }
    
    if (move_count == 0){
        gameover = true ;
        return bestMove;
    }
    
    int alpha = MIN;
    int beta  = MAX;
    Move m;
    int moveVal;
    player Nxturn = (turn.isBlack) ? white : black ;
    
#if (OPTIMISATION==2)
    int r_max_prev = r_max;
    int r_min_prev = r_min;
    int c_max_prev = c_max;
    int c_min_prev = c_min;
#endif
    
#if (NO==1)
    MV mov_val[move_count] ;
    move_ordering(board, mov_val, move_count, turn) ;
#endif

    while (move_count!=0){
        // Make a Move
        m =  Stack.top() ;
        board[m.row[0]] [m.col[0]] = turn.p ;
        board[m.row[1]] [m.col[1]] = turn.p ;
        
#if(TS==3 || TS==4)
        key ^=  ZobristTable[m.row[0]][m.col[0]][turn.isBlack];
        key ^=  ZobristTable[m.row[1]][m.col[1]][turn.isBlack];
#endif
        
#if (OPTIMISATION==2)
        r_max = min(max(max(m.row[0]+TRUNC_INCR,m.row[1]+TRUNC_INCR), r_max),18);
        r_min = max(min(min(m.row[0]-TRUNC_INCR,m.row[1]-TRUNC_INCR), r_min),0);
        c_max = min(max(max(m.col[0]+TRUNC_INCR, m.col[1]+TRUNC_INCR), c_max),18);
        c_min = max(min(min(m.col[0]-TRUNC_INCR, m.col[1]-TRUNC_INCR), c_min),0);
#endif
        
#if (TS==4)
        moveVal = -NegaScout(board, depth-1, -beta, -alpha, Nxturn);
        if (moveVal>alpha && beta!=MAX) moveVal = -NegaScout(board, depth-1, -MAX, -moveVal, Nxturn);
#elif (TS==3)
        moveVal = -NegaMaxWithMemory(board, depth-1, -beta, -alpha, Nxturn);
#elif (TS==2)
        moveVal = -NegaMax(board, depth-1, -beta, -alpha, Nxturn);
#endif
        
        // Undo the moves
        board[m.row[0]] [m.col[0]] = '_' ;
        board[m.row[1]] [m.col[1]] = '_' ;
 
#if(TS==3 || TS==4)
        key ^=  ZobristTable[m.row[0]][m.col[0]][turn.isBlack];
        key ^=  ZobristTable[m.row[1]][m.col[1]][turn.isBlack];
#endif
        
#if (OPTIMISATION==2)
        r_max = r_max_prev;
        r_min = r_min_prev;
        c_max = c_max_prev;
        c_min = c_min_prev;
#endif
        
        // Value of the current move if greater than the best value, then update best
        if (moveVal > alpha) bestMove = m ;
        alpha = max(alpha, moveVal) ;
        
#if(TS==4)
        beta = alpha+1;
#endif
        
        Stack.pop() ;
        move_count--;
    }
    
    return bestMove;
}

#endif /* FBM_NS_h */
