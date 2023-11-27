//
//  NegaMaxWithMemory.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 07/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef NegaMaxWithMemory_h
#define NegaMaxWithMemory_h

int NegaMaxWithMemory(char board[19][19], int depth, int alpha, int beta, player turn){
    
    // Lookup Node in Transpostion Table
    if (depth==0){
        itr0 = tt0.find(key);
        if(itr0!=tt0.end()){
            hit0++;
            return itr0->second ;
        }
        else {
            Node_count++ ;
            leaf_nodes++;
            int BestVal = evaluate(board, turn);
            tt0[key] = BestVal;
            return BestVal;
        }
    }
    
    if (depth <= DEPTH-3){
        itr1 = tt1.find(key);
        if(itr1 !=tt1.end()){
            if (itr1->second.flag == 'E'){
                hit1++;
                return itr1->second.value ;
            }
            else if (itr1->second.flag == 'L'){
                alpha = max(alpha, itr1->second.value);
            }
            else /*if (itr1->second.flag == 'U')*/{ 
                beta = min(beta, itr1->second.value);
            }
            if (alpha>=beta){
                hit1++ ;
                return itr1->second.value ;
            }
        }
    }
    
    Node_count++ ;
    
    // Fill Stack with max. of LIMIT no. of Moves and returns the no. of Moves
    unsigned long move_count = move_selector(board, turn);
    
    // Return zero if there is a tie
    if (move_count == 0 ) return 0;
    
    if (move_count == 1 && p_win){
        Stack.pop() ;
        p_win = false ;
        return MAX-1 ;
    }
    
    
#if (OPTIMISATION==2)
    int r_max_prev = r_max;
    int r_min_prev = r_min;
    int c_max_prev = c_max;
    int c_min_prev = c_min;
#endif

#if (NO==1)
    if(depth>=NO_MAX_DEPTH){
        int len = min(NO_MAX_MOV,(int)move_count);
        MV mov_val[len] ;
        move_ordering(board, mov_val, len, turn) ;
    }
#endif

    Move m;
    player Nxturn = (turn.isBlack) ? white : black ;
    int BestVal = MIN;
    int a = alpha ;
    
    while (move_count!=0){
        // Make a Move
        m = Stack.top();
        board[m.row[0]] [m.col[0]] = turn.p ;
        board[m.row[1]] [m.col[1]] = turn.p ;
        
        key ^=  ZobristTable[m.row[0]][m.col[0]][turn.isBlack];
        key ^=  ZobristTable[m.row[1]][m.col[1]][turn.isBlack];
        
#if (OPTIMISATION==2)
        r_max = min(max(max(m.row[0]+TRUNC_INCR,m.row[1]+TRUNC_INCR), r_max),18);
        r_min = max(min(min(m.row[0]-TRUNC_INCR,m.row[1]-TRUNC_INCR), r_min),0);
        c_max = min(max(max(m.col[0]+TRUNC_INCR, m.col[1]+TRUNC_INCR), c_max),18);
        c_min = max(min(min(m.col[0]-TRUNC_INCR, m.col[1]-TRUNC_INCR), c_min),0);
#endif
        
        BestVal = max(BestVal, -NegaMaxWithMemory(board, depth-1, -beta, -a, Nxturn));
        
#if (OPTIMISATION==2)
        r_max = r_max_prev;
        r_min = r_min_prev;
        c_max = c_max_prev;
        c_min = c_min_prev;
#endif
        
        // Undo the moves
        board[m.row[0]] [m.col[0]] = '_' ;
        board[m.row[1]] [m.col[1]] = '_' ;
        
        key ^=  ZobristTable[m.row[0]][m.col[0]][turn.isBlack];
        key ^=  ZobristTable[m.row[1]][m.col[1]][turn.isBlack];
        
        a = max(a, BestVal);
        if (a >= beta) {
            MTStack(move_count) ;
            break ;
        }
        Stack.pop() ;
        move_count--;
    }
    
    // Store Node in Transpostion Table
    if (depth <= DEPTH-3){
        tt1[key].value = BestVal ;
        if (BestVal <= alpha) tt1[key].flag = 'U' ;
        else if (BestVal >= beta) tt1[key].flag = 'L' ;
        else tt1[key].flag = 'E' ;
    }
    
    return BestVal;
}

#endif /* NegaMaxWithMemory_h */
