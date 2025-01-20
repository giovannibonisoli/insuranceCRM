#ifndef CLIENTS_H
#define CLIENTS_H

#include "utils.h"
#include <bits/stdc++.h>

using namespace std;
using namespace chrono;



class Interaction{
    string type;
    string date;
    string description;

    public:
        Interaction(string _type, string _date, string _report);

        string getType();
        
        string getDate();

        string getDescription();

        void printInteraction();
};


class Client{

    int clientID;
    string name, surname;
    string fiscalCode, email;
    vector<Interaction> interactions;
    
    public:
        Client(int _clientID, string _name, string _surname, string _fiscalCode, string _email);

        // Getter methods
        int getClientID();

        string getName();

        string getSurname();

        string getFiscalCode();

        string getEmail();

        vector<Interaction> getInteractions();

        // Setter methods. ClientID is not settable, it is unique.
        void setName(string _name);

        void setSurname(string _surname);

        void setFiscalCode(string _fiscalCode);

        void setEmail(string _email);

        // handle Interactions
        void readInteractions();

        void addInteraction(Interaction newInteraction);

        vector<Interaction> filterInteractionsByType(string type);

        void deleteInteractions();

        void printClient();
};


class ClientsManager{
    string clientsFilePath;
    vector<Client> clients;

    int getFileLIneByClientID(int clientID);
    
    public:
        ClientsManager();

        void readClients();

        vector<int> getClientsIDs();

        void addClient(string name, string surname, string fiscalCode, string email);

        void deleteClient(int clientID);

        void editClient(int clientID, string name, string surname, string fiscalCode, string email);

        void printFilteredClients(string filterName, string filterSurname);

        void printClients();

        void printClientInteractions(int clientID);
};

#endif