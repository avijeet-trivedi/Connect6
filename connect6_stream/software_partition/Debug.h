//
//  Debug.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 06/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef Debug_h
#define Debug_h

inline void print_board(char board[19][19]){
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

void showstack(stack <Move> s){
    Move m ;
    while (!s.empty())
    {
        m = s.top() ;
        cout <<"Row no.1 : "<<m.row[0]<<" Col. no.1 : "<<m.col[0]<<endl ;
        cout <<"Row no.2 : "<<m.row[1]<<" Col. no.2 : "<<m.col[1]<<endl ;
        s.pop();
    }
    cout << '\n';
}

#endif /* Debug_h */
