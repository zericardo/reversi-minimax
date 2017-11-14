#include <iostream> 
#include <list>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;


//Primeiro trabalho de Introdução à Programação Paralela.

struct boardPlace  //This struct represents a place on board.
{
  int row, column;
};

struct move //This struct represents a possible move for a player.
{
  int row, column; 
  list<boardPlace> whoChanges;  //beads that change color with this move
};

/*
  This function prints the board on screen.
  (It's not used on the main program, only 
  for check results)

  Parameter:
      board: (int **) The board that will be printed.
      boardSize: (int) The Size of the (square) board.
*/
void printBoard(int ** board,int boardSize)
{
  cout<<endl<<"Tabuleiro: "<<endl;
  for(int i=0;i<boardSize;i++)
    {
      for(int j=0;j<boardSize;j++)
	cout<<board[i][j]<<"\t";
      cout<<endl;
    }
  cout<<endl;
      
}

/*
  This function initialize the board with accordingly
  with reversi rules. 

  Parameters:
      boardSize: (int) the size of the board.

  Returns:
      (int **): the initialized board.
 */
int ** initializeBoard(int boardSize)
{
  int ** board = new int * [boardSize];
  int middle = boardSize/2;

  for(int i=0;i<boardSize;i++)
    board[i]= new int [boardSize];

  for(int i=0;i<boardSize;i++)
    for(int j=0;j<boardSize;j++)
      board[i][j]=0;

  board[middle-1][middle-1]=1;
  board[middle][middle]=1;
  board[middle][middle-1]=-1;
  board[middle-1][middle]=-1;
  
  return board;
}

/*
  Free memory of a given allocated board.

  Parameters:
      board: (int**) the board that will be erased from memory.
      boardSize: (int) the size of the board.
*/
void deleteBoard(int** board,int boardSize)
{
  for(int i=0;i<boardSize;i++)
    delete [] board[i];
  delete [] board; 
}

