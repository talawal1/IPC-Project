/*/////////////////////////////////////////////////////////////////////////
						Assignment 1 - Milestone 3
Full Name  : Teslim Ajibola Lawal
Email      : talawal1@myseneca.ca
Section    : ZCC

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"
#include <string.h>
//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
	// Discard all remaining char's from the standard input buffer:
	while (getchar() != '\n')
	{
		; // do nothing!
	}
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
	printf("<ENTER> to continue...");
	clearInputBuffer();
	putchar('\n');
}

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
// 
//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Prompt user for a number until an integer value is entered
int inputInt(void) {
	int number = 0;
	char newLine = 0;

	// Flag
	int done = 0;

	// While loop continues until a valid number is entered 
	while (done != 1) {
		scanf("%d%c", &number, &newLine);

		if (newLine == '\n') {
			done = 1;
		}

		else {
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
	}
	return number;
}

// Prompt user for a number until a positive number is entered
int inputIntPositive(void) {
	int number = 0;
	int done = 0;

	// While loop continues until a number greater than zero is entered
	while (done != 1) {
		number = inputInt();

		if (number > 0) {
			done = 1;
		}

		else {
			printf("ERROR! Value must be > 0: ");

		}
	}
	return number;
}



// Prompt user for a number until one is inputted in specified range
int inputIntRange(int lowerBound, int upperBound) {
	int number = 0;
	int done = 0;

	while (done != 1) {
		number = inputInt();

		if ((number >= lowerBound) && (number <= upperBound)) {
			done = 1;
		}

		else {
			printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound); //error message
		}
	}
	return number;
}

// Prompt user for a single character until one among a list of valid characters is inputted
char inputCharOption(const char validCharacters[]) {
	char userString[3];
	userString[0] = '\0';
	int matched = 0; // Value to change if character is found
	int i;
	int length = 0;

	//Flag variable
	int done = 0;

	while (done != 1) {
		userString[0] = '\0';
		scanf("%2s", userString);
		clearInputBuffer();
		length = strlen(userString);

		// Check if length of string is zero, that is user entered only one character
		if (length == 1) {
			for (i = 0; ((validCharacters[i] != '\0') && done != 1); i++) {
				//printf("%s", userString);
				if (userString[0] == validCharacters[i]) {
					matched = 1;
					done = 1;
				}
			}
		}

		else {
			if (matched == 0) {
				printf("ERROR: Character must be one of [");
				// Loop until end of string (null byte is found)
				for (i = 0; (validCharacters[i] != '\0'); i++) {
					printf("%c", validCharacters[i]);
				}
				printf("]: ");
				//clearInputBuffer();

			}
		}
	}


	return userString[0];
}

// Prompt user for a C string until string of valid length is inputted
void inputCString(char* inputtedString, int minCharacters, int maxCharacters) {
	int inputtedStringLength = 0;
	inputtedString[0] = '\0';
	// Flags
	int done = 0;
	int i;

	// String to temporarily store user input
	char tempString[500];
	while (done != 1) {

		scanf("%[^\n]", tempString);
		clearInputBuffer();
		inputtedStringLength = strlen(tempString);

		if ((inputtedStringLength >= minCharacters) && (inputtedStringLength <= maxCharacters))
		{
			for (i = 0; i < maxCharacters; i++) {
				inputtedString[i] = tempString[i];
			}
			done = 1;
		}

		else {
			if (minCharacters == maxCharacters) {
				printf("Invalid 10-digit number! Number: ");
			}

			else {
				if (inputtedStringLength < minCharacters) {
					printf("ERROR: String length must be between %d and %d chars: ", minCharacters, maxCharacters);
				}
				else if (inputtedStringLength > maxCharacters) {
					printf("ERROR: String length must be no more than %d chars: ", maxCharacters);
				}

			}

		}
		inputtedStringLength = 0;
	}
	return;
}

// Display phone number in a formatted format
void displayFormattedPhone(const char* inputtedString) {
	int inputtedStringLength = 0;
	int i;
	int valid = 1;
	int done = 0;
	int phoneNumberLength = 10;

	// Check if string is empty
	if (inputtedString != NULL) {
		for (i = 0; (inputtedString[i] != '\0') && done != 1; i++)
		{
			inputtedStringLength += 1;

			// If character is not a number, string is invalid and therefore not formatted
			if ((inputtedString[i] < '0') || (inputtedString[i] > '9')) {
				valid = 0;
				done = 1;
			}
		}

		// Check that all charcters are valid and length is of right size(10)
		if ((valid == 1) && (inputtedStringLength == phoneNumberLength)) {
			printf("(%c%c%c)%c%c%c-%c%c%c%c", inputtedString[0], inputtedString[1], inputtedString[2], inputtedString[3], inputtedString[4], inputtedString[5], inputtedString[6], inputtedString[7], inputtedString[8], inputtedString[9]);
		}
		else {
			printf("(___)___-____");
		}
	}

	else {
		printf("(___)___-____");
	}

	return;
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
