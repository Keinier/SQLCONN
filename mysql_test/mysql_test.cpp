// mysql_test.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include "../sqlcon/SQLCONN.h"

CSQLCONN *con;
int _tmain(int argc, _TCHAR* argv[])
{

	con=new CSQLCONN("kei-software.com",3306,"root","7628134k","keisoft_caidas",0,0);
	
	con->Connect();
	con->Query("select user_name,user_email from USER;");
	con->StoreResult();
	con->LoadFields();
	con->FetchRows();
	
	for(int i=0;i<=con->GetNumFields()-1;i++)
	{
		std::cout<< con->vFields[i]->name << "\t";
	}
	
	std::cout<<std::endl;

	for(int j=0;j<=con->GetNumRows()-1;j++){
		for(int z=0;z<=con->GetNumFields()-1;z++)
		{
		std::cout<< con->vRow[j][z] << "\t";
		}
		std::cout<<std::endl;
	}

	
	con->Close();

	delete con;
	system("pause");
	return 0;
}

