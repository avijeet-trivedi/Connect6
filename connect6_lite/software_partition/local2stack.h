//
//  local2stack.h
//  C6 NegaScout
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef local2stack_h
#define local2stack_h

inline void local2stack(stack <Move> local){
    while(!local.empty()){
        Stack.push(local.top()) ;
        local.pop() ;
    }
}

#endif /* local2stack_h */
