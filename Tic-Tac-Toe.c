
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int, int, int);
int isBoardFull(char [N][N]);
void createInitialBoard(char [N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int computerPlaysToWin(char [N][N], int * , int * );
void computerPlaysRandom(int * , int * , int , int );
void sumAllDimensions(char [N][N], int [N], int [N], int *, int *);
int memberOf(int , int [N]);
int computerPlaysToBlock(char [N][N], int * , int * );//I did the Bonus function 


int main()// given main
{

    int userRow, userCol, computerRow, computerCol;
    int taken;
    char board[N][N];
    char winner = 'N';
   
    srand(time(NULL));
    
    printf("This tic-tac-toe board is of size %d by %d\n", N, N);
   
    printf("Player symbol: X \nComputer symbol: O\n\n");

    printf("Here is the board - spaces are indicated by a ?\n");

    createInitialBoard(board);			// create a 3 X 3 board with '?' in each cell 
   
    while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
    {	   
	    taken = 0;
	   
		while (!(taken))                  // loop used to accept valid row and col values from the user
		{
	        readUserMove(&userRow, &userCol);                  //get user's move
			printf("You chose row %d and column %d \n", userRow, userCol);
			
			while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
			{
				printf("That's is an invalid row or column number - try again\n");
				readUserMove(&userRow, &userCol);
				printf("You chose row %d and column %d \n", userRow, userCol);
			}
				   
			if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
			{
				board[userRow-1][userCol-1] = 'X';			// store an X there
				taken = 1;
			}
			else
			{
				taken = 0;									// otherwise inform the user to enter values again
				printf("That spot is taken - please try another one\n");
			}
			
		} //end of while (!taken)
	
	   if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
	   {
		   printf("Congrats - you won against the computer :)\n");
		   winner = 'Y';
	   }
	   
	   else  if (!(isBoardFull(board)))            //check if the board is already full
	   {
		   taken = 0;
		   
		   while (!(taken))
		   {
				getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col
		   
				if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
				{
					board[computerRow][computerCol] = 'O';
					taken = 1;
	
				}
				else
				{
					taken = 0;		//That spot is taken - computer - try another one
				}	
		   }
		   
		   printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
		   
		   if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
		   {
			   printf("Oh the computer won this time :(( think hard next time\n");
			   winner = 'Y';
		   }  
	   }
	 
	   printCurrentBoard(board);  
	
	   printf("\nPress enter to continue \n");             
	   getchar();
		   
    } //end of while
   
    if (winner != 'Y')
    {
        printf("Game was a tie - no winner!\n\n");
    }
			
		
   return 0;
}

int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol)
{
/* 
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

   int winningSpot = 0;
   int blocked = 1;            //this declaration is required if you attempt the bonus part
   
   winningSpot = computerPlaysToWin(board, computerRow, computerCol);
   
   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user 
   {
	   computerPlaysRandom(computerRow, computerCol, userRow, userCol);
	   
	   /*
	   If you attempt the bonus part, then uncomment the code below and use it to first try and block user move
	   If unsuccessful, then it pick row and col (pseudo) randomly
	   */
	   
	   blocked = computerPlaysToBlock(board, computerRow, computerCol);
	   if (blocked == 0)
		   computerPlaysRandom(computerRow, computerCol, userRow, userCol);
	     
   }
 
   return winningSpot;
}

void createInitialBoard (char board [N][N]) //function that creates the first initial board with ? on each block 
{

    for(int i=0;i<N;i++)//for loop for the rows 
    {
        for(int j=0;j<N;j++)// for loops for the columns 
        {
            board[i][j]='?';

            printf(" %c",board[i][j]);
            if(j<2)
            {
                printf(" |");
            } 
        }
        if(i<2)
        {
            printf("\n------------\n");
        }
      
    }

}

