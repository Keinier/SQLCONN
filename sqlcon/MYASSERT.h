#ifndef __MYASSERT_H__
#define __MYASSERT_H__
#include "sqlexception.h"

#ifdef _DEBUG
#define TRACE(y) \
	fprintf(stdout,"\n\n-->[!] Trace: Executing-->\t %s  OK \n",#y);

#define MYASSERT_INT(x) \
	if(x){ \
	fprintf(stderr,"\n-->[X] Assertion Failure: (%s)\n @ - %s ( line %i )\n",#x,__FILE__,__LINE__);\
	throw(SQLException(mysql_error(_mysql)));\
	}else{\
	TRACE(x);\
	}

#define MYASSERT_PTR(x) \
	if(!x){ \
	fprintf(stderr,"\n-->[X] Assertion Failure: (%s)\n @ - %s ( line %i )\n",#x,__FILE__,__LINE__);\
	throw(SQLException(mysql_error(_mysql)));\
	}else{\
	TRACE(x);\
	}

#else
#define TRACE(y) y

#define MYASSERT_INT(x) \
	if(x){ \
	throw(SQLException(mysql_error(_mysql)));\
	exit(EXIT_FAILURE);\
	}

#define MYASSERT_PTR(x) \
	if(!x){ \
	throw(SQLException(mysql_error(_mysql)));\
	exit(EXIT_FAILURE);\
	}

#endif

#endif