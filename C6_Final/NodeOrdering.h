//
//  NodeOrdering.h
//  C6_Final
//
//  Created by Avijeet Trivedi on 21/03/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef NodeOrdering_h
#define NodeOrdering_h

struct MV{
    Move m;
    int Val;
};

bool Compare_Value_B(MV i1, MV i2){
    return (i1.Val < i2.Val);
}

bool Compare_Value_W(MV i1, MV i2){
    return (i1.Val > i2.Val);
}

#endif /* NodeOrdering_h */
