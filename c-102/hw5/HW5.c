#include<stdio.h>
#include<string.h>
#define MAX 125 /*defining macro*/

/*it is the structure created to determine the name and degree of parsed parts and store them.*/
typedef struct
{
    char name;
    int count;
}newick;

newick arr[MAX]; /*the array created on type of newick struct. the array stores parsed parts.*/
void parsing(newick *arr, char *buffer, int step, int step2, int counter, int len);/*the function parses input line.(name and degree)*/
void visualization(FILE* fp3, newick *arr, int start, int len2, int counter);/*visualization of parsed parts*/

int main(void)
{   
    
    char buffer[MAX] = {}; /*the array that stores the line in the file.*/
    /*variables for function*/
    int counter = 0;
    int start = 0;
    int step = 0;
    int step2 = 0;
    int len = 0;
    int len2  = 0;

    FILE* fp1 = fopen("input.txt", "r");/*the file opens in read mode*/
    FILE* fp3 = fopen("output.txt", "w");/*the file opens in write mode*/
    
    /*if the desired file is not found, it gives an error message and stops the code.*/
    if (fp1 == NULL)
    {
        printf("Could not open the input.txt\n");
		return 1;
    }
   
    /*reads to the end of the line and transfers it to the buffer array.*/
    fgets(buffer, MAX, fp1);

    /*assigns the size of the buffer array to the len variable*/
    len = strlen(buffer);
    
    /*this loop finds out how many letters are in the array*/
    for (int i = 0; i < len; i++)
    {
        if ((buffer[i] >= 'A' && buffer[i]  <= 'Z') || (buffer[i]  >= 'a' && buffer[i]  <= 'z'))
        {
            ++len2;
        }
    }

    parsing(arr, buffer, step, step2, counter, len);

    visualization(fp3, arr, start, len2, counter);

    /*close files*/
    fclose(fp1);
    fclose(fp3);

    return 0;
}

void parsing(newick *arr, char *buffer, int step, int step2, int counter, int len)
{
    /*if the number of steps reaches the array size, it returns empty.*/
    if (step >= len)
    {
        return;
    }
    /*if the array element is equal to one letter, the letter itself and its degree are transferred to the structure array.
    the function calls itself back by increasing the step numbers*/
    if ((buffer[step] >= 'A' && buffer[step]  <= 'Z') || (buffer[step]  >= 'a' && buffer[step]  <= 'z'))
    {
        arr[step2].name = buffer[step];
        arr[step2].count = counter;
        parsing(arr, buffer, ++step, ++step2, counter, len);
    }
    /*if the array element is equal to '(', it increases the degree for the next next letter.
    the function calls itself back by increasing the step number and counter*/
    else if (buffer[step] == '(')
    {
        parsing(arr, buffer, ++step, step2, ++counter, len);
    }
    /*if the array element is equal to ')', it decreases the degree for the next next letter.
    the function calls itself back by increasing the step number and decreasing counter*/
    else if (buffer[step] == ')')
    {
        parsing(arr, buffer, ++step, step2, --counter, len);
    }
    /*if the array element is equal to ',',it passes to the other element
    the function calls itself back by increasing the step number*/
    else if (buffer[step] == ',')
    {
        parsing(arr, buffer, ++step, step2, counter, len);
    }  
}

void visualization(FILE* fp3, newick *arr, int start, int len2, int counter)
{
    /*if the number of steps reaches the array size, it returns empty.*/
    if (start >= len2)
    {
        return;
    }
    /*'-' is written to the output file until the degree of the letter is equal to the counter.*/
    if (arr[start].count != counter)
    {
        fprintf(fp3, "-");
        return visualization(fp3, arr, start, len2, ++counter);
    }
    /*when the degree of the letter is equal to the counter, the letter itself is written and begins the new line.*/
    fprintf(fp3, "%c\n",arr[start].name);
    counter = 0;
    visualization(fp3, arr, ++start, len2, counter);
}