void printCurrentBoard (char board [N][N]) //This function prints the current board each time the computer or user do a move (updated)
{
    printf("\nCurrent board now is:\n\n");
    for(int i=0;i<N;i++)//for loop for rows
    {
        for(int j=0;j<N;j++)// for loop for columns 
        {
            printf(" %c",board[i][j]);
            if(j<2) 
            {
                printf(" |");
            }
            
        }
        if(i<2)
        {
            printf("\n------------\n");
        }
        
    }

    printf("\n");
}


int isBoardFull (char board [N][N]) // This function checks each place if it is full or not by acessing ecah row and column  
{
    int count=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(board[i][j] =='?')
            count++;
        }   
    }

    if(count == 0)//if the board is full
    {
        return 1;
    }
    
    else
    {
        return 0;
    }
}


void readUserMove (int *userRow, int *userCol) // This function scan's the user's position of placing his 'X' as the number of row and column 
{
    printf("\n\nYour move  - enter numbers between 1 and 3\n\n");
    printf("Enter row number: ");
    scanf("%d", userRow);
    printf("Enter column number: ");
    scanf("%d",userCol);
    printf("\n");
}


int isInputValid (int entered, int minimum, int maximum)// checks if the user input is valid as there is only 3 rows and 3 columns 
{  
    minimum=1;//the minimun input is number 1
    maximum=3;//the maximum input is number 3

    if(entered >=minimum && entered <=maximum)
    {
        return 1;
    } 
    else
    {
        return 0;
    }
}


int memberOf (int aNum, int someArray [N]) //this function returns 1 if the value exist in the given array 
{
    int found=0;
    for(int i=0;i<N;i++)
    {
        if(aNum == someArray[i])
        {
            found=1;
        }
      
    }

    return found;
}


int gameWon (char board [N][N], char symbol)// Uses the function of sumAllDimensions to check who win (either the computer or the user)
{
    int sumLD=0;
    int sumRD=0;
    int Rscore=0;
    int Cscore=0; 
    int sumR[N] ;
    int sumC[N] ;

    sumAllDimensions ( board,  sumR,  sumC,  &sumLD, &sumRD);

    if(symbol=='X')
    { 
     
       for(int i=0;i<N;i++)
       {
           Rscore += sumR[i];
           Cscore += sumC[i];
        }

        if(Rscore==3 || Cscore==3 ||sumLD==3 || sumRD==3)
        {
            return 1;
        }
         
    }
    else if (symbol=='O')
    { 

        for(int i=0;i<N;i++)
        {
            Rscore +=sumR[i];
            Cscore +=sumC[i];
        }
        if(Rscore==12 || Cscore==12 ||sumLD==12 || sumRD==12)
        {
             return 1;
        }
        
    }

    printf("\n");
    return 0;
}


int computerPlaysToWin (char board [N][N], int * cRow, int * cCol)// if there is 2 O's next to each other next to each other across, down or diagnoally the computer places it in the next position to win
{
    int score=0;

    for(int i=0;i<N;i++)
    {
        score=0;
    
        for(int j=0;j<N;j++)
        {

           if(board[i][j]=='?') 
            {
                *cRow = i;
                *cCol = j; 
                score = score+0;      
            }   
            else if(board[i][j]=='O') //across
            { 
                score = score+4;  
            } 
            else if(board[i][j]=='X') //across
            { 
                score = score+1;  
            } 
            if(j==2)
            {
                if(score == 8 )
                {
                    return 1;
                }
              
            }
         
        }

    
        score=0;
    
        for(int j=0;j<N;j++) // down the column 
        {   
            if(board[j][i]=='?') 
            {
                *cRow=j;
                *cCol=i; 
                score= score+0;      
            }   
            else if(board[j][i]=='O') 
            { 
                score= score+4;  
            } 
            else if(board[j][i]=='X') 
            { 
                score= score+1;  
            } 
            if(j==2)
            {
                if(score == 8 )
                {
                    return 1;
                }
              
            }         
        }
    }

     
    score=0;
    
    for(int i=0;i<N;i++)// left diagonal
    {
    
        if(board[i][i]=='?') 
        {
            *cRow =i;
            *cCol =i;
            score= score+0;      
        }   
        else if(board[i][i]=='O') 
        { 
            score= score+4; 
        }
        else if(board[i][i]=='X') 
        { 
            score= score+1; 
        } 

        if(i==2)
        {
            if(score == 8)
            return 1;
        }
   
    }

 
    score=0;
 
    for(int i=0;i<N;i++)// right diagonal
    {    
  
        for(int j=0;j<N;j++)
        {
  
            if ((i+j)==(N-1))
            {

                if(board[i][j]=='?') 
                {
                    *cRow=i;
                    *cCol=j;
                    score=score+0;      
                }   
                else if(board[i][j]=='O') 
                { 
                    score=score+4;  
                } 
                else if(board[i][j]=='X') 
                { 
                    score=score+1;  
                } 
        
            }     
        }

        if(i==2)
        {
            if(score == 8 )
            {
              return 1;
            }
        }
    }

    return 0;

}



