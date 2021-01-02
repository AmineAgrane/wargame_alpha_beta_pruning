#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_ROWS 10
#define N_COL 10
#define INFINI 10000
#define PROF_MAX 3
#define Minimax_AlphaBeta 0


// Pawn struct :  
//  1=> Dark 
// -1=> White
typedef struct Pawn_s {
	int color;	
	int value;
} Pawn;


int X1, Y1, X2, Y2;
Pawn *boardDegame;
int NbrNoeudExplore=1, NbrNoeudAlpha=1;
int coup=1;

// Functions 
void f_show_board(Pawn *board);
int f_convert_char2int(char c);
char f_convert_int2char(int i);
char f_convert_int2char(int i);
void f_copie_board(Pawn* source, Pawn* dest);
int f_test_move(Pawn *board, int l1, int c1, int l2, int c2, int color);
int f_move_pawn(Pawn *board, int l1, int c1, int l2, int c2, int color);
int f_battle(int l, int c);
int f_winner();
Pawn* f_raz_board();
void f_Human(int player);
int min(int a, int b);
int max(int a, int b);
int f_min(Pawn* boardActuel, int profondeur, int player);
int f_max(Pawn* boardActuel, int profondeur, int player);
void f_IA(int player);
int EvaluationDistancePawns(Pawn *game,int player);
int EvaluationGroupementPawns(Pawn *game, int player);
int Evaluation(Pawn *game,int player);
int f_eval(Pawn* game,int player);
int f_max_pruning(Pawn* boardActuel, int profondeur, int player, int alpha, int beta);
int f_min_pruning(Pawn* boardActuel, int profondeur, int player, int alpha, int beta);



int f_convert_char2int(char c) {
	if(c>='A' && c<='Z') {return (int)(c-'A');}
	if(c>='a' && c<='z') {return (int)(c-'a');}
	return -1;
}


char f_convert_int2char(int i) {
	return (char)i+'A';
 }

int min(int a, int b)
{
if(a<b){return a;}
else{return b;}
}

/* Init board, and return pointeur sur board*/
Pawn *f_init_board()
{
	Pawn *board=NULL;
	int i, j;
  #ifdef DEBUG
  	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
  #endif

    //Allocate memory 
	board = (Pawn *)malloc(N_ROWS*N_COL*sizeof(Pawn));
	if(board == NULL) { printf("error: unable to allocate memory\n"); 	exit(EXIT_FAILURE);}


	for(i=0; i<N_ROWS; i++)
	{
		for(j=0; j<N_COL; j++)
		{	board[i*N_COL+j].color = 0;	board[i*N_COL+j].value = 0; }
	}
    
    /* Blacks */
	board[9*N_COL+5].color = 1; 	board[9*N_COL+5].value = 1;
	board[9*N_COL+6].color = 1;  	board[9*N_COL+6].value = 2;
	board[9*N_COL+7].color = 1;   board[9*N_COL+7].value = 3;
	board[9*N_COL+8].color = 1; 	board[9*N_COL+8].value = 2;
	board[9*N_COL+9].color = 1; 	board[9*N_COL+9].value = 1;
	board[8*N_COL+0].color = 1; 	board[8*N_COL+0].value = 1;
	board[8*N_COL+1].color = 1; 	board[8*N_COL+1].value = 3;
	board[8*N_COL+2].color = 1; 	board[8*N_COL+2].value = 3;
	board[8*N_COL+3].color = 1; 	board[8*N_COL+3].value = 1;
	board[8*N_COL+6].color = 1; 	board[8*N_COL+6].value = 1;
	board[8*N_COL+7].color = 1; 	board[8*N_COL+7].value = 1;
	board[8*N_COL+8].color = 1; 	board[8*N_COL+8].value = 1;
	board[7*N_COL+1].color = 1; 	board[7*N_COL+1].value = 1;
	board[7*N_COL+2].color = 1;	  board[7*N_COL+2].value = 1;
  
    /* White */
	board[2*N_COL+7].color = -1;	board[2*N_COL+7].value = 1;
	board[2*N_COL+8].color = -1;	board[2*N_COL+8].value = 1;
	board[1*N_COL+1].color = -1;	board[1*N_COL+1].value = 1;
	board[1*N_COL+2].color = -1;	board[1*N_COL+2].value = 1;
	board[1*N_COL+3].color = -1;	board[1*N_COL+3].value = 1;
	board[1*N_COL+6].color = -1;	board[1*N_COL+6].value = 1;
	board[1*N_COL+7].color = -1;	board[1*N_COL+7].value = 3;
	board[1*N_COL+8].color = -1;	board[1*N_COL+8].value = 3;
	board[1*N_COL+9].color = -1;	board[1*N_COL+9].value = 1;
	board[0*N_COL+0].color = -1;	board[0*N_COL+0].value = 1;
	board[0*N_COL+1].color = -1;	board[0*N_COL+1].value = 2;
	board[0*N_COL+2].color = -1;	board[0*N_COL+2].value = 3;
	board[0*N_COL+3].color = -1;	board[0*N_COL+3].value = 2;
	board[0*N_COL+4].color = -1;	board[0*N_COL+4].value = 1;

   #ifdef DEBUG
   printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
   #endif

return board;
}

