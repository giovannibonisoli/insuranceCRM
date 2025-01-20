#include "clients.h"


Interaction::Interaction(string _type, string _date, string _description){
    type = _type;
    date = _date;
    description = _description;
}

string Interaction::getType(){
    return type;
}
        
string Interaction::getDate(){
    return date;            
}

string Interaction::getDescription(){
    return description;
}

void Interaction::printInteraction(){
    cout << "Type: " << type << endl;
    cout << "Date: " << date << endl;
    cout << "Description" << description << endl;
}


Client::Client(int _clientID, string _name, string _surname, string _fiscalCode, string _email){
    clientID = _clientID;
    name = _name;
    surname = _surname;
    fiscalCode = _fiscalCode;
    email = _email;
}

// Getter methods
int Client::getClientID(){
    return clientID;
}

string Client::getName(){
    return name;
}

string Client::getSurname(){
    return surname;
}

string Client::getFiscalCode(){
    return fiscalCode;
}

string Client::getEmail(){
    return email;
}

vector<Interaction> Client::getInteractions(){
    return interactions;
}

        // Setter methods. ClientID is not settable, it is unique.
void Client::setName(string _name){
    name = _name;
}

void Client::setSurname(string _surname){
    surname = _surname;
}

void Client::setFiscalCode(string _fiscalCode){
    if (isValidFiscalCode(_fiscalCode)){
        fiscalCode = _fiscalCode;
    }
    else{
        cout << "Fiscal code format not valid" << endl;
    }
}

void Client::setEmail(string _email){
    if (isValidEmail(_email)){
        email = _email;
    }
    else{
        cout << "Email format not valid" << endl;
    }
}

void Client::readInteractions(){
    string fileName = "data/interactions" + to_string(clientID) + ".csv";
    createCSVifNotExist(fileName, "type,date,description");

    ifstream file(fileName);
    string line;

    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        if (i == 0){
            string fields;
            getline(ss, fields, '\n');
        }
        else{
            string type, date, description;

            getline(ss, type, ',');
            getline(ss, date, ',');
            getline(ss, description, '\n');

            Interaction newInteraction(type, date, description);

            interactions.push_back(newInteraction);
        }
    }

    file.close();
}


void Client::deleteInteractions(){
    string fileName = "data/interactions" + to_string(clientID) + ".csv";
    remove(fileName.c_str());
 
    if (ifstream{fileName}.is_open())
    {
        cerr << "Error: Opening the deleted file: " << fileName << endl;
    }
}


void Client::printClient(){
    cout << "Name: " << name << endl;
    cout << "Surname: " << surname << endl;
    cout << "Fiscal Code: " << fiscalCode << endl;
    cout << "Email: " << email << endl;
}



int ClientsManager::getFileLIneByClientID(int clientID){

    ifstream file(clientsFilePath);
    string line;


    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        if (i == 0){
            string fields;
            getline(ss, fields, '\n');
        }
        else{
            string strID;
            getline(ss, strID, ',');

            int currentID = stoi(strID);
            if (currentID == clientID){
                file.close();
                return i;
            }
        }
        ++i;
    }

    return -1;
}


ClientsManager::ClientsManager(){
    clientsFilePath = "data/clients.csv";
}

void ClientsManager::readClients(){

    clients.clear();
    createCSVifNotExist(clientsFilePath, "clientID,name,surname,fiscalCode,email");

    ifstream file(clientsFilePath);
    string line;

    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        if (i == 0){
            string fields;
            getline(ss, fields, '\n');
        }
        else{
            int clientID;
            string name, surname, fiscalCode, email, strID;

            getline(ss, strID, ',');
            getline(ss, name, ',');
            getline(ss, surname, ',');
            getline(ss, fiscalCode, ',');
            getline(ss, email, '\n');

            clientID = stoi(strID);
            Client newClient(clientID, name, surname, fiscalCode, email);

            newClient.readInteractions();

            clients.push_back(newClient);
        }
        i++;
    }

    file.close();
}

vector<int> ClientsManager::getClientsIDs(){
    vector<int> IDs;

    for (Client client : clients){
        IDs.push_back(client.getClientID());
    }

    return IDs;
}

void ClientsManager::addClient(string name, string surname, string fiscalCode, string email){

    ofstream clientsFile(clientsFilePath, ios::app);
    
    if (!clientsFile) {
        cerr << "Error while opening the file: " << clientsFilePath << endl;
    }
    else{  

        int newID = 0;

        if (clients.size() != 0){
            for (int i=0; i<clients.size(); ++i){
                int currentID = clients[i].getClientID();
                if (currentID > newID){
                    newID = currentID;
                }
            }

            ++newID;
        }

        Client newClient(newID, name, surname, fiscalCode, email);
        clientsFile << newID << ",";
        clientsFile << name << ",";
        clientsFile << surname << ",";
        clientsFile << fiscalCode << ",";
        clientsFile << email << endl;
        clientsFile.close();

        newClient.readInteractions();

        clients.push_back(newClient);
    }
}

void ClientsManager::deleteClient(int clientID){

    for (int i = 0; i < clients.size(); ++i){
        if(clients[i].getClientID() == clientID){
            clients[i].deleteInteractions();
        }
    }

    int lineIndex = getFileLIneByClientID(clientID);

    deleteLine(clientsFilePath, lineIndex);
}

void ClientsManager::editClient(int clientID, string name, string surname, string fiscalCode, string email){

    for (int i = 0; i < clients.size(); ++i){
        if(clients[i].getClientID() == clientID){
            if (!name.empty()){
                clients[i].setName(name);
            }
            if (!surname.empty()){
                clients[i].setSurname(surname);
            }
            if(!fiscalCode.empty()){
                clients[i].setFiscalCode(fiscalCode);
            }
            if(!email.empty()){
                clients[i].setEmail(email);
            }

            int lineIndex = getFileLIneByClientID(clientID);

            string contentToReplace = to_string(clientID) + ',' + clients[i].getName();
            contentToReplace += ',' + clients[i].getSurname() + ',';
            contentToReplace += clients[i].getFiscalCode() + ',' + clients[i].getEmail();

            overwriteLine(clientsFilePath, lineIndex, contentToReplace);
        }
    }
}


void ClientsManager::printFilteredClients(string filterName, string filterSurname){
    
    vector<Client> filteredClients;

    for (Client client : clients){
        if ((!filterName.empty() && client.getName().find(filterName) != string::npos) || 
            (!filterSurname.empty() && client.getSurname().find(filterSurname) != string::npos)){
            filteredClients.push_back(client);
        }
    }


    if (filteredClients.size() != 0){
        cout << endl;
        cout << "Here are all the inserted clients!" << endl;
        for (int i=0; i < filteredClients.size(); ++i){
            cout << "Client " << i+1 <<  endl;
            filteredClients[i].printClient();
            cout << endl;
        }
    
    }
    else{
        cout << "No client has been found!" << endl;
        cout << endl;
    }
}


void ClientsManager::printClients(){

    cout << endl;
    if (clients.size() != 0){
        cout << "Here are all the clients matching the inserted data!" << endl;
        for (int i=0; i < clients.size(); ++i){
            cout << "Client " << i+1 <<  endl;
            clients[i].printClient();
            cout << endl;
        }
    
    }
    else{
        cout << "No client has been inserted!" << endl;
        cout << endl;
    }
}




