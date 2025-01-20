#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>

using namespace std;


bool isValidEmail(string email);

bool isValidFiscalCode(string fiscalCode);

void createCSVifNotExist(string fileName, string fields);

void deleteLine(string fileName, int lineIndex);

void overwriteLine(string fileName, int lineIndex, string contentToReplace);

bool isNumber(string str);

string getNotEmptyInput(string message);

#endif