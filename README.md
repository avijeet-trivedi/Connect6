# Connect6 Game Solver: A Novel Hardware-Software Co-Design Approach

## Overview
Welcome to the Connect6 Solver project! This project is a amalgamation of Hardware-Software Co-design and Game Theory, presenting a novel solution for the classic Connect6 game.

## Key Features

### 1. Novel Data Communication Technique
In the pursuit of improving performance from our reference model, we proposed a novel data communication technique by minimizing the bits transferred between hardware and software, we significantly reduce communication overhead, enhancing overall performance. In short, instead of sending the complete board every time at depth N (maximum depth) of the tree search, we send the complete board at depth N-1 and when the program reaches depth N, it just sends the move to the hardware accelerator and in the hardware the complete board is generated.

### 2. Advanced Tree-Searching Algorithms
To elevate the strategic aspect of the game, Connect6 Solver incorporates a suite of advanced tree-searching algorithms. Key optimizations include:
  
  - Negascout: A sophisticated variation of the min-max algorithm, maximizing the efficiency of move exploration.
  - Iterative Deepening: Enhancing search depth progressively for improved decision-making.
  - Node Ordering: A strategic arrangement of nodes during search to expedite optimal move discovery.
  - Memoization: Caching computed results to avoid redundant computations, speeding up the decision process.

## Directory Structure

The directory contains 3 sub-directories:
1. **connect6_sw** - contains complete software game solver
2. **connect6_lite** - contains hardware-software game solver that uses AXI-Lite interface for communication
3. **connect6_stream** - contains hardware-software game solver that uses AXI-Stream interface for communication

## Results
### 1. Efficiency Gains in Communication Overhead:
Achieved a remarkable 92% reduction in communication overhead.
### 2. Speed Gains Compared to a Prevalent Hardware-Software Codesign Model:
Realized a substantial 50% overall enhancement compared to the existing prevalent hardware-software codesign model.
### 3. Speed Gains Compared to Complete Software Model:
Demonstrated a significant 4x speed improvement over a complete software model, particularly on the Xilinx Zedboard SOC.

## Publication
This work is under review at "e-Prime - Advances in Electrical Engineering, Electronics and Energy", an Elsevier Journal.
![Submission Proof](https://github.com/avijeet-trivedi/Connect6/assets/59733259/1ad354b5-4f5c-44ad-88cb-6f950cf27a3e)

## Reference model
Our Reference model was develop from the below paper:  
J. Olivito, J. Resano and J. L. Briz, "Accelerating Board Games Through Hardware/Software Codesign," in IEEE Transactions on Computational Intelligence and AI in Games, vol. 9, no. 4, pp. 393-401, Dec. 2017, doi: 10.1109/TCIAIG.2016.2604923.




