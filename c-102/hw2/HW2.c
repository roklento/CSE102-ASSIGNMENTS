/*I used two different algorithms to sort the numbers. One of them is Bubble Sort. Bubble Sort (or sinking sort) is 
a straight-forward comparison sort algorithm that continuously compares adjacent indexes and swaps them if they are out of order.Bubble Sort efficiency is as follows :
Worst Case: O(n2) - Quadratic Time Hash
Mean State O(n2) - Quadratic Time Hash
The best case is the O(n) - National Time Hash.
The other algorithm I use is selection sort. Selection Sort is an unstable comparison sort algorithm with poor performance. 
Selection Sort uses the selection method and performs at O(n2) in the best, average, and worst case.*/
#include <stdio.h>
#define MAX 100

void sorting(int count1, int numberArr[], int count2, int numberCountArr[]); /* defined sort function*/

int main(void)
{
    int number1, number2; /* the variable we store when reading numbers from a file*/
    int counter = 1; /* the variable that holds how many units there are from the number*/
    int flag = 0; /*checkpoint*/
    int numberArr[MAX] = {}; /* the array where the numbers are stored*/
    int numberCountARR[MAX] = {}; /* the array that holds the amount of numbers */
    int array_length = 0; /* a variable that holds the length of the array momentarily*/
    char check; /* checkpoint*/

    FILE* fp1 = fopen("input.txt", "r"); /* opens three different pointer files in read mode, read mode, and write mode, respectively*/
    FILE* fp2 = fopen("input.txt", "r");
    FILE* fp3 = fopen("output.txt", "w");

    /* if the file is not found, the error message is suppressed and the code stops*/
    if(fp1 == NULL) 
    {
        printf("Could not open the input.txt\n");
		return 1;
    }
    if(fp2 == NULL)
    {
        printf("Could not open the input.txt\n");
		return 1;
    }
    if(fp3 == NULL)
    {
        printf("Could not open the output.txt\n");
		return 1;
    }

    int i = 0;

    /*the first loop is opened to hold the numbers in memory and continues to the end of the file.*/
    while(!feof(fp1)) 
    {
        fscanf(fp1, "%d", &number1); /*reads the numbers as int and assigns them to the number1 variable*/

        /*if our number has already been processed and is in the array, the checkpoint will be alerted.*/
        for(int j = 0; j < array_length; j++) 
        {
            if(numberArr[j] == number1)
            {   
                flag = 1;
                j = MAX;
            }
        }

        /*if the checkpoint has not been alerted, our number will continue to be processed.*/
        if(flag == 0)
        {
            numberArr[i] = number1; /* number is assigned to the array.*/

            fseek(fp2, ftell(fp1), SEEK_SET); /*the second loop determines where it will start when you return to the beginning.*/
            
            /*the second loop returns to the end of the file to find out if the number stored in the memory is a match.*/
            while(!feof(fp2))
            {
                fscanf(fp2, "%d", &number2);/*reads the numbers as int and assigns them to the number2 variable*/

                if(fscanf(fp2, "%c", &check) == EOF) /* if the cursor is located at the end of the file, the amount of the number is assigned to the array.*/
                {
                    numberCountARR[i] = counter;
                }

                /*if the cursor is not located at the end of the file, it tries to find the numbers that are equal to the number in the file.
                If finds it, the amount of count increases. At the end, the amount of  count is assigned to the array.*/
                else 
                {
                    if(number1 == number2)
                    {
                        counter++;  
                    }
                    numberCountARR[i] = counter;
                }
                
            }
            i++;
            array_length++;
        }
        flag = 0;
        counter = 1;
    }
    /* close files*/
    fclose(fp1);
    fclose(fp2); 
    
    sorting(array_length, numberArr, array_length, numberCountARR);/*the sort function is called*/

    /*the values in the arrays written to the output.txt file*/
    for(int i = 0; i < array_length; i++)
    {
        fprintf(fp3,"%d:%d\n",numberArr[i], numberCountARR[i]);
    }
    /*close file*/
    fclose(fp3);
}

void sorting(int count1, int numberArr[], int count2, int numberCountARR[])
{
    
    int flag1 = -1;
    int temp1, temp2, temp3;

    /*i used the bubble sort algorithm to sort the amount of numbers.*/
    while(flag1 != 0)
    {
        /*if the checkpoint does not change, the numbers are in order*/
        flag1 = 0;

        for(int i = 0; i < count2 - 1 ; i++)
        {
            for(int j = 0; j < count2 - 1 - i; j++)
            {   
                /*if the quantity of the number is sorted incorrectly, the array positions where the quantity of the number is located are displaced.*/
                if(numberCountARR[j] > numberCountARR[j + 1]) 
                {
                    temp1 = numberCountARR[j];
                    numberCountARR[j] = numberCountARR[j + 1];
                    numberCountARR[j + 1] = temp1;

                    /*The array positions change in the same way, so that the quantities of the changing numbers do not confuse the numbers.*/
                    temp2 = numberArr[j];
                    numberArr[j] = numberArr[j + 1];
                    numberArr[j + 1] = temp2;
                    flag1++;
                }
            }
        }
    }
    /*i used the selection sort algorithm to sort the numbers whose number quantities are equal.*/
    for(int i = 0; i < count1; i++)
    {
        for(int j = 0; j < count1; j++)
        {
            /*if the quantities of the numbers are equal and sorted incorrectly, the array locations change.*/
            if(numberCountARR[i] == numberCountARR[j])
            {
                if(numberArr[j] > numberArr[i])
                {
                    temp3 = numberArr[j];
                    numberArr[j] = numberArr[i];
                    numberArr[i] = temp3;
                }
            }
        }
    }
}
