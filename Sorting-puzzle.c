#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 4
#define COL 4

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
    
    printf("Move 0 using W,S,A,D and press X to quit\n");
    return getch();
}

void main(){
    
    printf("Welcome to the game..\n");
    int matrix[ROW][COL];

    setMatrix(matrix);
    int m = ROW-1, n = COL-1, win = 0;
    displayMatrix(matrix, m, n);
    
    char choice;
    int moves = 0;

    for ( choice = menu(); choice != 'x'; choice = menu())
    {
        switch (choice)
        {
            case 'w':
                if(m-1 >= 0){
                    swap(matrix, m, n, m-1, n);
                    m--;
                    moves++;
                }
                break;
            case 's':
                if(m+1 < ROW){
                    swap(matrix, m, n, m+1, n);
                    m++;
                    moves++;
                }
                break;
            case 'a':
                if(n-1 >= 0){
                    swap(matrix, m, n, m, n-1);
                    n--;
                    moves++;
                }                
                break;
            case 'd':
                if(n+1 < COL){
                    swap(matrix, m, n, m, n+1);
                    n++;
                    moves++;
                }
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
        system("cls");
        printf("Total moves : %d\n", moves);
        displayMatrix(matrix, m, n);
        if(checkMatrix(matrix)){
            printf("Success!!!!!!!!!!\n");
            printf("You completed the game with %d moves", moves);
            win = 1;
            break;
        }
        
    }
    

}