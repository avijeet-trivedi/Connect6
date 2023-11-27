//
//  NodeOrdering.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 06/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef NodeOrdering_h
#define NodeOrdering_h

struct MV{
    Move m;
    int Val;
};

bool Compare_Value(MV i1, MV i2){
    return (i1.Val < i2.Val);
}

inline void move_ordering(char board[19][19], MV mov_val[], unsigned long num_of_node, player turn){
    for (int i=0 ; i<num_of_node ; i++){
        board[Stack.top().row[0]] [Stack.top().col[0]] = turn.p ;
        board[Stack.top().row[1]] [Stack.top().col[1]] = turn.p ;
        mov_val[i].m = Stack.top() ;
        mov_val[i].Val = evaluate(board,turn)-i;
        board[Stack.top().row[0]] [Stack.top().col[0]] = '_' ;
        board[Stack.top().row[1]] [Stack.top().col[1]] = '_' ;
        Stack.pop() ;
    }
    
    sort(mov_val, mov_val+num_of_node, Compare_Value);
    
    for (unsigned long i=0 ; i<num_of_node ; i++) Stack.push(mov_val[i].m) ;
}
#endif /* NodeOrdering_h */
