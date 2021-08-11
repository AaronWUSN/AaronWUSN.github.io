#pragma once

static int CheckUserPermissionAccess();
static int RowCount(void* data, int argc, char** argv, char** azColName);
void ChangeCustomerChoice();
void NewUser();
int OpenDatabase();
void ReadDB();
void CreateClient();
void DeleteClient();