/*
  Returns the possible moves that a player can do in a given situation.

  Parameters:
      player: (int) The player which the function will search moves for.
      board: (int**) The game board where one wants to know the possible moves.
      boardSize: (int) The size of the board.

 Return:
     (list<move>): List with all possible moves for that player.
*/
list<move> returnMoves(int player,int **board, int boardSize)
{
  list<move> possibleMoves; //List of possible moves.
  list<boardPlace> finalList; //Final list of beads that vhange color.

  /*
    All the Eight directions (the X is the position that are being checked):

    1 2 3
    8 X 4
    7 6 5

   */

  //Runs among the board.
  for(int i=0;i<boardSize;i++)
    for(int j=0;j<boardSize;j++)
      if(board[i][j]==0) //If the place in board is empty
	{
	    //All the eight neighbors (or directions) that will be checked for beads to change and to validate the move
	    bool dOne=false, dTwo=false, dThree=false, dFour=false, dFive=false, dSix=false, dSeven=false, dEight=false;
	  if(i-1>=0 )//Upper row
	    {
	      if(board[i-1][j]==-player)//Left Column
		dTwo=true;
	      if(j-1>=0)
		if(board[i-1][j-1]==-player)//Same Column
		  dOne=true;
	      if(j+1<boardSize)
		if(board[i-1][j+1]==-player)//Right Column
		  dThree=true;
	    }
	  if(i+1<boardSize)//Lower row
	    {
	      if(board[i+1][j]==-player)
		dSix=true;
	      if(j-1>=0)
		if(board[i+1][j-1]==-player)
		  dSeven=true;
	      if(j+1<boardSize)
		if(board[i+1][j+1]==-player)
		  dFive=true;
	    }
	  if(j-1>=0)//Same row Left Column
	    if(board[i][j-1]==-player)
	      dEight=true;
	  if(j+1<boardSize)
	    if(board[i][j+1]==-player)
	      dFour=true;
	  
	  //Auxiliary variables here.
	  list<boardPlace> tempList;
	  boardPlace vizinho;
	  int auxi, auxj;
	  
	  //Check if the move in each direction is possible,
	  //and which beads will change color.
	  //Simple directions:
	  if(dTwo)
	    {
	      tempList.clear();
	      auxi=i-1;
	      while(auxi>=0)
		{
		  if(board[auxi][j]==0)
		    {
		      tempList.clear();
		      break;
		    }
		  else if(board[auxi][j]==-player)
		    {
		      vizinho.row=auxi;
		      vizinho.column=j;
		      tempList.push_back(vizinho);
		    }
		  else if(board[auxi][j]==player)
		    {
		      finalList.splice(finalList.end(),tempList);
		      tempList.clear();
		      break;
		    }
		  
		  auxi-=1;
		}	      
	    }

	  
	  if(dFour)
	    {
	      tempList.clear();
	      auxj=j+1;
	      while(auxj<boardSize)
		{
		  if(board[i][auxj]==0)
		    {
		      tempList.clear();
		      break;
		    }
		  else if(board[i][auxj]==-player)
		    {
		      vizinho.row=i;
		      vizinho.column=auxj;
		      tempList.push_back(vizinho);
		    }
		  else if(board[i][auxj]==player)
		    {
		      finalList.splice(finalList.end(),tempList);
		      tempList.clear();
		      break;
		    }
		  
		  auxj+=1;
		}	      
	    }

	  if(dSix)
	    {
	      tempList.clear();
	      auxi=i+1;
	      while(auxi<boardSize)
		{
		  if(board[auxi][j]==0)
		    {
		      tempList.clear();
		      break;
		    }
		  else if(board[auxi][j]==-player)
		    {
		      vizinho.row=auxi;
		      vizinho.column=j;
		      tempList.push_back(vizinho);
		    }
		  else if(board[auxi][j]==player)
		    {
		      finalList.splice(finalList.end(),tempList);
		      tempList.clear();
		      break;
		    }
		  
		  auxi+=1;
		}	      
	    }
	  

	  if(dEight)
	    {
	      tempList.clear();
	      auxj=j-1;
	      while(auxj>=0)
		{
		  if(board[i][auxj]==0)
		    {
		      tempList.clear();
		      break;
		    }
		  else if(board[i][auxj]==-player)
		    {
		      vizinho.row=i;
		      vizinho.column=auxj;
		      tempList.push_back(vizinho);
		    }
		  else if(board[i][auxj]==player)
		    {
		      finalList.splice(finalList.end(),tempList);
		      tempList.clear();
		      break;
		    }
		  
		  auxj-=1;
		}	      
	    }
	  
	  
	  //Mixed directions:
	  if(dOne)
	    {
	      tempList.clear();
	      auxi=i-1;
	      auxj=j-1;
	      while(auxi>=0 && auxj>=0)
		{
		  if(board[auxi][auxj]==0)
		    {
		      tempList.clear();
		      break;		   
		    }
		  else if(board[auxi][auxj]==-player)
		    {
		      vizinho.row=auxi;
		      vizinho.column=auxj;
		      tempList.push_back(vizinho);
		    }
		  else if(board[auxi][auxj]==player)
		    {
		      finalList.splice(finalList.end(),tempList);
		      tempList.clear();
		      break;
		    }
		  auxi-=1;
		  auxj-=1;
		}
	    }
	  
	  if(dThree)
	    {
	      tempList.clear();
	      auxi=i-1;
	      auxj=j+1;
	      while(auxi>=0 && auxj<boardSize)
		{
		  if(board[auxi][auxj]==0)
		    {
		      tempList.clear();
		      break;
		    }
		  else if(board[auxi][auxj]==-player)
		    {
		      vizinho.row=auxi;
		      vizinho.column=auxj;
		      tempList.push_back(vizinho);
		    }
		  else if(board[auxi][auxj]==player)
		    {
		      finalList.splice(finalList.end(),tempList);
		      tempList.clear();
		      break;
		    }
		  auxi-=1;
		  auxj+=1;
		}
	    }
	  
	  if(dFive)
	    {
	      tempList.clear();
	      auxi=i+1;
	      auxj=j+1;
	      while(auxi<boardSize && auxj<boardSize)
		{
		  if(board[auxi][auxj]==0)
		    {
		      tempList.clear();
		      break;
		    }
		  else if(board[auxi][auxj]==-player)
		    {
		      vizinho.row=auxi;
		      vizinho.column=auxj;
		      tempList.push_back(vizinho);
		    }
		  else if(board[auxi][auxj]==player)
		    {
		      finalList.splice(finalList.end(),tempList);
		      tempList.clear();
		      break;
		    }
		  auxi+=1;
		  auxj+=1;
		}
	    }

	  if(dSeven)
	    {
	      tempList.clear();
	      auxi=i+1;
	      auxj=j-1;
	      while(auxi<boardSize && auxj>=0)
		{
		  if(board[auxi][auxj]==0)
		    {
		      tempList.clear();
		      break;
		    }
		  else if(board[auxi][auxj]==-player)
		    {
		      vizinho.row=auxi;
		      vizinho.column=auxj;
		      tempList.push_back(vizinho);
		    }
		  else if(board[auxi][auxj]==player)
		    {
		      finalList.splice(finalList.end(),tempList);
		      tempList.clear();
		      break;
		    }
		  auxi+=1;	     
		  auxj-=1;
		}
	    }

	  
	  if(finalList.size()!=0) //If is a possible move.
	    {
	      move tempMove;
	      tempMove.row=i;
	      tempMove.column=j;
	      tempMove.whoChanges=finalList;
	      possibleMoves.push_back(tempMove);
	    }
	  finalList.clear();
	}
  
  return possibleMoves;
      
}

