#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#define MAXR 15
#define MAXS 41

bool gameOver;
int brojac = 0;

char aVojkoVNemoze;
int snakeR = MAXR/2 - 1;
int snakeS = MAXS/2;
int foodR, foodS;
int tailR[1000], tailS[1000];
int numTail = 1;
int score = 0;
int FoodIsEaten = 0;

enum eDirection{ STOP = 1, LEFT, RIGHT, UP, DOWN};
enum eDirection direction;

void input( char **mat);
void logic( char **mat);
char **draw( char **mat);


int main()
{
    int i, j;
    char **mat;

    mat = (char**)calloc(MAXR, sizeof(char*));
    for( i = 0; i < MAXR; i++)
        mat[i] = (char*)calloc(MAXS, sizeof(char));

        system("cls");

while( !gameOver ){
    printf("\r\t\tScore: %d", score);
    input( mat );
    logic( mat );
    if( gameOver ){
        system("color 4");
    }
    draw( mat );
    for( i = 0; i < MAXR; i++){
        for( j = 0; j < MAXS; j++){
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }
}

    //draw( mat );

    return 0;
}

void input( char **mat )
{
    int i, j;
    char cmd;

    if( _kbhit()){
        switch( _getch() ){
            case 72:{
                if( aVojkoVNemoze != 'D'){
                    direction = UP;
                    aVojkoVNemoze = 'U';
                }
                break;
            }
            case 80:{
                if( aVojkoVNemoze != 'U'){
                    direction = DOWN;
                    aVojkoVNemoze = 'D';
                }
                break;
            }
            case 75:{
                if( aVojkoVNemoze != 'R'){
                    direction = LEFT;
                    aVojkoVNemoze = 'L';
                }
                break;
            }
            case 77:{
                if( aVojkoVNemoze != 'L'){
                    direction = RIGHT;
                    aVojkoVNemoze = 'R';
                }
                break;
            }
        }
    }

}


void logic( char **mat)
{
    int i;
    int tmpR = snakeR;
    int tmpS = snakeS;
    int tmp2R, tmp2S;

    usleep(100000);
    for( i = 1; i < numTail; i++){
        tmp2R = tailR[i];
        tmp2S = tailS[i];
        tailR[i] = tmpR;
        tailS[i] = tmpS;
        tmpR = tmp2R;
        tmpS = tmp2S;
    }

switch( direction ){
    case UP:{
        snakeR--;
        usleep(1000);
        break;
    }
    case DOWN:{
        snakeR++;
        usleep(1000);
        break;
    }
    case LEFT:{
        snakeS--;
        break;
    }
    case RIGHT:{
        snakeS++;
        break;
    }
}

for( i = 1; i < numTail; i++){
        if( snakeR == tailR[i] && snakeS == tailS[i] )
            gameOver = true;
    }

///Odkomnetiraj ako zelis da te rubovi ube...

    if( snakeR == 0 ){
        gameOver = true;
        snakeR = 1;
    }

    if( snakeR == MAXR - 1 ){
        gameOver = true;
        snakeR = MAXR - 2;
    }

    if( snakeS == 0 ){
        gameOver = true;
        snakeS = 1;
    }

    if( snakeS == MAXS - 1 ){
        gameOver = true;
        snakeS = MAXS - 2;
    }

///Zakomnetiraj ako zelis da te rubovi ube...
/*
    if( snakeR == 0 ){
        snakeR = MAXR - 2;
    }

    if( snakeR == MAXR - 1 ){
        snakeR = 0;
    }

    if( snakeS == 0 ){
        snakeS = MAXS - 2;
    }

    if( snakeS == MAXS - 1 ){
        snakeS = 0;
    }
*/
}


char **draw( char **mat )
{
    int i, j, k;
    srand(time(NULL));

    system("cls");

    for( i = 0; i < MAXR; i++){
        for( j = 0; j < MAXS; j++){
            for( k = 0; k < numTail; k++){
                mat[tailR[k]][tailS[k]] = 'o';
            }
            if( j == 0 || j == MAXS - 1 ){
                mat[i][j] = 186;
            }
            else if( i == 0 || i == MAXR - 1){
                mat[i][j] = 205;
            }
            else
                mat[i][j] = 32;
        }
    }
/*
    if( snakeR >= MAXR - 2 )
        snakeR = MAXR - 2;
    if( snakeS >= MAXS - 2)
        snakeS = MAXS - 2;
    if( snakeR <= 1)
        snakeR = 1;
    if( snakeS <= 1)
        snakeS = 1;
*/
    if( (snakeR == foodR && snakeS == foodS) || (!brojac)){
        FoodIsEaten = 1;
        if( snakeR == foodR && snakeS == foodS){
            numTail++;
            score++;
        }
        foodR = 2 + rand() % (MAXR - 3);
        foodS = 2 + rand() % (MAXS - 3);
    }

    mat[foodR][foodS] = 145;
    mat[MAXR - 1][MAXS - 1] = 188;
    mat[MAXR - 1][0] = 200;
    mat[0][0] = 201;
    mat[0][MAXS - 1] = 187;
    mat[snakeR][snakeS] = 'O';

    brojac++;

    return mat;

}
