#include <stdio.h>

#define WATERLEVEL 128 /*the maximum water level*/
#define MAXSIZE 512 /*array size*/

typedef struct 
{
    int step; /*the variable that holds the steps*/
    int value; /* the variable that holds the value*/
}
island; 

island terraindata[MAXSIZE][MAXSIZE];

void move_on_island(island terraindata[][MAXSIZE], int size, int L, int land, int row, int column, int start_x, int start_y, int flag);/*the function that finds the lands that are connected to each other*/
 
int main(void)
{
    int L; /*water level*/
    int land = -1; /*the value given to distinguish between lands that are higher than the water level*/
    int flag = 0; /*checkpoint*/
    int start_x,start_y; /*the variable holding the initial position*/
    char check; /*checkpoint*/

    FILE* fp1 = fopen("input.txt", "r"); /*the file opens in read mode*/
    FILE* fp2 = fopen("output.txt", "w");/*the file opens in write mode*/

    if (fp1 == NULL) /*if the input file is not found, it gives a warning message and stops the code*/
    {
        printf("Could not open the input.txt\n");
		return 1;
    }

    fscanf(fp1, "%d", &L);/*the value in the first line of the file determines the water level*/

    while(!feof(fp1))/*all numbers are transferred to the struct array until the end of the file*/
    {
        if(fscanf(fp1, "%c", &check) == EOF)/*exits the loop when the file reaches the end so that it does not read the last line twice*/
        {
            break;
        }
        for(int i = 0; i < MAXSIZE; i++)
        {
            for(int j = 0; j < MAXSIZE; j++)
            {   
                fscanf(fp1, "%d", &terraindata[i][j].value);
            }
        }
    }

    for(int i = 0; i < MAXSIZE; i++)/*the location of lands higher than the water level is sent to the function*/
    {
        for(int j = 0; j < MAXSIZE; j++)
        {
            if(terraindata[i][j].value > L)
            {
                start_x = i;/*the initial location information is kept in memory*/
                start_y = j;
                move_on_island(terraindata, MAXSIZE, L, land, i, j, start_x, start_y, flag);/*parameters are sent to the recursive function*/
                flag = 0;
                land--; 
            }
        }
    }
    land = -1;

    int k = 1;
    for (int i = 0; i < MAXSIZE; i++)/*the locations of the islands are printed in the output.txt*/
    {
        for (int j = 0; j < MAXSIZE; j++)
        {
            if(terraindata[i][j].value == land) 
            {
                fprintf(fp2, "island_%d\tx_coordinate-> %d\ty_coordinate-> %d\n", k, i, j);
                k++;
                land--;
            }
        }
    }
    return 0;
}

void move_on_island(island terraindata[][MAXSIZE], int size, int L, int land, int row, int column, int start_x, int start_y, int flag)
{
    if(flag == 0)/*if it is the first time to enter the function*/
    {
        terraindata[row][column].value = land;

        if(column < MAXSIZE - 1 && terraindata[row][column+1].value > L)/*the right step is checked*/
        {
            terraindata[row][column+1].step = 1; /*it keeps in memory that it is progressing with the right step*/
            terraindata[row][column+1].value = land;
            flag = 1;
            move_on_island(terraindata, MAXSIZE, L, land, row, column+1, start_x, start_y, flag);
        }
        else if(row < MAXSIZE - 1 && terraindata[row+1][column].value > L) /* the down step is checked*/
        {
            terraindata[row+1][column].step = 2;/*it keeps in memory that it is progressing with the down step*/
            terraindata[row+1][column].value = land;
            flag = 1;
            move_on_island(terraindata, MAXSIZE, L, land, row+1, column, start_x, start_y, flag);
        }
        else if(column > 0 && terraindata[row][column-1].value > L) /* the left step is checked*/
        {
            terraindata[row][column-1].step = 3;/*it keeps in memory that it is progressing with the left step*/
            terraindata[row][column-1].value = land;
            flag = 1;
            move_on_island(terraindata, MAXSIZE, L, land, row, column-1, start_x, start_y, flag);
        }
        else if(row > 0 && terraindata[row-1][column].value > L)/* the up step is checked*/
        {
            terraindata[row-1][column].step = 4;/*it keeps in memory that it is progressing with the up step*/
            terraindata[row-1][column].value = land;
            flag = 1;
            move_on_island(terraindata, MAXSIZE, L, land, row-1, column, start_x, start_y, flag);
        }
        else/*if it has nowhere to step*/
        {
            return;
        }
    }

    if(flag == 1)/*if more than one has entered the function*/
    {
        if(start_x == row && start_y == column)/*if the starting position returns, it looks down again, if it cannot go down, the process is completed*/
        {
            if(row < MAXSIZE - 1 && terraindata[row+1][column].value > L)
            {
                terraindata[row+1][column].step = 2;
                terraindata[row+1][column].value = land; 
                move_on_island(terraindata, MAXSIZE, L, land, row+1, column, start_x, start_y, flag);
            }
            return;
        }
        
        terraindata[row][column].value = land;

        if(column < MAXSIZE - 1 && terraindata[row][column+1].value > L)/*the right step is checked*/
        {
            terraindata[row][column+1].step = 1; /*it keeps in memory that it is progressing with the right step*/
            terraindata[row][column+1].value = land;
            flag = 1;
            move_on_island(terraindata, MAXSIZE, L, land, row, column+1, start_x, start_y, flag);
        }
        else if(row < MAXSIZE - 1 && terraindata[row+1][column].value > L) /* the down step is checked*/
        {
            terraindata[row+1][column].step = 2;/*it keeps in memory that it is progressing with the down step*/
            terraindata[row+1][column].value = land;
            flag = 1;
            move_on_island(terraindata, MAXSIZE, L, land, row+1, column, start_x, start_y, flag);
        }
        else if(column > 0 && terraindata[row][column-1].value > L) /* the left step is checked*/
        {
            terraindata[row][column-1].step = 3;/*it keeps in memory that it is progressing with the left step*/
            terraindata[row][column-1].value = land;
            flag = 1;
            move_on_island(terraindata, MAXSIZE, L, land, row, column-1, start_x, start_y, flag);
        }
        else if(row > 0 && terraindata[row-1][column].value > L)/* the up step is checked*/
        {
            terraindata[row-1][column].step = 4;/*it keeps in memory that it is progressing with the up step*/
            terraindata[row-1][column].value = land;
            flag = 1;
            move_on_island(terraindata, MAXSIZE, L, land, row-1, column, start_x, start_y, flag);
        }
        else/*if it has nowhere to go, it returns, applying the exact opposite of the previously performed operation*/
        {   
            if(terraindata[row][column].step == 1)
            {
                column--;
            }
            else if(terraindata[row][column].step == 2)
            {
                row--;
            }
            else if(terraindata[row][column].step == 3)
            {
                column++;
            }
            else if(terraindata[row][column].step == 4)
            {
                row++;
            }

            move_on_island(terraindata, MAXSIZE, L, land, row, column, start_x, start_y, flag);
        }
    }
}