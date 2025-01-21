#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>

using namespace std;

// Function to check if a string is a number
bool isNumber(string str);

// Function to check if an email is valid
bool isValidEmail(string email);

// Function to check if a fiscal code is valid (16 characters, uppercase letters or numbers)
bool isValidFiscalCode(string fiscalCode);

// Function to check if a date is valid (dd-mm-yyyy)
bool isValidDate(string date);

/*
    Function to select from standard input an option from a number of options
    @param optionsNumber The number of options available
    @param message The message to display to the user
    @return The selected option as an integer (0 is included as a special option)
*/
int selectInputOption(int optionsNumber, string message);

/*  
    Function to get a non-empty input from standard input
    @param message The message to display to the user
    @return The input as a string
*/
string getNotEmptyInput(string message);

/*  
    Function to create a CSV file if it does not exist
    @param fileName The name of the file to create
    @param headers The headers to write in the file
*/
void createCSVifNotExist(string fileName, string headers);
/*
    Function to delete a line in a CSV file
    @param fileName The name of the file to delete the line from
    @param lineIndex The index of the line to delete
*/
void deleteCSVLine(string fileName, int lineIndex);

/*
    Function to overwrite a line in a CSV file
    @param fileName The name of the file to overwrite the line in
    @param lineIndex The index of the line to overwrite
    @param contentToReplace The content to replace the line with
*/
void overwriteCSVLine(string fileName, int lineIndex, string contentToReplace);

#endif