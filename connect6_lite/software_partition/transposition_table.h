//
//  transposition_table.h
//  C6 NegaScout
//
//  Created by Avijeet Trivedi on 20/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef transposition_table_h
#define transposition_table_h

unsigned long long int ZobristTable[19][19][2];
mt19937 mt(01234567);

unsigned long long int key = 0 ;

struct ttEntry {
    int value;
    char flag;          // E = EXACT ; L = LOWERBOUND ; U = UPPERBOUND
};

unordered_map<unsigned long long int, int> tt0 ;
unordered_map<unsigned long long int, ttEntry> tt1 ;

unordered_map<unsigned long long int, int>::iterator itr0 ;
unordered_map<unsigned long long int,ttEntry>::iterator itr1 ;

unsigned long long int hit1 = 0, hit0 = 0 ;

// Generates a Random number from 0 to 2^64-1
unsigned long long int randomInt(){
    uniform_int_distribution<unsigned long long int>dist(0, UINT64_MAX);
    return dist(mt);
}

// Initializes the table
void initTable(){
    for (int i = 0; i<19; i++)
        for (int j=0; j<19; j++)
            for (int k = 0; k<2; k++)
                ZobristTable[i][j][k] = randomInt();
}

#endif /* transposition_table_h */
