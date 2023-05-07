#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.c"
#define STR_BUFF_SIZE 1024

int numDigs(unsigned long long num){
	if(num == 0)
		return 1;
	else{
		int iter = 0;
		while(num > 0)
			num /= 10, iter++;
		return iter;
	}
}

char* itoa(unsigned long long num){
	int dgs = numDigs(num);
	char* numBuff = (char*)malloc(dgs+1);
	if(num == 0){
		numBuff[0] = '0';
		numBuff[1] = '\0';
		return numBuff;
	}
	else{
		sprintf(numBuff, "%llu", num);
		return numBuff;
	}
	return NULL;
}

char leadZerros(char* str, int num){
	int call = 0;
	while(str[call] == '0' && str[call])
		call++;
	if(call == num)
		return call;
	else
		return 0;
}

char* inputGen(char* str1, char* str2){
	char* ret = (char*)malloc(strlen(str1)+strlen(str2));
	// printf("strlen(str1)+strlen(str2) = %i\n", strlen(str1)+strlen(str2));
	int iter = 0;
	while(str1[iter]){
		ret[iter] = str1[iter];
		iter++;
	}
	int pos = iter;
	iter = 0;
	while(str2[iter]){
		ret[pos++] = str2[iter++];
	}
	ret[pos] = '\0';
	return ret;
}

int main(int argc, char const *argv[])
{
	char strBuff[1024];
	printf("enter your string: ");
	scanf("%1023s", &strBuff);
	int ldZerrs = 0;
	printf("enter the number of leading zeros: ");
	scanf("%i", &ldZerrs);
	printf("wait, magic happens...\n");
	char* numBuff = NULL;
	char* shaOutput = NULL;
	char* tmpInput = NULL;
	unsigned long long num = 0;
	do{
		free(shaOutput), shaOutput = NULL;
		free(numBuff), numBuff = NULL;
		free(tmpInput), tmpInput = NULL;
		numBuff = itoa(num++);
		tmpInput = inputGen(strBuff, numBuff);
		shaOutput = SHA256(tmpInput);
	}while(!leadZerros(shaOutput, ldZerrs));
	printf("\ncongratulations!\nyour string is: '%s'\nyour hash is: '%s'\n", tmpInput, shaOutput);

	return 0;
}


// printf("strBuff = %s\n", strBuff);
// printf("numBuff = %s\n", numBuff);
// printf("tmpInput = %s\n", tmpInput);
// printf("shaOutput = %s\n\n", shaOutput);