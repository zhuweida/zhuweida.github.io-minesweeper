
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
 

#define TRUE 0
#define FALSE 1


int height,width,NOM;
char board[50][50];
char game_board[50][50];
int lost = 0;
 

void display_welcome();
void build_board();
void build_gboard();
void create_mines();
void print_board();
void print_fullboard();
void start();
int play_game();
void play_again();
int check_win_game();
void check_for_mine(int, int);
int check_for_nearby_mines(int, int);
 
// Main function
int main ()
{
    display_welcome();
    printf("\nAny time you're ready... Just press ENTER. :)");
 
    // Get rid of welcome screen
    getchar();
    system("cls");

    printf("\nHeight:");
    
    scanf("%d", &height);
    printf("\nWidth:");
    scanf("%d", &width);
    printf("\nnumber of mine:");
    scanf("%d", &NOM);

    start();
    
 
    return 0;
 
}
 
/* Build board used for created random mines */
void build_board()
{
 
    int i, j;
 
    //--------------------------------
    // Assign char for board elements
    //--------------------------------
    for(i = 0; i <height; i++)
        for(j = 0; j < width; j++)
            board[i][j] = 'o';
 
    // Place mines in this board, it remains
    // hidden from user until the game has
    // finished.
    create_mines();
}
 
/* Build game board for user input */
void build_gboard()
{
 
    int i, j;
    int row, col, cur = 4;
    printf("Creating game board....\nReady..set..\nPLAY!\n\n");
    //----------------------------------------
    // Assign char 'o' for all board elements
    //----------------------------------------
    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++)
            game_board[i][j] = 'o';
     
    //--------------------------------
    // Print board
    //--------------------------------
    for(col = 0; col < width; col++)
        printf("%d ", col + 1);
     
    printf("\n\n");
 
    for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            printf("%c ", game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}
 
/* Create random places in the array for mines */
void create_mines()
{
    int i, random1,random2;
 

    srand(time(0));
     
    for (i = 0; i < NOM; i++)
    {
        random1 = random() % (height);
        random2 = random() % (width);
        if ( (board[random1][random2] != '*')){
            board[random1][random2] = '*';
        }
        else {
            i--;
            
        }
    }
    
 
}
 