// show board in terminal
void f_show_board(Pawn *board)
{
	int i,j,k;	
	printf("\n    ");
	for(k=0; k<N_COL; k++) {printf("%2c ",f_convert_int2char(k));}	printf("\n    ");
	for(k=0; k<N_COL; k++) {printf("-- ");}
	printf("\n");
	for(i=N_ROWS-1; i>=0; i--)
	{
		printf("%2d ", i);
		for(j=0; j<N_COL; j++)
		{
			printf("|");
			switch(board[i*N_COL+j].color)
			{
			case -1:	printf("%do",board[i*N_COL+j].value);	break;
			case 1:		printf("%dx",board[i*N_COL+j].value);	break;
			default:	printf("  ");
			}
		}
		printf("|\n    "); for(k=0; k<N_COL; k++){printf("-- ");}		printf("\n");
	}
	printf("    ");
}


// Copy du board
void f_copie_board(Pawn* source, Pawn* dest) {
	int i, j;
	for (i = 0; i < N_ROWS; i++)
	{
		for (j = 0; j < N_COL; j++)
		{
			dest[i * N_COL + j].color = source[i * N_COL + j].color;
			dest[i * N_COL + j].value = source[i * N_COL + j].value;
		}
	}
}

// Return a board with all values and colors set to 0 
Pawn* f_raz_board() {
	Pawn* game = NULL;
	int i, j;
	game = (Pawn *) malloc(N_ROWS * N_COL * sizeof (Pawn));
	for (i = 0; i < N_ROWS; i++)
	{
		for (j = 0; j < N_COL; j++)
		{
			game[i * N_COL + j].color = 0;
			game[i * N_COL + j].value = 0;
		}
	}
	return game;
}

// Return number of Pawns inside the board of the given player
int f_nbPawns(Pawn* game, int player) {

	int i,j,nbPawn=0;
	for (i = 0; i < N_COL; ++i) {
		for (j = 0; j < N_ROWS; ++j) {
			if (game[i * N_COL + j].color == player)	{	++nbPawn;	}
		}
	}
	return nbPawn;
}

// Return the sum of a players pawns values 
int f_value(Pawn* game, int player) {
	int i, j;
	int value=0;
	for (i = 0; i < N_COL; ++i)
	{
		for (j = 0; j < N_ROWS; ++j)
		{
			if (game[i * N_COL + j].color == player)
			{ 	value += game[i * N_COL + j].value;	}
		}
	}
	return value;
}

/*Return the winner of the game 
 1=> Black win 
-1=> White win   
 0=> No one win
 */
