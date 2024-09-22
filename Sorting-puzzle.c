#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define ROW 4
#define COL 4

int numOfScores;

int checkRepeat(int val, int mat[ROW][COL]){
    
    if(val == 0){
        return 1;
    }
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if(mat[i][j] == val){
                return 1;
            }
        }
    }
    return 0;
}

void displayMatrix(int mat[ROW][COL], int m, int n){
    
    for (int i = 0; i < ROW; i++)
    {   
        int flag = 1;
        for (int j = 0; j < COL; j++)
        {   
            if(i == m && j == n){
                printf("[%d]\t", mat[i][j]);
            }else{
            printf("%d\t", mat[i][j]);
            }
        }
        // printf("\n");
        if(flag) printf("\n");
    }
    
}

void setMatrix(int mat[ROW][COL]){
    
    srand(time(NULL));
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {   
            int val;
            if(i == ROW-1 && j == COL -1){
                break;
            }
            do{
                val = rand() % (ROW * COL);
            }while(checkRepeat(val, mat));
            mat[i][j] = val;
        }
        
    }
    mat[ROW -1][COL -1] = 0; 
    
}

void swap(int matrix[ROW][COL], int m, int n, int p, int q){

    // if(p < 0 || q < 0 || p > (ROW-1) || q > (COL-1)){
    //     printf("Invalid move..........\n");
    // }else{

        matrix[m][n] = matrix[p][q];
        matrix[p][q] = 0;
    // }

}

int checkMatrix(int matrix[ROW][COL]){
    
    int val = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if(matrix[i][j] < val){
                if(i == ROW-1 && j == COL-1 && matrix[i][j] == 0) return 1;
                return 0;
            }
            val = matrix[i][j];
        }
    }
    return 0;
}

char menu(){
    
    printf("Move [0] using arrow key and press esc to quit\n");
    return getch();
}

// void readScorecard(FILE *saveFile, int scorecard[5], char highscorers[5][15]){
int readScorecard(int scorecard[5], char highscorers[5][15]){

    FILE *saveFile;
    saveFile = fopen("scorecard", "r");
    if(saveFile == NULL)
        return -1;
    int i = 0;
    char value[100];
    while(fgets(value, 100, saveFile)){
        sscanf(value, "%s %d", highscorers[i], &scorecard[i]);
        i++;
    }
    fclose(saveFile);
    return i;
}

void sortScorecard(int scorecard[5], char highscorers[5][15], int n){

    for(int i = 0; i<n-1;i++){
        for (int j = i+1; j < n; j++){

            if(scorecard[i] > scorecard[j]){
                char tempName[15];
                int tempScore;

                tempScore = scorecard[i];
                strcpy(tempName, highscorers[i]);

                scorecard[i] = scorecard[j];
                strcpy(highscorers[i], highscorers[j]);
                
                scorecard[j] = tempScore;
                strcpy(highscorers[j], tempName);
            }
        }
        
    }
}

void game(int scorecard[5], char highscorers[5][15], int numOfScores){

    int matrix[ROW][COL];

    setMatrix(matrix);
    int m = ROW-1, n = COL-1, win = 0;
    displayMatrix(matrix, m, n);
    
    char choice;
    int moves = 0;

    for ( choice = menu(); choice != 27; choice = menu()) //27 is esc
    {   
        switch (choice)
        {
            case 72:  // up arrow
                if(m-1 >= 0){
                    swap(matrix, m, n, m-1, n);
                    m--;
                    moves++;
                }
                break;
            case 80:  // down arrow
                if(m+1 < ROW){
                    swap(matrix, m, n, m+1, n);
                    m++;
                    moves++;
                }
                break;
            case 75:  // left arrow
                if(n-1 >= 0){
                    swap(matrix, m, n, m, n-1);
                    n--;
                    moves++;
                }                
                break;
            case 77:  // right arrow
                if(n+1 < COL){
                    swap(matrix, m, n, m, n+1);
                    n++;
                    moves++;
                }
                break;
            default:
                break;
        }
        system("cls");
        printf("Total moves : %d\n", moves);
        displayMatrix(matrix, m, n);
        if(checkMatrix(matrix)){
            printf("Success!!!!!!!!!!\n");
            printf("You completed the game with %d moves\n", moves);
            win = 1;
            break;
        }
        
    }
    if(win){
        char name[15];
        printf("Enter your name:\n");
        scanf("%s", name);
        FILE *saveFile;
        if(numOfScores == -1){     
            
            saveFile = fopen("scorecard", "a");
            fprintf(saveFile, "%s %d", name, moves);
            fclose(saveFile);
        }else if(numOfScores < 5){

            scorecard[numOfScores] = moves;
            strcpy(highscorers[numOfScores++], name);
            sortScorecard(scorecard, highscorers, numOfScores);
            printf("num %d", numOfScores);
            FILE *saveFile;
            saveFile = fopen("scorecard", "w");

            for(int i = 0; i<numOfScores; i++){
                fprintf(saveFile, "%s %d\n", highscorers[i], scorecard[i]);
            }
            fclose(saveFile);
        }else if(moves < scorecard[4]){

            scorecard[numOfScores] = moves;
            strcpy(highscorers[numOfScores], name);
            sortScorecard(scorecard, highscorers, numOfScores);

            FILE *saveFile;
            saveFile = fopen("scorecard", "w");

            for(int i = 0; i<numOfScores; i++){
                fprintf(saveFile, "%s %d\n", highscorers[i], scorecard[i]);
            }
            fclose(saveFile);
        }else{
            printf("Sorry you cannot enter the hall of fames!\n");
        }

    }
    
    getch();
    printf("Enter any key to exit.");

}
void viewScorecard(int scorecard[5], char highscorers[5][15], int numOfScores){

    printf("Score card!\n\n");
    printf("Name\tHighscore\n");
    for (int  i = 0; i <numOfScores; i++)
    {
        printf("%s\t%d\n", highscorers[i], scorecard[i]);
    }
    printf("Enter any key to go back\n");
    getch();
}


void main(){

    printf("G A M E !!!\n\n\n");
    char highscorers[5][15];
    int scorecard[5];
    // printf("[");
    // for(int i = 0; i< 100; i++){
    //     printf("#");
    // }
    // printf("]");

    while(1){
        int numOfScores = readScorecard(scorecard, highscorers);
        system("cls");
        printf("Enter choice\n");
        printf("1.Start the game\n2.View Scorecard\n3.Exit\n");
        char ch = getch();
        switch (ch)
        {
        case '1':
            system("cls");
            game(scorecard, highscorers, numOfScores);
            break;
        case '2':
            viewScorecard(scorecard, highscorers, numOfScores);
            break;
        case '3':
            exit(0);
        }
    }
}
