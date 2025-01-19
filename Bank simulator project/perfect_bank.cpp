#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string f_Client = "clients.txt";
const string f_Users  = "Users.txt";

static void    Main_Menue();
static void	ft_Deposit();
static void	Transactions_screen();
static void	ManageUsersScreen();
void    Login();


struct  s_Client
{
    string account_number;
    string pin_code;
    string user_name;
    string Phone;
    double account_balance;
    bool mark_for_delet = false;
};

struct s_Users
{
    string  UserName;
    string  Password;
    int     Permissions;
    bool    MarkForDelete = false;
};

enum enMainMenuePermissions 
{
    eAll           = -1,
    pListClients   = 1,
    pAddNewClient  = 2,
    pDeleteClient  = 4,
    pUpdateClients = 8,
    pFindClient    = 16,
    pTranactions   = 32,
    pManageUsers   = 64
};


enum    e_Menue_option
{
    list_client     = 1,
    add_new_client  = 2,
    delet_client    = 3,
    update_client   = 4,
    find_client     = 5,
    Transaction     = 6,
    Manage_users    = 7,
    logout          = 8
};

enum    e_transactions_option
{
    Deposit             = 1,
    Withdraw            = 2,
    Total_Balances      = 3,
    return_Main_Menue   = 4
};

enum    eManageUsers 
{
    list_users  = 1,
    add_user    = 2,
    delete_user = 3,
    update_user = 4,
    find_user   = 5,
    main_menue  = 6
};

s_Users   CurrentUser;

void    Main_Menue();
static void	ft_Deposit();
static void	Transactions_screen();


/*              Who Ami                       */

void WhoAmI()
{
    system("clear");
    cout << "┌────────────────────────────────────────────────────────────────────────────────────────────┐\n";
    cout << "│                                                                                            │\n";
    cout << "│  🏦  Welcome to the Bank Simulator Project! 🏦                                             │\n";
    cout << "│                                                                                            │\n";
    cout << "│  This project is developed by: Aboubakr Jelloulat                                          │\n";
    cout << "│                                                                                            │\n";
    cout << "│  🚀 About the Project:                                                                     │\n";
    cout << "│  This is a bank management system simulator that allows you to manage clients and users.   │\n";
    cout << "│  You can perform various operations such as adding, deleting, updating, and finding        │\n";
    cout << "│  clients. Additionally, you can manage users, perform transactions like deposits and       │\n";
    cout << "│  withdrawals, and view total balances.                                                     │\n";
    cout << "│                                                                                            │\n";
    cout << "│  🔑 Default Login Credentials:                                                             │\n";
    cout << "│  You can run the program with the following credentials:                                   │\n";
    cout << "│  Username: ajelloul                                                                        │\n";
    cout << "│  Password: 1337                                                                            │\n";
    cout << "│                                                                                            │\n";
    cout << "│  🛠️ Tools Used:                                                                             │\n";
    cout << "│  - C++ Programming                                                                         │\n";
    cout << "│  - Vectors                                                                                 │\n";
    cout << "│  - Basic File Handling                                                                     │\n";
    cout << "│  - Bitwise Operators                                                                       │\n";
    cout << "│                                                                                            │\n";
    cout << "│                                                                                            │\n";
    cout << "│  Thank you: programming advices.com                                                        │\n";
    cout << "│                                                                                            │\n";
    cout << "└────────────────────────────────────────────────────────────────────────────────────────────┘\n";
    cout << "\nPress any key to continue...";
    cin.get();
    Login();
}

/*          This part for Give The permission       */

static bool CheckAccessPermission(enMainMenuePermissions Permission)
{
    if (CurrentUser.Permissions == enMainMenuePermissions::eAll)
        return (true);

    if ((Permission & CurrentUser.Permissions) == Permission)
        return (true);
    else
        return (false);
}

static void    PrintDeniedMessage()
{
    cout << " ╔══════════════════════════════════╗\n"
        << " ║  ⚠️  ACCESS DENIED  ⚠️             ║\n"
        << " ║                                  ║\n"
        << " ║  You don't have permission to    ║\n"
        << " ║  perform this action.            ║\n"
        << " ╚══════════════════════════════════╝ "<< endl;
}

