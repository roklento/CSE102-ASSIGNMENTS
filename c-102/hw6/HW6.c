#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGHT 10 /* macros defined*/
#define STRINGLEN 100

typedef struct gate
{
    int type; /* type gate */
	char name[MAXLENGHT];/* name gate */
	char in1name[MAXLENGHT];	/* first input name */
	char in2name[MAXLENGHT];	/* second input name */
    struct gate* in1;	/* first input address */
	struct gate* in2;	/* second input address */
	int output;/* the value of the gate after processing */
	int mem;/* the memory variable used in the flip-flop process  */
}
gate;

int eval(gate* g);	/*this function returns the results of the process*/

int main(void)
{
	int size;
    int counter = 0;
    int last_gate,result;
	char type_name[MAXLENGHT] = {};
	char gate_name[MAXLENGHT] = {};
    
	FILE *fp1 = fopen("circuit.txt", "r");/*the file opens in read mode*/
	FILE *fp2 = fopen("circuit.txt", "r");/*the file opens in read mode*/
	FILE *fp3 = fopen("input.txt", "r");/*the file opens in read mode*/

	/*if the desired file is not found, it gives an error message and stops the code.*/
    if (fp1 == NULL || fp2 == NULL)
    {
        printf("Could not open the circuit.txt\n");
		return 1;
    }
    if (fp3 == NULL)
    {
        printf("Could not open the input.txt\n");
		return 1;
    }

	char name[MAXLENGHT];
    char tmp[MAXLENGHT];
    char buffer[STRINGLEN];	

	while(!feof(fp1))
    {	
		fscanf(fp1, "%s", name);	
		if(strcmp(name, "INPUT") == 0)/* if type_name is "INPUT", the memory value increases up to the number of entered elements*/
        {	
			do
            {	
				fscanf(fp1, "%s", tmp);
				size++;/*the memory value increases by one with each element.*/
			}while(fgetc(fp1) == ' ');
		}
		else
        {
			fgets(buffer, STRINGLEN, fp1);/* if type_name is not "INPUT", the memory value increases by one with each new line*/
			size++;
		}	
	}
	
	gate *gates = (gate*)malloc(size * sizeof(gate));/*the struct array is created using the dynamic memory allocation method*/

	int i = 0;
	while(!feof(fp2))
    {	
		fscanf(fp2, "%s", type_name); /*assigns the name of the gate in each line to the variable type_name */

		if(strcmp(type_name, "INPUT") == 0)/* if type_name is "INPUT"*/
        {	
			do 
            {	
				fscanf(fp2, "%s", gate_name);	/* taken gate name of type "INPUT" */
				strcpy(gates[i].name, gate_name);	/* gate name is copied to struct array */
				gates[i].type = 0;	/* to find the type "INPUT", it equals 0 */
				counter++; /*the number of elements increases by one in the counter*/
				i++;
			}while (fgetc(fp2) == ' ');
		}
		else if(strcmp(type_name, "AND") == 0)/* if type_name is "AND"*/
        {	
			fscanf(fp2, " %s %s %s ", gates[i].name, gates[i].in1name, gates[i].in2name);	/* taken gate names of type "AND" */
			for(int j = 0; j < i; j++)/* find the gate index and access the information of the gate */
            {	
				if(strcmp(gates[i].in1name, gates[j].name) == 0)
                {
					gates[i].in1 = &gates[j];/*the address of the first input is assigned to the struct pointer.*/
				}
				if(strcmp(gates[i].in2name, gates[j].name) == 0)
                {
					gates[i].in2 = &gates[j];/*the address of the second input is assigned to the struct pointer.*/
				}
			}
			gates[i].type = 1;	/* to find the type "AND", it equals 1 */
		}
		else if(strcmp(type_name, "OR") == 0)/* if type_name is "OR"*/
        {	
			fscanf(fp2, " %s %s %s ", gates[i].name, gates[i].in1name, gates[i].in2name); 	/* taken gate names of type "OR" */
			for(int j = 0;j < i; j++)/* find the gate index and access the information of the gate */
            {	
				if(strcmp(gates[i].in1name, gates[j].name) == 0)
                {
					gates[i].in1 = &gates[j];	/*the address of the first input is assigned to the struct pointer.*/	
				}
				if(strcmp(gates[i].in2name, gates[j].name) == 0)
                {
					gates[i].in2 = &gates[j];	/*the address of the second input is assigned to the struct pointer.*/	
				}
			}
			gates[i].type = 2;	/* to find the type "OR", it equals 2 */
		}
		else if(strcmp(type_name, "NOT") == 0)/* if type_name is "OR"*/
        {	
			fscanf(fp2, " %s %s ", gates[i].name, gates[i].in1name);	/* taken gate names of type "OR" */				
			for(int j = 0;j < i ; j++) /*find the gate index and access the information of the gate */
            {	
				if(strcmp(gates[i].in1name, gates[j].name) == 0)
                {
					gates[i].in1 = &gates[j];	/*the address of the first input is assigned to the struct pointer.*/	
				}
			}
			gates[i].type = 3;	/*  to find the type "OR", it equals 3*/
		}
		else if(strcmp(type_name, "FLIPFLOP") == 0)/* if type_name is "FLIPFLOP"*/
        {	
			fscanf(fp2, " %s %s ", gates[i].name, gates[i].in1name);	/* taken gate names of type "FLIPFLOP" */			
			for(int j = 0; j < i; j++) /*find the gate index and access the information of the gate */
            {	
				if(strcmp(gates[i].in1name, gates[j].name) == 0)
                {
					gates[i].in1 = &gates[j];	/*the address of the first input is assigned to the struct pointer.*/	
				}
			}
			gates[i].type = 4;	/*  to find the type "OR", it equals 4 */
			gates[i].mem = 0; /* initially former-out of any flipflop is 0*/
		}
        i++;
	}
	last_gate = i - 1;	/* gets the index of the last gate*/

	while(!feof(fp3))
    {	
		for(i = 0; i < counter; i++)/*the values contained in each row are taken and considered as the value of the elements*/
        {	
			fscanf(fp3, "%d ", &gates[i].output);	
		}
		result = eval(&gates[last_gate]);	/*from the last gate, the processes start and progress recursively, as a result of which they return us an output value*/
		printf("%d\n", result);	/*result printed*/
	}
    /*files closed*/
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
    /*memory freed*/
	free(gates);
	return 0;
}

