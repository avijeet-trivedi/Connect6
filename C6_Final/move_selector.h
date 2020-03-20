//
//  move_selector.h
//  Connect6_2020
//
//  Created by Avijeet Trivedi on 15/02/20.
//  Copyright © 2020 Avijeet Trivedi. All rights reserved.
//

#ifndef move_selector_h
#define move_selector_h

void empty_places(uchar board[19][19]){
    for (u16 i = 0; i<19; i++)
        for (u16 j=0; j<19; j++)
            if(board[i][j]=='_') empty.push((19*i)+j) ;
}

unsigned long move_selector(uchar board[19][19], bool turn){
    
    stack <Move> local ;
    Move m ;
    queue <u16> temp;
    unsigned long size ;
    
    
    threat_finder(board, turn);     // Finding threat positions and Filling the corresponding FIFOs
    
    //BLACK'S TURN
    if (turn){
        //WIN IF POSSIBLE
        if (t4_b.size()>=2){
            m.row[0] = t4_b.front()/19 ;
            m.col[0] = t4_b.front()%19 ;
            t4_b.pop() ;
            m.row[1] = t4_b.front()/19 ;
            m.col[1] = t4_b.front()%19 ;
            Stack.push(m) ;
            b_win = true ;
            emptyQ() ;
            return 1;
        }
        
        //DEFENDING REAL THREATS t4
        else if (t4_w.size()>=2){
            m.row[0] = t4_w.front()/19 ;
            m.col[0] = t4_w.front()%19 ;
            t4_w.pop();
            m.row[1] = t4_w.front()/19 ;
            m.col[1] = t4_w.front()%19 ;
            Stack.push(m) ;
            emptyQ() ;
            return 1;
        }
        
        else if (t4_w.size()==1){
            m.row[0] = t4_w.front()/19 ;
            m.col[0] = t4_w.front()%19 ;
            
            queue <u16> temp_t3_b = t3_b ;
            queue <u16> temp_t3_w = t3_w ;
            queue <u16> temp_t2_b = t2_b ;
            queue <u16> temp_t2_w = t2_w ;
            
            while((!temp_t3_b.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t3_b.front()/19 ;
                m.col[1] = temp_t3_b.front()%19 ;
                temp_t3_b.pop() ;
                local.push(m) ;
            }
            while((!temp_t3_w.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t3_w.front()/19 ;
                m.col[1] = temp_t3_w.front()%19 ;
                temp_t3_w.pop() ;
                local.push(m) ;
            }
            while((!temp_t2_b.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t2_b.front()/19 ;
                m.col[1] = temp_t2_b.front()%19 ;
                temp_t2_b.pop() ;
                local.push(m) ;
            }
            while((!temp_t2_w.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t2_w.front()/19 ;
                m.col[1] = temp_t2_w.front()%19 ;
                temp_t2_w.pop() ;
                local.push(m) ;
            }
            
            if(local.empty()){
                queue <u16> temp_t1_b = t1_b ;
                queue <u16> temp_t1_w = t1_w ;
                while((!temp_t1_b.empty()) && local.size()<LIMIT){
                    m.row[1] = temp_t1_b.front()/19 ;
                    m.col[1] = temp_t1_b.front()%19 ;
                    temp_t1_b.pop() ;
                    local.push(m) ;
                }
                while((!temp_t1_w.empty()) && local.size()<LIMIT){
                    m.row[1] = temp_t1_w.front()/19 ;
                    m.col[1] = temp_t1_w.front()%19 ;
                    temp_t1_w.pop() ;
                    local.push(m) ;
                }
            }
            
            size = local.size() ;
            local2stack(local) ;
            emptyQ() ;
            return size ;
        }
        
        if(t3_b.size()>=2 && local.size()<LIMIT){
            temp = t3_b ;
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
        
        if(t2_b.size()>=2 && local.size()<LIMIT){
            temp = t2_b ;
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
        
        if(t3_b.size()!=0 && t3_w.size()!=0 && local.size()<LIMIT){
            queue <u16> temp2;
            temp = t3_b ;
            while(temp.size()>0 && local.size()<LIMIT){
                temp2 = t3_w ;
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
        
        if(t3_w.size()>=2 && local.size()<LIMIT){
            temp = t3_w ;
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
        
        if(t2_b.size()!=0 && t2_w.size()!=0 && local.size()<LIMIT){
            queue <u16> temp2;
            temp = t2_b ;
            while(temp.size()>0 && local.size()<LIMIT){
                temp2 = t2_w ;
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
        
        if(t2_w.size()>=2 && local.size()<LIMIT){
            temp = t2_w ;
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
        
        if(t1_b.size()>=2 && local.size()<LIMIT){
            temp = t1_b ;
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
        
        if(t1_w.size()>=2 && local.size()<LIMIT){
            temp = t1_w ;
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
  
        if(t1_b.size()==1 && t1_w.size()==1 && local.size()<LIMIT){
            m.row[0] = t1_b.front()/19 ;
            m.col[0] = t1_b.front()%19 ;
            m.row[1] = t1_w.front()/19 ;
            m.col[1] = t1_w.front()%19 ;
            local.push(m) ;
        }
  
        if(local.empty()){
            empty_places(board);
            if (t3_b.size()==1){
                m.row[0] = t3_b.front()/19 ;
                m.col[0] = t3_b.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t3_w.size()==1){
                m.row[0] = t3_w.front()/19 ;
                m.col[0] = t3_w.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t2_b.size()==1){
                m.row[0] = t2_b.front()/19 ;
                m.col[0] = t2_b.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t2_w.size()==1){
                m.row[0] = t2_w.front()/19 ;
                m.col[0] = t2_w.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t1_b.size()==1){
                m.row[0] = t1_b.front()/19 ;
                m.col[0] = t1_b.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            else if (t1_w.size()==1){
                m.row[0] = t1_w.front()/19 ;
                m.col[0] = t1_w.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            else{
                while(empty.size()>=2 && local.size()<LIMIT){
                    m.row[0] = empty.front()/19 ;
                    m.col[0] = empty.front()%19 ;
                    empty.pop() ;
                    unsigned long cnt = empty.size() ;
                    while(cnt>0 && local.size()<LIMIT){
                        m.row[1] = empty.front()/19 ;
                        m.col[1] = empty.front()%19 ;
                        empty.push(empty.front()) ;
                        empty.pop() ;
                        local.push(m) ;
                        cnt--;
                    }
                }
            }
            while(!empty.empty()){
                empty.pop() ;
            }
        }
        
        size = local.size() ;
        local2stack(local) ;
        emptyQ() ;
        return size ;
    }
    
    //whites turn
    else{
        //WIN IF POSSIBLE
        if (t4_w.size()>=2){
            m.row[0] = t4_w.front()/19 ;
            m.col[0] = t4_w.front()%19 ;
            t4_w.pop() ;
            m.row[1] = t4_w.front()/19 ;
            m.col[1] = t4_w.front()%19 ;
            Stack.push(m) ;
            w_win = true ;
            emptyQ() ;
            return 1;
        }
        
        //DEFENDING REAL THREATS t4
        else if (t4_b.size()>=2){
            m.row[0] = t4_b.front()/19 ;
            m.col[0] = t4_b.front()%19 ;
            t4_b.pop();
            m.row[1] = t4_b.front()/19 ;
            m.col[1] = t4_b.front()%19 ;
            Stack.push(m) ;
            emptyQ() ;
            return 1;
        }
        
        else if (t4_b.size()==1){
            queue <u16> temp_t3_b = t3_b ;
            queue <u16> temp_t3_w = t3_w ;
            queue <u16> temp_t2_b = t2_b ;
            queue <u16> temp_t2_w = t2_w ;
            
            m.row[0] = t4_b.front()/19 ;
            m.col[0] = t4_b.front()%19 ;
            
            while((!temp_t3_w.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t3_w.front()/19 ;
                m.col[1] = temp_t3_w.front()%19 ;
                temp_t3_w.pop() ;
                local.push(m) ;
            }
            
            while((!temp_t3_b.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t3_b.front()/19 ;
                m.col[1] = temp_t3_b.front()%19 ;
                temp_t3_b.pop() ;
                local.push(m) ;
            }
            while((!temp_t2_w.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t2_w.front()/19 ;
                m.col[1] = temp_t2_w.front()%19 ;
                temp_t2_w.pop() ;
                local.push(m) ;
            }
            while((!temp_t2_b.empty()) && local.size()<LIMIT){
                m.row[1] = temp_t2_b.front()/19 ;
                m.col[1] = temp_t2_b.front()%19 ;
                temp_t2_b.pop() ;
                local.push(m) ;
            }
            
            if(local.empty()){
                queue <u16> temp_t1_b = t1_b ;
                queue <u16> temp_t1_w = t1_w ;
                while((!temp_t1_w.empty()) && local.size()<LIMIT){
                    m.row[1] = temp_t1_w.front()/19 ;
                    m.col[1] = temp_t1_w.front()%19 ;
                    temp_t1_w.pop() ;
                    local.push(m) ;
                }
                while((!temp_t1_b.empty()) && local.size()<LIMIT){
                    m.row[1] = temp_t1_b.front()/19 ;
                    m.col[1] = temp_t1_b.front()%19 ;
                    temp_t1_b.pop() ;
                    local.push(m) ;
                }
            }
            
            size = local.size() ;
            local2stack(local) ;
            emptyQ() ;
            return size ;
        }
        
        if(t3_w.size()>=2 && local.size()<LIMIT){
            temp = t3_w ;
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
        
        if(t2_w.size()>=2 && local.size()<LIMIT){
            temp = t2_w ;
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
        
        
        if(t3_w.size()!=0 && t3_b.size()!=0 && local.size()<LIMIT){
            queue <u16> temp2;
            temp = t3_w ;
            while(temp.size()>0 && local.size()<LIMIT){
                temp2 = t3_b ;
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
        
        if(t3_b.size()>=2 && local.size()<LIMIT){
            temp = t3_b ;
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
        
        if(t2_w.size()!=0 && t2_b.size()!=0 && local.size()<LIMIT){
            queue <u16> temp2;
            temp = t2_w ;
            while(temp.size()>0 && local.size()<LIMIT){
                temp2 = t2_b ;
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
        
        if(t2_b.size()>=2 && local.size()<LIMIT){
            temp = t2_b ;
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
        
        if(t1_w.size()>=2 && local.size()<LIMIT){
            temp = t1_w ;
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
        
        if(t1_b.size()>=2 && local.size()<LIMIT){
            temp = t1_b ;
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

        if(t1_b.size()==1 && t1_w.size()==1 && local.size()<LIMIT){
            m.row[0] = t1_b.front()/19 ;
            m.col[0] = t1_b.front()%19 ;
            m.row[1] = t1_w.front()/19 ;
            m.col[1] = t1_w.front()%19 ;
            local.push(m) ;
        }
        
        if(local.empty()){
            empty_places(board);
            
            if (t3_w.size()==1){
                m.row[0] = t3_w.front()/19 ;
                m.col[0] = t3_w.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t3_b.size()==1){
                m.row[0] = t3_b.front()/19 ;
                m.col[0] = t3_b.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t2_w.size()==1){
                m.row[0] = t2_w.front()/19 ;
                m.col[0] = t2_w.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t2_b.size()==1){
                m.row[0] = t2_b.front()/19 ;
                m.col[0] = t2_b.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t1_w.size()==1){
                m.row[0] = t1_w.front()/19 ;
                m.col[0] = t1_w.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else if (t1_b.size()==1){
                m.row[0] = t1_b.front()/19 ;
                m.col[0] = t1_b.front()%19 ;
                while(!empty.empty() && local.size()<LIMIT){
                    m.row[1] = empty.front()/19 ;
                    m.col[1] = empty.front()%19 ;
                    local.push(m) ;
                    empty.pop() ;
                }
            }
            
            else{
                while(empty.size()>=2 && local.size()<LIMIT){
                    m.row[0] = empty.front()/19 ;
                    m.col[0] = empty.front()%19 ;
                    empty.pop() ;
                    unsigned long cnt = empty.size() ;
                    while(cnt>0 && local.size()<LIMIT){
                        m.row[1] = empty.front()/19 ;
                        m.col[1] = empty.front()%19 ;
                        empty.push(empty.front()) ;
                        empty.pop() ;
                        local.push(m) ;
                        cnt--;
                    }
                }
            }
            
            while(!empty.empty()){
                empty.pop() ;
            }
        }

        size = local.size() ;
        local2stack(local) ;
        emptyQ() ;
        return size ;
    }
}

#endif /* move_selector_h */