/*          This part for Manage client data       */

static vector<string> split_string(string s1, string seperator)
{
    vector<string> v_string;
    int pos = 0;
    string s_word;
 
    while ((pos = s1.find(seperator)) != std::string::npos)
    {
        s_word = s1.substr(0, pos); 
        if (s_word != "")
        {
            v_string.push_back(s_word);
        }

        s1.erase(0, pos + seperator.length());
    }

    if (s1 != "")
    {
        v_string.push_back(s1);
    }

    return (v_string);

}

static s_Client ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    s_Client Client;
    vector<string> v_data;
    v_data = split_string(Line, Seperator);

    Client.account_number = v_data[0];
    Client.pin_code = v_data[1];
    Client.user_name = v_data[2];
    Client.Phone = v_data[3];
    Client.account_balance = stod(v_data[4]);
    return (Client);
}

static string convert_vector_to_line(s_Client Client, string Seperator = "#//#")
{

    string line = "";
    line += Client.account_number + Seperator;
    line += Client.pin_code + Seperator;
    line += Client.user_name + Seperator;
    line += Client.Phone + Seperator;
    line += to_string (Client.account_balance);
    return (line);
}

static bool client_is_found(string account_number, string f_Client)
{
    vector <s_Client> v_clients;
    fstream MyFile;
    MyFile.open(f_Client, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        s_Client Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.account_number == account_number)
            {
                MyFile.close();
                return (true);
            }
            v_clients.push_back(Client);
        }
        MyFile.close();
    }
    return (false);
}

static s_Client Read_one_client()
{
    s_Client Client;
    cout << "Enter Account Number? ";

    getline(cin >> ws, Client.account_number);

    while (client_is_found(Client.account_number, f_Client))
    {
        cout << "\nClient with [" << Client.account_number << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.account_number);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.pin_code);

    cout << "Enter Name? ";
    getline(cin, Client.user_name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.account_balance;

    return (Client);
}

static vector <s_Client> Load_cleints_data_from_file(string f_Client)
{
    vector <s_Client> v_Clients;
    fstream my_file;
    my_file.open(f_Client, ios::in);

    if (my_file.is_open())
    {
        string Line;
        s_Client Client;

        while (getline(my_file, Line))
        {
            Client = ConvertLinetoRecord(Line);
            v_Clients.push_back(Client);
        }
        my_file.close();
    }
    return (v_Clients);
}

static void Print_client_info(s_Client Client)
{
    cout << "| " << setw(15) << left << Client.account_number;
    cout << "| " << setw(10) << left << Client.pin_code;
    cout << "| " << setw(40) << left << Client.user_name;
    cout << "| " << setw(15) << left << Client.Phone;
    cout << "| " << setw(15) << left << Client.account_balance;
}

static void show_screen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
    {
        PrintDeniedMessage();
        return ;
    }

    vector <s_Client> vClients = Load_cleints_data_from_file(f_Client);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n___________________________________________________________________________________________________" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(15) << "Phone";
    cout << "| " << left << setw(15) << "Balance";
    cout << "\n___________________________________________________________________________________________________" << endl;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (s_Client Client : vClients)
        {

            Print_client_info(Client);
            cout << endl;
        }
	cout << "\n___________________________________________________________________________________________________" << endl;
}

static void Print_Client_Card(s_Client Client)
{
    cout << "\nThe following are the client details: " << endl;
    cout << "_______________________________________" << endl;
    cout << "\nAccout Number: " << Client.account_number;
    cout << "\nPin Code     : " << Client.pin_code;
    cout << "\nName         : " << Client.user_name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.account_balance;
    cout << "\n_______________________________________" << endl;
}

static bool find_client_by_account_number(string AccountNumber, vector <s_Client> vClients, s_Client& Client)
{
    for (s_Client C : vClients)
    {

        if (C.account_number == AccountNumber)
        {
            Client = C;
            return (true);
        }

    }
    return (false);
}

