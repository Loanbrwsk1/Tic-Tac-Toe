#include <stdio.h>

#define LENGHT 3
#define O_PLAYER "\x1b[34;1mO\x1b[0m"
#define X_PLAYER "\x1b[31;1mX\x1b[0m"

/*
? Player O : 1
? Player X : -1
*/

void printGame(int game[LENGHT][LENGHT])
{
    int i, j;

    printf("\x1b[1;1H\x1b[2J");
    fflush(stdout);

    printf("   ");
    for(j = 1 ; j <= LENGHT ; j++)
        printf(" %d  ", j);
    printf("\n");

    for(i = 0 ; i < LENGHT ; i++){
        printf("  ");

        for(j = 0 ; j < LENGHT ; j++)
            printf("+---");
        printf("+\n%d ", i + 1);

        for(j = 0 ; j < LENGHT ; j++){
            if(game[i][j] == 1)
                printf("| %s ", O_PLAYER);
            else if(game[i][j] == -1)
                printf("| %s ", X_PLAYER);
            else
                printf("|   ");
        }
        printf("|\n");
    }
    printf("  ");
    for(j = 0 ; j < LENGHT ; j++)
        printf("+---");
    printf("+\n");
}

void game(void)
{
    if(LENGHT < 2){
        printf("\x1b[31;1mThe size of the grid must be greater than or equal to 2 !\x1b[0m\n");
        return;
    }

    int game[LENGHT][LENGHT] = {{0}}, player = 1, row, column, is_occuped = 0, row_sum = 0, column_sum = 0, diago1_sum = 0, diago2_sum = 0, i, round = 0;

    printGame(game);

    while(1){
        player == 1 ? printf("Player %s turn\n", O_PLAYER) : printf("Player %s turn\n", X_PLAYER);
        printf("Row : ");
        scanf("%d", &row);
        printf("Column : ");
        scanf("%d", &column);
        row--;
        column--;
        is_occuped = 0;

        if(row < 0 || row > LENGHT - 1 || column < 0 || column > LENGHT - 1){
            is_occuped = 1;
            printGame(game);
            printf("\x1b[31;1mPlace not in the grid !\x1b[0m\n");
        }

        if(game[row][column] != 0){
            is_occuped = 1;
            printGame(game);
            player == 1 ? printf("\x1b[33;1mPlace already use by player %s \x1b[33;1m!\x1b[0m\n", X_PLAYER) : printf("\x1b[33;1mPlace already use by player %s \x1b[33;1m!\x1b[0m\n", O_PLAYER);
        }
        
        if(!is_occuped){
            round++;
            game[row][column] = player;
            printGame(game);

            for(i = 0 ; i < LENGHT ; i++)
                row_sum += game[row][i];
            for(i = 0 ; i < LENGHT ; i++)
                column_sum += game[i][column];
            for(i = 0 ; i < LENGHT ; i++)
                diago1_sum += game[2 - i][0 + i];
            for(i = 0 ; i < LENGHT ; i++)
                diago2_sum += game[0 + i][0 + i];

            if (row_sum == LENGHT || row_sum == -LENGHT || column_sum == LENGHT || column_sum == -LENGHT || diago1_sum == LENGHT || diago1_sum == -LENGHT || diago2_sum == LENGHT || diago2_sum == -LENGHT){
                player == 1 ? printf("\x1b[32;1mPlayer %s\x1b[32;1m wins !\x1b[0m\n", O_PLAYER) : printf("\x1b[32;1mPlayer %s\x1b[32;1m wins !\x1b[0m\n", X_PLAYER);
                break;
            }

            if(round == LENGHT * LENGHT){
                printf("\x1b[32;1mGame is finished ! Nobody wins !\x1b[0m\n");
                break;
            }

            row_sum = 0;
            column_sum = 0;
            diago1_sum = 0;
            diago2_sum = 0;
            player *= -1;
        }
    }
}

int main(void)
{
    game();
    return 0;
}