/* A player win if he rachs the last row or eat all its oppnent pawns*/
int f_winner() {
	int i, j, sum1=0, sum2=0;
  #ifdef DEBUG
  	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
  #endif

	//Quelqu'un est-il arrive sur la ligne de l'autre
	for(i=0; i<N_COL; i++)
	{
		if(boardDegame[i].color == 1) {return 1;}
		if(boardDegame[(N_ROWS-1)*N_COL+i].color == -1) {return -1;}
	}

	//taille des armees
	for(i=0; i<N_ROWS; i++)
	{
		for(j=0; j<N_COL; j++)
		{
			if(boardDegame[i*N_COL+j].color == 1) {sum1++;}
			if(boardDegame[i*N_COL+j].color == -1) {sum2++;}
		}
	}
	if(sum1==0) {return -1;}
	if(sum2==0) {return 1;}

  #ifdef DEBUG
  	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
  #endif
	return 0;
}


/* Take the case row and col, and the return the pawn winner */
int f_battle(int l, int c) {
	int i, j, mini, maxi, minj, maxj;
	int sum=0;

  #ifdef DEBUG
  	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
  #endif

	mini = l-1<0?0:l-1;
	maxi = l+1>N_ROWS-1?N_ROWS-1:l+1;
	minj = c-1<0?0:c-1;
	maxj = c+1>N_COL-1?N_COL-1:c+1;

	for(i=mini; i<=maxi; i++)
	{
		for(j=minj; j<=maxj; j++)
		{
			sum += boardDegame[i*N_COL+j].color*boardDegame[i*N_COL+j].value;
		}
	}
	sum -= boardDegame[l*N_COL+c].color*boardDegame[l*N_COL+c].value;

  #ifdef DEBUG
  	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
  #endif
	if(sum < 0) {return -1;}
	if(sum > 0) {return 1;}
	return boardDegame[l*N_COL+c].color;
}


/* Check if a move is possible*/
int f_test_move(Pawn *board, int l1, int c1, int l2, int c2, int color) {
  #ifdef DEBUG
  	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);	printf("de (%d,%d) vers (%d,%d)\n", l1, c1, l2, c2);
  #endif

	/* Erreur, hors du board */
	if(l1 < 0 || l1 >= N_ROWS || l2 < 0 || l2 >= N_ROWS || c1 < 0 || c1 >= N_COL || c2 < 0 || c2 >= N_COL)
	{return 1;}
	/* Erreur, il n'y a pas de Pawn a deplacer ou le Pawn n'appartient pas au player*/
	if(board[l1*N_COL+c1].value == 0 || board[l1*N_COL+c1].color != color)
	{return 1;}
	/* Erreur, tentative de tir fratricide */
	if(board[l2*N_COL+c2].color == board[l1*N_COL+c1].color)
	{return 1;}
   /*Saut supérieur à 1 & Meme case*/
	if(l1-l2 >1 || l2-l1 >1 || c1-c2 >1 || c2-c1 >1 || (l1==l2 && c1==c2))
	{return 1;}

  #ifdef DEBUG
  	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
  #endif
	return 0;
}


/* Move the pawn to the given position */
int f_move_pawn(Pawn *board, int l1, int c1, int l2, int c2, int color)
{
	int winner=0;
  #ifdef DEBUG
  	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
  #endif

	if(f_test_move(board, l1, c1, l2, c2, color) != 0)	{return 1;}
	/* Cas ou il n'y a personne a l'arrivee */
	if(board[l2*N_COL+c2].value == 0)
	{
		board[l2*N_COL+c2].color = board[l1*N_COL+c1].color;
		board[l2*N_COL+c2].value = board[l1*N_COL+c1].value;
		board[l1*N_COL+c1].color = 0;
		board[l1*N_COL+c1].value = 0;
	}
	else
	{
		winner=f_battle(l2, c2);
		/* victoire */
		if(winner == color)
		{
			board[l2*N_COL+c2].color = board[l1*N_COL+c1].color;
			board[l2*N_COL+c2].value = board[l1*N_COL+c1].value;
			board[l1*N_COL+c1].color = 0;
			board[l1*N_COL+c1].value = 0;
		}
		/* defaite */
		else if(winner != 0)
		{
			board[l1*N_COL+c1].color = 0;
			board[l1*N_COL+c1].value = 0;
		}
	}

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	return 0;
}

