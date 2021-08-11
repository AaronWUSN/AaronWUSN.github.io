#include <conio.h>
#include "FinalProject.h"
#include "sqlite3.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
sqlite3* db;

//Access SQLite Database
int OpenDatabase()
{
	int opendb = sqlite3_open("FINAL.db", &db);

	if (opendb) {
		cout << "Cannot Open Database" << endl;
	}
	else {
		cout << "Database Opened Successfully" << endl;
	}
	return opendb;
}

//Callback function for SQLite features
static int Callback(void *data, int argc, char **argv, char **azColName) 
{
	int i;

	for (i = 0; i < argc; i++) {
		cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
	}
	cout << endl;
	return 0;
}

//SQL help finding row value
static int RowCount(void* data, int argc, char** argv, char** azColName) {
	(*(int*)data)++;
	return 0;
}

//Display client and selection from DB
void ReadDB()
{
	char* zErrMsg = 0;
	int readDB;
	const char *sql;
	const char* data = "";

	cout << "Service Selected (1 = Brokerage , 2 = Retirement)" << endl;

	sql = "SELECT * FROM CLIENTS";

	readDB = sqlite3_exec(db, sql, Callback, (void*)data, &zErrMsg);

	if (readDB != SQLITE_OK) {
		cerr << "SQL error: " << zErrMsg << endl;
	}
}

void CreateClient() 
{
	string newName;
	int newSel;
	sqlite3_stmt* NewClient;

	cin.ignore();
	cout << "Enter Name Of Client: " << endl;
	getline(cin, newName);

	//Lower potential for injection with character limit
	while(newName.size() > 30) {
		cout << "Name can be at most 30 characters" << endl << "Enter Name Of Client: " << endl;
		getline(cin, newName);
	}
	cout << "Enter Selection Of Client: (1 = Brokerage, 2 = Retirement)" << endl;
	cin >> newSel;
	while (newSel != 1 && newSel != 2) {
		cout << "Invalid selection: " << newSel << endl << "Enter Selection Of Client (1 = Brokerage, 2 = Retirement)" << endl;
		cin >> newSel;
	}

	//Cast newName to const char* for SQL
	const char* newName2 = newName.c_str();

	//Prepare SQL entry
	//This helps against injection attacks
	if (sqlite3_prepare_v2(db, "INSERT INTO CLIENTS(NAME, SELECTION) VALUES(?,?)", -1, &NewClient, 0) != SQLITE_OK) {
		cout << "Could Not Prepare Statement" << endl;
	}

	//Bind SQL TEXT entry
	if (sqlite3_bind_text(
		NewClient,
		1, //index of wildcard
		newName2, //text to bind
		-1, //length (terminate at first null)
		SQLITE_STATIC) != SQLITE_OK)
	{
		cout << "Could Not Bind Text" << endl;
	}
	if (sqlite3_bind_int(
		NewClient,
		2, //Index of wildcard
		newSel) != SQLITE_OK)
	{
		cout << "Could Not Bind INT" << endl;
	}

	//Display the entry
	cout << "Entering " << newName << " With Selection " << to_string(newSel) << " Into Database" << endl;

	//Execute the prepared SQL statement
	if (sqlite3_step(NewClient) != SQLITE_DONE) {
		cout << "Could Not Execute Statement" << endl;
	}
	else {
		cout << "Entry Created Successfully" << endl;
	}
}

void DeleteClient() 
{
	int delid;
	string confirmdel;
	int rowcount;
	string dirty;

	//SQL inquiry variable setup
	char* zErrMsg = 0;
	int pullID;
	int DeleteUser;
	string query;
	const char* sql;
	const char* data = "";
	string sql2;

	ReadDB();

	cin.ignore();
	while (1) {
		cout << "Enter the ID of the client you wish to delete" << endl;
		getline(cin, dirty);
		try {
			delid = stoi(dirty);
		}
		catch (...) {
			delid = -1;
		}
		//delId is an int, so no possible injection attack
		query = (string("SELECT ID FROM CLIENTS WHERE ID=") + to_string(delid));
		rowcount = 0;
		sqlite3_exec(db, query.c_str(), RowCount, &rowcount, &zErrMsg);
		if (rowcount == 1)
			break;
		cout << "Invalid ID" << endl;
	}
	//Confirm deletion
	while (1) {
		cout << "Are you sure you wish to delete client: " << endl;

		sql2 = string("SELECT * FROM CLIENTS WHERE ID = ") + to_string(delid);
		sql = sql2.c_str();

		pullID = sqlite3_exec(db, sql, Callback, (void*)data, &zErrMsg);

		cout << "y = YES, n = NO" << endl;
		cin >> confirmdel;

		//Allows for uppercase or lowercase selection
		if (confirmdel == "y" || confirmdel == "Y") {
			sql2 = string("DELETE FROM CLIENTS WHERE ID = ") + to_string(delid);
			sql = sql2.c_str();
			DeleteUser = sqlite3_exec(db, sql, Callback, (void*)data, &zErrMsg);
			return;
		}
		else if (confirmdel == "n" || confirmdel == "N") {
			cout << "Delete Aborted " << endl;
			return;
		}
		else {
			cout << "Invalid selection, please try again" << endl;
		}
	}
}

//Encryption key setup
string EncryptDecrypt(string encryptdata)
{
	char key = 'S';
	string output = encryptdata;

	for (int i = 0; i < encryptdata.size(); i++)
		output[i] = encryptdata[i] ^ key;
	return output;
}

