/*
* Neel Gondalia
* Anagram - Brute Force
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define ARRAYSIZE 30000
#define FILENAME "data.txt"
#define DUMMYCHAR ' '
#define STR_MAX_LEN 20
#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"

/*
 * Brute force helper function that checks if a string sent to the function is an anagram of the string that is to be examined.
 */
int checkIfAnagram(char *str, char *toBeExamined, char* copyToBeExamined)
{
    bool isAnagram;
    int i = 0, j = 0;

    if (strlen(str) == strlen(toBeExamined))
    {
        for (i = 0; i < strlen(str); i++)			//loops until user string char found, if a char not found, breaks and realizes not an anagram
        {
            isAnagram = false;
            for (j = 0; j < strlen(toBeExamined); j++)
            {
                if (str[i] == toBeExamined[j])
                {
                    isAnagram = true;
                    toBeExamined[j] = DUMMYCHAR;			//replaces already examined character with a dummy char so dont access it again
                    break;
                }
            }
            if (!isAnagram)
                return 0;
        }
        if (isAnagram)
        {
            printf (GREEN "* anagram found: %s\n" RESET, copyToBeExamined);
            return 1;
        }
    }
    return 0;
}

int main ()
{
    int flag = 1;
    while (flag == 1)
    {
		int i = 0, anagramCount = 0;
		char copyToBeExamined[STR_MAX_LEN];
		char toBeExamined[STR_MAX_LEN];
		FILE *fptr = fopen(FILENAME, "r");
		
		//gets user string
		char *userStr = malloc(sizeof(char)*STR_MAX_LEN);
		printf("\nEnter a string to find anagrams of: ");
		fgets(userStr,STR_MAX_LEN,stdin);
		userStr[strcspn(userStr,"\n")] = 0;
		
		printf (RED "\n***************** ANAGRAMS FINDER ALGORITHM RESULTS ****************************\n" RESET);
		printf ("\n--> String examined for anagrams is: %s\n", userStr);
		
		clock_t startTime = clock();
		for (i = 0; i < ARRAYSIZE; i++)
		{
			fscanf(fptr, "%s", toBeExamined);
			strcpy(copyToBeExamined, toBeExamined);
			anagramCount += checkIfAnagram(userStr,toBeExamined,copyToBeExamined);			//anagram counter
		}
		
		printf (GREEN "*** TOTAL ANAGRAM COUNT: %d\n" RESET, anagramCount);
		printf(YELLOW "--> Search Execution Time: %f seconds\n\n" RESET, (double)(clock() - startTime) / CLOCKS_PER_SEC);
		printf (RED "********************************************************************************\n\n" RESET);
		
		free(userStr);
		
		//user choice to continue searching for anagrams
		char *cont = malloc(sizeof(char) * STR_MAX_LEN);
		printf ("Want to examine another string for anagrams? (yes/no)\n");
		fgets(cont,STR_MAX_LEN,stdin);
		cont[strcspn(cont,"\n")] = 0;
		
		if (strcmp(cont,"no") == 0) flag = 0;
		free(cont);
		fclose(fptr);
	}
	
	return 0;
}
