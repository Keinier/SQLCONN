#include "StdAfx.h"
#include "SQLCONN.h"


void CSQLCONN::CleanUP(void)
{
	mysql_library_end();
	
	_mysql=0;
	_host=NULL; 
	_user=NULL;
	_pass=NULL;  
	_unixsocket=NULL;
	_database=NULL;	
	_clientflags=NULL;	
	_port=3306;	
}
void CSQLCONN::InitLibrary(void)
{
	CleanUP();
	mysql_library_init(0,NULL,NULL);
}
void CSQLCONN::InitClient(void)
{
	try{
	MYASSERT_PTR((_mysql=mysql_init(0)));
	}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}
CSQLCONN::CSQLCONN(void)
{
	InitLibrary();
	InitClient();
}

CSQLCONN::CSQLCONN(sql_str host,sql_uint port,sql_str user,sql_str pass,sql_str database=NULL,sql_str unixsock=NULL,sql_ulong flags=0)
{
	InitLibrary();
	InitClient();

	_host=host; 
	_user=user;
	_pass=pass;  
	_unixsocket=unixsock;
	_database=database;	
	_clientflags=flags;	
	_port=port;	

}
void CSQLCONN::Close(void)
{
		if(_mysql){
	mysql_close(_mysql);

	}
	this->CleanUP();
	
}
CSQLCONN::~CSQLCONN(void)
{
	Close();
}
void CSQLCONN::Connect(void)
{	
	try{
	MYASSERT_PTR(mysql_real_connect(_mysql,this->_host,this->_user,this->_pass,this->_database,this->_port,this->_unixsocket,this->_clientflags));
	}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}

sql_uint CSQLCONN::Ping(void)
{
	sql_uint rate;
	try{

	MYASSERT_INT(rate=mysql_ping(_mysql));
		}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
	return rate;
}
void CSQLCONN::Option(enum mysql_option option, sql_str arg)
{
	try{

	MYASSERT_INT(mysql_options(_mysql,option,arg));
		}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}

sql_ulong CSQLCONN::GetThreadId(void)
{
	return mysql_thread_id(_mysql);
}

void CSQLCONN::Dump(void)
{
	try{

	MYASSERT_INT(mysql_dump_debug_info(_mysql));
		}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}

sql_ulonglong CSQLCONN::GetAffectedRows(void)
{
	return mysql_affected_rows(_mysql);
}

void CSQLCONN::AutoCommit(bool mode)
{
	try{
	MYASSERT_INT(mysql_dump_debug_info(_mysql));
		}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}

void CSQLCONN::ChangeUser(sql_str user,sql_str pass,sql_str db)
{
	try{
	MYASSERT_INT(mysql_change_user(_mysql, user, pass,db));
		}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}

sql_str CSQLCONN::GetCharSetName(void)
{
	return (sql_str) mysql_character_set_name(_mysql);
}


void CSQLCONN::DataSeek(sql_ulonglong offset)
{
	if((offset >0) && (offset < mysql_num_rows(result))){
	mysql_data_seek(result,offset);
	}
}

void CSQLCONN::Query(sql_str query)
{
	try{
	MYASSERT_INT(mysql_real_query(_mysql, query,strlen(query)));
		}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}

bool CSQLCONN::Commit(void)
{
	return (bool) mysql_commit(_mysql);
}

void CSQLCONN::UseResult(void)
{
	try{
	MYASSERT_PTR((result=mysql_use_result(_mysql)));
	}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}

void CSQLCONN::StoreResult(void)
{
		try{
	MYASSERT_PTR((result=mysql_store_result(_mysql)));
	}catch (SQLException e)
	{
		fprintf(stderr,"Exception Error: %s \n",e.what());
	}
}

void CSQLCONN::LoadFields(void)
{
	MYSQL_FIELD* _f;
	if(result!=NULL){
	while((_f=mysql_fetch_field (result)))
	{
		vFields.insert(vFields.end(),_f);
	}
	}


}

void CSQLCONN::FreeResult(void)
{
	mysql_free_result(result);
}

sql_uint CSQLCONN::GetNumFields(void)
{
	if(result!=0){
	return ( mysql_num_fields(result));
	}else{
		return 0;
	}
}

sql_ulonglong CSQLCONN::GetNumRows(void)
{
	return (mysql_num_rows(result));
}


void CSQLCONN::FetchRows(void)
{
	MYSQL_ROW row;
	sql_uint num_fields;
	sql_uint i;
	
	
	if(result!=NULL){
		num_fields = mysql_num_fields(result);
	while ((row = mysql_fetch_row(result)))
	{
		
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(result);
		vRow.insert(vRow.end(),row);
		
	/*	for(i = 0; i < num_fields; i++)
		{
			printf("[%.*s] ", (int) lengths[i],row[i] ? row[i] : "NULL");
		}
		printf("\n");*/
}
	}

}