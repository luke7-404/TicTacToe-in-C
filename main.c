// Included Files
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Preconditions
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';


// Declaration For Functions
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);


int main(){

    char winner = ' '; // Undecided winner

    resetBoard(); // Function call which outputs a new game board

    // While there is no winner and are free spaces
    while(winner == ' ' && checkFreeSpaces() != 0){

        printBoard(); // print the board

        playerMove(); // Calls to get the player's move

        // calls the check winner function and gives the win-state to the winner variable 
        winner = checkWinner(); 

        // Checks if there is a winner or if there are no unused spaces left and if true breaks out of the while loop
        if (winner != ' ' || checkFreeSpaces() == 0){
            break;
        }

        computerMove(); // Calls to get the computer's move

        // calls the check winner function and gives the win-state to the winner variable 
        winner = checkWinner(); 

        // Checks if there is a winner or if there are no unused spaces left and if true breaks out of the while loop
        if (winner != ' ' || checkFreeSpaces() == 0){
            break;
        }
    }
    
    printBoard();
    printWinner(winner);
    

    return 0;
}



//This function resets a game board with empty spaces (' ') as initial values
void resetBoard(){
    
    //Looping through the rows of the board
    for (int i = 0; i < 3; i++)
    {
        //Looping through the columns of the board
        for (int j = 0; j < 3; j++)
        {
            //Set each element of the board to an empty space
            board[i][j] = ' ';
        }
    }
}



// This function prints the current state of a game board
void printBoard(){

    // 1st Row
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");

    // 2nd Row
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");

    // 3rd Row
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}



// This function checks the number of empty spaces left on the 3x3 board
int checkFreeSpaces(){
    // Initialize 'freeSpace' variable to 9, as that is the total number of spaces
    int freeSpace = 9;

    // Nested loop iterates through each element of the 3x3 'board' char array.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // If an element is not equal to a blank space character, decrement 'freeSpace'.
            if(board[i][j] != ' '){
                freeSpace--;
            }
        }
        
    }
    // Return the final count of free spaces remaining on the board.
    return freeSpace;
}


// This function allows the player to make a move on the board
void playerMove(){
    int x, y; // Declare x and y positions
    
    // Ask the player where they want to place their move as long as the square is not already occupied.
    do{
        printf("Enter Row Number 1-3: ");
        scanf("%d", &x);
        x--;

        printf("Enter Column Number 1-3: ");
        scanf("%d", &y);
        y--;

        // Check if the selected square is already occupied by a player's piece
        if(board[x][y] != ' '){
            printf("Occupied Square\n");
        }
        // Otherwise, set the selected location on the board
        else{
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
    
}


void computerMove(){

    // Generate a random number, a seed, based on the time
    srand(time(0));
    int x, y;

    if(checkFreeSpaces() > 0){
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        
        board[x][y] = COMPUTER;
    } else{
        printWinner(' ');
    }
}


// This function checks if there is a winner
char checkWinner(){

    // The if statements check if all three squares 
    // in a row are the same, return the symbol
    
    // Check Rows
    for (int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }
    
    // Check Columns
    for (int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];
        }
    }

    // Check Diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){

        return board[0][0];
        
    } else if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){

        return board[0][2];

    } else{

        // If no winner has been found, return an empty space (' ').
        return ' ';
    }
}



void printWinner(char winner){

    if (winner == PLAYER){
        printf("YOU WIN!");
    } else if (winner == COMPUTER){
        printf("YOU LOSE!");
    }else{
        printf("DRAW");
    }
}