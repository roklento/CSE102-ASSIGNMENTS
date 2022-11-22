#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100 /* defining macro */

double price_of_obj(char object[MAX]); /* the function that calculates the value of the object*/
int isNumber(char* buffer); /*the function checks the strings */
int parseInput(char *buffer, int *quant,char parts[][MAX], int *num_of_parts);/* a function that parses entries into strings (quantity, object name, number of parts)*/
void delete_white_space(char *buffer); /*the function that deletes extra spaces in entries*/

int main(void)
{
    char object[MAX] = {}; /*the array that holds the object name*/
    printf("Define The Object: ");
    scanf("%[^\n]s",object);
    getc(stdin); /*the function used for the buffer ('enter key' between 'object name')*/
    printf("%s is %.2f dollars.\n",object,price_of_obj(object)); /*printing the results*/
    return 0;
}

double price_of_obj(char object[MAX])
{
    /*pointers for various c functions*/
    char buffer[MAX];
    char *ptr = &(buffer[0]);
    char **pointer;
    size_t line = MAX;
    
    /*variables for string parsing*/
    int quant[MAX];
    char parts[MAX][MAX];
    int num_of_parts;
    double total = 0.00;

    /*gets the names or prices of the objects*/
    printf("What is %s \n",object);
    getline(&ptr,&line,stdin);
    
    /*if input string is number then return that number as double*/
    if(isNumber(buffer))    
    {
        return strtod(buffer,pointer);
    }
    else
    {   
        
        delete_white_space(buffer);/*delete white-spaces from input buffer*/
        
        parseInput(buffer,quant,parts,&num_of_parts);/* if input is string form, parse the string */

        for (int i = 0; i < num_of_parts; i++)
        {
            double price = price_of_obj(parts[i]);/*call the recursive function for every part of the object*/
            total += quant[i] * price; /*keep the total*/

        }
        return total;
    }
}

/*checks the string, if it has number in it. returns 1 if it's number , returns 0 if it's not a number*/
int isNumber(char* buffer)
{
    int number = 1;

    for (int i = 0; i < strlen(buffer) - 1; i++)
    {
        if((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '.' ) /*if the digit is not input*/
        {
            number = 0;
        }
    }
    return number;
}

/*parses the string */
int parseInput(char *buffer,int quant[],char parts[][MAX], int *num_of_parts)
{
    char *temp = buffer;
    char *token;
    int i = 0;

    /*outer loop parses the string for every '+' operation*/
    while ((token = strtok_r(temp, " + ", &temp))) 
    {
        char *token1;
        char *temp2 = token;
        
        /*inner loop parses the string for every '*' operation*/
        while ((token1 = strtok_r(temp2, " * ", &temp2))) 
        {
            /*saves the string according to it's type. 
            if it's number, saves it to quant integer array, if it's a name saves it to parts array*/
            if(isNumber(token1))   
            {
                sscanf( token1, " %d", &quant[i]);
            }
            else    
            {
                strcpy(parts[i], token1);
            }
        }
        i++;
    }
    *num_of_parts = i;/*saves number of parts*/

    return 0;
}

/*if the input buffer has white space as element then remove it from input*/
void delete_white_space(char *buffer)
{
    
    int size = strlen(buffer); /* get the size of buffer*/
    int counter = 0;

    /* count non-white-space character*/
    for(int i = 0 ; i < size; i++)
    {
        if(buffer[i] != ' ')
        {
            buffer[counter] = buffer[i];
            counter++;
        }
    }
    buffer[counter-1] = '\0'; /*delete white-space character*/
}