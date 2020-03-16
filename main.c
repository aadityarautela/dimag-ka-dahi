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
		printf("Source file not specified\n");
		exit(0);
	}
	
	//Opening the source file
	FILE *fp;
	fp = fopen(argv[1],"r");
	char program[30000];
	fgets(program,30000,fp);
	fclose(fp);

	//Initializing the array
	char array[65536] = {0};
	char *ptr = array;

	//Parsing the source file
	int i;
	for(i=0;i<strlen(program);i++){
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
		}
	}
	return 0;
}
