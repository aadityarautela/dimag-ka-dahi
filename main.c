#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Defining the eight language commands
#define INC_DP '>'
#define DEC_DP '<'
#define INC_VAL '+'
#define DEC_VAL '-'
#define OUT_VAL '.'
#define INP_VAL ','
#define JMP_FWD '['
#define JMP_BCK ']'

int main(int argc, char *argv[]){
	if(argc ==1){
		perror("Source file not specified");
		return (-1);
	}
	
	//Opening the source file
	FILE *fp;
	fp = fopen(argv[1],"r");
	if(fp == NULL) {
		perror("Error opening file");
		return (-1);
	}
	char program[30000];
	int r;
	int proglen=0;
	for(r=0;r<30000;r++){
		program[r]=fgetc(fp);
		proglen++;
		if(feof(fp)) break;
	}	
	fclose(fp);

	//Initializing the array
	char array[65536] = {0};
	char *ptr = array;

	//Parsing the source file
	int i;
	for(i=0;i<proglen;i++){
		//For implementing nested loops
		int nested=0;
		
		//Parsing through each character of program
		switch(program[i]){
			case INC_DP:
				if(ptr==&array[65535]) ptr = array;
				else ++ptr;
				break;
			case DEC_DP:
				if(ptr==array) ptr = &array[65535];
				else --ptr;
				break;
			case INC_VAL:
				++*ptr;
				break;
			case DEC_VAL:
				--*ptr;
				break;
			case OUT_VAL:
				putchar(*ptr);
				break;
			case INP_VAL:
				*ptr = getchar();
				break;
			case JMP_FWD:
				if(*ptr==0){
					i++;
					while(nested>0||program[i]!=']'){
						if(program[i]=='[') nested++;
						else if(program[i]==']') nested--;
						i++;
					}
				}
				break;
			case JMP_BCK:
				if(*ptr!=0){
					i--;
					while(nested>0||program[i]!='['){
						if(program[i]==']') nested++;
						else if(program[i]=='[') nested--;
						i--;
					}
					i--;
				}
				break;
			default:
				break;
		}
	}
	return 0;
}
