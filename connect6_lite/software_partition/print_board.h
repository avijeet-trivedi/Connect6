//
//  print_board.h
//  C6 NegaScout
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef print_board_h
#define print_board_h

inline void print_board(uchar board[19][19]){
    for(int i=0 ;i<19; i++){
        if(i==0){
            cout<<"  ";
            for(int k=0;k<19;k++){
                cout<<k<<" ";
                if(k<10) cout<<" ";
            }
            cout<<endl<<endl;
        }
        cout<<i<<" ";
        for (int j=0 ; j<19; j++){
            if(j==0 && i<10) cout<<" ";
            
            cout<<board[i][j]<<"  ";
        }
        cout<<endl ;
    }
}

#endif /* print_board_h */
