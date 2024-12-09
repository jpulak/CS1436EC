// program for creating an inventory manager
// organizing given inputs and store in file

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// constnat var provded in compliance to instructions

const int MAX_ITEMS = 10;

// func prototype (at least one function included)

void addItem(string name[], int quantity[], double price[], int &count);
void displayInventory(const string name[], const int quantity[], const double price[], int count);
double calcTotalVal(const int quantity[], const double price[], int count);
void saveFile(const string name[], const int quantity[], const double price[], int count);
void loadFile(string name[], int quantity[], double price[], int &count);

//main function

int main() {
    
    // initialize all the lists with constant
    
    string name[MAX_ITEMS];
    int quantity[MAX_ITEMS];
    double price[MAX_ITEMS];

    // initialize var
    
    int count = 0;
    int choice; // user input
    
    // bonus points- load previous saved file/ create new file
    
    loadFile(name, quantity, price, count);

    // do-while to show options (at least one loop included )
    
    do {
        cout << "\n~ Menu for Managing Inventory ~\n";
        cout << "1 - Add a new item in the inventory? \n";
        cout << "2 - View all the inventory items? \n";
        cout << "3 - Calculate total value of the inventory? \n";
        cout << "4 - Save program in file and exit? \n";
        cout << "Please enter your choice : ";
        cin >> choice;

        // switch case used to filter through given input (at least one switch statement included)
        
        switch (choice) {
            case 1:
                addItem(name, quantity, price, count);
                break;
            case 2:
                displayInventory(name, quantity, price, count);
                break;
            case 3:
                cout << "Total Inventory Value: $"
                     << fixed << setprecision(2)
                     << calcTotalVal(quantity, price, count) << endl;
                break;
            case 4:
                saveFile(name, quantity, price, count);
                cout << "Saved inventory - Hope to see you soon agian!\n";
                break;
            default:
                cout << "x_x Invalid x_x"<<"\nPlease try again!\n";
        }
    } while (choice != 4);
    
    return 0;
}

//------------------------------------------------------------------------------
// func definitions below 
//------------------------------------------------------------------------------

// 1- fucntion for adding a new item to the inventory
// gather user data and store

void addItem(string name[], int quantity[], double price[], int &count) {
    bool canAdd = true;

    if (count >= MAX_ITEMS) 
    {
        cout << "~o~ Inventory is full! ~o~"<<"\nCannot add more items :(\n";
        canAdd = false;
    } 
    else 
    {
        // gather user input 
        
        cout << "Enter item name: ";
        cin >> name[count];
        cout << "Enter item quantity (1-1000): ";
        cin >> quantity[count];
        
        //validate
        
        while (quantity[count] < 1 || quantity[count] > 1000) 
        {
            cout << "x_x Invalid quantity x_x"<<"\nEnter value between 1 and 1000: ";
            cin >> quantity[count];
        }
        
        //gather user input
        
        cout << "Enter item price (up to $10,000): ";
        cin >> price[count];
        
        //validate
        
        while (price[count] <= 0 || price[count] > 10000) 
        {
            cout << "x_x Invalid price x_x"<<"\nEnter value between 0 and 10,000: ";
            cin >> price[count];
        }
        count++;
    }
}

// 2- display inventory in a tabular format (like lab)
// use given data to organize into given table format
// name - quantity - price

void displayInventory(const string name[], const int quantity[], const double price[], int count) {
    if (count == 0) 
    {
        cout << "* o * Inventory is empty * o *\n";
    } 
    else 
    {
        
        // formatted output
        
        cout<<endl;
        cout<< "Inventory Storage"<<endl<<endl;
        cout << left << setw(20) << "Item Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price" << endl;
        cout << "-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n";
        for (int i = 0; i < count; i++) 
        {
            cout << left << setw(20) << name[i]
                 << setw(10) << quantity[i]
                 << "$" << fixed << setprecision(2) << price[i] << endl;
        }
    }
}

// 3- calculate the total inventory value
// display price of all the given data

double calcTotalVal(const int quantity[], const double price[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) 
    {
        total += quantity[i] * price[i];
    }
    return total;
}

// bonus points- save inventory data to a file

void saveFile(const string name[], const int quantity[], const double price[], int count) {
    ofstream outFile("inventory.txt");
    bool success = outFile.is_open();

    if (!success) 
    {
        cout << "x_x Error opening file for writing x_x\n";
    } 
    else 
    {
        for (int i = 0; i < count; i++) 
        {
            outFile << name[i] << " " << quantity[i] << " " << price[i] << endl;
        }
        outFile.close();
    }
}

// bonus points- load inventory data from a file

void loadFile(string name[], int quantity[], double price[], int &count) {
    ifstream inFile("inventory.txt");
    bool fileExists = inFile.is_open();
    
    // if file exists
    
    if (fileExists) 
    {
        while (count < MAX_ITEMS && inFile >> name[count] >> quantity[count] >> price[count]) 
        {
            count++;
        }
        inFile.close();
    }
    return;
}