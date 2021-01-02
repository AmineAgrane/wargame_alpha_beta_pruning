# Setting of the game
The goal of this project is to create a simplified version of "wargame" to be played by 2 players. Each turn, each player may move only one of its pawn by one square in all 8 directions. It is forbidden to move to a square occupied by one of its own pawns or to move out of the playground.

If the destination square is occupied by an enemy pawn, we take it if the the sum of its pawns on the 8 adjacent squares is greater than the sum of the enemy pawns on these same 8 adjacent squares.  A player loses if he has no more pawns left or if the other player manages to reach with one of his pawns the other player's back line.

Game situation at the start and valid movements of each pawns. The number indicates the value of a pawn. The black dot indicates pawns belonging to Black. The other pawns belong to White. White starts the game.

In order to play a game by human, commands must be given inside the terminal. Some examples of the command syntax  :
- **D1D2** (go from the **D1** square to the **D2** square)
- **B7B6** (go from the **B7** square to the **B6** square)
- etc

# Minimax & Alpha/Beta Pruning : 
The objective is to implement a low-level artificial intelligence, so that it can play a game and compete with a human player. The Minimax algorithm is then implemented. The Minimax algorithm is a decision making algorithm used for
in game theory. This algorithm allows us to find an optimal move for a given player, assuming the opponent plays in an optimal way.

The structure used in this algorithm is a tree: The root represents the initial situation of the game, and the nodes represent the different possible strokes. A value can be associated to each node using a heuristic function. A tree can be given a depth limit that it cannot exceed.


Alpha-beta pruning is an optimization technique for the minimax algorithm, it uses a confidence interval [alpha, beta] to determine whether to cut the branches of the game tree that do not need to be searched for because there is already a better
available shot. This algorithm performs the same work and gives the same results as the minmax algorithm, while avoiding visiting all the nodes of the tree, which results in a consequent gain in terms of performance and computing time.  This allows us to perform a search much faster and to go further in the game tree.

##### Experimental analysis : 
For each of the 2 algorithms, and for each of the possible depths (from 1 to 3), we play 5 games of 15 moves. At the end of the 15th move, we take the total number of explored nodes during the game.


# Heuristic Function :
The heuristic function is a function that, for a given player and a given board, assigns an integer value. This value is an indicator of the "favorable situation" for the given player. If a board is assigned a large value, it increases the player's chances of winning, a small value when it minimizes the chances of winning, and a large value when it minimizes the chances of losing. the player's chances of victory.

The criteria taken into account to implement my heuristic are :
- **The number of pawns** : If the number of pawns reaches 0 the player loses the game. A low number of pawns reduces the player's chances of capturing an opponent's checker and reaching the finish line, and it also weakens the player's defense.

- **The values of the pawns** : A pawn with a value of 3 has a greater chance of capturing an opponent's pawn, reaching the finish line and protecting its brother pawns than a pawn with a value of 1.

- **The distance of the pawns to the opponent's finish line** : The more the player has a large number of pawns close to the finish line, the more likely he is to win.

- **The proximity of the pawns:** : An isolated pawn is easier to capture for the opponent than a grouped pawn. This criterion comes also to fill/complete the criterion of proximity with the finishing line

- **The difference in the number of pawns of the 2 players** : Capturing an opponent's pawn increases the player's chances of winning. This criterion is taken into account in order to "eat" the opponent's pawns when you have the opportunity to do so.