#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
	char* word; // Dynamically allocated string
	int frequency;
} WordFrequency;

//Global word frequency array and word count
//Both setted empty first
WordFrequency* wordArray = NULL;
int wordCount = 0;

void readfile_procceswords();
int search_word(char *word);
void new_word(char *word);
void free_memory();
void display_result();
// I break down my program with given functions (Implementation Guidelines 1)

//The program is divided into the given functions as provided in the assignment instructions.
//Implementation Guidelines 1
int main() {
	
	readfile_procceswords();
	display_result();
	free_memory();
	return 0;
}

//Function that reads the string in the file named input.txt
//Extracts words with usage of fscanf function
//Filters the nonleters with isalpha function
//Converts to lowercase letters with tolower function
//If there is the same exact word in data it add 1 to frequency if not it creates a new word

void readfile_procceswords()
{
	int i, j=0;
	char clean[50],
		 word[50];
	
	FILE *inp = fopen("input.txt" ,"r");
	
	if (inp == NULL)
	{
		printf("File is not opened");
	}
	
	while(fscanf(inp, "%s", word)==1){
		int j=0;
		char clean [60];
		for(i=0;word[i]!='\0';i++){
			if(isalpha(word[i]))
			clean[j++]=tolower(word[i]);
		}
		
//***forgetting this part has made many attempts with errors
	clean[j]='\0';

//Using the functions that defined bottom
//Searched the word to use the appropriate approach
	if(strlen(clean)>0)
	{
	int	placeOfSearchedWord=search_word(clean);
	if(placeOfSearchedWord!=-1){
		wordArray[placeOfSearchedWord].frequency++;	
	}
	else{
		new_word(clean);
	}
	}
}
//***
	fclose(inp);
}

//Allocate memory for new word, copy the new word and set frequency of new word to 1
//Reallocate wordArray to include new index
//used malloc() and realloc() functions
void new_word(char *word)
{
	int wordLength=strlen(word) + 1;
	int newWordCount= (wordCount + 1) * sizeof(WordFrequency);

	wordArray = realloc(wordArray, newWordCount);
	wordArray[wordCount].word = malloc(wordLength);

	strcpy(wordArray[wordCount].word, word);
	wordArray[wordCount].frequency = 1;
	wordCount++;
}

// Searches for a word in wordArray by comparing strings with strcmp function
//retun -1 if it is a new word, otherwise return the first index word is used

int search_word(char *word)
{
	int i=0, areTheySame, sameWith=-1;
	for(i=0;i<wordCount;i++){
	areTheySame=strcmp(word,wordArray[i].word);
		if(areTheySame==0){
			sameWith=i;
		}
	}
	return sameWith;
}

//free memory in array and words in array with free() function
void free_memory()
{
	int i;
	for(i=0;i<wordCount;i++)
	{
		if(wordArray[i].word != NULL) 
			free(wordArray[i].word);
	}
	
	if(wordArray != NULL)
		free(wordArray);
}

//Prints each word and frequency
//
void display_result()
{
	int i;
	printf("Word Frequency:\n");
	for(i=0;i<wordCount;i++)
		printf("%s : %d\n", wordArray[i].word, wordArray[i].frequency);
}



