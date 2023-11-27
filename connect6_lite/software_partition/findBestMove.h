//
//  findBestMove.h
//  C6 NegaScout
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef findBestMove_h
#define findBestMove_h

Move findBestMove(uchar board[19][19], player turn){
    
    // Depth of the TREE
    int depth = DEPTH ;
   
    MV moves[LIMIT] ;
    
    // Fill Stack with max. of LIMIT no. of Moves and returns the no. of Moves

    unsigned int move_count = move_selector(board, moves, turn);

    Move bestMove ;
    
    if (move_count == 1){
        //exit(3);
        bestMove = moves[0].m ;
        return bestMove;
    }
    
    if (move_count == 0){
        //exit(3);
        gameover = true ;
        return bestMove;
    }
    
    int alpha = MIN;
    int beta  = MAX;
    Move m;
    int moveVal=MIN;
    player Nxturn = (turn.isBlack) ? white : black ;
    
#if (OPTIMISATION==2)
    int r_max_prev = r_max;
    int r_min_prev = r_min;
    int c_max_prev = c_max;
    int c_min_prev = c_min;
#endif
    
//#if (NO==1)
//    move_ordering(board, moves, move_count, turn) ;
//#endif
    
    for (int i=0 ; i!=move_count ; i++){
        // Make a Move
        m =  moves[i].m ;
        board[m.row[0]] [m.col[0]] = turn.p ;
        board[m.row[1]] [m.col[1]] = turn.p ;
        
#if (TREE_SEARCH==1 || TREE_SEARCH==2)
        key ^=  ZobristTable[m.row[0]][m.col[0]][turn.isBlack];
        key ^=  ZobristTable[m.row[1]][m.col[1]][turn.isBlack];
#endif
        
#if (OPTIMISATION==2)
        r_max = min(max(max(m.row[0]+2, m.row[1]+2), r_max),18);
        r_min = max(min(min(m.row[0]-2, m.row[1]-2), r_min),0);
        c_max = min(max(max(m.col[0]+2, m.col[1]+2), c_max),18);
        c_min = max(min(min(m.col[0]-2, m.col[1]-2), c_min),0);
#endif
        
#if (TREE_SEARCH==2)
        moveVal = -NegaScout(board, depth-1, -beta, -alpha, Nxturn);
        if (moveVal>alpha && beta!=MAX) moveVal = -NegaScout(board, depth-1, -MAX, -moveVal, Nxturn);
#elif (TREE_SEARCH==1)
        moveVal = -NegaMaxWithMemory(board, depth-1, -beta, -alpha, Nxturn);
#elif (TREE_SEARCH==0)
        moveVal = -NegaMax(board, depth-1, -beta, -alpha, Nxturn);
#endif
        
#if (OPTIMISATION==2)
        r_max = r_max_prev;
        r_min = r_min_prev;
        c_max = c_max_prev;
        c_min = c_min_prev;
#endif
        
#if (TREE_SEARCH==1 || TREE_SEARCH==2)
        key ^=  ZobristTable[m.row[0]][m.col[0]][turn.isBlack];
        key ^=  ZobristTable[m.row[1]][m.col[1]][turn.isBlack];
#endif
        
        // Undo the moves
        board[m.row[0]] [m.col[0]] = '_' ;
        board[m.row[1]] [m.col[1]] = '_' ;
 
        // Value of the current move if greater than the best value, then update best
        if (moveVal > alpha) {
            bestMove = m ;
            alpha = moveVal;
        }
#if (TREE_SEARCH==2)
        beta = alpha+1;
#endif
    }
    return bestMove;
}

#endif /* findBestMove_h */
