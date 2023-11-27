//
//  move_selector.h
//  C6 Code
//
//  Created by Avijeet Trivedi on 07/04/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef MoveSelector_h
#define MoveSelector_h

inline unsigned long move_selector(char board[19][19], player turn){
    
    stack <Move> local ;
    Move m ;
    queue <int> temp;
    unsigned long size ;
    
    threat_finder(board, turn);     // Finding threat positions and Filling the corresponding FIFOs
    
    //WIN IF POSSIBLE
    if (t4_p.size()>=2){
        m.row[0] = t4_p.front()/19 ;
        m.col[0] = t4_p.front()%19 ;
        t4_p.pop() ;
        m.row[1] = t4_p.front()/19 ;
        m.col[1] = t4_p.front()%19 ;
        Stack.push(m) ;
        p_win = true ;
        emptyQ() ;
        return 1 ;
    }
    
    //DEFENDING REAL THREATS t4
    else if (t4_o.size()>=2){
        m.row[0] = t4_o.front()/19 ;
        m.col[0] = t4_o.front()%19 ;
        t4_o.pop();
        m.row[1] = t4_o.front()/19 ;
        m.col[1] = t4_o.front()%19 ;
        Stack.push(m) ;
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
        
        while((!temp_t3_p.empty()) && local.size()<LIMIT){
            m.row[1] = temp_t3_p.front()/19 ;
            m.col[1] = temp_t3_p.front()%19 ;
            temp_t3_p.pop() ;
            local.push(m) ;
        }
        while((!temp_t3_o.empty()) && local.size()<LIMIT){
            m.row[1] = temp_t3_o.front()/19 ;
            m.col[1] = temp_t3_o.front()%19 ;
            temp_t3_o.pop() ;
            local.push(m) ;
        }
        while((!temp_t2_p.empty()) && local.size()<LIMIT){
            m.row[1] = temp_t2_p.front()/19 ;
            m.col[1] = temp_t2_p.front()%19 ;
            temp_t2_p.pop() ;
            local.push(m) ;
        }
        while((!temp_t2_o.empty()) && local.size()<LIMIT){
            m.row[1] = temp_t2_o.front()/19 ;
            m.col[1] = temp_t2_o.front()%19 ;
            temp_t2_o.pop() ;
            local.push(m) ;
        }
        
        if(local.empty()){
            queue <int> temp_t1_p = t1_p ;
            queue <int> temp_t1_o = t1_o ;
            while((!temp_t1_p.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t1_p.front()/19 ;
                m.col[1] = temp_t1_p.front()%19 ;
                temp_t1_p.pop() ;
                local.push(m) ;
            }
            while((!temp_t1_o.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t1_o.front()/19 ;
                m.col[1] = temp_t1_o.front()%19 ;
                temp_t1_o.pop() ;
                local.push(m) ;
            }
        }
        
        size = local.size() ;
        local2stack(local) ;
        emptyQ() ;
        return size ;
    }
    
    if(t3_p.size()>=2 && local.size()<LIMIT){
        temp = t3_p ;
        while(temp.size()>=2 && local.size()<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && local.size()<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                local.push(m) ;
                cnt--;
            }
        }
    }
    
    if(t2_p.size()>=2 && local.size()<LIMIT){
        temp = t2_p ;
        while(temp.size()>=2 && local.size()<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            m.row[1] = temp.front()/19 ;
            m.col[1] = temp.front()%19 ;
            temp.pop() ;
            local.push(m) ;
        }
    }
    
    if(t3_p.size()!=0 && t3_o.size()!=0 && local.size()<LIMIT){
        queue <int> temp2;
        temp = t3_p ;
        while(temp.size()>0 && local.size()<LIMIT){
            temp2 = t3_o ;
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            while(temp2.size()>0 && local.size()<LIMIT){
                m.row[1] = temp2.front()/19 ;
                m.col[1] = temp2.front()%19 ;
                temp2.pop() ;
                local.push(m) ;
            }
        }
    }
    
    if(t3_o.size()>=2 && local.size()<LIMIT){
        temp = t3_o ;
        while(temp.size()>=2 && local.size()<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && local.size()<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                local.push(m) ;
                cnt--;
            }
        }
    }
    
    if(t2_p.size()!=0 && t2_o.size()!=0 && local.size()<LIMIT){
        queue <int> temp2;
        temp = t2_p ;
        while(temp.size()>0 && local.size()<LIMIT){
            temp2 = t2_o ;
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            while(temp2.size()>0 && local.size()<LIMIT){
                m.row[1] = temp2.front()/19 ;
                m.col[1] = temp2.front()%19 ;
                temp2.pop() ;
                local.push(m) ;
            }
        }
    }
    
    if(t2_o.size()>=2 && local.size()<LIMIT){
        temp = t2_o ;
        while(temp.size()>=2 && local.size()<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && local.size()<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                local.push(m) ;
                cnt--;
            }
        }
        
    }
    
    if(t1_p.size()>=2 && local.size()<LIMIT){
        temp = t1_p ;
        while(temp.size()>=2 && local.size()<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && local.size()<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                local.push(m) ;
                cnt--;
            }
        }
    }
    
    if(t1_o.size()>=2 && local.size()<LIMIT){
        temp = t1_o ;
        while(temp.size()>=2 && local.size()<LIMIT){
            m.row[0] = temp.front()/19 ;
            m.col[0] = temp.front()%19 ;
            temp.pop() ;
            unsigned long cnt = temp.size() ;
            while(cnt>0 && local.size()<LIMIT){
                m.row[1] = temp.front()/19 ;
                m.col[1] = temp.front()%19 ;
                temp.push(temp.front()) ;
                temp.pop() ;
                local.push(m) ;
                cnt--;
            }
        }
    }
    
    if(t1_p.size()==1 && t1_o.size()==1 && local.size()<LIMIT){
        m.row[0] = t1_p.front()/19 ;
        m.col[0] = t1_p.front()%19 ;
        m.row[1] = t1_o.front()/19 ;
        m.col[1] = t1_o.front()%19 ;
        local.push(m) ;
    }
    
    if(local.empty()){
        empty_places(board);
        if (t3_p.size()==1){
            m.row[0] = t3_p.front()/19 ;
            m.col[0] = t3_p.front()%19 ;
            while(!empty_queue.empty() && local.size()<LIMIT){
                m.row[1] = empty_queue.front()/19 ;
                m.col[1] = empty_queue.front()%19 ;
                local.push(m) ;
                empty_queue.pop() ;
            }
        }
        
        else if (t3_o.size()==1){
            m.row[0] = t3_o.front()/19 ;
            m.col[0] = t3_o.front()%19 ;
            while(!empty_queue.empty() && local.size()<LIMIT){
                m.row[1] = empty_queue.front()/19 ;
                m.col[1] = empty_queue.front()%19 ;
                local.push(m) ;
                empty_queue.pop() ;
            }
        }
        
        else if (t2_p.size()==1){
            m.row[0] = t2_p.front()/19 ;
            m.col[0] = t2_p.front()%19 ;
            while(!empty_queue.empty() && local.size()<LIMIT){
                m.row[1] = empty_queue.front()/19 ;
                m.col[1] = empty_queue.front()%19 ;
                local.push(m) ;
                empty_queue.pop() ;
            }
        }
        
        else if (t2_o.size()==1){
            m.row[0] = t2_o.front()/19 ;
            m.col[0] = t2_o.front()%19 ;
            while(!empty_queue.empty() && local.size()<LIMIT){
                m.row[1] = empty_queue.front()/19 ;
                m.col[1] = empty_queue.front()%19 ;
                local.push(m) ;
                empty_queue.pop() ;
            }
        }
        
        else if (t1_p.size()==1){
            m.row[0] = t1_p.front()/19 ;
            m.col[0] = t1_p.front()%19 ;
            while(!empty_queue.empty() && local.size()<LIMIT){
                m.row[1] = empty_queue.front()/19 ;
                m.col[1] = empty_queue.front()%19 ;
                local.push(m) ;
                empty_queue.pop() ;
            }
        }
        else if (t1_o.size()==1){
            m.row[0] = t1_o.front()/19 ;
            m.col[0] = t1_o.front()%19 ;
            while(!empty_queue.empty() && local.size()<LIMIT){
                m.row[1] = empty_queue.front()/19 ;
                m.col[1] = empty_queue.front()%19 ;
                local.push(m) ;
                empty_queue.pop() ;
            }
        }
        else{
            while(empty_queue.size()>=2 && local.size()<LIMIT){
                m.row[0] = empty_queue.front()/19 ;
                m.col[0] = empty_queue.front()%19 ;
                empty_queue.pop() ;
                unsigned long cnt = empty_queue.size() ;
                while(cnt>0 && local.size()<LIMIT){
                    m.row[1] = empty_queue.front()/19 ;
                    m.col[1] = empty_queue.front()%19 ;
                    empty_queue.push(empty_queue.front()) ;
                    empty_queue.pop() ;
                    local.push(m) ;
                    cnt--;
                }
            }
        }
        while(!empty_queue.empty()){
            empty_queue.pop() ;
        }
    }
    
    size = local.size() ;
    local2stack(local) ;
    emptyQ() ;
    return size ;
    
}

#endif /* MoveSelector_h */
