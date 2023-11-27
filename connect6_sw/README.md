## This directory contains the complete software game solver. 

You can run this in any preferred C++ compiler like Xcode.

Feel free to play around with the following parameter to compare performance.
******************************************************************************************
LIMIT : Number of potential moves to be selected from the board from one node of the tree search
******************************************************************************************
DEPTH : Depth of the tree 
******************************************************************************************
W4 : Weight for t4 threats that is used in the board evaluation formula  
W3 : Weight for t3 threats that is used in the board evaluation formula  
W2 : Weight for t2 threats that is used in the board evaluation formula  
******************************************************************************************
TS : Treesearch Algorithm type
******************************************************************************************
 TS = 0 : AlphaBeta
 TS = 1 : AlphaBeta With Memory
 TS = 2 : NegaMax
 TS = 3 : NegaMax With Memory
 TS = 4 : NegaScout With Memory
******************************************************************************************
TRUNC_BOARD : The reduction factor to minimize the board size around the active game locations 
******************************************************************************************
 Can take value from 0 to 6  
 Maximum Row Number = 18-TRUNC_BOARD  
 Minimum Row Number = TRUNC_BOARD  
 Maximum Column Number = 18-TRUNC_BOARD  
 Minimum Column Number = TRUNC_BOARD  
******************************************************************************************
OPTIMISATION : Type for board evaluation
OPTIMISATION = 0 : Threat finder evaluates the complete board  
OPTIMISATION = 1 : Threat finder evaluates a dynamic board which is updated at every move  
OPTIMISATION = 2 : Threat finder evaluates a dynamic board which is updated at every node  
******************************************************************************************
 NO : Enable Node Ordering
 NO = 1 : Enables Node Ordering
 NO = 0 : Disables Node Ordering
******************************************************************************************
 NO_MAX_DEPTH : Minimum Distance from the leaf node at which Node Ordering is done  
******************************************************************************************
 NO_MAX_MOV : Max number of nodes on which node ordering is performed 
******************************************************************************************
Note : For the top most node, all the nodes are ordered
