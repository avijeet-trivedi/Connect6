//
//  MTStack.h
//  C6_Final
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef MTStack_h
#define MTStack_h

inline void MTStack(unsigned long move_count) {
    while(move_count!=0){
        Stack.pop() ;
        move_count--;
    }
}

#endif /* MTStack_h */
