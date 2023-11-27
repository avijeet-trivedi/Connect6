//
//  move_selector.h
//  C6 NegaScout
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef move_selector_h
#define move_selector_h

inline void empty_places(uchar board[19][19]){
    for (int i = 0; i<19; i++)
        for (int j=0; j<19; j++)
            if(board[i][j]=='_') empty.push((19*i)+j) ;
}

inline unsigned int move_selector(uchar board[19][19], MV moves[LIMIT], player turn){
    
    unsigned int i=0 ;
    Move m ;
    queue <int> temp;
    
    threat_finder(board, turn);     // Finding threat positions and Filling the corresponding FIFOs
    
    //WIN IF POSSIBLE
    if (t4_p.size()>=2){
        m.row[0] = t4_p.front()/19 ;
        m.col[0] = t4_p.front()%19 ;
        t4_p.pop() ;
        m.row[1] = t4_p.front()/19 ;
        m.col[1] = t4_p.front()%19 ;
        moves[i].m = m  ;
        p_win = true ;
        emptyQ() ;
        return 1;
    }
    
    //DEFENDING REAL THREATS t4
    else if (t4_o.size()>=2){
        m.row[0] = t4_o.front()/19 ;
        m.col[0] = t4_o.front()%19 ;
        t4_o.pop();
        m.row[1] = t4_o.front()/19 ;
        m.col[1] = t4_o.front()%19 ;
        moves[i].m = m ;
        emptyQ() ;
        return 1;
    }
    
    else if (t4_o.size()==1){
        m.row[0] = t4_o.front()/19 ;
        m.col[0] = t4_o.front()%19 ;
        
        queue <int> temp_t3_p = t3_p ;
        queue <int> temp_t3_o = t3_o ;
        queue <int> temp_t2_p = t2_p ;
        queue <int> temp_t2_o = t2_o ;
        
        while((!temp_t3_p.empty()) && i<LIMIT){
            m.row[1] = temp_t3_p.front()/19 ;
            m.col[1] = temp_t3_p.front()%19 ;
            temp_t3_p.pop() ;
            moves[i].m = m ; i++  ;
        }
        while((!temp_t3_o.empty()) && i<LIMIT){
            m.row[1] = temp_t3_o.front()/19 ;
            m.col[1] = temp_t3_o.front()%19 ;
            temp_t3_o.pop() ;
            moves[i].m = m ; i++  ;
        }
        while((!temp_t2_p.empty()) && i<LIMIT){
            m.row[1] = temp_t2_p.front()/19 ;
            m.col[1] = temp_t2_p.front()%19 ;
            temp_t2_p.pop() ;
            moves[i].m = m ; i++  ;
        }
        while((!temp_t2_o.empty()) && i<LIMIT){
            m.row[1] = temp_t2_o.front()/19 ;
            m.col[1] = temp_t2_o.front()%19 ;
            temp_t2_o.pop() ;
            moves[i].m = m ; i++  ;
        }
        
        if(i==0){
            queue <int> temp_t1_p = t1_p ;
            queue <int> temp_t1_o = t1_o ;
            while((!temp_t1_p.empty()) && i<LIMIT){
                m.row[1] = temp_t1_p.front()/19 ;
                m.col[1] = temp_t1_p.front()%19 ;
                temp_t1_p.pop() ;
                moves[i].m = m ; i++  ;
            }
            while((!temp_t1_o.empty()) && i<LIMIT){
                m.row[1] = temp_t1_o.front()/19 ;
                m.col[1] = temp_t1_o.front()%19 ;
                temp_t1_o.pop() ;
                moves[i].m = m ; i++  ;
            }
        }
        
        emptyQ() ;
        return i ;
    }
    
    if(t3_p.size()>=2 && i<LIMIT){
        temp = t3_p ;
        while(temp.size()>=2 && i<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && i<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                moves[i].m = m ; i++  ;
                cnt--;
            }
        }
    }
    
    if(t2_p.size()>=2 && i<LIMIT){
        temp = t2_p ;
        while(temp.size()>=2 && i<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            m.row[1] = temp.front()/19 ;
            m.col[1] = temp.front()%19 ;
            temp.pop() ;
            moves[i].m = m ; i++  ;
        }
    }
    
    if(t3_p.size()!=0 && t3_o.size()!=0 && i<LIMIT){
        queue <int> temp2;
        temp = t3_p ;
        while(temp.size()>0 && i<LIMIT){
            temp2 = t3_o ;
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            while(temp2.size()>0 && i<LIMIT){
                m.row[1] = temp2.front()/19 ;
                m.col[1] = temp2.front()%19 ;
                temp2.pop() ;
                moves[i].m = m ; i++  ;
            }
        }
    }
    
    if(t3_o.size()>=2 && i<LIMIT){
        temp = t3_o ;
        while(temp.size()>=2 && i<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && i<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                moves[i].m = m ; i++  ;
                cnt--;
            }
        }
    }
    
    if(t2_p.size()!=0 && t2_o.size()!=0 && i<LIMIT){
        queue <int> temp2;
        temp = t2_p ;
        while(temp.size()>0 && i<LIMIT){
            temp2 = t2_o ;
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            while(temp2.size()>0 && i<LIMIT){
                m.row[1] = temp2.front()/19 ;
                m.col[1] = temp2.front()%19 ;
                temp2.pop() ;
                moves[i].m = m ; i++  ;
            }
        }
    }
    
    if(t2_o.size()>=2 && i<LIMIT){
        temp = t2_o ;
        while(temp.size()>=2 && i<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && i<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                moves[i].m = m ; i++  ;
                cnt--;
            }
        }
        
    }
    
    if(t1_p.size()>=2 && i<LIMIT){
        temp = t1_p ;
        while(temp.size()>=2 && i<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && i<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                moves[i].m = m ; i++  ;
                cnt--;
            }
        }
    }
    
    if(t1_o.size()>=2 && i<LIMIT){
        temp = t1_o ;
        while(temp.size()>=2 && i<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && i<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                moves[i].m = m ; i++  ;
                cnt--;
            }
        }
    }
    
    if(t1_p.size()==1 && t1_o.size()==1 && i<LIMIT){
        m.row[0] = t1_p.front()/19 ;
        m.col[0] = t1_p.front()%19 ;
        m.row[1] = t1_o.front()/19 ;
        m.col[1] = t1_o.front()%19 ;
        moves[i].m = m ; i++  ;
    }
    
    if(i==0){
        empty_places(board);
        if (t3_p.size()==1){
            m.row[0] = t3_p.front()/19 ;
            m.col[0] = t3_p.front()%19 ;
            while(!empty.empty() && i<LIMIT){
                m.row[1] = empty.front()/19 ;
                m.col[1] = empty.front()%19 ;
                moves[i].m = m ; i++  ;
                empty.pop() ;
            }
        }
        
        else if (t3_o.size()==1){
            m.row[0] = t3_o.front()/19 ;
            m.col[0] = t3_o.front()%19 ;
            while(!empty.empty() && i<LIMIT){
                m.row[1] = empty.front()/19 ;
                m.col[1] = empty.front()%19 ;
                moves[i].m = m ; i++  ;
                empty.pop() ;
            }
        }
        
        else if (t2_p.size()==1){
            m.row[0] = t2_p.front()/19 ;
            m.col[0] = t2_p.front()%19 ;
            while(!empty.empty() && i<LIMIT){
                m.row[1] = empty.front()/19 ;
                m.col[1] = empty.front()%19 ;
                moves[i].m = m ; i++  ;
                empty.pop() ;
            }
        }
        
        else if (t2_o.size()==1){
            m.row[0] = t2_o.front()/19 ;
            m.col[0] = t2_o.front()%19 ;
            while(!empty.empty() && i<LIMIT){
                m.row[1] = empty.front()/19 ;
                m.col[1] = empty.front()%19 ;
                moves[i].m = m ; i++  ;
                empty.pop() ;
            }
        }
        
        else if (t1_p.size()==1){
            m.row[0] = t1_p.front()/19 ;
            m.col[0] = t1_p.front()%19 ;
            while(!empty.empty() && i<LIMIT){
                m.row[1] = empty.front()/19 ;
                m.col[1] = empty.front()%19 ;
                moves[i].m = m ; i++  ;
                empty.pop() ;
            }
        }
        else if (t1_o.size()==1){
            m.row[0] = t1_o.front()/19 ;
            m.col[0] = t1_o.front()%19 ;
            while(!empty.empty() && i<LIMIT){
                m.row[1] = empty.front()/19 ;
                m.col[1] = empty.front()%19 ;
                moves[i].m = m ; i++  ;
                empty.pop() ;
            }
        }
        else{
            while(empty.size()>=2 && i<LIMIT){
                m.row[0] = empty.front()/19 ;
                m.col[0] = empty.front()%19 ;
                empty.pop() ;
                unsigned long cnt = empty.size() ;
                while(cnt>0 && i<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    empty.push(empty.front()) ;
                    empty.pop() ;
                    moves[i].m = m ; i++  ;
                    cnt--;
                }
            }
        }
        while(!empty.empty()){
            empty.pop() ;
        }
    }
    
    emptyQ() ;
    return i ;
    
}

#endif /* move_selector_h */
