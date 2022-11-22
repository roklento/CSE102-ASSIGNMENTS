#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAX 1000 /*max number of polynomial file lines*/
#define powers 3 /*the maximum number of prescribed degrees*/

int main(void)
{
    char coefficient_arr[MAX] = {}; /*the array that holds the coefficients of the polynomial*/
    char degree_arr[powers] = {}; /*the array that holds the degree of the polynomial*/
    char polynomial[MAX] = {}; /* the array that holds the polynomial read from the polynomial file as a string*/
    char check; /*checkpoint*/
    double values; /* the variable that holds the numbers read from the variable file*/
    double coefficient; /* the variable that holds the coefficient*/
    double sum = 0; /*the variable that holds the result of the polynomial*/
    int degree = 1; /* the variable that holds the degree*/
    int array_size_poly; /* the variable that holds size of polynomial array*/
    int flag = 0; /*checkpoint*/

    FILE* fp1 = fopen("values.txt", "r"); /* the values.txt file opens in read mode*/
    FILE* fp2 = fopen("polynomial.txt", "r");/* the polynomial.txt file opens in read mode*/
    FILE* fp3 = fopen("evaluations.txt", "w");/* the evaluations.txt file opens in write mode*/

    /*if there are no files to be read, the warning message is suppressed and the code is exited*/
    if(fp1 == NULL) 
    {
        printf("Could not open the values.txt\n");
		return 1;
    }
    if(fp2 == NULL)
    {
        printf("Could not open the polynomial.txt\n");
		return 1;
    }

    /*the file is read to the end of the line and assigned to the polynomial array*/
    while(fgets(polynomial, MAX, fp2))
    {   
    }

    /* the size of the polynomial array is calculated and assigned*/
    array_size_poly = strlen(polynomial);

    /*returns the fp1 pointer until it reaches the end of the file*/
    while(!feof(fp1))
    {
        /*reads the numbers in an double size and assigns them to the values variable*/
        fscanf(fp1, "%lf", &values);

        /*breaks the loop when the file reaches the end*/
        if(fscanf(fp1, "%c", &check) == EOF)
        {
            break;
        }

        int j = 0;
        int k = 0;

        /*the array returns until end*/
        while(j < array_size_poly-1)
        {
            k = 0;

            /*Since the part up to the character 'x' will be our coefficient, 
            the characters that are read until they reach the character 'x' are assigned to the coefficient array.*/
            while(polynomial[j] != 'x')
            {
                flag = 1;/*this checkpoint reports that the loop has been entered at least once.*/
                strcpy(coefficient_arr+k, polynomial+j);
                k++;
                j++;
            }

            /*if the loop has been entered at least once*/
            if(flag != 0)
            {
                if(polynomial[j-1] == '-') /*if the variable of the polynomial is '-x', the coefficient variable assigned -1.*/
                {
                    coefficient = -1.00; 
                } 
                else if(polynomial[j-1] == '+')/* if the variable of the polynomial is '+x', the coefficient variable assigned 1.*/
                {
                    coefficient = 1.00;
                }
                else /*if 'x' is a number in front of the variable, the coefficient array that holds this number in the char array is converted to a double number using the sscanf function.*/
                {
                    sscanf(coefficient_arr, "%lf", &coefficient);
                }
            }
            else/*if the first character of the polynomial is 'x', the coefficient variable assigned 1*/
            {   
                if(polynomial[0] == 'x')
                {
                    coefficient = 1.00;
                }
            } 
            j++;

            /*if the degree of the variable 'x' is greater than 2, the character 'x' is followed by '^'.*/
            if(polynomial[j] == '^')
            {
                j++;

                /*the degree of the variable 'x' is read up to the sign of the other number and assigned to the degree variable*/
                do
                {
                    int k = 0;  
                    degree_arr[k] = polynomial[j];
                    j++;
                    k++;
                }while(!(polynomial[j] == '+' || polynomial[j] == '-') && j < array_size_poly-1);
                sscanf(degree_arr, "%d", &degree);
            }  
            /*instead of the variable 'x', the values number is written and an operation is performed on this value. 
            The result of the operation is assigned to the sum variable and it is summed up by the sum of the other variable 'x' and finally gives the result of the polynomial.*/
            sum = sum + (coefficient * pow(values,degree));

            /*variables and array are brought to their initial state for the new loop*/
            coefficient = 0.00;
            degree = 1;
            flag = 0;
            memset(degree_arr, 0 , MAX); 
        }
        /*the polynomial results are written to file evaluations.txt*/
        fprintf(fp3, "%.2lf\n", sum);
        sum = 0;
    }
    /*close files*/
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}