static s_Client ChangeClientRecord(string account_nb)
{
    s_Client Client;

    Client.account_number = account_nb;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.pin_code);

    cout << "Enter Name? ";
    getline(cin, Client.user_name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.account_balance;
    return (Client);
}

static bool Mark_client_for_delet(string account_number, vector <s_Client>& vClients)
{

    for (s_Client& C : vClients)
    {

        if (C.account_number == account_number)
        {
            C.mark_for_delet = true;
            return (true);
        }

    }
    return (false);
}

static vector <s_Client> SaveCleintsDataToFile(string f_Client, vector <s_Client> vClients)
{
    fstream MyFile;
    MyFile.open(f_Client, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (s_Client C : vClients)
        {

            if (C.mark_for_delet == false)
            {
                DataLine = convert_vector_to_line(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }
    return (vClients);
}

static void AddDataLineToFile(string f_Client, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(f_Client, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

static void AddNewClient()
{
    s_Client Client;
    Client = Read_one_client();
    AddDataLineToFile(f_Client, convert_vector_to_line(Client));
}

static void Add_new_Client()
{
    char AddMore = 'Y';
    do
    {
        cout << "\n\t\tAdding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully,\n\tdo you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

static bool DeleteClientByAccountNumber(string AccountNumber, vector <s_Client>& vClients)
{
    s_Client Client;
    char Answer = 'n';

    if (find_client_by_account_number(AccountNumber, vClients, Client))
    {

        Print_Client_Card(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Mark_client_for_delet(AccountNumber, vClients);
            SaveCleintsDataToFile(f_Client, vClients);

            vClients = Load_cleints_data_from_file(f_Client);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
    return false;
}

static bool update_client_by_account_number(string AccountNumber, vector <s_Client>& vClients)
{

    s_Client Client;
    char Answer = 'n';

    if (find_client_by_account_number(AccountNumber, vClients, Client))
    {

        Print_Client_Card(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (s_Client& C : vClients)
            {
                if (C.account_number == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(f_Client, vClients);

            cout << endl << "Client Updated Successfully." << endl;
            return true;
        }

    }
    else
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;
        
	return false;
}

static string Read_account_number_of_client()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return (AccountNumber);
}

static void delet_client_screen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
    {
        PrintDeniedMessage();
        return ;
    }

    cout << "\n-----------------------------------" << endl;
    cout << "\tDelete Client : ";
    cout << "\n-----------------------------------" << endl;

    vector <s_Client> vClients = Load_cleints_data_from_file(f_Client);
    string AccountNumber = Read_account_number_of_client();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

static void update_client_screen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
    {
        PrintDeniedMessage();
        return ;
    }
    cout << "\n-----------------------------------" << endl;
    cout << "\tUpdate Client Info : ";
    cout << "\n-----------------------------------" << endl;

    vector <s_Client> vClients = Load_cleints_data_from_file(f_Client);
    string AccountNumber = Read_account_number_of_client();
    update_client_by_account_number(AccountNumber, vClients);

}

static void Add_newClient_screen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
    {
        PrintDeniedMessage();
        return ;
    }
    cout << "\n-----------------------------------" << endl;
    cout << "\tAdd New Clients : ";
    cout << "\n-----------------------------------" << endl;

    Add_new_Client();
}

static void Find_client_screen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
    {
        PrintDeniedMessage();
        return ;
    }
    cout << "\n-----------------------------------" << endl;
    cout << "\tFind Client : ";
    cout << "\n-----------------------------------" << endl;

    vector <s_Client> vClients = Load_cleints_data_from_file(f_Client);
    s_Client Client;
    string AccountNumber = Read_account_number_of_client();
    if (find_client_by_account_number(AccountNumber, vClients, Client))
        Print_Client_Card(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

static void End_program_screen()
{
    cout << "\n-----------------------------------" << endl;
    cout << "\tProgram Ends ...";
    cout << "\n-----------------------------------" << endl;
}

/*          This part for Transactions       */

static void Go_back()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    Main_Menue();
}

static short read_user_choice()
{
    short choice;
    do
    {
        cout << "Choose what do you want to do? [1 to 7] :   ";
        cin >> choice;
    } while (choice < 1 || choice > 8);

    return choice;
}

static short	choice_Transactions()
{
	short choice;
    do
    {
        cout << "Choose what do you want to do? [1 to 4] :   ";
        cin >> choice;
    } while (choice < 1 || choice > 4);

    return (choice);
}

static double Read_deposit_amount()
{
	double	amount;

	do
	{
		cout << "Please enter deposit amount ?  ";
		cin >> amount;
	} while (amount < 0);
	return (amount);
}

static void	Change_deposit_amount(string AccountNumber, double amount,vector <s_Client>& vClients)
{
	char	accept;
    cout << "Are you sure you want perform this transaction? y/n ?  ";
	cin >> accept;

    if (accept == 'y' || accept == 'Y')
    {
        for (s_Client& C : vClients)
        {
            if (C.account_number == AccountNumber)
            {
                C.account_balance += amount;
                SaveCleintsDataToFile(f_Client, vClients);
                cout << endl << "Amount changed Successfully :  " << C.account_balance << endl;
                break;
            }
        }
    }
}

static void	ft_Deposit()
{

	vector <s_Client> vClients;
	s_Client Client;
	string AccountNumber;

	vClients = Load_cleints_data_from_file(f_Client);
    AccountNumber = Read_account_number_of_client();
    while (!find_client_by_account_number(AccountNumber, vClients, Client))
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] does not exist!";
        AccountNumber = Read_account_number_of_client();
    }
    Print_Client_Card(Client);
    double amount = Read_deposit_amount();
    Change_deposit_amount(AccountNumber, amount, vClients);

}

static void Go_Back_To_Transactions_Menue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    Transactions_screen();

}
static void	Deposit_screen()
{
	cout << "\n-----------------------------------" << endl;
    cout << "\t Deposit Screen : ";
    cout << "\n-----------------------------------" << endl;

    ft_Deposit();
}

static void	Withdraw_screen()
{
	cout << "\n-----------------------------------" << endl;
    cout << "\t Withdraw Screen : ";
    cout << "\n-----------------------------------" << endl;

    vector <s_Client> vClients;
	s_Client Client;
	string AccountNumber;

	vClients = Load_cleints_data_from_file(f_Client);
    AccountNumber = Read_account_number_of_client();
    while (!find_client_by_account_number(AccountNumber, vClients, Client))
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] does not exist!";
        AccountNumber = Read_account_number_of_client();
    }
    Print_Client_Card(Client);
    double amount;

    cout <<  endl << "Please enter withdraw amount? : ";
    cin >> amount;

    while (Client.account_balance < amount)
    {
        cout << endl << "Amount Exceeds the balance, you can withdraw up to : " << Client.account_balance<< endl;
        cout << "Please enter another amount? ";
        cin >> amount;
    }

    Change_deposit_amount(AccountNumber, amount * (-1), vClients);
}

static void print_client_balance(s_Client Client)
{
    cout << "| " << setw(18) << left << Client.account_number;
    cout << "| " << setw(40) << left << Client.user_name;
    cout << "| " << setw(15) << left << Client.account_balance;
}

static void Total_Balances_screen()
{
    double Total_balances = 0;
    vector <s_Client>    v_Client;
    v_Client = Load_cleints_data_from_file(f_Client);

    cout << "\n\t\t\tBalances List(" << v_Client.size() << ") Client (s). " << endl;
    cout << " ___________________________________________________________________________________________\n" << endl;
    cout << "| " << left << setw(18) << "Account Number ";
    cout << "| " << left << setw(40) << "Client Name ";
    cout << "| " << left << setw(15) << "Balance ";
    cout << "\n ___________________________________________________________________________________________\n" << endl;

    if (v_Client.size() == 0)
        cout << "\t\tNo Clients Available In the System!";
    else
    {
        for (s_Client &one_client : v_Client)
        {
            print_client_balance(one_client);
            Total_balances += one_client.account_balance;
            cout << endl;
        }
    }
    cout << " ___________________________________________________________________________________________\n" << endl;


    cout << "\t\t\t  Total Balances = " << Total_balances << endl;
}

static void	Transactions_Menue_option(e_transactions_option option)
{
	switch (option)
	{
	case e_transactions_option::Deposit :
    {
		system ("clear");
		Deposit_screen();
        Go_Back_To_Transactions_Menue();
		break;
    }

	case e_transactions_option::Withdraw : 
    {
		system ("clear");
		Withdraw_screen();
        Go_Back_To_Transactions_Menue();
		break;
    }

    case e_transactions_option::Total_Balances : 
    {
		system ("clear");
		Total_Balances_screen();
        Go_Back_To_Transactions_Menue();
		break;
    }

    case e_transactions_option::return_Main_Menue : 
    {
		Main_Menue();
		break;
    }
	}

}

static void	Transactions_screen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pTranactions))
    {
        PrintDeniedMessage();
        return ;
    }
    system ("clear");
	cout << "\n======================================" << endl;
    cout << "\tTransactions Menue Screen : ";
    cout << "\n======================================" << endl;

	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n" << endl;

	Transactions_Menue_option ((e_transactions_option) choice_Transactions());
}

