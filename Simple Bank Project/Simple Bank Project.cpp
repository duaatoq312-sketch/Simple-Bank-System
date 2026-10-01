#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

const string ClientFileName = "client-records.txt";
const string UserFile = "Users.txt";

void LoginScreen();
void ManageUsersScreen();
short AskForUserPermissions();
struct stClient
{
	string AccountNumber = "";
	string PinCode;
	string Name;
	string phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

struct stUser
{
	string username;
	string password;
	short permissions = 0;
	bool MarkForDeleteUser = false;
};
stUser CurrentUser;   //Global variable
void MainMenueScreen(stUser);
void PrintClientCard(stClient);
void ShowAllUsersScreen();


enum enMainMenueOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransaction = 6, eManageUsersScreen = 7,
	eLogout = 8
};

enum enTransactionMenueOptions
{
	eDeposit = 1, eWithdraw = 2,
	eTotalBalances = 3, eMainMenue = 4
};
enum enUserMenueOptions
{
	eShowAllUsers = 1, eAddUser, eDeleteUser,
	eUpdateUser, eFindUser, euMainMenue
};
enum enPermissions
{
	eFullAccess = -1, elist = 1, eadd = 2, edeleteuser = 4, eupdate = 8, efind = 16, etrans = 32, emanage = 64

};
string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber? ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, AccountNumber);
	return AccountNumber;
}
string ReadUserName()
{
	string username;
	cout << "\nEnter UserName : ";
	getline(cin >> ws, username);
	return username;
}
string ReadUserPass()
{
	string passkey;
	cout << "\nEnter Password: ";
	getline(cin >> ws, passkey);
	return passkey;
}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 8]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

vector<string> SplitString(string line, string delimeter = "#//#")
{
	vector<string>vString;
	string sWord = "";
	size_t pos = 0;
	while ((pos = line.find(delimeter)) != std::string::npos)
	{
		sWord = line.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		line.erase(0, pos + delimeter.length());
	}
	if (line != "")
	{
		vString.push_back(line);
	}
	return vString;
}


stClient ConvertLineToRecord(string line, string delimeter = "#//#")
{
	stClient client;

	vector<string>vString = SplitString(line);

	client.AccountNumber = vString[0];
	client.PinCode = vString[1];
	client.Name = vString[2];
	client.phone = vString[3];
	client.AccountBalance = stod(vString[4]);
	return client;
}
string ConvertRecordToLine(stClient client, string delimeter = "#//#")
{
	string line = "";
	line += client.AccountNumber + delimeter;
	line += client.PinCode + delimeter;
	line += client.Name + delimeter;
	line += client.phone + delimeter;
	line += to_string(client.AccountBalance);

	return line;
}
vector<stClient> LoadingDataFromFile(string FileName)
{
	vector<stClient>vClients;
	stClient client;
	string line;
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			if (line.empty())
				continue;


			client = ConvertLineToRecord(line, "#//#");
			vClients.push_back(client);
		}

		MyFile.close();
	}
	return vClients;
}
bool FindClientByAccountNumber(string AccountNumber, stClient& client)
{
	vector<stClient>vClients = LoadingDataFromFile(ClientFileName);
	for (stClient& n : vClients)
	{
		if (n.AccountNumber == AccountNumber)
		{
			client = n;
			return true;
		}
	}
	return false;
}

void FindClient()
{
	cout << "=============================================\n";
	cout << "\n                Find Client\n";
	cout << "=============================================\n";
	string AccountNumber = ReadClientAccountNumber();

	stClient client;

	if (FindClientByAccountNumber(AccountNumber, client))
	{
		PrintClientCard(client);
	}
	else
	{
		cout << "Account isn't Found\n";
	}
}

vector<stClient> SaveClientsDataToFile(vector<stClient>& vClients, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (stClient& n : vClients)
		{
			if (!n.MarkForDelete)
			{

				MyFile << ConvertRecordToLine(n) << endl;
			}
		}
		MyFile.close();

	}
	return vClients;
}

