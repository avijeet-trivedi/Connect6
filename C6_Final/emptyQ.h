//
//  emptyQ.h
//  C6_Final
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef emptyQ_h
#define emptyQ_h

inline void emptyQ () {
    while(!t4_b.empty()){
        t4_b.pop() ;
    }
    
    while(!t3_b.empty()){
        t3_b.pop() ;
    }
    
    while(!t2_b.empty()){
        t2_b.pop() ;
    }
    
    while(!t1_b.empty()){
        t1_b.pop() ;
    }
    
    while(!t4_w.empty()){
        t4_w.pop() ;
    }
    
    while(!t3_w.empty()){
        t3_w.pop() ;
    }
    
    while(!t2_w.empty()){
        t2_w.pop() ;
    }
    while(!t1_w.empty()){
        t1_w.pop() ;
    }
}

#endif /* emptyQ_h */