//Check for new user, and prompt for username and password to save
void NewUser()
{
	string newusername;
	string newpass;
	string pw;

	//Initialize read from files
	ifstream userfile;
	ifstream passfile;

	//Open username and password files
	userfile.open("Username.txt");
	passfile.open("Pass.txt");

	//Check to see if files exist. If not, create them, prompt input, and encrypt them.
	if (userfile.is_open() == false && passfile.is_open() == false) {

		//create files
		ofstream userfile2;
		userfile2.open("Username.txt");
		ofstream passfile2;
		passfile2.open("Pass.txt");

		//Ask for input
		cout << "NEW USER DETECTED, PLEASE SET UP USERNAME/PASSWORD" << endl;
		cout << "Enter New Username:" << endl;
		getline(cin, newusername);
		cout << "Enter New Password:" << endl;

		//Hide Password
		for (int i = 0; i < 1000; i++) {
			pw = _getch();
			if (pw == "\r")
				break;
			cout << "*";
			newpass += pw;
		}

		//encrypt data and send to files
		string userencrypt = EncryptDecrypt(newusername);
		userfile2 << userencrypt;
		string passencrypt = EncryptDecrypt(newpass);
		passfile2 << passencrypt;

		//Close files after using
		userfile2.close();
		passfile2.close();
	}
	else {
		cout << "Proceeding To Login" << endl;
	}
}

static int CheckUserPermissionAccess()
{
	//Check for a new user
	NewUser();

	string username;
	string password;
	string user;
	string pass;
	string pw;

	cout << endl << "Enter Your Username: ";
	getline(cin, user);
	cout << "Enter Your Password: ";

	//Hide Password
	for (int i = 0; i < 1000; i++) {
		pw = _getch();

		if (pw == "\r")
			break;
		cout << "*";
		pass += pw;
	}
	cout << endl;

	//Encrypt inputs for check
	user = EncryptDecrypt(user);
	pass = EncryptDecrypt(pass);

	//Initialize read from files
	ifstream userfile3;
	ifstream passfile3;

	//Open username and password files
	userfile3.open("Username.txt");
	passfile3.open("Pass.txt");

	if (userfile3.is_open())
	{
		getline(userfile3, username);
	}
	else {
		cout << "File Not Open" << endl;
	}

	if (passfile3.is_open())
	{
		getline(passfile3, password);
	}

	//Close files after using
	userfile3.close();
	passfile3.close();

	//Checks username vs input
	if (user == username && pass == password)
	{
		return 1;
	}
	else
	{
		cout << endl << "Invalid Login, Try Again" << endl;
		return 0;
	}
}

//Allows user to change customer selection
void ChangeCustomerChoice()
{
	int changechoice;
	int changesel;
	int rowcount;
	string ChangeChoiceDirty;
	string query;
	
	//SQL inquiry variable setup
	char* zErrMsg = 0;
	int changedb;
	const char* sql;
	const char* data = "";
	string sql2;

	ReadDB();
	
	cin.ignore();
	while (1) {
		cout << "Enter the ID of the client you wish to change: " << endl;
		getline(cin, ChangeChoiceDirty);
		try {
			changechoice = stoi(ChangeChoiceDirty);
		}
		catch (...) {
			changechoice = -1;
		}
		//changechoice is an int, so no possible injection attack
		query = (string("SELECT ID FROM CLIENTS WHERE ID=") + to_string(changechoice));
		rowcount = 0;
		sqlite3_exec(db, query.c_str(), RowCount, &rowcount, &zErrMsg);

		//Throw error if that id is not used in database
		if (rowcount == 0) {
			cout << "Invalid ID" << endl;
			break;
		}
		else {
			cout << "Enter the client's new service choice (1 = Brokerage , 2 = Retirement): ";
			cin >> changesel;

			//Prevents invalid selection of service choice
			if (changesel < 1 || changesel > 2) {
				cout << "Invalid Choice, Please Try Again" << endl;
				break;
			}
			else {
				//SQL Update function
				sql2 = string("UPDATE CLIENTS SET SELECTION = ") + to_string(changesel) + string(" WHERE ID = ") + to_string(changechoice);
				sql = sql2.c_str();

				//Execute update function
				changedb = sqlite3_exec(db, sql, Callback, (void*)data, &zErrMsg);
				return;
			}
		}
	}
}
int main()
{
	int MainMenuChoice;
	int loginsuccess = 0;
	string MenuSel;

	//Created By Statement
	cout << "Created By Aaron Walker" << endl;

	//Open Database
	if (OpenDatabase()) {
		return -1;
	}

	//If user hasn't logged in, make them login
	while (loginsuccess == 0)
	{
		loginsuccess = CheckUserPermissionAccess();
	}

	//After successful login, print the menu and run the menu loop
	while (loginsuccess == 1)
	{
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "DISPLAY the client list (Enter 1)" << endl;
		cout << "CHANGE a client's choice (Enter 2)" << endl;
		cout << "CREATE a new client (Enter 3)" << endl;
		cout << "DELETE a client (Enter 4)" << endl;
		cout << "EXIT the program (Enter 5)" << endl;

		cin >> MenuSel;

		//Runs the input through the stringsteam. Also prevents problems with inputs > INT_MAX
		stringstream sanitize3;
		sanitize3 << MenuSel;
		sanitize3 >> MainMenuChoice;

		//Switch case menu
		switch (MainMenuChoice) {
		case 1:
			ReadDB();
			break;
		case 2:
			ChangeCustomerChoice();
			break;
		case 3:
			CreateClient();
			break;
		case 4:
			DeleteClient();
			break;
		case 5:
			sqlite3_close(db);
			loginsuccess = 0;
			return 0;
		default:
			cout << "Try Again" << endl;
		}
	}
}