//
//  showstack.h
//  C6 NegaScout
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef showstack_h
#define showstack_h

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


#endif /* showstack_h */