/*          This part for Manage Users data      */

static s_Users  ConvertLineOfUserstoRecord(string Line, string seperator = "#//#")
{
    vector <string> v_data = split_string(Line, seperator);
    s_Users User;

    User.UserName    =  v_data[0];
    User.Password    =  v_data[1];
    User.Permissions =  stoi(v_data[2]);

    return (User);
}

static short    ChoiceUsersMenue()
{
    short choice;

    do
    {
        cout << "Choice what do you want to do? [1 to 6]? ";
        cin >> choice;
    } while (choice < 1 || choice > 6);
    return (choice);
}

vector <s_Users> LoadUsersDataFromFile(string pathname)
{
    vector <s_Users> v_Users;

    fstream file;
    file.open(pathname, ios::in); // reading mode
    if (file.is_open())
    {
        string  Line;
        s_Users  User;
    
        while (getline (file, Line))
        {
            User = ConvertLineOfUserstoRecord(Line);
            v_Users.push_back(User);
        }
        file.close();
    }
    return (v_Users);
}

bool    FindUserByUsernameAndPassword(string Username, string Password, s_Users& User)
{
    vector <s_Users> v_Users = LoadUsersDataFromFile(f_Users);

    for (s_Users U : v_Users)
    {
        if (U.UserName == Username && U.Password == Password)
        {
            User    = U;
            return (true);
        }
    }
    return (false);
}

