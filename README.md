# reversi-minimax

This was a project for the subject of parallel programing and it uses the minimax stragy to play the revesi game.
All positions in the board have the same weight (it was a project rule, not the best choice). 
There are four versions of the code: a sequential version, two versions with using the shared memory paradigm (openMP and pThreads) and one version using the message passing paradigm (openMPI)

Dependency packages (on linux debian/ubuntu/mint): build-essentials (sequential, openMP, pThreads and openMPI) other depencies (for the parallel versions) will be added later with the code.

Input:
------
The input must be in a file named "reversi.conf" with two (positive integer) numbers separated by spaces: the size o the (squared) reversi board and the number of levels that you want the minimax strategy to predict (memory problems).

Output:
-------
The output is the file "game.txt", it has three columns, the first one is the color of the bead being played and the second and third ones are the positions of the bead on the board (line and column).