bool MarkClientForDeleteByAccountNumber(vector<stClient>& vClients, string AccountNumber)
{
	for (stClient& n : vClients)
	{
		if (n.AccountNumber == AccountNumber)
		{
			n.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool MarkUserForDeleteByAccountNumber(vector<stUser>& vUsers, string Username)
{
	for (stUser& u : vUsers)
	{
		if (u.username == Username)
		{
			u.MarkForDeleteUser = true;
			return true;
		}
	}
	return false;
}
void AddDataLineToFile(string FileName, string line)
{

	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << line << endl;
		MyFile.close();
	}

}
void PrintClientCard(stClient client)
{
	cout << "\n                Client Card\n";
	cout << "=============================================\n";
	cout << "\nAccount Number: " << client.AccountNumber;
	cout << "\nPinCode: " << client.PinCode;
	cout << "\nClient Name: " << client.Name;
	cout << "\nPhone: " << client.phone;
	cout << "\nBalance: " << client.AccountBalance;
	cout << "\n=============================================\n";

}
stClient ReadClientData()
{
	stClient NewClient;
	NewClient.AccountNumber = ReadClientAccountNumber();
	while (FindClientByAccountNumber(NewClient.AccountNumber, NewClient))
	{
		cout << "\nAccount number is Already used , Enter another one: \n";
		getline(cin >> ws, NewClient.AccountNumber);

	}

	cout << "PinCode: ";
	getline(cin, NewClient.PinCode);

	cout << "Client Name : ";
	getline(cin, NewClient.Name);

	cout << "Phone: ";
	getline(cin, NewClient.phone);

	while (true)
	{
		cout << "Balance: ";
		cin >> NewClient.AccountBalance;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again.\n";
		}
		else
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}

	return NewClient;
}

stClient ChangeClientRecord(string AccountNumber)
{
	stClient client;
	client.AccountNumber = AccountNumber;

	cout << "\nPin code: ";
	getline(cin >> ws, client.PinCode);
	cout << "\nName: ";
	getline(cin, client.Name);
	cout << "\nPhone : ";
	getline(cin, client.phone);
	while (true)
	{
		cout << "Balance: ";
		cin >> client.AccountBalance;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again.\n";
		}
		else
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
	return client;
}

bool UpdateClientData()
{
	cout << "=============================================\n";
	cout << "\n                Update Client\n";
	cout << "=============================================\n";

	string AccountNumber = ReadClientAccountNumber();
	stClient client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, client))
	{
		PrintClientCard(client);
		cout << "Are you sure you want update client ? [y/n]\n";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{

			vector<stClient>vClients = LoadingDataFromFile(ClientFileName);

			for (stClient& n : vClients)
			{
				if (n.AccountNumber == AccountNumber)
				{
					n = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(vClients, ClientFileName);
			system("cls");
			cout << "Client Account Updated successfully..";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number : " << AccountNumber << " isn't found";
	}
	return false;
}

void AddNewClient()
{
	stClient client;
	client = ReadClientData();
	AddDataLineToFile(ClientFileName, ConvertRecordToLine(client));
	cout << "\n\n\t\t\tClient has been Added Successfully..\n";

}

void AddClients()
{
	cout << "=============================================\n";
	cout << "\n                Add Clients\n";
	cout << "=============================================\n";
	char Answer = 'n';
	do
	{
		AddNewClient();
		cout << "\nDo you want to Add more clients ?";
		cin >> Answer;

	} while (tolower(Answer) == 'y');
}


bool DeleteClientByAccountNumber()
{
	string AccountNumber = ReadClientAccountNumber();
	stClient client;
	char Answer = 'y';

	system("cls");

	if (FindClientByAccountNumber(AccountNumber, client))
	{
		PrintClientCard(client);
		cout << "\nAre you sure you want delete client ?[Y/N]\n";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			vector<stClient>vClients = LoadingDataFromFile(ClientFileName);
			MarkClientForDeleteByAccountNumber(vClients, AccountNumber);
			SaveClientsDataToFile(vClients, ClientFileName);
			system("cls");
			cout << "Client is deleted ..\n";
			return true;
		}
	}

	else
	{
		system("cls");
		cout << "\nClient with Account Number " << AccountNumber << " is not found..\n";
		return false;
	}
	return false;
}

bool Depositing(string AccountNumber, double Amount)
{
	char answer = 'y';
	cout << "\nAre you sure you want perform this transaction? ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		vector<stClient>vClients = LoadingDataFromFile(ClientFileName);

		for (stClient& n : vClients)
		{
			if (n.AccountNumber == AccountNumber)
			{
				n.AccountBalance += Amount;
				SaveClientsDataToFile(vClients, ClientFileName);
				cout << "\nDone successfully , New balance is : " << n.AccountBalance;

				return true;
			}
		}
	}
	return false;
}