// Print general stats about the party
void Statistiqueboard(Pawn *game, int player)
{
	int nbPawns= 0;
  printf("Player %d :\n", player);
  printf("Nb : %d / Values : %d / Distance : %d\n",f_nbPawns(game,player),f_value(game, player),EvaluationDistancePawns(game, player));
	//On parcours le board de gauche à droite du haut vers le bas
	for(int ligne=9; ligne >=0; ligne--)
	{
		for(int colonne=0; colonne < N_COL; colonne++)
		{	//On trouve un Pawn du player
			if(game[ligne * N_COL+colonne].color == player)
			 {
					 printf("player %d : %c%d /color : %d/ value : %d\n",player,f_convert_int2char(colonne), ligne,game[ligne * N_COL+colonne].color,
				   game[ligne * N_COL+colonne].value);
			 }
	  }
	}
}

// Return an int value which is an heuristic about the grouped pawns
int EvaluationGroupementPawns(Pawn *game, int player)
{
int valueboard = 0, GroupePawn=0;

//On parcours le board de gauche à droite du haut vers le bas
for(int ligne=N_ROWS-1; ligne >=0; ligne--)
{
	for(int colonne=0; colonne < N_COL; colonne++)
	{
		//On trouve un Pawn du player
		if(game[ligne*N_COL+colonne].color == player)
		 {
			 GroupePawn=0;
			 //On boucle autour du Pawn
			 for(int i=-1; i<=1; i++) {
				 for(int j=-1;j<=1;j++) {
						if(game[(ligne+i)*N_COL+colonne+j].color == player) {
							 GroupePawn = GroupePawn + game[ligne+i * N_COL+colonne+j].value;
						 }
				 }
			 }
     if(GroupePawn <= 1 )  { GroupePawn=-25; }
		 valueboard = valueboard + GroupePawn;
		 }
	}
}

return valueboard;
}

// Return an int value, which is an heuristic about the proximity of the player to the winning row
int EvaluationDistancePawns(Pawn *game,int player)
{
	int Val = 0;
	int valuesPosition[]={12,19,25,37,65,78,100,170,250,600};

	for(int ligne=N_ROWS-1; ligne >=0; ligne--)
	{
		for(int colonne=0; colonne < N_COL; colonne++)
		{	//On trouve un Pawn du player
			if(game[ligne * N_COL+colonne].color == player)
			 {	// Pawn X
				 if(player==1)
				 {  Val= Val+ valuesPosition[10 - (ligne+1)];	 }
				 // Pawn O
			   else if(player==-1)
			   { 	Val=	Val + valuesPosition[ligne];		}
	     }
	   }
   }
return Val;
}

// General Heuristic
int Evaluation(Pawn *game,int player) {

	int sumEvaluation=0, NbPawnsplayer=0, NbPawnsAdversaire=0;

	NbPawnsplayer = f_nbPawns(game,player);
	NbPawnsAdversaire = f_nbPawns(game,-player);
	sumEvaluation = NbPawnsplayer*7 + f_value(game, player)*4 + EvaluationDistancePawns(game, player) + 2*EvaluationGroupementPawns(game, player);
    sumEvaluation = sumEvaluation + (NbPawnsplayer - NbPawnsAdversaire)*280; 

  return (sumEvaluation);
 }


// Evaluation function
int f_eval(Pawn* game,int player) {
	return (Evaluation(game, player) - Evaluation(game, -player));
}

// Generate a random boolean value
int random_bool()
{ return (rand() % 2); }


int f_min(Pawn* boardActuel, int profondeur, int player) {
	int value_min = INFINI;
	Pawn* boardCopie = f_init_board();
	f_copie_board(boardActuel, boardCopie);

	if(profondeur >= PROF_MAX || f_winner() != 0)
	{ return(f_eval(boardActuel,-player));	}

	//On parcours le board
	for(int ligne=N_ROWS-1; ligne >=0; ligne--) {
		for(int colonne=0; colonne < N_COL; colonne++) {
			//On trouve un Pawn du player
			if(boardActuel[ligne * N_COL+colonne].color == player) {

				for(int i=-1; i<=1; i++) {
					for(int j=-1; j<=1; j++) {
						f_copie_board(boardActuel, boardCopie);
						if(!f_move_pawn(boardCopie,ligne, colonne, ligne+i, colonne+j, player)) {
							  NbrNoeudExplore++;
								value_min = min(value_min,f_max(boardCopie,profondeur+1,-player));
						}
					}
				}
			}
		}
	}
	return value_min;
}


