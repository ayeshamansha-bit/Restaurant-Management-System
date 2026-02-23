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
    cout << "\n\t\t\t\t================== FOOD MENU ==================\n";
    cout << "\t\t\t\t  "<<left<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Catagory"<<setw(10)<<"Price"<<endl;
        
    for (int i = 0; i < totalItems; i++)
    {
        cout <<"\t\t\t\t  "<<left<<setw(5)<< menu[i].id<<setw(15)<<menu[i].name<<setw(15)<<menu[i].category<<setw(10)<<menu[i].price<<endl;
    }
}

// Add Item
void addItem()
{
    Food *ptr = &menu[totalItems];

    cout << "\t\t\t\t\t     Enter ID: ";
    cin >> ptr->id;

    cout << "\t\t\t\t\t     Enter Name: ";
    cin >> ptr->name;

    cout << "\t\t\t\t\t     Enter Category: ";
    cin >> ptr->category;

    cout << "\t\t\t\t\t     Enter Price: ";
    cin >> ptr->price;

    totalItems++;
    saveFile();

    cout << "\t\t\t\t\t     Item Added Successfully!\n";
}

// Delete Item
void deleteItem()
{
    int id;
    cout << "\t\t\t\t\t     Enter ID to Delete: ";
    cin >> id;

    for(int i=0;i<totalItems;i++)
    {
        if(menu[i].id==id)
        {
            for(int j=i;j<totalItems-1;j++)
                menu[j]=menu[j+1];

            totalItems--;
            saveFile();
            cout << "\t\t\t\t\t     Item Deleted!\n";
            return;
        }
    }

    cout << "\t\t\t\t\t     Item Not Found!\n";
}

// Update Price
void updatePrice()
{
    int id;
    cout << "\t\t\t\t\t     Enter ID to Update: ";
    cin >> id;

    for(int i=0;i<totalItems;i++)
    {
        if(menu[i].id==id)
        {
            cout << "\t\t\t\t\t     Enter New Price: ";
            cin >> menu[i].price;
            saveFile();
            cout << "\t\t\t\t\t     Price Updated!\n";
            return;
        }
    }

    cout <<"\t\t\t\t\t     Item Not Found!\n";
}

// Admin Panel
void adminPanel()
{
    int choice;

    do
    {
        cout << "\n\t\t\t\t================== Admin Panel==================\n";
        cout << "\t\t\t\t\t  1. View Menu\n";
        cout << "\t\t\t\t\t  2. Add Item\n";
        cout << "\t\t\t\t\t  3. Delete Item\n";
        cout << "\t\t\t\t\t  4. Update Price\n";
        cout << "\t\t\t\t\t  5. Exit\n";
        cout << "\t\t\t\t\t    Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: showMenu(); break;
            case 2: addItem(); break;
            case 3: deleteItem(); break;
            case 4: updatePrice(); break;
            case 5: cout<<"\t\t\t\t\t     Exiting Admin Panel\n"; break;
            default:cout<<"\t\t\t\t\t     Invalid Choice\n";
        }

    }while(choice!=5);
}

// Admin Login
void adminLogin()
{
    string user, pass;

    cout << "\t\t\t\t\t     Enter Username: ";
    cin >> user;

    cout << "\t\t\t\t\t     Enter Password: ";
    cin >> pass;

    if(user=="admin" && pass=="1234")
        adminPanel();
    else
        cout << "\t\t\t\t\t     Invalid Login!\n";
}

// Customer Panel
void customerPanel()
{
	string name;
    cout << "\t\t\t\t\t     Enter Customer Name: ";
    cin >> name;

    int id, quantity,choice;
    char more;
    float bill=0;

    do
    {
        cout<<"\n\t\t\t\t\t What you want?"<<endl;
        cout<<"\t\t\t\t\t  1: View menu."<<endl;
        cout<<"\t\t\t\t\t  2: Order Food."<<endl;
        cout<<"\t\t\t\t\t  3: Generate Bill."<<endl;
        cout<<"\t\t\t\t\t  4: Exit."<<endl;
        cout<<"\t\t\t\t\t     Enter your choice: ";
        cin >>choice;
        switch(choice){
        	case 1:
        		showMenu();   break;
        	case 2:
			   do{
			    cout<<"\t\t\t\t\t     Enter food id: ";
				cin>>id;		
                cout<<"\t\t\t\t\t     Enter Quantity: ";
                cin >> quantity;
for(int i=0;i<totalItems;i++)
        {
            if(menu[i].id==id)
            {
            //Storing order in cart
                Cartname[cartcount]=menu[i].name;
                Cartprice[cartcount]=menu[i].price;
                CartQty[cartcount]=quantity;
                cartcount++;
				 bill += menu[i].price* quantity;
                cout<<"\t\t\t\t\t     Added to Cart!\n";
            }
        }
         cout<< "\t\t\t\t\t     Order More? (y/n): ";
         cin >> more;
    }while(more=='y'||more=='Y');
    break;
    case 3:
    	 cout<<"\n\t\t\t\t================== CART ==================\n";
    	 cout <<"\t\t\t\t  "<<left<<setw(15)<<"Name"<<setw(10)<<"Qty"<<setw(10)<<"Price"<<endl;
        
    for (int i = 0; i <cartcount; i++)
    {
        cout <<"\t\t\t\t  "<<left<<setw(15)<< Cartname[i]<<setw(10)<<CartQty[i]<<setw(10)<<Cartprice[i]<<endl;
    }
    break;
        
    case 4:
       cout << "\n\t\t\t\t================== BILL ==================\n";
       cout << "\t\t\t\t\t     Customer: " << name << endl;
       cout << "\t\t\t\t\t     Total Bill: " << bill << endl;
       cout << "\t\t\t\t\t     Thank You!\n";
       break;
    case 5:
    	cout<<"\t\t\t\t\t     Thankyou for coming!"<<endl;
    	break;
    default:
    	cout<<"\t\t\t\t\t     Invalid input."<<endl;
} }while (choice!=5);
}
// Main Function
 int main(){
    loadFile();

    if(totalItems==0)
        defaultMenu();

    int choice;

    do
    {
    cout << "\n\t\t\t\t                 WELCOME                       \n";
    cout << "\n\t\t\t\t===============================================" << endl;
    cout << "\t\t\t\t         RESTAURANT MANAGEMENT SYSTEM          " << endl;
    cout << "\t\t\t\t===============================================" << endl;
        cout << "\t\t\t\t\t  1. Admin Login\n";
        cout << "\t\t\t\t\t  2. Customer Login\n";
        cout << "\t\t\t\t\t  3. Exit\n";
        cout << "\t\t\t\t\t     Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: adminLogin(); break;
            case 2: customerPanel(); break;
            case 3: cout<<"\t\t\t\t\t    Good Bye!\n"; break;
            default:cout<<"\t\t\t\t\t    Invalid Choice!\n";
        }

    }while(choice!=3);

    return 0;
}



