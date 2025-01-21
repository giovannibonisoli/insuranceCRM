#ifndef CLIENTS_H
#define CLIENTS_H

#include "utils.h"
#include <bits/stdc++.h>

using namespace std;
using namespace chrono;



class Interaction {
    /*
        The Interaction class represents a single interaction related to a client.
        Each interaction contains details about the type, date, and a description.
    */

    string type;        // The type of the interaction (contract or appointment).
    string date;        // The date of the interaction in a specific format (e.g., DD-MM-YYYY).
    string description; // A brief description of the interaction.

    public:
        /*
            Constructor for the Interaction class.
            Initializes an interaction with the given type, date, and description.
            @param _type The type of the interaction.
            @param _date The date of the interaction.
            @param _report A description of the interaction.
        */
        Interaction(string _type, string _date, string _report);

        /*
            Retrieves the type of the interaction.
            @return A string representing the interaction type.
        */
        string getType();

        /*
            Retrieves the date of the interaction.
            @return A string representing the interaction date.
        */
        string getDate();

        /*
            Retrieves the description of the interaction.
            @return A string representing the interaction description.
        */
        string getDescription();

        /*
            Prints the details of the interaction (type, date, description) to the console.
        */
        void printInteraction();
};



class Client {
    /*
        The Client class represents a single client in the system.
        Each client has a unique ID, personal information (name, surname, fiscal code, email),
        and a list of interactions associated with them.
    */

    int clientID;                // Unique identifier for the client. Non editable.
    string name, surname;        // Client's first and name.
    string fiscalCode, email;    // Client's fiscal code and email address.
    vector<Interaction> interactions; // List of interactions associated with the client.

    public:
        /*
            Constructor for the Client class.
            Initializes a client with the given ID, name, surname, fiscal code, and email.
            @param _clientID The unique ID of the client.
            @param _name The first name of the client.
            @param _surname The last name of the client.
            @param _fiscalCode The fiscal code of the client.
            @param _email The email address of the client.
        */
        Client(int _clientID, string _name, string _surname, string _fiscalCode, string _email);

        // Getter methods

        /*
            Retrieves the unique ID of the client.
            @return The client's ID as an integer.
        */
        int getClientID();

        /*
            Retrieves the first name of the client.
            @return The client's name as a string.
        */
        string getName();

        /*
            Retrieves the last name of the client.
            @return The client's surname as a string.
        */
        string getSurname();

        /*
            Retrieves the fiscal code of the client.
            @return The client's fiscal code as a string.
        */
        string getFiscalCode();

        /*
            Retrieves the email address of the client.
            @return The client's email as a string.
        */
        string getEmail();

        // Setter methods. ClientID is not settable, as it is unique.

        /*
            Updates the client's first name, ensuring it is not empty.
            @param _name The new first name of the client.
        */
        void setName(string _name);

        /*
            Updates the client's last name, ensuring it is not empty.
            @param _surname The new surname of the client.
        */
        void setSurname(string _surname);

        /*
            Updates the client's fiscal code, validating the format.
            @param _fiscalCode The new fiscal code of the client.
        */
        void setFiscalCode(string _fiscalCode);

        /*
            Updates the client's email address, validating the format.
            @param _email The new email address of the client.
        */
        void setEmail(string _email);

        // Methods to handle interactions

        /*
            Reads the interactions associated with the client from a CSVFile.
            If FILE does not exist, it is created.
            Typically used to populate the `interactions` vector.
        */
        void readInteractions();

        /*
            Adds a new interaction to the client's list of interactions
            by appending it to the file and reading the interactions again.
            @param newInteraction The Interaction object to be added.
        */
        void addInteraction(Interaction newInteraction);

        /*
            Prints all interactions associated with the client to the console.
        */
        void printInteractions();

        /*
            Prints interactions filtered by the given criteria.
            @param type The type of interaction to filter by.
            @param date The date of interaction to filter by.
            @param description The description to filter by.
        */
        void printFilteredInteractions(string type, string date, string description);

        /*
            Deletes all interactions associated with the client, deleting
            the file where they are stored and reading the interactions again.
        */
        void deleteInteractions();

        /*
            Prints the client's details, including their personal information and all interactions.
        */
        void printClient();
};



class ClientsManager {
    /*
        ClientsManager class is responsible for managing clients and their interactions.
        It reads client data from a CSV file and provides functionalities to add, delete,
        edit, and view clients. It also handles interactions related to clients, 
        allowing for filtering and displaying specific information.
    */

    string clientsFilePath; // Path to the CSV file where client data is stored.
    vector<Client> clients; // List of clients managed by this class.

    /*
        Returns a pointer to the client with the given ID.
        @param clientID The ID of the client to retrieve.
        @return A pointer to the Client object if found, otherwise nullptr.
    */
    Client *getClientByID(int clientID);

    /*
        Finds the line number in the file corresponding to the given client ID.
        @param clientID The ID of the client.
        @return The line number in the file where the client is stored.
    */
    int getCSVLineByClientID(int clientID);

    public:
        // Default contructor
        ClientsManager();

        /*
            Reads client data from the file specified by `clientsFilePath`.
            Populates the `clients` vector with the retrieved data.
        */
        void readClients();

        /*
            Allows the user to select a client ID based on user input.
            @return The ID of the selected client.
        */
        int selectClientIDbyInput();

        /*
            Adds a new client to the list and updates the data file.
            @param name The first name of the client.
            @param surname The surname of the client.
            @param fiscalCode The fiscal code of the client.
            @param email The email address of the client.
        */
        void addClient(string name, string surname, string fiscalCode, string email);

        /*
            Deletes a client with the given ID from the list and the data file.
            @param clientID The ID of the client to delete.
        */
        void deleteClient(int clientID);

        /*
            Edits the details of an existing client.
            @param clientID The ID of the client to edit.
            @param name The new first name of the client.
            @param surname The new surname of the client.
            @param fiscalCode The new fiscal code of the client.
            @param email The new email address of the client.
        */
        void editClient(int clientID, string name, string surname, string fiscalCode, string email);

        /*
            Prints the list of all clients to the console.
        */
        void printClients();

        /*
            Prints the list of clients filtered by the given name and surname.
            @param filterName The name to filter clients by.
            @param filterSurname The surname to filter clients by.
        */
        void printFilteredClients(string filterName, string filterSurname);

        /*
            Adds a new interaction for the client with the given ID.
            @param clientID The ID of the client to add the interaction to.
            @param type The type of interaction (e.g., meeting, call).
            @param date The date of the interaction.
            @param description A brief description of the interaction.
        */
        void addInteraction(int clientID, string type, string date, string description);

        /*
            Prints all interactions for the client with the given ID.
            @param clientID The ID of the client whose interactions are to be printed.
        */
        void printClientInteractions(int clientID);

        /*
            Prints interactions filtered by the given type, date, or description.
            @param type The type of interaction to filter by.
            @param date The date of interaction to filter by.
            @param description The description to filter by.
        */
        void printFilteredInteractions(string type, string date, string description);
};


#endif