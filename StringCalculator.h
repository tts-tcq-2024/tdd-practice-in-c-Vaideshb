#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Function declarations
static void extractDelimiter(const char** inputString, char* customDelimiter, int* delimiterOffset);
static bool checkDelimiter(char character, char customDelimiter);
static int sumNumbers(const char** inputString, char customDelimiter, int* negativeCount, int* negativeNumbers);
static void processSingleNumber(const char** inputString, char customDelimiter, int* totalSum, int* negativeCount, int* negativeNumbers);
static int parseInteger(const char** inputString, char customDelimiter);
static void handleNegative(int number, int* negativeNumbers, int* negativeCount);
static void validateNegatives(int* negativeNumbers, int negativeCount);
static void createNegativeMessage(char* errorMessage, int* negativeNumbers, int negativeCount);
static void appendNegativeNumbers(char* errorMessage, int* negativeNumbers, int negativeCount);

// Main function to add numbers in a string
int add(const char* inputString) {
    if (inputString == NULL || strlen(inputString) == 0) {
        return 0;
    }

    const char* currentPointer = inputString;
    char customDelimiter = ',';
    int delimiterOffset = 0;
    int totalSum = 0;
    int negativeNumbers[100];
    int negativeCount = 0;

    extractDelimiter(&currentPointer, &customDelimiter, &delimiterOffset);
    currentPointer += delimiterOffset;

    totalSum = sumNumbers(&currentPointer, customDelimiter, &negativeCount, negativeNumbers);

    validateNegatives(negativeNumbers, negativeCount);

    return totalSum;
}

// Extract custom delimiter from the input string
static void extractDelimiter(const char** inputString, char* customDelimiter, int* delimiterOffset) {
    if (**inputString == '/' && *(*inputString + 1) == '/') {
        *customDelimiter = *(*inputString + 2);
        *delimiterOffset = 4;
    } else {
        *delimiterOffset = 0;
    }
}

// Check if the character is a delimiter
static bool checkDelimiter(char character, char customDelimiter) {
    return character == customDelimiter || character == '\n';
}

// Sum the numbers in the input string
static int sumNumbers(const char** inputString, char customDelimiter, int* negativeCount, int* negativeNumbers) {
    int totalSum = 0;

    while (**inputString != '\0') {
        processSingleNumber(inputString, customDelimiter, &totalSum, negativeCount, negativeNumbers);

        if (checkDelimiter(**inputString, customDelimiter)) {
            (*inputString)++;
        }
    }

    return totalSum;
}

// Process a single number in the input string
static void processSingleNumber(const char** inputString, char customDelimiter, int* totalSum, int* negativeCount, int* negativeNumbers) {
    int number = parseInteger(inputString, customDelimiter);
    handleNegative(number, negativeNumbers, negativeCount);

    if (number <= 1000) {
        *totalSum += number;
    }
}

// Parse an integer from the input string
static int parseInteger(const char** inputString, char customDelimiter) {
    char buffer[100];
    int bufferIndex = 0;
    while (**inputString != '\0' && !checkDelimiter(**inputString, customDelimiter)) {
        buffer[bufferIndex++] = **inputString;
        (*inputString)++;
    }
    buffer[bufferIndex] = '\0';
    return atoi(buffer);
}

// Handle negative numbers by storing them in an array
static void handleNegative(int number, int* negativeNumbers, int* negativeCount) {
    if (number < 0) {
        negativeNumbers[*negativeCount] = number;
        (*negativeCount)++;
    }
}

// Validate if there are any negative numbers and handle them
static void validateNegatives(int* negativeNumbers, int negativeCount) {
    if (negativeCount > 0) {
        char errorMessage[200];
        createNegativeMessage(errorMessage, negativeNumbers, negativeCount);
        fprintf(stderr, "%s\n", errorMessage);
        exit(EXIT_FAILURE);
    }
}

// Create an error message for negative numbers
static void createNegativeMessage(char* errorMessage, int* negativeNumbers, int negativeCount) {
    sprintf(errorMessage, "negatives not allowed: ");
    appendNegativeNumbers(errorMessage, negativeNumbers, negativeCount);
}

// Append negative numbers to the error message
static void appendNegativeNumbers(char* errorMessage, int* negativeNumbers, int negativeCount) {
    for (int i = 0; i < negativeCount; i++) {
        char buffer[12];
        sprintf(buffer, "%d", negativeNumbers[i]);
        strcat(errorMessage, buffer);
        if (i < negativeCount - 1) {
            strcat(errorMessage, ",");
        }
    }
}

#endif // STRING_CALCULATOR_H
