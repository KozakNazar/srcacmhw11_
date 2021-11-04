#define _CRT_SECURE_NO_WARNINGS
/******************************************************************
* Lviv'2020 // ACM // Boyer–Moore string-search algorithm example *
*    file: acmhw14.c                                              *
*******************************************************************/
#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#define MAX_WORD_SIZE 64
#define MAX_WORDS 256

#define CHAR_COUNT 256 

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void printMatchIndexes(int * matchIndexes){
	printf("matchIndexes:\r\n");
	if (*matchIndexes != -1) do{
		printf("%d\r\n", *matchIndexes);
	} while (*++matchIndexes);
}

void badCharHeuristic(char *str, int size, int badchars[CHAR_COUNT]){
	int index;
	for (index = 0; index < CHAR_COUNT; badchars[index++] = -1);
	for (index = 0; index < size; badchars[(int)str[index]] = index, ++index);
}

void limitedSearch(char *text, int textSize, char *pattern, int patternSize, int * matchIndexes){
	int scanner;
	int badchars[CHAR_COUNT];
	//int patternSize = (int)strlen(pattern);
	//int textSize = (int)strlen(text);

	badCharHeuristic(pattern, patternSize, badchars);

	for (scanner = 0; scanner <= (textSize - patternSize);){
		int downScanner = patternSize;
		while (--downScanner >= 0 && pattern[downScanner] == text[scanner + downScanner]);

		if (downScanner < 0){
			*matchIndexes++ = scanner;
			scanner += (scanner + patternSize < textSize) ? patternSize - badchars[(int)text[scanner + patternSize]] : 1;
		}
		else{
			scanner += MAX(1, downScanner - badchars[(int)text[scanner + downScanner]]);
		}
	}
}

void search(char* text, char* pattern, int* matchIndexes) {
	limitedSearch(text, (int)strlen(text), pattern, (int)strlen(pattern), matchIndexes);
}

int main(){
	int matchIndexes[MAX_WORDS] = { -1 };
	char * text = (char*)
		"Sir, in my heart there was a kind of fighting "
		"That would not let me sleep. Methought I lay "
		"Worse than the mutines in the bilboes. Rashly- "
		"And prais'd be rashness for it-let us know "
		"Our indiscretion sometimes serves us well ... "
		; // — Hamlet, Act 5, Scene 2, 4–8

	search(text, (char*)"let", matchIndexes);

	printMatchIndexes(matchIndexes);

#ifdef __linux__ 
	(void)getchar();
#elif defined(_WIN32)    
	system("pause");
#else
#endif

	return 0;
}