int f_max(Pawn* boardActuel, int profondeur, int player) {
	int NbrNoeudAvant=0, NbrNoeudApres=0;
	int value_max=-INFINI;
	Pawn* boardCopie=f_init_board();
	f_copie_board(boardActuel, boardCopie);

	if(profondeur >= PROF_MAX || f_winner() != 0)
	{ 	return(f_eval(boardActuel, -player));  }

	//On parcours le board
	for(int ligne=N_ROWS-1; ligne >=0; ligne--) {
		for(int colonne=0; colonne < N_COL; colonne++) {
			//On trouve un Pawn du player
			if(boardActuel[ligne * N_COL+colonne].color == player){

				for(int i=-1; i<=1; i++) {
					for(int j=-1;j<=1;j++) {
					  f_copie_board(boardActuel, boardCopie);
						if(f_test_move(boardCopie, ligne, colonne, ligne+i, colonne+j, player) == 0)
						{
							 f_move_pawn(boardCopie,ligne, colonne, ligne+i, colonne+j, player);
							 NbrNoeudExplore++;
							 NbrNoeudAvant=NbrNoeudExplore;
							 int newVal = f_min(boardCopie,profondeur+1,-player);
							 NbrNoeudApres = NbrNoeudExplore;
							 int diff = NbrNoeudApres - NbrNoeudAvant;

							  if(value_max < newVal)
								{
									value_max = newVal;
									if(profondeur == 0) {
										X1 = ligne; Y1 = colonne;
										X2 = ligne+i; Y2 = colonne+j;
									}
								}
								else if (value_max == newVal) {
									int bool_test = random_bool();
									//printf("BOOL : %d\n",bool_test);
									if(bool_test==1) {
										value_max = newVal;
										if(profondeur == 0) {
											X1 = ligne; Y1 = colonne;
											X2 = ligne+i; Y2 = colonne+j;
										}
									}
								}
						}
					}
				}
			}
		}
	}
	return value_max;
}



int f_min_pruning(Pawn* boardActuel, int profondeur, int player, int alpha, int beta)
{
	int value_min = INFINI;
	Pawn* boardCopie = f_init_board();
	f_copie_board(boardActuel, boardCopie);

	if(profondeur >= PROF_MAX || f_winner() != 0)
	{ return(f_eval(boardActuel,-player));	}

	//On parcours le board
	for(int ligne=N_ROWS-1; ligne >=0; ligne--)
	{
		for(int colonne=0; colonne < N_COL; colonne++)
		{
			//On trouve un Pawn du player
			if(boardActuel[ligne * N_COL+colonne].color == player)
			{
				//On teste tout les coups possibles
				for(int i=-1; i<=1; i++)
				{
					for(int j=-1; j<=1; j++)
					{
						f_copie_board(boardActuel, boardCopie);
						if(!f_move_pawn(boardCopie,ligne, colonne, ligne+i, colonne+j, player))
						{
							  NbrNoeudExplore++;
								value_min = min(value_min,f_max_pruning(boardCopie,profondeur+1,-player, alpha, beta));
								beta = min(beta, value_min);
								if(beta <=alpha)
								  { return value_min; }
						}
					}
				}
			}
		}
	}
	return value_min;
}


