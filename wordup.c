// Josephine McCue
// 4/26/2025
// CS 135 Project 10 

#include <stdio.h>
#define FILE_INPUT "mystery.txt"
#define CLUE_CAP 5 + 1
#define STR_CAP 100

void input_to_lowercase (int row, int length, char str[][length]);
void get_guess (int guessNum, int length, char guess[][length]);
int valid_check (int row, int length, char array[][length]);
void clear_array (int rows, int length, char array[][length]);
int check_guess (int row, int length, char guess[][length], char word[], char clues[][length]);
void display_clues (int rows, int length, char guess[][length], char clues[][length]);

int main (){
	char word[STR_CAP], guesses[6][STR_CAP], clues[6][CLUE_CAP];
	int guess = 0, correctGuess = 0;
	
	FILE *fp;
	fp = fopen(FILE_INPUT, "r");
	if (fp == NULL){
		printf("Sorry, could not get today's word. Try again tomorrow.\n");
		return 0;
	}
	fscanf (fp, "%s", word);
	fclose (fp);
	clear_array (6, CLUE_CAP, clues);
	do {	
		get_guess (guess, STR_CAP, guesses);
		
		input_to_lowercase(guess, STR_CAP, guesses);
		// check if guess is correct 
		// display previous guesses and clues (if incorrect) OR  display winning message if correct
		
		
		
		correctGuess = check_guess (guess, STR_CAP, guesses, word, clues);
		switch (correctGuess){
			case 0:
			//display previous guesses and clues 
				display_clues (guess, STR_CAP, guesses, clues);
				break;
			case 1: 
			//display word in all caps and then winning message
				printf("================================\n");
				printf("\t\t");
				for (int index = 0; index < CLUE_CAP - 1; index ++){
					printf("%c", word[index] - 32);
				}
				if (guess == 1){
				printf("\n\tYou won in %d guess!\n", guess + 1);
				}
				else {
				printf("\n\tYou won in %d guesses!\n", guess + 1);
				}
				switch (guess){
					case 1:
						printf("\t\tGOATED!\n");
						break;	
					case 2:
					case 3:
						printf("\t\tAmazing!\n");
						break;
					case 4:
					case 5:
						printf("\t\tNice!\n");
						break;
					default: 
				}
				break;
		}
		
	guess++;
	} while (guess < 6 && correctGuess == 0);
	
	if (correctGuess == 0){
	display_clues (guess, STR_CAP, guesses, clues);
	printf("You lost, better luck next time!\n");
	}
	
	return 0;
}

void input_to_lowercase (int row, int length, char str[][length]){
	for (int index = 0; str[row][index] != '\0'; index ++){
		if (str[row][index] <= 90 && str[row][index] >= 65){
			str[row][index] = str[row][index] - 32;
		}
	}
}

void get_guess (int guessNum, int length, char guess[][length]){
	int validGuess;
	if (guessNum < 5){
		printf("Guess %d! Enter your guess: ", guessNum + 1);
	}
	else {
		printf("FINAL GUESS : ");
	}
	
	scanf("%s", guess[guessNum]);
	
	validGuess = valid_check (guessNum, length, guess);
	
	while (validGuess == 0){
		printf("\nPlease try again: ");
		scanf("%s", guess[guessNum]);
		validGuess = valid_check (guessNum, length, guess);
	}
}
 
int valid_check (int row, int length, char array[][length]){
	int validLength = 1, validLetters = 1, valid = 1, strLength = 0;
	
	for (int index = 0; array[row][index] != '\0'; index ++){
		strLength++;
	}
	if (strLength != CLUE_CAP - 1){
		validLength = 0;
		printf("Your guess must be 5 letters long.");
	}
	
	for (int index = 0; array[row][index] != '\0'; index ++){
		if (array[row][index] < 65 || array[row][index] > 90 && array[row][index] < 97 || array[row][index] > 122){
			validLetters = 0;
		}
	}
	if (validLetters == 0){
		printf("Your guess must only contain letters.");
	}
	
	if (validLetters == 0 || validLength == 0){
		valid = 0;
	}

	return valid;
}
void clear_array (int rows, int length, char array[][length]){
	for (int rowIndex = 0; rowIndex < rows; rowIndex++){
		for (int lengthIndex = 0; lengthIndex < length; lengthIndex++){
			if (lengthIndex == length - 1){
				array[rowIndex][lengthIndex] = '\0';
			}
			else {
				array[rowIndex][lengthIndex] = ' ';
			}
		}
	}
}

int check_guess (int row, int length, char guess[][length], char word[], char clues[][length]){
	int correct = 1; 

	// finds right letters in wrong place and underlines: 
	for (int index = 0; word[index] != '\0'; index++){
		char letter = word[index];
		for (int i = 0; guess[row][i] != '\0'; i++){
			if (guess[row][i] == letter){
				clues[row][i] = '^';
				i = CLUE_CAP;
			}
		}
	}
	// makes letter uppercase if in the right place: 
	for (int index = 0; word[index] != '\0'; index++){
		if (guess[row][index] == word[index]){
			guess[row][index] = guess[row][index] - 32; 
			clues[row][index] = ' ';
		}
		else {
			correct = 0;
		}
	}
	return correct;
}
void display_clues (int rows, int length, char guess[][length], char clues[][length]){
	printf("================================\n");
	for (int index = 0; index < rows + 1; index ++){
		printf("%s\n", guess[index]);
		printf("%s\n", clues[index]);
	}
}
