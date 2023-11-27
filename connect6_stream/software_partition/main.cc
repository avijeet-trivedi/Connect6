//
//  main.cpp
//  Connect 6
//
//  Created by Avijeet Kumar Trivedi on 14/03/22.
//

/****************************************************************************************
 main.cpp
 C6 Code
 For development of Novel Hardware/Software Co-Design for Connect6 Game-Solver
 Created by Avijeet Trivedi
 Copyright © 2020 Avijeet Trivedi. All rights reserved.
 ****************************************************************************************/

/*****************************************************************************************
 This file contains the both, SW and HW-SW Co-design of the Connect6 Game Solver.

 Following Techniques are used in this Game Solver :
 1. Searching Algorithm
    1. Alpha Beta
    2. Alpha Beta with Memory
    3. NegaMax
    4. NegaMax with Memory
    5. NegaScout with Memory
 2. Node Ordering
 3. Threat Based searching and evaluation
 4. A more exhaustive (covering all the corner cases) move_selector function
 5. 4 types of communication schemes between HW and SW
******************************************************************************************/

#define SDK 1
/******************************************************************************************
 SDK = 0 : Running on Xcode
 SDK = 1 : Running on VIVADO SDK (2018.3)
*******************************************************************************************/

#define LIMIT 200
#define DEPTH 2
#define W4 50
#define W3 5
#define W2 1

//MODEL3, TS0 - Reference
//TRUNCBOARD-0
//OPT 0
//

#define  MODEL 4
/******************************************************************************************
 MODEL = 0 : SW Only
 MODEL = 1 : HW_SW with Lite
 MODEL = 2 : HW_SW with Lite Upgrade
 MODEL = 3 : HW_SW with Stream
 MODEL = 4 : HW_SW with Stream Upgrade
*******************************************************************************************/

#define TS 4
/******************************************************************************************
 TS = 0 : AlphaBeta
 TS = 1 : AlphaBeta With Memory
 TS = 2 : NegaMax
 TS = 3 : NegaMax With Memory
 TS = 4 : NegaScout With Memory
 ******************************************************************************************/

#define TRUNC_BOARD 3
/******************************************************************************************
 TRUNC_BOARD can take value from 0 to 6
 Maximum Row Number = 18-TRUNC_BOARD;
 Minimum Row Number = TRUNC_BOARD;
 Maximum Column Number = 18-TRUNC_BOARD;
 Minimum Column Number = TRUNC_BOARD;
 ******************************************************************************************/
#define TRUNC_INCR 5

#define OPTIMISATION 0
/******************************************************************************************
 OPTIMISATION = 0 : Threat finder evaluates the complete board
 OPTIMISATION = 1 : Threat finder evaluates a dynamic board which is updated at every move
 OPTIMISATION = 2 : Threat finder evaluates a dynamic board which is updated at every node
 ******************************************************************************************/

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
 ******************************************************************************************/
#include <iostream>
#include <queue>
#include <stack>
#include <random>
#include <unordered_map>
#include <cmath>
#include <algorithm>
using namespace std ;

#if (SDK==0)
#include <chrono>
using namespace std::chrono;
#endif

#if (SDK==1)
#include "platform.h"
#include "xparameters.h"
#include "xtime_l.h"
XTime t_elapse ;
#endif

#include "Variables.h"
#include "Debug.h"
#include "ModelSelector.h"

int main(){

    //cout<<"Let's play Connect6"<<endl ;

#if (MODEL==3 || MODEL==4)
    initialise_dma(DMA_DEV_ID);
#endif

#if (SDK==0)
    auto start = high_resolution_clock::now();
#else
    int start, end ;
    XTime_GetTime(&t_elapse);
    start =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));
#endif

#if (OPTIMISATION==1 || OPTIMISATION==2)
    // DEFINING INITIAL RELEVANT ZONE
    int x = TRUNC_BOARD;
    r_max = 18-x;
    r_min = x;
    c_max = 18-x;
    c_min = x;
#endif

    // FIRST BLACK DISK PLACED AT THE CENTER OF THE BOARD
    char board[19][19] =
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

#if (TS==1 || TS==3 || TS==4)
    initTable();
    key ^=  ZobristTable[9][9][1];