static  void    GoBackToManageUsersScreen()
{
    cout << "\n\nPress any key to go back to Users Menue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    ManageUsersScreen();
}

void PrintUserCard(s_Users User)
{
    cout << "\nThe following are the user details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername    : " << User.UserName;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n-----------------------------------\n";

}

// ********************** list users *******************


static void    PrintUsersInfo(s_Users  User)
{
    cout << "| " << setw(25) << User.UserName;
    cout << "| " << setw(15) << User.Password;
    cout << "| " << setw(10) << User.Permissions;
}

static void ListUsers()
{
    vector <s_Users> vUsers = LoadUsersDataFromFile(f_Users);

    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
    cout << "\n_________________________________________________________________" << endl;
    cout << "| " << left << setw(25) << " User Name ";
    cout << "| " << left << setw(15) << " Password ";
    cout << "| " << left << setw(10) << " Permissions ";
    cout << "\n_________________________________________________________________" << endl;

    if (vUsers.size() == 0)
        cout << "\t\tNo Users Available In the System!";
    else
    {
        for (s_Users &User : vUsers)
        {
            PrintUsersInfo(User);
            cout << endl;
        }
    }
   cout << "|________________________________________________________________" << endl;
}
 // ******************** Add new users *********************

static bool UserExistsByUsername(string username, string pathname)
{
    vector <s_Users> v_Users;
    fstream file;
    file.open(pathname, ios::in);

    if (file.is_open())
    {
        string  Line;
        s_Users User;
    
        while (getline(file, Line))
        {
            User = ConvertLineOfUserstoRecord(Line);
            if (User.UserName == username)
            {
                file.close();
                return (true);
            }
        }
        file.close();
    }
    return (false);
}


