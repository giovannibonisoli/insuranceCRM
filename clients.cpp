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
    cout << "Description: " << description << endl;
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

// Setter methods. ClientID is not settable, it is unique.
void Client::setName(string _name){
    if (_name.empty()){
        cout << "Name cannot be empty" << endl;
    }
    else{
        name = _name;
    }
}

void Client::setSurname(string _surname){
    if (_surname.empty()){
        cout << "Surname cannot be empty" << endl;
    }
    else{
        surname = _surname;
    }
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

    // Create the file with the interaction of the clients if it does not exist
    // It is identified by the clientID
    string fileName = "data/interactions" + to_string(clientID) + ".csv";
    createCSVifNotExist(fileName, "type,date,description");

    interactions.clear();

    ifstream file(fileName);
    string line;

    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        if (i == 0){

            // Skip the headers
            string headers;
            getline(ss, headers, '\n');
        }
        else{

            // Read the interaction data
            string type, date, description;

            getline(ss, type, ',');
            getline(ss, date, ',');
            getline(ss, description, '\n');

            Interaction newInteraction(type, date, description);
            interactions.push_back(newInteraction);
        }
        ++i;
    }

    file.close();
}


void Client::addInteraction(Interaction newInteraction){

    // Open the interaction file in append mode
    string fileName = "data/interactions" + to_string(clientID) + ".csv";
    ofstream interactionsFile(fileName, ios::app);
    
    if (!interactionsFile) {
        cerr << "Error while opening the file: " << fileName << endl;
    }
    else{  

        interactionsFile << newInteraction.getType() << ",";
        interactionsFile << newInteraction.getDate() << ",";
        interactionsFile << newInteraction.getDescription() << "\n";

        interactionsFile.close();

        // Call readInteractions to update the interactions vector
        readInteractions();
    }

}

void Client::printInteractions(){

    if (interactions.size() > 0){
        cout << endl;
        cout << "Here are all the interactions of " << name << " " << surname << endl;
        cout << endl;

        // Print all the interactions
        for (Interaction interaction : interactions){
            interaction.printInteraction();
            cout << endl;
        }
        cout << endl;
    }
    else{
        cout << "No interactions have been found for " << name << " " << surname << endl;
        cout << endl;
    }
    
}


void Client::printFilteredInteractions(string type, string date, string description){

    if (interactions.size() > 0){

        // Filter the interactions based on the criteria
        vector<Interaction> filteredInteraction;
        for (Interaction interaction : interactions){
            if ((!type.empty() && interaction.getType() == type) || 
                (!date.empty() && interaction.getDate() == date) || 
                (!description.empty() && interaction.getDescription().find(description) != string::npos)){

                filteredInteraction.push_back(interaction);
            }
        }

        // Print the filtered interactions if any has been found
        if (filteredInteraction.size() != 0){
            cout << "Client: " << name << " " << surname << endl;
            cout << endl;
            for (Interaction interaction : filteredInteraction){
                interaction.printInteraction();
                cout << endl;
            }
        }
    }
}