#endif

    int num_move = 1 ;
    player turn = white;             // true --> BLACK'S TURN && false --> WHITE'S TURN

    //print_board(board);

    Move bestMove;

    while(true){

        bestMove = findBestMove(board, turn);

        if(gameover){
            //print_board(board);
            //cout<<"No Moves Left"<<endl<<"GAMEOVER"<<endl ;
            break ;
        }

        num_move++ ;

        board[bestMove.row[0]] [bestMove.col[0]] = turn.p ;
        board[bestMove.row[1]] [bestMove.col[1]] = turn.p ;

#if (TS==1 || TS==3 || TS==4)
        key ^=  ZobristTable[bestMove.row[0]][bestMove.col[0]][turn.isBlack];
        key ^=  ZobristTable[bestMove.row[1]][bestMove.col[1]][turn.isBlack];
#endif

        //cout<<"Best Move "<<turn.p<<"1 => "<<"ROW: "<<bestMove.row[0]<<" COl:"<<bestMove.col[0]<<endl ;
        //cout<<"Best Move "<<turn.p<<"2 => "<<"ROW: "<<bestMove.row[1]<<" COl:"<<bestMove.col[1]<<endl ;
        //print_board(board);

        //cout<<"board["<<bestMove.row[0]<<"]["<<bestMove.col[0]<<"]='"<<turn.p<<"';"<<endl;
        //cout<<"board["<<bestMove.row[1]<<"]["<<bestMove.col[1]<<"]='"<<turn.p<<"';"<<endl;

        if (p_win){
            //print_board(board);
            //cout<<turn.p<<" WINS"<<endl ;
            break ;
        }

#if (OPTIMISATION==1 || OPTIMISATION==2)
        //Updating the relevant zone
        r_max = min(max(max(bestMove.row[0]+TRUNC_INCR,bestMove.row[1]+TRUNC_INCR), r_max),18);
        r_min = max(min(min(bestMove.row[0]-TRUNC_INCR,bestMove.row[1]-TRUNC_INCR), r_min),0);
        c_max = min(max(max(bestMove.col[0]+TRUNC_INCR, bestMove.col[1]+TRUNC_INCR), c_max),18);
        c_min = max(min(min(bestMove.col[0]-TRUNC_INCR, bestMove.col[1]-TRUNC_INCR), c_min),0);
#endif

#if (TS==1 || TS==3 || TS==4)
        tt0.erase(tt0.begin(), tt0.end());
        tt1.erase(tt1.begin(), tt1.end());
#endif

        turn = (turn.isBlack) ? white : black ;
    }


    //cout<<"TS : "<<TS<<endl;
    //cout<<"NO : "<<NO<<endl;
    //cout<<"OPTIMISATION : "<<OPTIMISATION<<endl<<endl;

#if (SDK==0)
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout <<endl<<"Time of Execution : "<< duration.count()/1000000<< " seconds"<<endl;
    cout <<"Evaluation Time of leaf nodes : "<<eval_time/1000000<< " seconds"<<endl;
    cout <<"Time in TA : "<<TA_time/1000000<< " seconds"<<endl<<endl;

#else
    XTime_GetTime(&t_elapse);
    end =  1.0 * ((t_elapse) / (COUNTS_PER_SECOND/1000000));

    cout<<"Time of Execution : " << (end - start) << " micro-seconds"<<endl ;
    cout<<"Time taken in evaluation of leaf nodes with communication overhead : "<< eval_time << endl ;
    cout<<"Time taken in evaluation of leaf nodes without communication overhead : "<< hw_time << endl ;
#endif

    cout<<"No. of moves made : "<<num_move<<endl;
    cout<<"No. of nodes traversed : "<<Node_count<<endl;
    cout<<"No. of leaf nodes : "<<leaf_nodes<<endl<<endl;

#if (TS==1 || TS==3 || TS==4)
    cout<<"HIT at depth 0 : "<<hit0<<endl;
    cout<<"HIT at depth 1 : "<<hit1<<endl;
    cout<<"Total HITS : "<<hit0+hit1<<endl<<endl;
#endif

    return 0;
}
