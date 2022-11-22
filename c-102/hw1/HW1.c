/* Although we didn't do sorting, I used the selection sorting algorithm for this algorithm. selection sorting is a very inefficient sorting method. at worst, at best, the transaction hash is O(n^2). The good thing about selection sort is it never makes more than O(n) swaps and can be useful when memory write is a costly operation.*/
#include<stdio.h>

int main(void)
{
	int number_1,number_2;
	int digit = 1;
	int temp;
	char n;
	
	/*We open files with two different pointers in read and read + write mode. This is because the first pointer stores our numbers in memory, while the other pointer reads the file to the end to find the number that is equal to it, and if it finds the number that is equal to it, it deletes the file and adds spaces instead.*/
	FILE* fp1 = fopen("file.txt", "r");
	FILE* fp2 = fopen("file.txt", "r+");
	FILE* fp3 = fopen("file.txt", "r+");
	
	/*if it cannot find the file, it makes return 1 with a warning message*/
	if(fp1 == NULL)
	{
		printf("Could not open the file.txt\n");
		return 1;
	}
	if(fp2 == NULL)
	{
		printf("Could not open the file.txt\n");
		return 1;
	}
	
	/*This is the necessary process to ensure that my code written in the unix environment does not give errors in files from windows. This process has been tried to be corrected by replacing the extra (\r) character used to go to the beginning of the line in windows with a space.*/
	while(!feof(fp3))
	{
		fscanf(fp3, "%c", &n);
		if(n == '\r')
		{
			fseek(fp3, -1,SEEK_CUR);
			fputs(" ",fp3);	
		}
	}
	
	/* close the file*/
	fclose(fp3);
	
	/*the first loop is opened to hold the numbers in memory and continues to the end of the file.*/
	while(!feof(fp1))
	{	
		/*to assign each number to a variable as an int value, the numbers are read from the file.*/
		fscanf(fp1, "%d", &number_1);
		
		/*to preserve the original of the number, a variable is temporarily used.*/
		temp = number_1;
		
		/*if the number is negative, the variable assigned to hold the digit numbers is incremented by one because it will use extra digits.*/
		if(number_1 < 0)
		{
			digit++;
		}
		
		/*this loop is finding number of digits*/	
		while(temp >= 10)
		{
			temp /= 10;
			digit++;
		}
		
		/*the second loop determines where it will start when you return to the beginning.*/
		fseek(fp2, ftell(fp1), SEEK_SET);
		
		/*the second loop returns to the end of the file to find out if the number stored in the memory is a match.*/
		while(!feof(fp2))
		{	
			fscanf(fp2, "%d", &number_2);
			
			/*if the number stored in memory matches, the line is sent back as many digits as the number, and the number is overwritten with as many spaces as the number of digits.*/
			if(number_1 == number_2)
			{
				fseek(fp2, -digit, SEEK_CUR);
				for(int i = 0; i < digit; i++)
				{
					fputs(" ",fp2);
				}
				
				/*The variable sent to search is synchronized to 0 for new numbers.*/
				number_2 = 0;
			}
		}
		/*the variable holding the number of digits is reset to keep the digits of the new numbers correct.*/
		digit = 1;
	}
	
	/*close files*/
	fclose(fp1);
	fclose(fp2);
}