int f_max_pruning(Pawn* boardActuel, int profondeur, int player, int alpha, int beta)
{
	int value_max=-INFINI;
	Pawn* boardCopie=f_init_board();
	f_copie_board(boardActuel, boardCopie);

	if(profondeur >= PROF_MAX || f_winner() != 0)
	{ return(f_eval(boardActuel, -player)); }

	//On parcours le board
	for(int ligne=N_ROWS-1; ligne >=0; ligne--)
	{
		for(int colonne=0; colonne < N_COL; colonne++)
		{
			//On trouve un Pawn du player
			if(boardActuel[ligne * N_COL+colonne].color == player)
			{
				// On teste tous les coups possibles
				for(int i=-1; i<=1; i++)
				{
					for(int j=-1;j<=1;j++)
					{
					  f_copie_board(boardActuel, boardCopie);
						if(f_test_move(boardCopie, ligne, colonne, ligne+i, colonne+j, player) == 0)
						{
							 f_move_pawn(boardCopie,ligne, colonne, ligne+i, colonne+j, player);
							 NbrNoeudExplore++;
							 int newVal = f_min_pruning(boardCopie,profondeur+1,-player, alpha, beta);
							 if(value_max < newVal)
								{
									value_max = newVal;
									if(profondeur == 0)
									{
										X1 = ligne; Y1 = colonne;
										X2 = ligne+i; Y2 = colonne+j;
									}

								}
								else if (value_max == newVal)
								{
									int bool_test = random_bool();
									//printf("BOOL : %d\n",bool_test);
									if(bool_test==1)
									{
										value_max = newVal;
										if(profondeur == 0)
										{
											X1 = ligne; Y1 = colonne;
											X2 = ligne+i; Y2 = colonne+j;
										}
									}
								}
								if(value_max > alpha) {alpha=value_max;}
								if(beta<=alpha) {return value_max;}
						}
					}
				}
			}
		}
	}
	return value_max;
}


void f_IA(int player)
{

#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

if(Minimax_AlphaBeta == 1)
{f_max(boardDegame,0, player);}
else
{f_max_pruning(boardDegame,0, player,-INFINI, INFINI);}


printf("Coups : %d / Number of explorated nodes : %d\n",coup++,NbrNoeudExplore);
f_move_pawn(boardDegame,X1,Y1,X2,Y2,player);

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
}


/*Demande le choix du player Human et calcule le coup demande*/
void f_Human(int player)
{
	char c1, c2, buffer[32];
	int l1, l2;

#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	printf(" Turn of the Player : ");
	switch(player)
	{
	case -1:	printf("o ");	break;
	case 1:		printf("x ");	break;
	default:	printf("Unknown ");
	}

	while(1)
	{
		fgets(buffer, 32, stdin);
		if(sscanf(buffer, "%c%i%c%i\n", &c1, &l1, &c2, &l2) == 4)
		{
			if(f_move_pawn(boardDegame, l1, f_convert_char2int(c1), l2, f_convert_char2int(c2), player) == 0)
				break;
		}
		fflush(stdin);
		printf("Bad choice !\n");
	}

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
}

int main(int argv, char *argc[])
{
	srand(time(NULL));
	int fin = 0, mode=0, ret, player=1;
	printf("Max depth: %d\n",PROF_MAX);
	if(Minimax_AlphaBeta == 1)
	{printf("Algorithm : MinMax Only\n");}
	else
	{printf("Algorithme : MinMax with AlphaBeta Pruning\n");}
	printf("1)- Human vs IA\t2)- Human vs Human\t3)- IA vs IA\n");
	scanf("%d",&mode);

	boardDegame = f_init_board();
	while (!fin)
	{
		//f_eval(boardDegame,player);
		f_show_board(boardDegame);
		if(mode==1)
		{
			if(player>0)
				f_Human(player);
			else
				f_IA(player);
		}
		else if(mode==2)
		{
			//Statistiqueboard(boardDegame,player);
			f_Human(player);
		}
		else
		{
			f_IA(player);
		}

		if ((ret = f_winner()) != 0)
		{
			switch (ret)
			{
			case 1:
				f_show_board(boardDegame);
				printf("### player X WIN ! ###\n");
				fin = 1;
				break;
			case -1:
				f_show_board(boardDegame);
				printf("### player O WIN ! ###\n");
				fin = 1;
				break;
			}
		}
		player = -player;
	}

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif

	return 0;
}
