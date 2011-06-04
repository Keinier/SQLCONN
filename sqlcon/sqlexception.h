
#ifndef _SQL_EXCEPTION_H_
#define _SQL_EXCEPTION_H_


#include <stdexcept>
#include <string>
#include <memory>



#define MEMORY_ALLOC_OPERATORS(Class) \
	void* operator new(size_t size) throw (std::bad_alloc) { return ::operator new(size); }  \
	void* operator new(size_t, void*) throw(); \
	void* operator new(size_t, const std::nothrow_t&) throw(); \
	void* operator new[](size_t) throw (std::bad_alloc); \
	void* operator new[](size_t, void*) throw(); \
	void* operator new[](size_t, const std::nothrow_t&) throw(); \
	void* operator new(size_t N, std::allocator<Class>&);

#ifdef _WIN32
#pragma warning (disable : 4290)
//warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)


#pragma warning(push)
#pragma warning(disable: 4275)
#endif
class   SQLException : public std::runtime_error
{
#ifdef _WIN32
#pragma warning(pop)
#endif
protected:
	const std::string sql_state;
	const int errNo;

public:
	SQLException(const SQLException& e) : std::runtime_error(e.what()), sql_state(e.sql_state), errNo(e.errNo) {}

	SQLException(const std::string& reason, const std::string& SQLState, int vendorCode) :
		std::runtime_error	(reason		),
		sql_state			(SQLState	),
		errNo				(vendorCode)
	{}

	SQLException(const std::string& reason, const std::string& SQLState) : std::runtime_error(reason), sql_state(SQLState), errNo(0) {}

	SQLException(const std::string& reason) : std::runtime_error(reason), sql_state("HY000"), errNo(0) {}

	SQLException() : std::runtime_error(""), sql_state("HY000"), errNo(0) {}

	const std::string & getSQLState() const
	{
		return sql_state;
	}

	const char * getSQLStateCStr() const
	{
		return sql_state.c_str();
	}


	int getErrorCode() const
	{
		return errNo;
	}

	virtual ~SQLException() throw () {};

protected:
	MEMORY_ALLOC_OPERATORS(SQLException)
};

struct   MethodNotImplementedException : public SQLException
{
	MethodNotImplementedException(const MethodNotImplementedException& e) : SQLException(e.what(), e.sql_state, e.errNo) { }
	MethodNotImplementedException(const std::string& reason) : SQLException(reason, "", 0) {}
};

struct   InvalidArgumentException : public SQLException
{
	InvalidArgumentException(const InvalidArgumentException& e) : SQLException(e.what(), e.sql_state, e.errNo) { }
	InvalidArgumentException(const std::string& reason) : SQLException(reason, "", 0) {}
};

struct   InvalidInstanceException : public SQLException
{
	InvalidInstanceException(const InvalidInstanceException& e) : SQLException(e.what(), e.sql_state, e.errNo) { }
	InvalidInstanceException(const std::string& reason) : SQLException(reason, "", 0) {}
};


struct   NonScrollableException : public SQLException
{
	NonScrollableException(const NonScrollableException& e) : SQLException(e.what(), e.sql_state, e.errNo) { }
	NonScrollableException(const std::string& reason) : SQLException(reason, "", 0) {}
};


#endif /* _SQL_EXCEPTION_H_ */