/*
  This function receives a move, and returns the final state of the board
  after the move done.

  Parameters:
      player: (int) who is making the move.
      moves: (move) the move that will be done.
      board: (int**) The board of the game before the move.
      boardSize: (int) The size of previous bord.

  Return:
      (int**): A copy of board, with the move done (and beads changed).
*/
int** makeMove(int player, move moves ,int** board,int boardSize)
{
  int** boardCopy;
  
  boardCopy = new int * [boardSize];

  for(int i=0;i<boardSize;i++)
    boardCopy[i] = new int [boardSize];

  for(int i=0;i<boardSize;i++)
    for(int j=0;j<boardSize;j++)
      boardCopy[i][j]=board[i][j];

  
      boardCopy[moves.row][moves.column]=player;

      for(list<boardPlace>::iterator it2=moves.whoChanges.begin();it2 !=moves.whoChanges.end() ;it2++)
	boardCopy[it2->row][it2->column]=player;
    
  
  return boardCopy;
}

/*
  Calculate the score of the game on a given situation.
  Parameters:
      board: (int **) The board which someone want to know the score.
      boardSize: (int) The size of the board.
  Returns:
      (int): The sum of all pieces on the board.
*/
int score(int** board, int boardSize)
{
  int total=0;
  
  for(int i=0;i<boardSize;i++)
    for(int j=0;j<boardSize;j++)
      total+=board[i][j];

  return total;
}

/*
  This function returns the maximum among the numbers alpha and beta.
  It also turns the best move (by reference) to the new value if 
  beta is smaller than alpha (or randomly if they are equal). 
  
  Parameters:
      alpha: (int) first number to compare.
      beta: (int) seccond number to compare.
      bestMove: (move) the previously best move for the player.
      it: (move) the current position on the board. (may be the new best move)
 Returns:
     (int): The bigger number among the two.
*/
int max(int alpha, int beta, move & bestMove, move it, int n)
{
  if(alpha>beta)
    return alpha;
  else if(alpha==beta && n==0)
    {
      float random = rand()/(RAND_MAX+1.0);
      if(random>=0.5)
	{
	  bestMove.row=it.row;
	  bestMove.column=it.column;
	  bestMove.whoChanges=it.whoChanges;
	  return beta;
	}
      else
	return alpha;
    }
  else
    {      
      bestMove.row=it.row;
      bestMove.column=it.column;
      bestMove.whoChanges=it.whoChanges;
      return beta;
    }
}

/*
  This function returns the minimum among the numbers alpha and beta.
  It also turns the best move (by reference) to the new value if 
  beta is smaller than alpha (or randomly if they are equal). 
  
  Parameters:
      alpha: (int) first number to compare.
      beta: (int) seccond number to compare.
      bestMove: (move) the previously best move for the player.
      it: (move) the current position on the board. (may be the new best move)
  Returns:
      (int): The smaller number among the two.
*/
int min(int alpha, int beta, move & bestMove, move it,int n)
{
  if(alpha<beta)
    return alpha;
  else if(alpha==beta && n==0)
    {
      float random = rand()/(RAND_MAX+1.0);
      if(random>=0.5)
	{
	   bestMove.row=it.row;
	   bestMove.column=it.column;
	   bestMove.whoChanges=it.whoChanges;
	   return beta;
	}
      else
	return alpha;
    }
  else
    {
      bestMove.row=it.row;
      bestMove.column=it.column;
      bestMove.whoChanges=it.whoChanges;
      return beta;
    }
}

