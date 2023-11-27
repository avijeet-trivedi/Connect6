//
//  emptyQ.h
//  C6 NegaScout
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef emptyQ_h
#define emptyQ_h

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

#endif /* emptyQ_h */
