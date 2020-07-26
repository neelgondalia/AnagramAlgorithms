/*
* Neel Gondalia
* Anagram - Presorting Technique
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define ARRAYSIZE 30000
#define FILENAME "data.txt"
#define STR_MAX_LEN 20
#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"

//makes two copies of a data string. One to sort and one to keep unsorted
typedef struct {
    char unsortedData[STR_MAX_LEN];
    char sortedData[STR_MAX_LEN];
}data;

/*
 * compare for individual number or string to be used for qsort
 */
static int compare(const void *a, const void *b)
{
    char *a1 = (char *) a;
    char *b1 = (char *) b;
    return strcmp(a1,b1);
}

/*
 * compare for array of structs that is to be used for qsort
 */
static int compareBySortedString (const void *a, const void *b)
{
    data *ia = (data *)a;
    data *ib = (data *)b;
    return strcmp(ia->sortedData, ib->sortedData);
}
/*
 * wrapper function that calls qsort on a string passed
 */
void sort(char *arr, int n)
{
    qsort(arr, n, sizeof(char), compare);
}

/*
 * finds the string to be found in the sorted array of structs
 */
int binarySearch(data arr[], int l, int r, char *toFind)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (strcmp(arr[mid].sortedData, toFind) == 0)
            return mid;

        if (strcmp(arr[mid].sortedData, toFind) > 0)
            return binarySearch(arr, l, mid - 1, toFind);
        
        return binarySearch(arr, mid + 1, r, toFind);
    }
    return -1;
}

/*
 * By help of binary seach, finds an anagram match index and traverses up and down from that index in the sorted array until matches are not found
 */
void findAnagrams (data allData[], char *userStr) {

    int found = binarySearch(allData,0,ARRAYSIZE-1,userStr);
    int numberOfAnagrams = 0;
	
	//no matches found
    if (found == -1) 
    {
        printf("*** TOTAL ANAGRAM COUNT: %d\n", numberOfAnagrams);
        return;
    }

    numberOfAnagrams++;
    printf (GREEN "* anagram found: %s\n" RESET, allData[found].unsortedData);
    
    //traversing down from the index found
    for (int i = (found-1); i > 0; i--) {
        if (strcmp(allData[i].sortedData, userStr) == 0) {
            numberOfAnagrams++;
            printf(GREEN "* anagram found: %s\n" RESET, allData[i].unsortedData);
        }
        else
            i = 0;
    }
	
	//traversing up from the index found
    for (int i = (found + 1); i < ARRAYSIZE; i++)
    {
        if (strcmp(allData[i].sortedData, userStr) == 0)
        {
            numberOfAnagrams++;
            printf(GREEN "* anagram found: %s\n" RESET, allData[i].unsortedData);
        }
        else
            i = ARRAYSIZE;
    }

    printf("*** TOTAL ANAGRAM COUNT: %d\n", numberOfAnagrams);
}

int main()
{
    FILE *fptr = fopen(FILENAME, "r");

    data toBeChecked[ARRAYSIZE];
    char temp[STR_MAX_LEN];
	
	//double presorting
	clock_t preSortTime = clock();
    for (int i = 0; i < ARRAYSIZE; i++) 
    {
        fscanf(fptr, "%s", toBeChecked[i].unsortedData);
        strcpy(temp, toBeChecked[i].unsortedData);
        sort(temp,strlen(temp));							//sorting individual string/number
        strcpy(toBeChecked[i].sortedData, temp);
    }
    fclose(fptr);
    qsort(toBeChecked, ARRAYSIZE, sizeof(data), compareBySortedString);		//sorting array of structs
	double psTime = (double)(clock() - preSortTime) / CLOCKS_PER_SEC;
	printf(YELLOW "\n****** Double Presorting Execution Time: %fs\n" RESET, psTime);

	int flag = 1;
	while (flag == 1)
	{
		//gets user string
		char *str = malloc(sizeof(char)*STR_MAX_LEN);
		printf("\nEnter a string to find anagrams of: ");
		fgets(str,STR_MAX_LEN,stdin);
		str[strcspn(str,"\n")] = 0;
		sort(str, strlen(str));

		printf (RED "\n***************** PRESORTING ANAGRAMS FINDER ALGORITHM RESULTS ****************************\n" RESET);
		printf("\n--> String being examined for anagrams: %s\n", str);
		clock_t searchTime = clock();
		findAnagrams(toBeChecked, str);						//finds anagrams
		printf(YELLOW "--> Searching Execution Time: %f seconds\n\n" RESET, (double)(clock() - searchTime) / CLOCKS_PER_SEC);
		printf (RED "*********************************************************************************************\n\n" RESET);
		
		free(str);
		
		char *cont = malloc(sizeof(char) * STR_MAX_LEN);
		printf ("Want to examine another string for anagrams? (yes/no)\n");
		fgets(cont,STR_MAX_LEN,stdin);
		cont[strcspn(cont,"\n")] = 0;
		
		if (strcmp(cont,"no") == 0) flag = 0;
		free(cont);
	}
	
	return 0;
}
