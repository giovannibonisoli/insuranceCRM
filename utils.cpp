#include "utils.h"
#include <regex>


bool isValidEmail(string email){
    regex emailRegex(R"(^[^\s@]+@[^\s@]+\.[^\s@]+$)");
    return regex_match(email, emailRegex);
}

bool isValidFiscalCode(string fiscalCode){
    regex fiscalCodeRegex("^[A-Z0-9]{16}$");
    return regex_match(fiscalCode, fiscalCodeRegex);
}


int chooseOption(int optionsNumber, string message){

    while(1){
        string input = getNotEmptyInput(message);

        if (isNumber(input)) {
            int chosenOption = stoi(input);
            if(chosenOption >= 0 and chosenOption <= optionsNumber){
                return chosenOption;
            }
            else{
                cout << "Insert a number among the available options!" << endl;
            }
        }
        else{
            cout << "Insert a valid number!" << endl;
        }
    }
}


void createCSVifNotExist(string fileName, string fields){
    ifstream file(fileName);
    if (!file.is_open()) {
        ofstream newFile(fileName);
        if (!newFile) {
            cerr << "Error while creating the file: " << fileName << endl;
        }
        else{  
            newFile << fields << endl;
            newFile.close();
            cout << "File created: " << fileName << endl;

            newFile.close();
        }
    }
}

void deleteLine(string fileName, int lineIndex){

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error while opening the file: " << fileName << endl;
    }
    else{
        
        vector<string> lines;
        string line;

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

        ofstream file(fileName);
        for (i=0; i<lines.size(); ++i){
            file << lines[i] << endl;
        }

        file.close();
    }
}


void overwriteLine(string fileName, int lineIndex, string contentToReplace){

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error while opening the file: " << fileName << endl;
    }
    else{
        
        vector<string> lines;
        string line;

        int i = 0;
        while (getline(file, line)) {
            if (i != lineIndex){
                stringstream ss(line);

                string lineContent;
                getline(ss, lineContent, '\n');

                lines.push_back(lineContent);
            }
            else{
                lines.push_back(contentToReplace);
            }

            ++i;
        }

        file.close();

        ofstream file(fileName);
        for (i=0; i<lines.size(); ++i){
            file << lines[i] << endl;
        }

        file.close();
    }
}


bool isNumber(string str){
    for (char ch : str) {
        int v = ch;
        if (!(ch >= 48 && ch <= 57)) {
            return false;
        }
    }
 
    return true;
}

string getNotEmptyInput(string message){

    string input;

    while (1){
        cout << endl;
        cout << message;
        getline(cin, input);

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