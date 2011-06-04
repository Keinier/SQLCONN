#ifndef __SQLCONN_H__
#define __SQLCONN_H__

#include "stdafx.h"
#include "datatype.h"
#include "sqlexception.h"
#include "MYASSERT.h"


#include <vector>

class CSQLCONN
{
private:
	
	/* Atributos del conector para conexion */

	MYSQL* _mysql; // <-- Ligadura del cliente con el MSDB
	MYSQL_RES *result; // <-- Resultados de consultas
	sql_str _host; // <-- URL/IP del servidor MSDB
	sql_str _user;	// <-- Usuario para accesar al MSDB
	sql_str _pass;  // <-- Password para accesar al MSDB
	sql_str _unixsocket;	// <-- Socket UNIX implementado para la conexion (SOLO UNIX)
	sql_str _database;	// <-- Nombre de la base de datos a trabajar
	sql_ulong _clientflags;	// <-- Opciones extras para la conexion con el servidor
	sql_uint _port;	// <-- Puerto donde el MSDB escucha

	// campos
public:
	std::vector<MYSQL_FIELD*> vFields;
	std::vector<MYSQL_ROW> vRow;




	// Metodos de Inicialización del objeto //
	void CleanUP(void);
	void InitLibrary(void);
	void InitClient(void);

	// Metodos para la gestion de conexion //

	void Connect(void);
	void Close(void); // <--- Es llamada automaticamente al destruirse el objeto

	/* Metodos para configuraciones */

	void Option(enum mysql_option option, sql_str arg);
	void AutoCommit(bool mode);
	bool Commit(void);
	void ChangeUser(sql_str user,sql_str pass,sql_str db);
	
	/* Métodos testeo de conexion */
	sql_uint Ping(void);
	sql_ulong GetThreadId(void);
	sql_str GetCharSetName(void);

	/* Metodos resultados de consultas */

	sql_ulonglong GetAffectedRows(void); // <-- Obtiene los registros afectados
	sql_uint GetNumFields(void);
	sql_ulonglong GetNumRows(void);

	void DataSeek(sql_ulonglong offset);
	void Query(sql_str query);
	void UseResult(void);
	void StoreResult(void);
	void FreeResult(void);
	void FetchRows(void);
	/* Metodos de manipulacion de campos */
	void LoadFields(void);

	/* DEBUG FUNCTIONS */
	void Dump(void); 
	void DebugDump(void);

	// Constructores del Objeto //
	CSQLCONN(void); // <-- Constructor por defecto

	/* Constructor por efecto */
	CSQLCONN(sql_str host,sql_uint port,sql_str user,sql_str pass,sql_str database,sql_str unixsock,sql_ulong flags); 
	~CSQLCONN(void);// <-- Destructor por defecto
	
};

#endif //__SQLCONN_H__
