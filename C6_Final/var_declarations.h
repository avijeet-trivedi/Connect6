//
//  var_declarations.h
//  C6_Final
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef var_declarations_h
#define var_declarations_h

#include <iostream>
#include <queue>
#include <stack>
#include <chrono>
#include <random>
#include <unordered_map>

using namespace std::chrono;
using namespace std ;

typedef int u16 ;
typedef int u32 ;
typedef char uchar ;

u16 r_max = 18, r_min = 0 ;
u16 c_max = 18, c_min = 0 ;

struct Move{
    int row[2]={-1,-1};
    int col[2]={-1,-1} ;
};

struct t_cnt{
    u16 t4 = 0;
    u16 t3 = 0;
    u16 t2 = 0;
    u16 t1 = 0;
};

queue <u16> t4_b;
queue <u16> t3_b;
queue <u16> t2_b;
queue <u16> t1_b;

queue <u16> t4_w;
queue <u16> t3_w;
queue <u16> t2_w;
queue <u16> t1_w;

queue <u16> empty;

bool turn ;

const int MIN = -65535 ;
const int MAX =  65535 ;

bool b_win = false;
bool w_win = false ;
bool gameover = false ;

stack <Move> Stack ;     // Move Storage

u32 Node_count = 0, leaf_nodes = 0 ;

int eval_time = 0, TA_time = 0 ;

#endif /* var_declarations_h */
