#include "clients.h"


void showMainMenu(){
    cout << "MAIN MENU" << endl;
    cout <<  endl;
    cout << "1. Show all clients" << endl;
    cout << "2. Add new client" << endl;
    cout << "3. Edit client" << endl;
    cout << "4. Delete client" << endl;
    cout << "5. Search client" << endl;
    cout << "6. Add Interaction" << endl;
    cout << "7. Visualize client interactions" << endl;
    cout << "8. Search interactions" << endl;
    cout << "9. Exit" << endl;
    cout <<  endl;
}



int main(){
    ClientsManager manager;

    manager.readClients();


    cout << "Welcome to InsuraPro CRM!" << endl;
    cout << endl;


    while (1){

        showMainMenu();

        int optionNumber = chooseOption(9, "Choose a menu option: ");

        if (optionNumber == 1){
            // 1. Show all clients

            manager.printClients();
        }
        else if (optionNumber == 2){
            // 2. Add new client

            string name, surname, fiscalCode, email;
            
            name = getNotEmptyInput("Insert name: ");
            surname = getNotEmptyInput("Insert surname: ");

            while (1){
                fiscalCode = getNotEmptyInput("Insert fiscalCode: ");
                if(isValidFiscalCode(fiscalCode)){
                    break;
                }
                else{
                    cout << "No valid fiscal code inserted" << endl;
                }

            }

            while (1){
                email = getNotEmptyInput("Insert email: ");
                if(isValidEmail(email)){
                    break;
                }
                else{
                    cout << "No valid email inserted" << endl;
                }

            }

            manager.addClient(name, surname, fiscalCode, email);
            
        }
        else if (optionNumber == 3){
            // 3. Edit client

            manager.printClients();

            int clientID = manager.selectClientIDbyInput();


            string newName;
            cout << "Insert name (Press enter to leave unchanged): ";
            getline(cin, newName);

            string newSurname;
            cout << "Insert surname (Press enter to leave unchanged): ";
            getline(cin, newSurname);

            string newFiscalCode;
            while (1){
                cout << "Insert fiscal code (Press enter to leave unchanged): ";
                getline(cin, newFiscalCode);

                if(!newFiscalCode.empty() && !isValidFiscalCode(newFiscalCode)){
                    cout << "Fiscal code must contain 16 ";
                    cout << "numeric characters or capital letters" << endl;
                }
                else{
                    break;
                }
            }

            string newEmail;
            while (1){
                cout << "Insert email (Press enter to leave unchanged): ";
                getline(cin, newEmail);

                if(!newEmail.empty() && !isValidEmail(newEmail)){
                    cout << "Email must follow the format <address>@<domain>.<country> " << endl;
                }
                else{
                    break;
                }
            }
            
            if (newName.empty() && newSurname.empty() && 
                newEmail.empty() && newFiscalCode.empty()){
                    cout << "No data has been modified" << endl;
            }
            else{
                manager.editClient(clientID, newName, newSurname, newFiscalCode, newEmail);
            }
            
        }
        else if (optionNumber == 4){
            // 4. Delete client

            manager.printClients();
            int clientID = manager.selectClientIDbyInput();

            manager.deleteClient(clientID);
        }
        else if (optionNumber == 5){
            // 5. Search client

            string filterName;
            cout << "Insert name (Press enter to leave it empty): ";
            getline(cin, filterName);

            string filterSurname;
            cout << "Insert surname (Press enter to leave it empty): ";
            getline(cin, filterSurname);

            if (filterName.empty() && filterSurname.empty()){
                cout << "No data data inserted for search" << endl;
            }
            else{
                manager.printFilteredClients(filterName, filterSurname);
            }
        }
        else if (optionNumber == 6){
            // 6. Add Interaction

            manager.printClients();
            int clientID = manager.selectClientIDbyInput();

            string type, date, description;
            
            while (1){
                type = getNotEmptyInput("Insert the interaction type (contract or appointment): ");

                if (type == "contract" || type == "appointment"){
                    break;
                }
                else {
                    cout << "Interaction type must be a 'appointment or a 'contract'" << endl;
                }
            }


            while (1){
                date = getNotEmptyInput("Insert the interaction date (dd-mm-yyyy): ");
                if(isValidDate(date)){
                    break;
                }
                else{
                    
                    cout << "Email must follow the format dd-mm-yyyy" << endl;
                }
            }


            description = getNotEmptyInput("Insert the interaction description: ");
            manager.addInteraction(clientID, type, date, description);
        }
        else if (optionNumber == 7){
            // 7. Visualize client interactions

            manager.printClients();
            int clientID = manager.selectClientIDbyInput();
            manager.printClientInteractions(clientID);
        }
        else if (optionNumber == 9){
            // 9. Exit
            cout << "Goodbye!" << endl;
            break;
        }
    }

    // manager.deleteUser(0);
}