void computerPlaysRandom (int * cRow, int * cCol, int uRow, int uCol)// generates random position for the computer to place his 'O'
{
    int tRow=0;
    int tCol=0;
    if((uRow+uCol)%(2)==0)
    {
        if(uRow==0 && uCol==0)
        {
            do 
            {
                tRow = rand() %3;
                tCol=rand()%3;
            } 
            while ((tRow==1 && tCol==2) || (tRow==2 && tCol==1) );

        }
        else if(uRow==0 && uCol==2)
        {
            do 
            {
                tRow = rand() %3;
                tCol=rand()%3;
            } 
            while ((tRow==1 && tCol==0) || (tRow==2 && tCol==1));
        }
        else if(uRow==2 && uCol==0)
        {
            do 
            {
                tRow = rand() %3;
                tCol=rand()%3;
            } 
            while ((tRow==0 && tCol==1) || (tRow==1 && tCol==2) );
        }
        else if(uRow==2 && uCol==2){
        do 
        {
            tRow = rand() %3;
            tCol=rand()%3;
        } 
        while ((tRow==0 && tCol==1) || (tRow==1 && tCol==0) );

    }

    else if(uRow==1 && uCol==1)
    {      
        tRow = rand() %3;
        tCol=rand()%3;
    
    }
    }
    else 
    {
        if(uRow==0 && uCol==1)
        {
            do 
            {
                tRow = rand() %3;
                tCol=rand()%3;
            } 
            while ((tRow==1 && tCol==0) || (tRow==2 && tCol==0) || (tRow==1 && tCol==2) || (tRow==2 && tCol==2));

        }
        else if(uRow==1 && uCol==0)
        {
            do 
            {
                tRow = rand() %3;
                tCol=rand()%3;
            } 
            while ((tRow==0 && tCol==1) || (tRow==0 && tCol==2) || (tRow==2 && tCol==1) || (tRow==2 && tCol==2));

        }
        else if(uRow==2 && uCol==1)
        {
        do 
        {
            tRow = rand() %3;
            tCol=rand()%3;
        } 
        while ((tRow==0 && tCol==0) || (tRow==1 && tCol==0) || (tRow==0 && tCol==2) || (tRow==1 && tCol==2));
    }
    
    else if(uRow==1 && uCol==2)
    {
       do 
       {
            tRow = rand() %3;
            tCol=rand()%3;
        } 
        while ((tRow==0 && tCol==0) || (tRow==0 && tCol==1) || (tRow==2 && tCol==0) || (tRow==2 && tCol==1));
    }
    }

    *cRow=tRow;
    *cCol=tCol;
}



