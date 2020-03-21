/*****************************************************************************************
 main.cpp
 Connect6_Final
 For development of Novel Hardware/Software Co-Design for Connect6 Game-Solver
 Created by Avijeet Trivedi
 Copyright © 2020 Avijeet Trivedi. All rights reserved.
******************************************************************************************/

/*****************************************************************************************
 This file is an integration of Connect6_2020, TA_Optimisation, Dynamic_board_optimisation,
 TA_Optimisation4 & C6_TranspostionTable
 
 Following Techniques are used in this Game Solver :
    1. Alpha-Beta with Memory using Transpositon Table and Zobrist Hashing
    2. Node Ordering
    3. Use of relevant board selection in thread_finder function
    4. A more exhaustive (covering all the corner cases) move_selector function
******************************************************************************************/

#define LIMIT 200
#define DEPTH 3
#define W4 180
#define W3 80
#define W2 49

#define TRUNC_BOARD 0
/******************************************************************************************
 TRUNC_BOARD can take value from 0 to 6
 Maximum Row Number = 18-TRUNC_BOARD;
 Minimum Row Number = TRUNC_BOARD;
 Maximum Column Number = 18-TRUNC_BOARD;
 Minimum Column Number = TRUNC_BOARD;
********************************************************************************************/

#define TT 1
/*******************************************************************************************
 For this program, Transposition Table is applied only at depth 0 and 1
 TT = 0 : Transposition Table disabled
 TT = 1 : Transposition Table enabled
********************************************************************************************/

#define OPTIMISATION 0
/******************************************************************************************
 OPTIMISATION = 0 : Threat finder evaluates the complete board
 OPTIMISATION = 1 : Threat finder evaluates a dynamic board which is updated at every move
 OPTIMISATION = 2 : Threat finder evaluates a dynamic board which is updated at every node
*******************************************************************************************/


#define NO 1
#define NO_MAX_DEPTH 2
#define NO_MAX_MOV 3
/******************************************************************************************
 NO --> Node Ordering
 NO = 1 : Enables Node Ordering
 NO = 0 : Disables Node Ordering
 
 NO_MAX_DEPTH --> Minimum Distance from the leaf node at which Node Ordering is done
 NO_MAX_MOV --> Max number of nodes on which node ordering is performed
 
 Note : For the top most node, all the nodes are ordered
 *******************************************************************************************/

#include "var_declarations.h"
#include "print_board.h"
#include "evaluate.h"
#include "threat_finder.h"
//#include "showstack.h"
#include "local2stack.h"
#include "emptyQ.h"
#include "move_selector.h"
#include "MTStack.h"

#if(NO==1)
#include "NodeOrdering.h"
#endif

#if(TT==1)
#include "transposition_table.h"
#include "AlphaBetaWithMemory.h"
#else
#include "AlphaBeta.h"
#endif

#include "findBestMove.h"

int main(){
    auto start = high_resolution_clock::now();
    
    cout<<"Let's play Connect6"<<endl ;
    
#if (OPTIMISATION==1 || OPTIMISATION==2)
    // DEFINING INITIAL RELEVANT ZONE
    u16 x = TRUNC_BOARD;
    r_max = 18-x;
    r_min = x;
    c_max = 18-x;
    c_min = x;
#endif

    // FIRST BLACK DISK PLACED AT THE CENTER OF THE BOARD
    uchar board[19][19] =
    {  //  0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //0
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //1
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //2
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //3
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //4
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //5
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //6
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //7
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //8
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', 'B', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //9
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //10
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //11
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //12
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //13
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //14
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //15
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //16
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' },  //17
        { '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_' }   //18
    };
    
#if (TT==1)
    initTable();
    key ^=  ZobristTable[9][9][0];
#endif
    
    u16 num_move = 1 ;
    bool turn = false;             // true --> BLACK'S TURN && false --> WHITE'S TURN
    
    print_board(board);
    
    Move bestMove;
    
    while(true){
        
        bestMove = findBestMove(board, turn);
        
        if(gameover){
            print_board(board);
            cout<<"No Moves Left"<<endl<<"GAMEOVER"<<endl ;
            break ;
        }
        
        num_move++ ;
        
        if(!turn){
            board[bestMove.row[0]] [bestMove.col[0]] = 'W' ;
            board[bestMove.row[1]] [bestMove.col[1]] = 'W' ;
#if (TT==1)
            key ^=  ZobristTable[bestMove.row[0]][bestMove.col[0]][1];
            key ^=  ZobristTable[bestMove.row[1]][bestMove.col[1]][1];
#endif
            cout<<"Best Move w1 => "<<"ROW: "<<bestMove.row[0]<<" COl:"<<bestMove.col[0]<<endl ;
            cout<<"Best Move w2 => "<<"ROW: "<<bestMove.row[1]<<" COl:"<<bestMove.col[1]<<endl ;
            
            if (w_win){
                print_board(board);
                cout<<"WHITE WINS"<<endl ;
                break ;
            }
        }
        
        else{
            board[bestMove.row[0]] [bestMove.col[0]] = 'B' ;
            board[bestMove.row[1]] [bestMove.col[1]] = 'B' ;
#if (TT==1)
            key ^=  ZobristTable[bestMove.row[0]][bestMove.col[0]][0];
            key ^=  ZobristTable[bestMove.row[1]][bestMove.col[1]][0];
#endif
            cout<<"Best Move b1 => "<<"ROW: "<<bestMove.row[0]<<" COl:"<<bestMove.col[0]<<endl ;
            cout<<"Best Move b2 => "<<"ROW: "<<bestMove.row[1]<<" COl:"<<bestMove.col[1]<<endl ;
            
            if (b_win){
                print_board(board);
                cout<<"BLACK WINS"<<endl ;
                break ;
            }
        }
        
#if (OPTIMISATION==1 || OPTIMISATION==2)
        //Updating the relevant zone
        r_max = min(max(max(bestMove.row[0]+2,bestMove.row[1]+2), r_max),18);
        r_min = max(min(min(bestMove.row[0]-2,bestMove.row[1]-2), r_min),0);
        c_max = min(max(max(bestMove.col[0]+2, bestMove.col[1]+2), c_max),18);
        c_min = max(min(min(bestMove.col[0]-2, bestMove.col[1]-2), c_min),0);
#endif
        
#if (TT==1)
        TT0.erase(TT0.begin(), TT0.end());
        TT1.erase(TT1.begin(), TT1.end());
#endif
        
        print_board(board);
        turn = !turn ;
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout <<endl<<"Time of Execution : "<< duration.count()/1000000<< " seconds"<<endl;
    cout <<"Evaluation Time of leaf nodes : "<<eval_time/1000000<< " seconds"<<endl;
    cout <<"Time in TA : "<<TA_time/1000000<< " seconds"<<endl<<endl;
    
    cout <<"% time in evaluation of leaf nodes : "<<(eval_time*100)/duration.count()<<" %"<<endl;
    cout <<"% time in TA : "<<(TA_time*100)/duration.count()<< " %"<<endl<<endl;

    cout<<"No. of moves made : "<<num_move<<endl;
    cout<<"No. of nodes traversed : "<<Node_count<<endl;
    cout<<"No. of leaf nodes : "<<leaf_nodes<<endl<<endl;

#if (TT==1)
    cout<<"HIT at depth 0 : "<<hit0<<endl;
    cout<<"HIT at depth 1 : "<<hit1<<endl<<endl;
#endif
    return 0;
}