int ReadPermissionsToSet()
{

    int Permissions = 0;
    char Answer = 'n';


    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give access to : \n ";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pListClients;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pFindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pTranactions;
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pManageUsers;
    }

    return Permissions;
}

static s_Users  ReadUserInfo()
{
    s_Users User;

    cout << "Enter Username? ";
    getline(cin >> ws, User.UserName);

    while (UserExistsByUsername(User.UserName, f_Users)) 
    {
        cout << "\nUser with [" << User.UserName << "] already exists. Enter another Username? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Enter Password? ";
    getline(cin, User.Password);

    User.Permissions = ReadPermissionsToSet();
    return (User);
}

string ConvertUserRecordToLine(s_Users User, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += User.UserName + Seperator;
    stClientRecord += User.Password + Seperator;
    stClientRecord += to_string(User.Permissions);

    return stClientRecord;

}

static void AddUsersToFile(string pathname, string DataLine)
{
    fstream file;

    file.open (pathname, ios::out | ios::app);
    if (file.is_open())
    {
        file << DataLine << endl;
        file.close();
    }
}

static void AddNewUser()
{
    s_Users User;
    User    = ReadUserInfo();
    AddUsersToFile(f_Users, ConvertUserRecordToLine(User));
}

static void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        cout << "\n\t\tAdding New User:\n\n";

        AddNewUser();
        cout << "\nUser  Added Successfully,\n\tdo you want to add more users? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

static void AddNewUserScreen()
{
    cout << "\n-----------------------------------" << endl;
    cout << "\tAdd New User : ";
    cout << "\n-----------------------------------" << endl;

    AddNewUsers();
}

// ************** delete user *****************

static bool FindUserByUsername(string Username, vector <s_Users> vUsers, s_Users& User)
{

    for (s_Users U : vUsers)
    {
        if (U.UserName == Username)
        {
            User = U;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByUsername(string Username, vector <s_Users>& vUsers)
{
    for (s_Users& U : vUsers)
    {
        if (U.UserName == Username)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <s_Users> SaveUsersDataToFile(string FileName, vector <s_Users> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;
    if (MyFile.is_open())
    {
        for (s_Users U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertUserRecordToLine(U);
                MyFile << DataLine << endl;

            }
        }
        MyFile.close();
    }
    return vUsers;
}

bool DeleteUserByUsername(string Username, vector <s_Users>& vUsers)
{
    s_Users User;
    char Answer = 'n';

    if (Username == "ajelloul")
    {
        cout << "\n\nYou cannot Delete This User.";
        return (false);
    }
    
    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUsername(Username, vUsers);
            SaveUsersDataToFile(f_Users, vUsers);

            vUsers  = LoadUsersDataFromFile(f_Users); // Only refrech Users
            return (true);
        }
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return (false);
    }
}

static string  ReadUserName()
{
    string Username;

    cout << "\nPlease enter Username? ";
    cin >> Username;
    return (Username);
}

static void  DeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Users Screen";
    cout << "\n-----------------------------------\n";

    vector <s_Users>    v_Users = LoadUsersDataFromFile(f_Users);
    DeleteUserByUsername(ReadUserName(), v_Users);
}
// *********** update users ********// 

static s_Users ChangeUserRecord(string Username)
{
    s_Users User;

    User.UserName = Username;

    cout << "\n\nEnter Password? ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadPermissionsToSet();

    return (User);
}

static bool UpdateUserByUsername(string Username, vector <s_Users>& vUsers)
{

    s_Users User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsers, User))
    {

        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (s_Users& U : vUsers)
            {
                if (U.UserName == Username)
                {
                    U =  ChangeUserRecord(Username);
                    break;
                }
            }
            SaveUsersDataToFile(f_Users, vUsers);
            cout << "\n\nUser Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Account Number (" << Username << ") is Not Found!";
        return false;
    }
}

void UpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Users Screen";
    cout << "\n-----------------------------------\n";

    vector <s_Users> v_Users = LoadUsersDataFromFile(f_Users);

    UpdateUserByUsername(ReadUserName(), v_Users);
}
// ***************************** find users ********************** 
 
static void FindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector <s_Users> vUsers = LoadUsersDataFromFile(f_Users);
    s_Users User;
    string Username = ReadUserName();
    if (FindUserByUsername(Username, vUsers, User))
        PrintUserCard(User);
    else
        cout << "\nUser with Username [" << Username << "] is not found!";

}


static void UsersMenueOption(eManageUsers   choice)
{
    switch (choice)
    {
    case eManageUsers::list_users :
    {
        system("clear");
        ListUsers();
        GoBackToManageUsersScreen();
        break;
    }
    case eManageUsers::add_user :
    {
        system("clear");
        AddNewUserScreen();
        GoBackToManageUsersScreen();
        break;
    }
    case eManageUsers::delete_user :
    {
        system ("clear");
        DeleteUserScreen();
        GoBackToManageUsersScreen();
        break;
    }
    case eManageUsers::update_user :
    {
        system ("clear");
        UpdateUserScreen();
        GoBackToManageUsersScreen();
        break;
    }
    case eManageUsers::find_user :
    {
        system ("clear");
        FindUserScreen();
        GoBackToManageUsersScreen();
        break;
    }
    case eManageUsers::main_menue :
    {
        Main_Menue();
    }
    }

}

static void	ManageUsersScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
    {
        PrintDeniedMessage();
        return ;
    }

    system ("clear");
	cout << "\n======================================" << endl;
	cout << "\t\tManage Users Menue Screen : ";
	cout << "\n======================================" << endl;
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "\n======================================" << endl;
    UsersMenueOption((eManageUsers) ChoiceUsersMenue());
}


static void Main_Menu_Option(e_Menue_option option)
{
    switch (option)
    {
    case e_Menue_option::list_client:
    {
        system("clear");
        show_screen();
        Go_back();
        break;
    }
    case e_Menue_option::add_new_client:
       system("clear");
        Add_newClient_screen();
        Go_back();
        break;

    case e_Menue_option::delet_client:
        system("clear");
        delet_client_screen();
        Go_back();
        break;

    case e_Menue_option::update_client:
        system("clear");
        update_client_screen();
        Go_back();
        break;

    case e_Menue_option::find_client:
       system("clear");
        Find_client_screen();
        Go_back();
        break;

    case e_Menue_option::Transaction :
        system("clear");
        Transactions_screen();
        Go_back();
        break;

    case e_Menue_option::Manage_users :
        system("clear");
		ManageUsersScreen();
        break;
    case e_Menue_option::logout :
        system("clear");
        Login();
    }
}

void Main_Menue(void)
{
    system("clear");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
	cout << "\t[8] logout.\n";
    cout << "===========================================\n";
    Main_Menu_Option((e_Menue_option)read_user_choice());
}
/*          This part for login       */

static bool    LodingUserInfo(string Username, string Password)
{
    if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
       return true;
    else
        return false;
}

void    Login()
{
    bool    IsFaildLogin = false;

    string  Username, Password;

    do
    {
        system ("clear");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";
        if (IsFaildLogin)
        {
            cout << "Invalid Username/Password!\n";
        }
         
        cout << "Enter Username? ";
        cin >> Username;
    
        cout << "Enter Password? ";
        cin >> Password;
        IsFaildLogin = !LodingUserInfo(Username, Password);

    } while (IsFaildLogin);
    
    Main_Menue();
}

int main()
{
    WhoAmI();

    return (0);
}