int computerPlaysToBlock (char board[N][N], int * cRow, int * cCol)//checks if the user has 2 X's next to each other either across, down or diagonally so that he places the 'O' to block and not allow the user to win 
{
 
    int score=0;
  
    for(int i=0;i<N;i++)
    {
        score=0;
     
        for(int j=0;j<N;j++)  //across
        {
     
            if(board[i][j]=='?') 
            {
                *cRow = i;
                *cCol = j; 
                score = score+0;    
            }   
            else if(board[i][j]=='X') 
            { 
                score = score+1;  
            } 
            else if(board[i][j]=='O') 
            { 
                score = score+4;  
            } 

            if(j==2)
            {
                if(score == 2 )
                {
                    return 1;
                }
              
            }
         
        }
   
        score=0;
    
        for(int j=0;j<N;j++) // down
        {   
      
            if(board[j][i]=='?') 
            {
                *cRow=j;
                *cCol=i; 
                score= score+0;      
            }   
            else if(board[j][i]=='X') 
            { 
                score= score+1;  
            } 
            else if(board[j][i]=='O') 
            { 
                score= score+4;  
            } 
            if(j==2)
            {
                if(score == 2 )
                {
                    return 1;
                }
              
            }         
        }
    }

     
    score=0;
    
    for(int i=0;i<N;i++)// left diagonal
    {
    
        if(board[i][i]=='?') 
        {
            *cRow =i;
            *cCol =i;
            score=score+0;      
        }   
        else if(board[i][i]=='X')
        { 
            score= score+1; 
        }
        else if(board[i][i]=='O')
        {
            score=score+4;
        }  

        if(i==2)
        {
            if(score == 2 )
            {
                return 1;
            }
        }  
    }

    score=0;
   
    for(int i=0;i<N;i++)// right diagonal
    {    
  
        for(int j=0;j<N;j++)
        {
  
            if ((i+j)==(N-1))
            {
                if(board[i][j]=='?') 
                {
                    *cRow=i;
                    *cCol=j;
                    score=score+0;  
                }   
                else if(board[i][j]=='X') 
                { 
                    score=score+1;  
                }
                else if(board[i][j]=='O')
                {
                    score=score+4;
                } 
            }        
        }

        if(i==2)
        {
            if(score == 2 )
            {
                return 1;
            }
        }
    }
    return 0;
}



void sumAllDimensions (char board [N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRD)//calculates the score each time the computer or user plays to check if someone won
{
    int score=0;   
    for(int i=0;i<N;i++)
    {
        score=0;
        for(int j=0;j<N;j++) //cross
        {
            if(board[i][j]=='X')
            {
                score = score+1;
                sumR[j]=1;          
            }
              
            else if(board[i][j]=='O')
            {

                score = score+4;
                sumR[j]=4;
            }
            else 
            {

                score = score+0;
                sumR[j]=0;
            }    
        }
        if(score==3 || score==12)
        {
            break;
        }

        score=0;
        for(int j=0;j<N;j++) //down
        {
           
            if(board[j][i]=='X')
            {
                score = score+1;
                sumC[j]=1;
            }

            else if(board[j][i]=='O')
            {
                score = score+4;
                sumC[j]=4;
            }   
            else 
            {

                score = score+0;
                sumC[j]=0;
            }   
        }

        if(score==3 || score==12)
        {
            break;
        }
    }
     

    score=0;
    for(int i=0;i<N;i++)// left diagonal
    {
        if(board[i][i]=='X')
        {
            score = score+1;
        }

        else  if(board[i][i]=='O')
        {
            score = score+4;
        }
        else 
        {
            score = score+0;                
        }   

         
    
        if(i==2)
        {
            *sumLD=score;
        }  
    }

    
        score=0;
        for(int i=0;i<N;i++)// right diagonal
        {
     
            for(int j=0;j<N;j++)
            {
  
                if ((i+j)==(N-1))
                {
          
                    if(board[i][j]=='X')
                    {

                        score = score+1;
                    }
 
                    else if(board[i][j]=='O')
                    {
                        score = score+4;
                    }
            
                    else
                    {
                        score = score+0;
                    }
         
                }       
            }

            
            if(i==2)
            {
                *sumRD=score;
            }
            } 

        }

