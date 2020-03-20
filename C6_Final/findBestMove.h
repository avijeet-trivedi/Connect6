//
//  findBestMove.h
//  C6_Final
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef findBestMove_h
#define findBestMove_h

Move findBestMove(uchar board[19][19], bool turn){
    
    // Depth of the TREE = DEPTH + 1
    u16 depth = DEPTH ;
    
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
    
    // MAXIMIZERS TURN (BLACK)
    if(turn){
        
#if (OPTIMISATION==2)
        u16 r_max_prev = r_max;
        u16 r_min_prev = r_min;
        u16 c_max_prev = c_max;
        u16 c_min_prev = c_min;
#endif
        
#if (NO==1)
        MV mov_val[move_count] ;
        
        for (int i=0 ; i<move_count ; i++){
            m =  Stack.top() ;
            board[m.row[0]] [m.col[0]] = 'B' ;
            board[m.row[1]] [m.col[1]] = 'B' ;
            mov_val[i].m = m;
            mov_val[i].Val = evaluate(board);
            board[m.row[0]] [m.col[0]] = '_' ;
            board[m.row[1]] [m.col[1]] = '_' ;
            Stack.pop() ;
        }
        
        sort(mov_val, mov_val+move_count, Compare_Value_B);
        
        for (int i=0 ; i<move_count ; i++){
            Stack.push(mov_val[i].m) ;
        }
#endif
        
        while (move_count!=0){
            // Make a Move
            m =  Stack.top() ;
            board[m.row[0]] [m.col[0]] = 'B' ;
            board[m.row[1]] [m.col[1]] = 'B' ;
            
#if (TT==1)
            key ^=  ZobristTable[m.row[0]][m.col[0]][0];
            key ^=  ZobristTable[m.row[1]][m.col[1]][0];
#endif
            
#if (OPTIMISATION==2)
            r_max = min(max(max(m.row[0]+2,m.row[1]+2), r_max),18);
            r_min = max(min(min(m.row[0]-2,m.row[1]-2), r_min),0);
            c_max = min(max(max(m.col[0]+2, m.col[1]+2), c_max),18);
            c_min = max(min(min(m.col[0]-2, m.col[1]-2), c_min),0);
#endif
            
#if (TT==1)
            int moveVal = AlphaBetaWithMemory(board, depth, alpha, beta, !turn);
#else
            int moveVal = AlphaBeta(board, depth, alpha, beta, !turn);
#endif
            
            // Undo the moves
            board[m.row[0]] [m.col[0]] = '_' ;
            board[m.row[1]] [m.col[1]] = '_' ;
            
#if (TT==1)
            key ^=  ZobristTable[m.row[0]][m.col[0]][0];
            key ^=  ZobristTable[m.row[1]][m.col[1]][0];
#endif
            
#if (OPTIMISATION==2)
            r_max = r_max_prev;
            r_min = r_min_prev;
            c_max = c_max_prev;
            c_min = c_min_prev;
#endif
            
            // Value of the current move if greater than the best value, then update best
            if (moveVal > alpha) bestMove = m;
            alpha = max(alpha, moveVal) ;
            
            Stack.pop() ;
            move_count--;
        }
    }
    
    // MINIMIZER TURN (WHITE)
    else{
        
#if (OPTIMISATION==2)
        u16 r_max_prev = r_max;
        u16 r_min_prev = r_min;
        u16 c_max_prev = c_max;
        u16 c_min_prev = c_min;
#endif
        
#if (NO==1)
        MV mov_val[move_count] ;
        
        for (int i=0 ; i<move_count ; i++){
            m =  Stack.top() ;
            board[m.row[0]] [m.col[0]] = 'W' ;
            board[m.row[1]] [m.col[1]] = 'W' ;
            mov_val[i].m = m;
            mov_val[i].Val = evaluate(board);
            board[m.row[0]] [m.col[0]] = '_' ;
            board[m.row[1]] [m.col[1]] = '_' ;
            Stack.pop() ;
        }
        
        sort(mov_val, mov_val+move_count, Compare_Value_W);
        
        for (int i=0 ; i<move_count ; i++){
            Stack.push(mov_val[i].m) ;
        }
#endif
        
        while (move_count!=0){
            // Make a Move
            m = Stack.top() ;
            board[m.row[0]] [m.col[0]] = 'W' ;
            board[m.row[1]] [m.col[1]] = 'W' ;
            //print_board(board);
#if (TT==1)
            key ^=  ZobristTable[m.row[0]][m.col[0]][1];
            key ^=  ZobristTable[m.row[1]][m.col[1]][1];
#endif
            
#if (OPTIMISATION==2)
            r_max = min(max(max(m.row[0]+2,m.row[1]+2), r_max),18);
            r_min = max(min(min(m.row[0]-2,m.row[1]-2), r_min),0);
            c_max = min(max(max(m.col[0]+2, m.col[1]+2), c_max),18);
            c_min = max(min(min(m.col[0]-2, m.col[1]-2), c_min),0);
#endif
            
#if (TT==1)
            int moveVal = AlphaBetaWithMemory(board, depth, alpha, beta, !turn);
#else
            int moveVal = AlphaBeta(board, depth, alpha, beta, !turn);
#endif
            
            // Undo the moves
            board[m.row[0]] [m.col[0]] = '_' ;
            board[m.row[1]] [m.col[1]] = '_' ;
            
#if (TT==1)
            key ^=  ZobristTable[m.row[0]][m.col[0]][1];
            key ^=  ZobristTable[m.row[1]][m.col[1]][1];
#endif
            
#if (OPTIMISATION==2)
            r_max = r_max_prev;
            r_min = r_min_prev;
            c_max = c_max_prev;
            c_min = c_min_prev;
#endif
            
            // Value of the current move if greater than the best value, then update best
            if (moveVal < beta) bestMove = m;
            beta = min(beta, moveVal) ;
            
            Stack.pop() ;
            move_count--;
        }
    }
    return bestMove;
}


#endif /* findBestMove_h */
