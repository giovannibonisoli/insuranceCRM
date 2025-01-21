#include "utils.h"
#include <regex>


bool isNumber(string str){
    for (char ch : str) {
        int v = ch;
        if (!(ch >= 48 && ch <= 57)) {
            return false;
        }
    }
 
    return true;
}

bool isValidEmail(string email){
    regex emailRegex(R"(^[^\s@]+@[^\s@]+\.[^\s@]+$)");
    return regex_match(email, emailRegex);
}

bool isValidFiscalCode(string fiscalCode){
    regex fiscalCodeRegex("^[A-Z0-9]{16}$");
    return regex_match(fiscalCode, fiscalCodeRegex);
}

bool isValidDate(string date) {
    regex datePattern(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-(\d{4})$)");
    return std::regex_match(date, datePattern);
}


int selectInputOption(int optionsNumber, string message){

    while(1){
        // Get the user input ensuring its not empty
        string input = getNotEmptyInput(message);

        // Check if the input is a number
        if (isNumber(input)) {

            int chosenOption = stoi(input);

            // Check if the input is among the available options
            if(chosenOption >= 0 and chosenOption <= optionsNumber){
                return chosenOption;
            }
            else{
                cout << "Insert a number among the available options!" << endl;
            }
        }
        else{
            cout << "Insert a numeric value!" << endl;
        }
    }
}


string getNotEmptyInput(string message){
    string input;

    while (1){
        cout << endl;
        cout << message;
        getline(cin, input);

        // Check if the input is empty
        if (input.size() == 0){
            cout << "No empty input is allowed!" << endl;
        }
        else{
            break;
        }
    }

    cout << endl;
    return input;
}


void createCSVifNotExist(string fileName, string headers){
    ifstream file(fileName);

    // Check if the file exists
    if (!file.is_open()) {

        // Create the file if it does not exist
        ofstream newFile(fileName);
        if (!newFile) {
            cerr << "Error while creating the file: " << fileName << endl;
        }
        else{ 
            
            newFile << headers << endl;
            newFile.close();

            cout << "File created: " << fileName << endl;
            cout << endl;
        }
    }
}

void deleteCSVLine(string fileName, int lineIndex){

    ifstream file(fileName);

    // Check if the file exists
    if (!file.is_open()) {
        cerr << "Error while opening the file: " << fileName << endl;
    }
    else{
        
        vector<string> lines;
        string line;

        // Get all the lines except the one to delete
        int i = 0;
        while (getline(file, line)) {
            if (i != lineIndex){
                stringstream ss(line);

                string lineContent;
                getline(ss, lineContent, '\n');

                lines.push_back(lineContent);
            }
            ++i;
        }

        file.close();

        // Write the lines back to the file
        ofstream file(fileName);
        for (i=0; i<lines.size(); ++i){
            file << lines[i] << endl;
        }

        file.close();
    }
}


void overwriteCSVLine(string fileName, int lineIndex, string contentToReplace){

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error while opening the file: " << fileName << endl;
    }
    else{
        vector<string> lines;
        string line;

        // Get all the lines except the one to overwrite
        int i = 0;
        while (getline(file, line)) {
            if (i != lineIndex){
                stringstream ss(line);

                string lineContent;
                getline(ss, lineContent, '\n');

                lines.push_back(lineContent);
            }
            else{

                // Replace the line with the new content
                lines.push_back(contentToReplace);
            }

            ++i;
        }

        file.close();

        // Write the lines back to the file
        ofstream file(fileName);
        for (i=0; i<lines.size(); ++i){
            file << lines[i] << endl;
        }

        file.close();
    }
}