void ShowDepositScreen()
{
	cout << "\n=============================================\n";
	cout << "\n\tDeposit Screen\n";
	cout << "\n=============================================\n";

	double Amount = 0;
	string AccountNumber = ReadClientAccountNumber();
	stClient client;
	while (!FindClientByAccountNumber(AccountNumber, client))
	{
		system("cls");
		cout << "Client with Account number [" << AccountNumber << "] doesn't exist\n ";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(client);
	cout << "\nPlease enter Deposit Amount : ";
	cin >> Amount;
	Depositing(AccountNumber, Amount);
}

void ShowWithdrawScreen()
{
	cout << "\n=============================================\n";
	cout << "\nWithdraw Screen\n";
	cout << "\n=============================================\n";

	double Amount = 0;
	string AccountNumber = ReadClientAccountNumber();
	stClient client;
	while (!FindClientByAccountNumber(AccountNumber, client))
	{
		cout << "Client with Account number [" << AccountNumber << "] doesn't exist\n ";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(client);
	cout << "\nPlease enter Withdraw Amount : ";
	cin >> Amount;


	while (client.AccountBalance < Amount)
	{
		cout << "Amount Exceeds the balance , you can withdraw up to " << client.AccountBalance << endl;
		cout << "Please enter another amount : ";
		cin >> Amount;
	}
	Depositing(AccountNumber, Amount * -1);
}

void PrintClientBalance(stClient client)
{

	cout << "| " << setw(20) << left << client.AccountNumber;
	cout << "| " << setw(40) << left << client.Name;
	cout << "| " << setw(20) << left << client.AccountBalance;
	cout << "\n\n------------------------------------------------------------------------------------------------------------\n\n";

}

void ShowTotalBalances()
{
	vector<stClient>vClients = LoadingDataFromFile(ClientFileName);
	double TotalBalances = 0;

	if (vClients.size() == 0)

		cout << "\t\t\t\tNo Clients Available In the System!";

	else

		cout << "\n                   Balances List (" << vClients.size() << ") client (s).\n";
	cout << "\n============================================================================================================\n";
	cout << "| " << setw(20) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(20) << left << "Account Balance";
	cout << "\n============================================================================================================\n\n";


	for (stClient& n : vClients)
	{
		PrintClientBalance(n);
		TotalBalances += n.AccountBalance;
	}

	cout << "\n\n------------------------------------------------------------------------------------------------------------\n\n";
	cout << "\t\t\t\tTotal balances is : " << TotalBalances;
}

void GoBackToTransactionMenue()
{
	cout << "\n\nPress any key to go back to transaction menue.... \n";
	system("pause>0");
}

void PerformTransactionOptions(enTransactionMenueOptions option)
{
	system("cls");
	switch (option)
	{

	case eDeposit:
		ShowDepositScreen();
		GoBackToTransactionMenue();
		break;

	case eWithdraw:
		ShowWithdrawScreen();
		GoBackToTransactionMenue();
		break;

	case eTotalBalances:
		ShowTotalBalances();
		GoBackToTransactionMenue();
		break;

	case euMainMenue:
		break;

	}
}
stUser ConvertLineToUserRecord(string line)
{
	stUser record;
	vector<string>vstring = SplitString(line);
	record.username = vstring[0];
	record.password = vstring[1];
	record.permissions = stoi(vstring[2]);
	return record;
}

void ShowTransactionMenue()
{
	short answer;
	do
	{
		system("cls");
		cout << "\n=============================================\n";
		cout << "\n\t\tTransaction Menue\n";
		cout << "\n=============================================\n";
		cout << "\n[1]Deposit.\n\n";
		cout << "[2]Withdraw.\n\n";
		cout << "[3]Total Balances.\n\n";
		cout << "[4]Main Menue.\n\n";
		cout << "\n=============================================\n";
		cout << "Choose what do you want to do [1 to 4]: ";
		cin >> answer;
		PerformTransactionOptions(enTransactionMenueOptions(answer));

	} while (answer != 4);

}

void PrintClientRecord(stClient client)
{
	cout << "| " << left << setw(20) << client.AccountNumber
		<< "| " << left << setw(10) << client.PinCode
		<< "| " << left << setw(40) << client.Name
		<< "| " << left << setw(12) << client.phone
		<< "| " << left << setw(12) << client.AccountBalance;
	cout << "\n--------------------------------------------------------------------------------------------------------------------\n";

}


void PrintAllClientsData()
{

	vector<stClient>vClients = LoadingDataFromFile(ClientFileName);
	if (vClients.size() == 0)
		cout << "\t\t\tNo Clients Available In the System!";
	else

		cout << "\n\t\t\t\tClient List (" << vClients.size() << ") client (s).";
	cout << "\n--------------------------------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(20) << "Account Number: ";
	cout << "| " << left << setw(10) << "PinCode: ";
	cout << "| " << left << setw(40) << "Client Name: ";
	cout << "| " << left << setw(12) << "Phone: ";
	cout << "| " << left << setw(12) << "Balance: ";
	cout << "\n--------------------------------------------------------------------------------------------------------------------\n";


	for (stClient& client : vClients)
	{

		PrintClientRecord(client);
	}
}
bool UserExistsByUserName(string username, string FileName)
{
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string line;
		stUser user;

		while (getline(MyFile, line))
		{
			user = ConvertLineToUserRecord(line);
			if (user.username == username)
			{
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...\n";
	system("pause>0");
}

stUser ReadNewUser()
{
	stUser user;

	user.username = ReadUserName();
	while (UserExistsByUserName(user.username, UserFile))
	{
		cout << "\nUser is already exists !";
		user.username = ReadUserName();
	}
	user.password = ReadUserPass();
	user.permissions = AskForUserPermissions();

	return user;
}
void PrintMenueMenue()
{
	cout << "\t\t\t\n\nYou're logged in as : " << CurrentUser.username << "\n\n";

	cout << "\n=============================================\n";
	cout << "\n\t\tBank System\n";
	cout << "\n=============================================\n";
	cout << "\n[1]Show Clients List.\n\n";
	cout << "[2]Add New Client.\n\n";
	cout << "[3]Delete Client.\n\n";
	cout << "[4]Update Client Info.\n\n";
	cout << "[5]FindClient.\n\n";
	cout << "[6]Transactions.\n\n";
	cout << "[7]Manage Users.\n\n";
	cout << "[8]Logout.\n\n";
	cout << "\n=============================================\n";

}
void PerfromMainMenueOption(enMainMenueOptions option)
{
	system("cls");

	switch (option)
	{

	case enMainMenueOptions::eListClients:

		PrintAllClientsData();
		GoBackToMainMenue();

		break;

	case enMainMenueOptions::eAddNewClient:

		AddClients();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeleteClient:
		DeleteClientByAccountNumber();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eUpdateClient:
		UpdateClientData();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:
		FindClient();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eTransaction:

		ShowTransactionMenue();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eManageUsersScreen:
		ManageUsersScreen();
		break;

	case enMainMenueOptions::eLogout:
		LoginScreen();
		break;
	}

}
bool CheckUserAccessPermission(enPermissions perm)
{
	return (CurrentUser.permissions & perm) == perm;
}
enPermissions ReturnOptionPermissionNumber(short number)
{
	switch (number)
	{
	case 1:
		return elist;
		break;
	case 2:
		return eadd;
		break;
	case 3:
		return edeleteuser;
		break;
	case 4:
		return eupdate;
		break;
	case 5:
		return efind;
		break;
	case 6:
		return etrans;
		break;
	case 7:
		return emanage;
		break;
	}
}
void MainMenueScreen(stUser user)
{
	short number = 0;
	do
	{
		system("cls");
		PrintMenueMenue();
		number = ReadMainMenueOption();
		enPermissions permission = ReturnOptionPermissionNumber(number);
		if ((CheckUserAccessPermission(permission) || number == 8))
		{
			PerfromMainMenueOption((enMainMenueOptions)number);
		}
		else
		{
			cout << "\nYour access has been denied , please contact Admin...";
			system("pause>0");
		}
	} while (number != 8);
}

string ConvertUserRecordToLine(stUser record, string delim = "#//#")
{
	string line;
	return line += record.username + delim + record.password + delim + to_string(record.permissions);
}

vector<stUser> LoadingUsersDataFromFile()
{
	vector<stUser>vUsers;
	stUser record;
	string line;
	fstream MyFile;

	MyFile.open(UserFile, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			if (line.empty())
				continue;

			record = ConvertLineToUserRecord(line);
			vUsers.push_back(record);
		}
		MyFile.close();
	}
	return vUsers;
}
vector<stUser> SaveUserDataToFile(vector<stUser>& vUser)
{
	fstream MyFile;
	MyFile.open(UserFile, ios::out);
	if (MyFile.is_open())
	{
		for (stUser& user : vUser)
		{
			if (!user.MarkForDeleteUser)
			{
				string line = ConvertUserRecordToLine(user);
				MyFile << line << endl;
			}
		}
		MyFile.close();
	}
	vUser = LoadingUsersDataFromFile();
	return vUser;
}
bool FindUserByUsername(string username, vector<stUser>& vUsers, stUser& user)
{
	for (stUser& U : vUsers)
	{
		if (U.username == username)
		{
			user = U;
			return true;
		}
	}
	return false;
}

bool FindUserByUsernameAndPassword(string username, string password, stUser& U)
{
	vector<stUser>vUsers = LoadingUsersDataFromFile();
	for (stUser& user : vUsers)
	{
		if (user.username == username && user.password == password)
		{
			U = user;
			return true;
		}
	}
	return false;
}


short AskForUserPermissions()
{
	char answer;
	int permission = 0;
	cout << "\nDo You want to give full access for the user  ? [y][n]";
	cin >> answer;

	if (tolower(answer) == 'y')
		return -1;
	else
		cout << "\nDo you want to give access to :\n";

	cout << "Show client list [y][n]?\n";
	cin >> answer;
	if (answer == 'y')
		permission = permission | elist;
	cout << "Add new client [y][n]?\n";
	cin >> answer;
	if (answer == 'y')
		permission |= eadd;

	cout << "Delete client [y][n]?\n";
	cin >> answer;
	if (answer == 'y')
		permission |= edeleteuser;

	cout << "Update client [y][n]?\n";
	cin >> answer;
	if (answer == 'y')
		permission |= eupdate;

	cout << "Find client [y][n]?\n";
	cin >> answer;
	if (answer == 'y')
		permission |= efind;

	cout << "Transactions [y][n]?\n";
	cin >> answer;
	if (answer == 'y')
		permission |= etrans;

	cout << "Manage Users [y][n]?\n";
	cin >> answer;
	if (answer == 'y')
		permission |= emanage;

	return permission;
}

void AddOneUser()
{
	stUser user;
	vector<stUser>vUsers = LoadingUsersDataFromFile();
	user = ReadNewUser();
	AddDataLineToFile(UserFile, ConvertUserRecordToLine(user));
}

void AddNewUsers()
{
	char more = 'y';
	do
	{
		AddOneUser();
		cout << "\nUser  has been added successfully ,Do you want to add more users?\n";
		cin >> more;
	} while (more == 'y' || more == 'Y');

}
void ShowAddNewUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n-----------------------------------\n";
	AddNewUsers();
}
void PrintUserRecordLine(stUser user)
{
	cout << "|" << left << setw(30) << user.username;
	cout << "|" << left << setw(30) << user.password;
	cout << "|" << left << setw(30) << user.permissions;

}
void ShowAllUsersScreen()
{
	vector<stUser>vUsers = LoadingUsersDataFromFile();
	cout << "              Users Number is : " << vUsers.size()
		<< "\n===============================================================================\n";
	cout << "|" << left << setw(30) << "Username";
	cout << "|" << left << setw(30) << "password";
	cout << "|" << left << setw(30) << "Permissions";
	cout << "\n===============================================================================\n";

	if (vUsers.size() == 0)
	{
		cout << "\nNo Users Available in the system !";
	}
	else
	{
		for (stUser& user : vUsers)
		{
			PrintUserRecordLine(user);
			cout << endl;
		}
		cout << "\n===============================================================================";
	}

}
void PrintUserCard(stUser user)
{
	cout << "\nUser Information\n";
	cout << "================================\n";
	cout << "\nUser Name: " << user.username;
	cout << "\nPassword: " << user.password;
	cout << "\nPermissions: " << user.permissions;

	cout << "\n\n================================\n";

}
bool DeleteUserByUsername(vector<stUser>& vUsers, string username)
{

	if (username == "Admin")
	{
		cout << "\nYou can't delete Admin .\n";
		system("pause>0");
		return false;
	}
	stUser user;
	char answer = 'y';
	if (FindUserByUsernameAndPassword(user.username, user.password, user))
	{
		PrintUserCard(user);
		cout << "\nAre you sure you want to delete user?\n";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			MarkUserForDeleteByAccountNumber(vUsers, username);
			SaveUserDataToFile(vUsers);
			//Refresh 
			vUsers = LoadingUsersDataFromFile();
			cout << "\nUser has been deleted successfully ";

			return true;
		}
	}
	else
	{
		cout << "\nUser with Username (" << username << ") is Not Found!";
		system("pause>0");
		return false;
	}
}
void ShowDeleteUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Users Screen";
	cout << "\n-----------------------------------\n";

	string username = ReadUserName();
	vector<stUser>vUsers = LoadingUsersDataFromFile();
	DeleteUserByUsername(vUsers, username);
}
stUser ChangeUserRecord(string username)
{
	stUser user;
	user.username = username;
	user.password = ReadUserPass();
	user.permissions = AskForUserPermissions();
	return user;
}
void UpdateUserByUsername(string username, vector<stUser>& vUsers)
{
	stUser user;
	char answer = 'n';
	if (FindUserByUsername(username, vUsers, user))
	{
		PrintUserCard(user);
		cout << "\nAre you syre you want to Update user ?[y][n]";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			for (stUser& u : vUsers)
			{
				if (u.username == user.username && u.password == user.password)
				{
					u = ChangeUserRecord(username);
					break;
				}
			}
			SaveUserDataToFile(vUsers);
		}
	}
	else
	{
		printf("\nUser with username : %s is not found !", username.c_str());
	}
}
void ShowUserUpdateScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Users Screen";
	cout << "\n-----------------------------------\n";
	string username = ReadUserName();
	vector<stUser>vUsers = LoadingUsersDataFromFile();
	UpdateUserByUsername(username, vUsers);
	cout << "\nUser updated successfully .";
}
void ShowFindUserScreen()
{
	string username = ReadUserName();
	vector<stUser>vUsers = LoadingUsersDataFromFile();
	stUser user;
	if (FindUserByUsername(username, vUsers, user))
	{
		PrintUserCard(user);
		system("pause>0");
	}
	else
	{
		cout << "User Not found in system !\n";
	}
}
void PerformMangeUsersScreen(enUserMenueOptions option)
{
	system("cls");
	switch (option)
	{
	case enUserMenueOptions::eShowAllUsers:
		ShowAllUsersScreen();
		system("pause>0");
		break;

	case enUserMenueOptions::eAddUser:
		ShowAddNewUserScreen();
		break;

	case enUserMenueOptions::eDeleteUser:
		ShowDeleteUserScreen();
		break;

	case enUserMenueOptions::eUpdateUser:
		ShowUserUpdateScreen();
		break;

	case enUserMenueOptions::eFindUser:
		ShowFindUserScreen();
		break;

	}
}

