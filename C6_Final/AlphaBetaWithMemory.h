//
//  AlphaBetaWithMemory.h
//  C6_Final
//
//  Created by Avijeet Trivedi on 21/03/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef AlphaBetaWithMemory_h
#define AlphaBetaWithMemory_h

int AlphaBetaWithMemory(uchar board[19][19], int depth, int alpha, int beta, bool turn){
    Node_count++ ;
    
    int BestVal;
    
    if (depth == 0){
        itr0 = TT0.find(key);
        if(itr0!=TT0.end()){
            hit0++;
            return itr0->second ;
        }
        else {
            BestVal = evaluate(board);
            TT0[key] = BestVal;
            return BestVal;
        }
    }
    
    if (depth==1){
        itr1 = TT1.find(key);
        if(itr1 !=TT1.end()){
            if(itr1->second.LB >= beta){
                hit1++ ;
                return itr1->second.LB ;
            }
            if(itr1->second.UB <= alpha){
                hit1++ ;
                return itr1->second.UB ;
            }
            alpha = max(alpha, itr1->second.LB);
            beta = min(beta, itr1->second.UB);
        }
    }
    
    // Fill Stack with max. of LIMIT no. of Moves and returns the no. of Moves
    unsigned long move_count = move_selector(board, turn);
    
    // Return zero if there is a tie
    if (move_count == 0 ) BestVal = 0;
    
    //MAXIMIZER'S TURN
    else if (turn){
        if (move_count == 1 && b_win){
            Stack.pop() ;
            b_win = false ;
            BestVal = MAX ;
        }
        
        else {
            BestVal = MIN ;
            int a = alpha ;
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
                
                key ^=  ZobristTable[m.row[0]][m.col[0]][0];
                key ^=  ZobristTable[m.row[1]][m.col[1]][0];
                
#if (OPTIMISATION==2)
                r_max = min(max(max(m.row[0]+2,m.row[1]+2), r_max),18);
                r_min = max(min(min(m.row[0]-2,m.row[1]-2), r_min),0);
                c_max = min(max(max(m.col[0]+2, m.col[1]+2), c_max),18);
                c_min = max(min(min(m.col[0]-2, m.col[1]-2), c_min),0);
#endif
                
                BestVal = max(AlphaBetaWithMemory(board, depth-1, a, beta, !turn), BestVal);
                
                // Undo the moves
                board[m.row[0]] [m.col[0]] = '_' ;
                board[m.row[1]] [m.col[1]] = '_' ;
                
                key ^=  ZobristTable[m.row[0]][m.col[0]][0];
                key ^=  ZobristTable[m.row[1]][m.col[1]][0];
                
#if (OPTIMISATION==2)
                r_max = r_max_prev;
                r_min = r_min_prev;
                c_max = c_max_prev;
                c_min = c_min_prev;
#endif
                
                a = max(a,BestVal) ;
                if (a >= beta) {
                    MTStack(move_count) ;
                    break ;
                }
                
                Stack.pop() ;
                move_count--;
            }
        }
    }
    
    // MINIMIZER'S TURN
    else{
        if (move_count == 1 && w_win){
            Stack.pop() ;
            w_win = false ;
            BestVal = MIN ;
        }
        
        else{
            BestVal = MAX ;
            int b = beta ;
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
                
                key ^=  ZobristTable[m.row[0]][m.col[0]][1];
                key ^=  ZobristTable[m.row[1]][m.col[1]][1];
                
#if (OPTIMISATION==2)
                r_max = min(max(max(m.row[0]+2,m.row[1]+2), r_max),18);
                r_min = max(min(min(m.row[0]-2,m.row[1]-2), r_min),0);
                c_max = min(max(max(m.col[0]+2, m.col[1]+2), c_max),18);
                c_min = max(min(min(m.col[0]-2, m.col[1]-2), c_min),0);
#endif
                
                BestVal = min(AlphaBetaWithMemory(board, depth-1, alpha, b, !turn), BestVal);
                
                // Undo the moves
                board[m.row[0]] [m.col[0]] = '_' ;
                board[m.row[1]] [m.col[1]] = '_' ;
                
                key ^=  ZobristTable[m.row[0]][m.col[0]][1];
                key ^=  ZobristTable[m.row[1]][m.col[1]][1];
                
#if (OPTIMISATION==2)
                r_max = r_max_prev;
                r_min = r_min_prev;
                c_max = c_max_prev;
                c_min = c_min_prev;
#endif
                
                b = min(b,BestVal) ;
                if (b <= alpha){
                    MTStack(move_count) ;
                    break ;
                }
                
                Stack.pop() ;
                move_count--;
            }
        }
    }
    
    if (depth == 1){
        // Found an accurate minimax value
        if (BestVal > alpha && BestVal < beta) TT1[key] = {BestVal, BestVal};
        
        // Fail high result implies a lower bound
        else if (BestVal >= beta) TT1[key].LB = BestVal;
    }
    
    return BestVal;
}

#endif /* AlphaBetaWithMemory_h */
