# Connect6 Game Solver: A Novel Hardware-Software Co-Design Approach

## Overview
Welcome to the Connect6 Solver project! This project is a amalgamation of Hardware-Software Co-design and Game Theory, presenting a novel solution for the classic Connect6 game.
This detailed description of this work is published in the form of a research paper in "e-Prime - Advances in Electrical Engineering, Electronics and Energy", an Elsevier Journal.

A. K. Trivedi, S. Garg, and N. Pandey, “Novel hardware/software co-design approach for Connect6 game-solver,” e-Prime - Advances in Electrical Engineering, Electronics and Energy, vol. 7, p. 100395, Mar. 2024, doi: [https://doi.org/10.1016/j.prime.2023.100395](https://doi.org/10.1016/j.prime.2023.100395)



## Architecture 
### 1. Complete Software Game Solver
The complete software Game Solver is crafted entirely in C++. The code incorporates self-play functionality, allowing the Game Solver to engage in strategic battles against itself. The program boasts support for various tree searching algorithms, including MinMax, AlphaBeta, AlphaBeta with [Memoization](https://en.wikipedia.org/wiki/Memoization), NegaMax, NegaMax with Memoization, and [NegaScout](https://www.chessprogramming.org/NegaScout). Users have the flexibility to fine-tune parameters such as node ordering, tree search depth, relevant board truncation, number of child nodes, and more. For additional details on configuration options, please refer to the documentation provided in [connect6_sw](connect6_sw) directory.
 
### 2. Hardware Software Game Solver
The Hardware-Software Co-design of the Game Solver is developed on the Xilinx ZedBoard SOC, leveraging Vivado HLx and the SDK tool. 
The solver algorithm is partitioned, with the board evaluator implemented on the FPGA and the tree search executed on the ARM Cortex-A9 processor. 
The board evaluater is taken to the hardware partition to leverage the scope of parallelism in evaluating the board, which will reduce the time for finding the best move. 
Furthermore, on time profiling it was found that this functiin take the maximum percentage time spent by the program. 

For communication between the hardware and software partitions, two protocols were used:
1. AXI-Lite - A memory-mapped protocol used for communication between a master and a slave.
2. AXI-Stream - A protocol designed for high-throughput, unidirectional streaming of data between a master and a slave.

In our initial reference model, we employed the AXI Stream protocol to transfer the entire board to the FPGA for evaluation each time a leaf node was reached during the program execution. The following diagram shows the reference model architecture:
![Communication Model S](https://github.com/avijeet-trivedi/Connect6/assets/59733259/5aa0f430-451c-45c9-836f-aa4b49892605)

However, in our optimized communication model, we have streamlined the process. Now, we send the complete board to the FPGA when reaching a node one level above the leaf node, utilizing a combination of AXI Lite and AXI Stream protocols. This allows for a more efficient data transfer strategy. Upon reaching the leaf node, we transmit only the move using AXI Lite, as this protocol is more lightweight for transmitting move data with fewer bits. Leveraging the board already stored in the hardware, the FPGA then reconstructs the complete board using the received move. Subsequently, the evaluation is performed, and the threat counts are communicated back to the software using AXI Lite. This refined communication scheme has resulted in a significant reduction in communication overhead, leading to a notable improvement in the speed and efficiency of the game solver.

The codesign code of the model that employs AXI-Lite for transmitting the board one level above the leaf node is present in [connect6_lite](connect6_lite) directory and the architecture for the same is shown below.
![Communication Model LU](https://github.com/avijeet-trivedi/Connect6/assets/59733259/136b7c24-c8ca-4ba3-ac60-cb77a448e26e)

The codesign code of the model that employs AXI-Stream for transmitting the board one level above the leaf node is present in [connect6_stream](connect6_stream) directory and the architecture for the same is shown below.
![Communication Model SU](https://github.com/avijeet-trivedi/Connect6/assets/59733259/2c01157e-0f94-466b-8408-92d46cc6609a)

## Key Features

### 1. Novel Data Communication Technique
In the pursuit of improving performance from our reference model, we proposed a novel data communication technique by minimizing the bits transferred between hardware and software, we significantly reduce communication overhead, enhancing overall performance. In short, instead of sending the complete board every time at depth N (maximum depth) of the tree search, we send the complete board at depth N-1 and when the program reaches depth N, it just sends the move to the hardware accelerator and in the hardware the complete board is generated.

### 2. Advanced Tree-Searching Algorithms
To elevate the strategic aspect of the game, Connect6 Solver incorporates a suite of advanced tree-searching algorithms. Key optimizations include:
  
  - Negascout: A sophisticated variation of the min-max algorithm, maximizing the efficiency of move exploration.
  - Iterative Deepening: Enhancing search depth progressively for improved decision-making.
  - Node Ordering: A strategic arrangement of nodes during search to expedite optimal move discovery.
  - Memoization: Caching computed results to avoid redundant computations, speeding up the decision process.

## Results
### 1. Efficiency Gains in Communication Overhead:
Achieved a remarkable 92% reduction in communication overhead.
### 2. Speed Gains Compared to a Prevalent Hardware-Software Codesign Model:
Realized a substantial 50% overall enhancement compared to the existing prevalent hardware-software codesign model.
### 3. Speed Gains Compared to Complete Software Model:
Demonstrated a significant 4x speed improvement over a complete software model, particularly on the Xilinx Zedboard SOC.

## Reference model
Our Reference model was developed from the below paper:  
J. Olivito, J. Resano and J. L. Briz, "Accelerating Board Games Through Hardware/Software Codesign," in IEEE Transactions on Computational Intelligence and AI in Games, vol. 9, no. 4, pp. 393-401, Dec. 2017, doi: 10.1109/TCIAIG.2016.2604923.

## Note
For additional information regarding the project and its implementation, please feel free to contact me via email at avijeet.trivedi@gmail.com. I would be happy to provide further details and address any inquiries you may have. Looking forward to discussing the project with you.



