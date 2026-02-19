#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int MAX = 50;
struct Food
{
    int id;
    string name;
    string category;
    float price;
};

Food menu[MAX];
int totalItems = 0;

// Function Prototypes
void loadFile();
void saveFile();
void showMenu();
void adminLogin();
void adminPanel();
void customerPanel();
void addItem();
void deleteItem();
void updatePrice();
void defaultMenu();

// Load Data From File
void loadFile()
{
    ifstream file("menu.txt");
    totalItems = 0;

    while (file >> menu[totalItems].id 
                >> menu[totalItems].name 
                >> menu[totalItems].category 
                >> menu[totalItems].price)
    {
        totalItems++;
    }

    file.close();
}

// Save Data To File
void saveFile()
{
    ofstream file("menu.txt");

    for (int i = 0; i < totalItems; i++)
    {
        file << menu[i].id << " "
             << menu[i].name << " "
             << menu[i].category << " "
             << menu[i].price << endl;
    }

    file.close();
}

// Default Menu (30 items)
void defaultMenu()
{
    totalItems = 30;

    string names[30] = {
    "Biryani","Karahi","Nihari","Pulao","Haleem",
    "Qorma","ChapliKabab","BBQ","Sajji","Daal",

    "Kheer","GulabJamun","Jalebi","IceCream","Custard",
    "Tea","Coffee","ColdDrink","MilkShake","Falooda",

    "Burger","Pizza","Fries","Sandwich","Shawarma",
    "Pasta","HotDog","Nuggets","Roll","Tikka"
    };

    string categories[30] = {
    "Pakistani","Pakistani","Pakistani","Pakistani","Pakistani",
    "Pakistani","Pakistani","Pakistani","Pakistani","Pakistani",

    "Sweet","Sweet","Sweet","Sweet","Sweet",
    "Drink","Drink","Drink","Drink","Drink",

    "FastFood","FastFood","FastFood","FastFood","FastFood",
    "FastFood","FastFood","FastFood","FastFood","FastFood"
    };

    float prices[30] = {
    250,800,500,200,300,700,350,900,1000,150,
    120,100,80,150,130,50,100,120,200,180,
    300,1000,200,250,280,400,250,300,220,350
    };

    for(int i=0;i<30;i++)
    {
        menu[i].id = i+1;
        menu[i].name = names[i];
        menu[i].category = categories[i];
        menu[i].price = prices[i];
    }

    saveFile();
}

// Display Menu
void showMenu()
{
    cout << "\n================ FOOD MENU ================\n";
    cout << left << setw(5) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Category"
         << setw(10) << "Price" << endl;

    for (int i = 0; i < totalItems; i++)
    {
        cout << left << setw(5) << menu[i].id
             << setw(15) << menu[i].name
             << setw(15) << menu[i].category
             << setw(10) << menu[i].price << endl;
    }
}

// Add Item
void addItem()
{
    Food *ptr = &menu[totalItems];

    cout << "Enter ID: ";
    cin >> ptr->id;

    cout << "Enter Name: ";
    cin >> ptr->name;

    cout << "Enter Category: ";
    cin >> ptr->category;

    cout << "Enter Price: ";
    cin >> ptr->price;

    totalItems++;
    saveFile();

    cout << "Item Added Successfully!\n";
}

// Delete Item
void deleteItem()
{
    int id;
    cout << "Enter ID to Delete: ";
    cin >> id;

    for(int i=0;i<totalItems;i++)
    {
        if(menu[i].id==id)
        {
            for(int j=i;j<totalItems-1;j++)
                menu[j]=menu[j+1];

            totalItems--;
            saveFile();
            cout << "Item Deleted!\n";
            return;
        }
    }

    cout << "Item Not Found!\n";
}

// Update Price
void updatePrice()
{
    int id;
    cout << "Enter ID to Update: ";
    cin >> id;

    for(int i=0;i<totalItems;i++)
    {
        if(menu[i].id==id)
        {
            cout << "Enter New Price: ";
            cin >> menu[i].price;
            saveFile();
            cout << "Price Updated!\n";
            return;
        }
    }

    cout << "Item Not Found!\n";
}

// Admin Panel
void adminPanel()
{
    int choice;

    do
    {
        cout << "\n----- ADMIN PANEL -----\n";
        cout << "1. View Menu\n";
        cout << "2. Add Item\n";
        cout << "3. Delete Item\n";
        cout << "4. Update Price\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: showMenu(); break;
            case 2: addItem(); break;
            case 3: deleteItem(); break;
            case 4: updatePrice(); break;
            case 5: cout<<"Exiting Admin Panel\n"; break;
            default: cout<<"Invalid Choice\n";
        }

    }while(choice!=5);
}

// Admin Login
void adminLogin()
{
    string user, pass;

    cout << "Enter Username: ";
    cin >> user;

    cout << "Enter Password: ";
    cin >> pass;

    if(user=="admin" && pass=="1234")
        adminPanel();
    else
        cout << "Invalid Login!\n";
}

// Customer Panel
void customerPanel()
{
    string name;
    cout << "Enter Customer Name: ";
    cin >> name;

    int id, quantity;
    char more;
    float bill=0;

    do
    {
        showMenu();

        cout << "Enter Item ID: ";
        cin >> id;

        cout << "Enter Quantity: ";
        cin >> quantity;

        for(int i=0;i<totalItems;i++)
        {
            if(menu[i].id==id)
            {
                bill += menu[i].price * quantity;
                cout<<"Added to Cart!\n";
            }
        }

        cout << "Order More? (y/n): ";
        cin >> more;

    }while(more=='y'||more=='Y');

    cout << "\n======= BILL =======\n";
    cout << "Customer: " << name << endl;
    cout << "Total Bill: " << bill << endl;
    cout << "Thank You!\n";
}

// Main Function
int main()
{
    loadFile();
    if(totalItems==0)
        defaultMenu();
    int choice;
    do
    {
    cout << "\n                 WELCOME                       \n";
    cout << "\n===============================================" << endl;
    cout << "         RESTAURANT MANAGEMENT SYSTEM          " << endl;
    cout << "===============================================" << endl;
        cout << " 1. Admin Login\n";
        cout << " 2. Customer Login\n";
        cout << " 3. Exit\n";
        cout << " Enter Choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1: adminLogin(); break;
            case 2: customerPanel(); break;
            case 3: cout<<"Good Bye!\n"; break;
            default: cout<<"Invalid Choice!\n";
        }

    }while(choice!=3);

    return 0;
}