void Client::deleteInteractions(){

    // Delete the file with the interactions of the client
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


Client *ClientsManager::getClientByID(int clientID){
    for (Client& client : clients){
        if(clientID == client.getClientID()){
            return &client;
        }
    }

    return nullptr;
}


int ClientsManager::getCSVLineByClientID(int clientID){
    ifstream file(clientsFilePath);
    string line;


    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        if (i == 0){

            // Skip the headers
            string fields;
            getline(ss, fields, '\n');
        }
        else{
            
            string strID;
            getline(ss, strID, ',');

            int currentID = stoi(strID);

            // If the clientID is found, return the line number
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

    // Create the file with the clients if it does not exist
    createCSVifNotExist(clientsFilePath, "clientID,name,surname,fiscalCode,email");

    ifstream file(clientsFilePath);
    string line;

    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        if (i == 0){

            // Skip the headers
            string headers;
            getline(ss, headers, '\n');
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

            // Once the client is created, call this function to create the interaction CSV file
            newClient.readInteractions();

            clients.push_back(newClient);
        }
        i++;
    }

    file.close();
}


int ClientsManager::selectClientIDbyInput(){
    string message = "Select a client by the numeric index (0 to exit): ";

    int indexClient = selectInputOption(clients.size(), message);

    // 0 as return value is treated as an option to exit
    if(indexClient == 0){
        return -1;
    }

    return clients[indexClient - 1].getClientID();
}


void ClientsManager::addClient(string name, string surname, string fiscalCode, string email){

    ofstream clientsFile(clientsFilePath, ios::app);
    
    if (!clientsFile) {
        cerr << "Error while opening the file: " << clientsFilePath << endl;
    }
    else{  

        int newID = 0;

        // If there are clients, find the highest ID and increment it to create a new one
        if (clients.size() != 0){
            for (int i=0; i<clients.size(); ++i){
                int currentID = clients[i].getClientID();
                if (currentID > newID){
                    newID = currentID;
                }
            }
            ++newID;
        }

        // Write the new client to the CSV file
        clientsFile << newID << ",";
        clientsFile << name << ",";
        clientsFile << surname << ",";
        clientsFile << fiscalCode << ",";
        clientsFile << email << endl;
        clientsFile.close();

        Client newClient(newID, name, surname, fiscalCode, email);

        // Once the client is created, call this function to create the interaction CSV file
        newClient.readInteractions();

        // Call readClients to update the clients vector
        readClients();
    }
}


void ClientsManager::deleteClient(int clientID){
    Client* client = getClientByID(clientID);
    if (client) {
        // Before deleting the client, delete the interactions CSV file
        client->deleteInteractions();

        // Delete the client from the clients CSV file
        int lineIndex = getCSVLineByClientID(clientID);
        deleteCSVLine(clientsFilePath, lineIndex);

        // Call readClients to update the clients vector
        readClients();

    } else {
        std::cout << "Client not found!" << std::endl;
    }    
}


void ClientsManager::editClient(int clientID, string name, string surname, string fiscalCode, string email){

    Client* client = getClientByID(clientID);
    if (client) {

        if (!name.empty()){
            client->setName(name);
        }
        if (!surname.empty()){
            client->setSurname(surname);
        }
        if(!fiscalCode.empty()){
            client->setFiscalCode(fiscalCode);
        }
        if(!email.empty()){
            client->setEmail(email);
        }

        // OverWrite the line in the CSV file corresponding to the client with the new data
        int lineIndex = getCSVLineByClientID(clientID);

        string contentToReplace = to_string(clientID) + ',' + client->getName();
        contentToReplace += ',' + client->getSurname() + ',';
        contentToReplace += client->getFiscalCode() + ',' + client->getEmail();

        overwriteCSVLine(clientsFilePath, lineIndex, contentToReplace);

        // Call readClients to update the clients vector
        readClients();

        
    } else {
        std::cout << "Client not found!" << std::endl;
    }   
}


void ClientsManager::printFilteredClients(string filterName, string filterSurname){
    
    vector<Client> filteredClients;

    // Filter the clients based on the criteria
    for (Client client : clients){
        if ((!filterName.empty() && client.getName().find(filterName) != string::npos) || 
            (!filterSurname.empty() && client.getSurname().find(filterSurname) != string::npos)){
            filteredClients.push_back(client);
        }
    }

    // Print the filtered clients if any has been found
    if (filteredClients.size() != 0){
        cout << endl;
        cout << "Here are the clients matching the filter!" << endl;
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
        cout << "Here are all the inserted clients!" << endl;
        cout << endl;
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


void ClientsManager::addInteraction(int clientID, string type, string date, string description){
    Client* client = getClientByID(clientID);

    if (client) {
        Interaction newInteraction(type, date, description);

        // Add the interaction to the client
        client->addInteraction(newInteraction);

    }
    else {
        std::cout << "Client not found!" << std::endl;
    }   
}


void ClientsManager::printClientInteractions(int clientID){
    Client* client = getClientByID(clientID);
    if (client) {
        client->printInteractions();
    } 
    else {
        std::cout << "Client not found!" << std::endl;
    }
}


void ClientsManager::printFilteredInteractions(string type, string date, string description){
    cout << endl;
    cout << "Here are the interactions matching to the inserted filters!" << endl;
    cout << endl;
    for (Client client : clients){
        client.printFilteredInteractions(type, date, description);
        cout << endl;
    }
}
