//
//  Variables.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 06/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef Variables_h
#define Variables_h

int r_max = 18, r_min = 0 ;
int c_max = 18, c_min = 0 ;

struct Move{
    int row[2]={-1,-1};
    int col[2]={-1,-1} ;
};

struct t_cnt{
    int t4 = 0;
    int t3 = 0;
    int t2 = 0;
    int t1 = 0;
};

struct player{
    bool isBlack;
    char p;
    char o;
};

player black {true, 'B', 'W'};
player white {false, 'W', 'B'};

queue <int> t4_p;
queue <int> t3_p;
queue <int> t2_p;
queue <int> t1_p;

queue <int> t4_o;
queue <int> t3_o;
queue <int> t2_o;
queue <int> t1_o;

queue <int> empty_queue;

const int MIN = -65535 ;
const int MAX =  65535 ;

bool p_win = false;
bool gameover = false ;

stack <Move> Stack ;     // Move Storage

int Node_count = 0, leaf_nodes = 0 ;

int eval_time = 0, TA_time = 0, hw_time=0 ;

inline void local2stack(stack <Move> local){
    while(!local.empty()){
        Stack.push(local.top()) ;
        local.pop() ;
    }
}

inline void MTStack(unsigned long move_count) {
    while(move_count!=0){
        Stack.pop() ;
        move_count--;
    }
}

inline void empty_places(char board[19][19]){
    for (int i = 0; i<19; i++)
        for (int j=0; j<19; j++)
            if(board[i][j]=='_') empty_queue.push((19*i)+j) ;
}

inline void emptyQ () {
    while(!t4_p.empty()){
        t4_p.pop() ;
    }
    
    while(!t3_p.empty()){
        t3_p.pop() ;
    }
    
    while(!t2_p.empty()){
        t2_p.pop() ;
    }
    
    while(!t1_p.empty()){
        t1_p.pop() ;
    }
    
    while(!t4_o.empty()){
        t4_o.pop() ;
    }
    
    while(!t3_o.empty()){
        t3_o.pop() ;
    }
    
    while(!t2_o.empty()){
        t2_o.pop() ;
    }
    while(!t1_o.empty()){
        t1_o.pop() ;
    }
}

#endif /* Variables_h */