/*
  This function implements the miniMax method. If exists
  a possible move it do the miniMax, else it only returns 
  the score. The control about change player or game over
  if don't have availabre move is in main(). It also 
  changes bestMove (by reference).

  Parameters:
      player: (int) who is playing now.
      numLevels: (int) number of levels of maxMin strategy.
      totalEmptyPlaces: (int) the board total empty places.
      bestMove: (move &) the best move that should be made.
      board: (int **) the game board.
      boardSize: (int) the size of the board

 Returns:
     (int): the score associated with the best move.
*/
int miniMax(int player, int numLevels,int totalEmptyPlaces, move & bestMove, int ** board, int boardSize, bool &jaFoi, int n)
{
  list<move> possibleMoves = returnMoves(player,board,boardSize);

  if(possibleMoves.empty())
    {
      player=-player;
      possibleMoves = returnMoves(player,board,boardSize);
      if(n==0)
	jaFoi=true;//Flag to change player in main program
    }

  int alpha,beta;
  int ** boardAux;
  move bestMoveAux;

  if(!possibleMoves.empty())//If there is any move avaible
    {
      if(totalEmptyPlaces==0 || numLevels==0)//On the limit of numLevels or the table.
	return score(board,boardSize);
      else if(player==-1)
	{
	  alpha=(boardSize*boardSize);//maximum score in game
	  for(list<move>::iterator it=possibleMoves.begin();it!=possibleMoves.end();it++){
	    boardAux=makeMove(player,*it,board,boardSize);
	    beta=miniMax(-player,numLevels-1,totalEmptyPlaces-1,bestMoveAux,boardAux,boardSize,jaFoi,n+1);//Recursive call
	    alpha=min(alpha,beta,bestMove,*it,n);	
	    deleteBoard(boardAux,boardSize);
	  }
	  return alpha;
	}
      
      else
	{
	  alpha=-(boardSize*boardSize);//minimum score in game
	  for(list<move>::iterator it=possibleMoves.begin();it!=possibleMoves.end();it++){
	    boardAux=makeMove(player,*it,board,boardSize);
	    beta=miniMax(-player,numLevels-1,totalEmptyPlaces-1,bestMoveAux,boardAux,boardSize,jaFoi,n+1);//Recursive call
	    alpha=max(alpha,beta,bestMove,*it,n);
	    deleteBoard(boardAux,boardSize);
	  }
	  return alpha;
	}
    }
  else //No possible moves, do nothing. 
    return score(board,boardSize);
}

int main(int argc, char * argv[])
{
  srand( time(NULL) );
  int boardSize, numLevels;
  
  ifstream infile("reversi.conf");
  infile >> boardSize;
  infile >> numLevels;
  infile.close();


  int player=-1,totalEmptyPlaces = ((boardSize*boardSize)-4); 
  int** board = initializeBoard(boardSize);
  move bestMove;
  bool gameOver=false;//Game Over flag.
  bool jaFoi=false;//Changed player flag.
  
  //output file
  ofstream saida;
  saida.open("game.txt");
  
  while(!gameOver)
    {
      jaFoi=false;
      //invalid board positions used
      //to know if exists a possible move 
      //in miniMax.
      bestMove.row=-1;
      bestMove.column=-1;
      bestMove.whoChanges.clear();
      

      miniMax(player,2*numLevels,totalEmptyPlaces,bestMove, board, boardSize, jaFoi, 0); 

      if(jaFoi)
	player=-player;
      
      if(bestMove.row!=-1 && bestMove.column!=-1)//Exist one possible move.
	{
	  int ** boardAux;
	  boardAux=board;
	  board=makeMove(player,bestMove,board,boardSize);
	  deleteBoard(boardAux,boardSize);


	  if(player==1)
	    {
	      //cout<<"white "<<bestMove.row<<" "<<bestMove.column<<endl;
	      saida<<"white "<<fabs(bestMove.row-boardSize+1)<<" "<<bestMove.column<<endl;
	    }
	  if(player==-1)
	    {
	      //cout<<"black "<<bestMove.row<<" "<<bestMove.column<<endl;
	      saida<<"black "<<fabs(bestMove.row-boardSize+1)<<" "<<bestMove.column<<endl;
	    }
	  player=-player;
	  totalEmptyPlaces--;
	}
      else
	gameOver=true;	      
	
            
      
      if(totalEmptyPlaces==0)
	gameOver=true;	  
	
    }

  saida.close();
  deleteBoard(board,boardSize);
  return 0;
}