/* Print the game board */
void print_board()
{
    int row, col;
 
    system("cls");
    for(col = 0; col < width; col++)
        printf("%d ", col + 1);
     
    printf("\n\n");
        for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            printf("%c ", game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}
 
/* Print the full board showing mines */
void print_fullboard()
{
    int row, col;
 
    system("cls");
    for(col = 0; col < width; col++)
        printf("%d ", col + 1);
     
    printf("\n\n");
        for(row = 0; row < height; row++)
    {
        for(col = 0; col < width; col++)
        {
            printf("%c ", board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}
 
/* Take user input for playing of the game */
int play_game()
{
    int r_selection = 0, c_selection = 0, 
        nearbymines = 0, nearbymines2 = 0,
        nearbymines3 = 0, nearbymines4 = 0,
        nearbymines5 = 0, nearbymines6 = 0,
        nearbymines7 = 0, nearbymines8 = 0,
        i = 0;
 


    do {
    printf("\nMake a selection (ie. row [ENTER] col): \n");
    printf("Row--> ");
    scanf("%d", &r_selection);
    printf("Col--> ");
    scanf("%d", &c_selection);
     
    } while(r_selection < 1 || r_selection > height || c_selection < 1 || r_selection > width);

 
    check_for_mine(r_selection - 1, c_selection - 1);
 
    if(lost == 1)
        return -1;
     
    // Checks for nearby mines at every direction from user
    // input location. Assigns that location the number
    // of mines found nearby, updating the board.
    nearbymines = check_for_nearby_mines(r_selection - 1, c_selection - 1);
    game_board[r_selection - 1][c_selection - 1] = (char)( ((int)'0') + nearbymines );
 
    //--------------------------------------------------
    // The following checks for mines nearby elements
    // in the array with no mines
    if(nearbymines == 0)
    {
        if(c_selection != width)
        {
            i = 0;
            while(nearbymines == 0 && (c_selection - 1 + i) < width)
            {
                // This is checking elements to the right
                nearbymines = check_for_nearby_mines(r_selection - 1, (c_selection - 1 + i));
                if(nearbymines != -1)
                {
                game_board[r_selection - 1][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines );
                i++;
                }
            }
                if(r_selection != 1)
                {
                    i = 0;
                    while(nearbymines5 == 0 && (c_selection - 1 + i) < width && (r_selection - 1 - i) > 0)
                    {

                        nearbymines5 = check_for_nearby_mines((r_selection - 1 - i), (c_selection - 1 + i));
                        if(nearbymines5 != -1)
                        {
                        game_board[(r_selection - 1) - i][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines5);
                        i++;
                        }
                    }
                }
                if(r_selection != height)
                {
                    i = 0;
                    while(nearbymines6 == 0 && (r_selection - 1 + i) < height && (c_selection - 1 + i) < width )
                    {

                        nearbymines6 = check_for_nearby_mines((r_selection - 1 + i), (c_selection - 1 + i));
                        if(nearbymines != -1)
                        {
                        game_board[(r_selection - 1) + i][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines6);
                        i++;
                        }
                    }
                }
        }
 
        if(r_selection != height)
        {
            i = 0;
            while(nearbymines2 == 0 && (r_selection - 1 + i) < height)
            {

                nearbymines2 = check_for_nearby_mines((r_selection - 1 + i), c_selection - 1);
                if(nearbymines2 != -1)
                {
                game_board[(r_selection - 1) + i][c_selection - 1] = (char) ( ((int)'0') + nearbymines2 );
                i++;
                }
            }
 
            if(c_selection != width)
            {
                i = 0;
                while(nearbymines7 == 0 && (r_selection - 1 + i) < height && (c_selection - 1 - i) > 0)
                {

                    nearbymines7 = check_for_nearby_mines((r_selection - 1 + i), (c_selection - 1 - i));
                    if(nearbymines != -1)
                    {
                    game_board[(r_selection - 1) + i][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines7);
                    i++;
                    }
                }
            }
        }
 
        if(r_selection != 1)
        {
            i = 0;
            while(nearbymines3 == 0 && (r_selection - i) > 0)
            {

                nearbymines3 = check_for_nearby_mines((r_selection - 1 - i), c_selection - 1);
                if(nearbymines3 != -1)
                {
                game_board[(r_selection - 1) - i][c_selection - 1] = (char) ( ((int)'0') + nearbymines3 );
                i++;
                }
            }
            if(c_selection != width)
            {
                while(nearbymines8 == 0 && (c_selection - 1 - i) > 0 && (r_selection - 1 - i) > 0)
                {

                    nearbymines8 = check_for_nearby_mines((r_selection - 1 - i), (c_selection - 1 - i));
                    if(nearbymines8 != -1)
                    {
                    game_board[(r_selection - 1) - i][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines8);
                    i++;
                    }
                }    
            }
        }
 
        if(c_selection != 1)
        {
            i = 0;
            while(nearbymines4 == 0 && (c_selection - i) > 0)
            {

                nearbymines4 = check_for_nearby_mines(r_selection - 1, (c_selection - 1 - i));
                if(nearbymines4 != -1)
                {
                game_board[r_selection - 1][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines4 );
                i++;
                }
            }
        }
    }
 
 
 
    // Handles a player winning.
    if(check_win_game() == TRUE)
    {
        system("cls");
        print_fullboard();
        printf("\n\nYou've won the game!! Congrats!!\n\n");
        play_again();
    }
 
    return 0;
}
 
/* Check whether user input has selected a mine */
void check_for_mine(int r_select, int c_select)
{
    if(board[r_select][c_select] == '*')
    {
        printf("\nYou've hit a mine! You lose!\n");
        getchar(); getchar();
        lost = 1;
    }
}
 

int check_for_nearby_mines(int r_select, int c_select)
{
    int nearby_mine_count = 0;
     
    if(board[r_select][c_select] == '*')
    {
        return -1;
    }

    if(r_select < (height - 1) && c_select < (width - 1))
    {

        if(board[r_select + 1][c_select] == '*')
            nearby_mine_count++;

        if(board[r_select][c_select + 1] == '*')
            nearby_mine_count++;

        if(board[r_select + 1][c_select + 1] == '*')
            nearby_mine_count++;
 

        if(c_select != 0)
        {
            if(board[r_select + 1][c_select - 1] == '*')
                nearby_mine_count++;

            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;
        }

        if(r_select != 0)
        {
     
            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;
          
            if(board[r_select - 1][c_select + 1] == '*')
                nearby_mine_count++;
   
            if(c_select != 0)
            {
            
                if(board[r_select - 1][c_select - 1] == '*')
                    nearby_mine_count++;
            }
        }
    }

    if(r_select == (height - 1) && c_select != (width - 1))
    {

            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;

            if(board[r_select - 1][c_select + 1] == '*')
                nearby_mine_count++;
    }
 
    if(c_select == (width - 1) && r_select != (height - 1))
    {
       
            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;
     
            if(board[r_select + 1][c_select - 1] == '*')
                nearby_mine_count++;
    }

    if(r_select == (height - 1) && c_select == (width - 1))
    {
       
            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;
      
            if(board[r_select - 1][c_select - 1] == '*')
                nearby_mine_count++;
 
            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;
    }
 
    return nearby_mine_count;
}
 
/* Check if user has won game */
int check_win_game()
{
    int row, col;
 
    for(row = 0; row < height; row++)
        for(col = 0; col < width; col++)
        {
            if(game_board[row][col] == 'o' && board[row][col] != '*')
                return FALSE;
        }
 
    return TRUE;
}
// Ask user if they wish to play again.
void play_again()
{
    char ans;
 
    printf("\n\nWould you like to play again? (y/n) --> ");
    scanf(" %c", &ans);
 
    if(toupper(ans) == 'Y')
    {
        system("cls");
        start();
    }
 
    else
    {
        printf("\n\nThanks for playing! Bye.");
        (void) getchar();
        exit(EXIT_SUCCESS);
    }
}

void display_welcome()
{
    puts("-----------------------Welcome to Minesweeper!---------------------------");

}
 
void start()
{
    lost = 0;    
    build_board();
    build_gboard();
     
    // Start playing game
    do
    {
    play_game();
    print_board();
    } while(lost != 1);   
 
    // Once user is lost, print the board with all the mines.
    print_fullboard();
 
    // Play again?
    play_again();
}