int eval(gate* g)
{	
	/*INPUT*/
	if(g->type == 0)
    {
		return g->output;	/*it is base case in recursive function. if gate is type "INPUT", return input*/
	}
    /*AND*/	
	else if(g->type == 1)
    {	
		int in1 = eval(g->in1);	 /*sends the address in1 to get the first input value of the gate*/
		int in2 = eval(g->in2);	/*sends the address in1 to get the second input value of the gate.*/ 
		return in1 && in2;	
	}
    /*OR*/
	else if(g->type == 2)
    { 	
		int in1 = eval(g->in1);	/*sends the address in1 to get the first input value of the gate*/
		int in2 = eval(g->in2);	/*sends the address in1 to get the second input value of the gate*/
		return in1 || in2;	
	}
    /*NOT*/
	else if(g->type == 3)
    { 	
		int in1 = eval(g->in1);	/*sends the address in1 to get the first input value of the gate*/
		return !in1;		
	}
    /*FLIPFLOP*/
	else if(g->type == 4)
    {
		int in1 = eval(g->in1);	/*sends the address in1 to get the first input value of the gate*/
		int memory2 = g->mem;	/*the current memory value is called for the process and assigned to the memory2 variable*/

		if(in1 == 0) /* if the input is 0, the value in memory is returned  */
        {
            if(memory2 == 0)
            {	
				g->mem = 0;
				return 0;
			}
            else if(memory2 == 1)
            {
				g->mem = 1;
				return 1;			
			}
        }					
		else if(in1 == 1) /* if the input is 1, as a result of the process, the memory value changes, and the new memory value is stored in memory */
        {		
			if(memory2 == 0)
            {	
				g->mem = 1;
				return 1;
			}
			else if(memory2 == 1)
            {
				g->mem = 0;
				return 0;			
			}
		}
	} 		
}
