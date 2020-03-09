# Game-of-Life

Non-player game written in C Language.

Idea of the game made by John Horton Conway and remade by me

The game consists in simulating the generations of a certain number of cells and their survival. There are some rules:

1-Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2-Any live cell with two or three live neighbours lives on to the next generation.
3-Any live cell with more than three live neighbours dies, as if by overcrowding.
4-Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

So, the game have to show exactly the way that the generations advances by the agreement of these rules.

IMPORTANT : The general language of this program is in Portuguese-Brazil Language. If you still have any doubts, send me an message and I'll try to solve it for you.

To compile the program use the terminal command on Linux : gcc gameoflife.c -o gameoflife.out

To execute the program, make sure the "primeira-g.txt" is in the same directory of the code "gameoflife.c" and run in terminal command : ./gameoflife.out