void ManageUsersScreen()
{
	short number = 0;

	while (number != 6)
	{
		system("cls");
		cout << "========================================\n"
			<< "            Manage User Screen\n"
			<< "========================================\n";

		cout << "\n\n[1]Show All Users."
			<< "\n\n[2]Add user."
			<< "\n\n[3]Delete User."
			<< "\n\n[4]Update users."
			<< "\n\n[5]Find user."
			<< "\n\n[6]Back to main menue.";
		cout << "\n\n========================================\n";

		cout << "\nChoose what do you want to do [1-6] :\n";
		cin >> number;
		PerformMangeUsersScreen((enUserMenueOptions)number);
	}
}
bool LoadingUserInfo(string username, string password)
{
	if (FindUserByUsernameAndPassword(username, password, CurrentUser))
		return true;
	else
		return false;
}

void LoginScreen()
{
	bool LoginFailed = false;

	do
	{
		system("cls");
		cout << "======================================================="
			<< "\n              Login Screen\n"
			<< "=======================================================";

		if (LoginFailed)
		{
			cout << "\nWrong username/password !";
			system("pause>0");
		}

		string username = ReadUserName();
		string password = ReadUserPass();
		LoginFailed = !LoadingUserInfo(username, password);

	} while (LoginFailed);

	MainMenueScreen(CurrentUser);
}

int main()
{
	LoginScreen();

	system("pause>0");
	return 0;
}
