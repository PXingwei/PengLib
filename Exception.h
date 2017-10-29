#ifndef _EXCEPTION_H__
#define _EXCEPTION_H__
#include "Object.h"
#include <cstdlib>
#include <cstring>

namespace PengLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:

	char* m_message;
	char* m_location;

	void init(const char* message, const char* file, int line);

public:

	Exception(const char* message);

	Exception(const char* file, int line);

	Exception(const char* message, const char* file, int line);

	Exception(const Exception& obj);

	Exception& operator = (const Exception& obj);

	const char* message() const;

	const char* location() const;

	virtual ~Exception() = 0;

};

class ArithmaticException : public Exception
{
public:
	ArithmaticException(const char* message) : Exception(message) {}

	ArithmaticException(const char* file, int line): Exception(file, line) {}

	ArithmaticException(const char* message, const char* file, int line): Exception(message, file, line) {}

	ArithmaticException(const ArithmaticException& obj): Exception(obj) {}

	ArithmaticException& operator = (const ArithmaticException& obj)
	{
		Exception::operator = (obj);
		return *this;
	}

};

class indexOutOfBoundsException : public Exception
{
public:
	indexOutOfBoundsException(const char* message) : Exception(message) {}

	indexOutOfBoundsException(const char* file, int line): Exception(file, line) {}

	indexOutOfBoundsException(const char* message, const char* file, int line): Exception(message, file, line) {}

	indexOutOfBoundsException(const indexOutOfBoundsException& obj): Exception(obj) {}

	indexOutOfBoundsException& operator = (const indexOutOfBoundsException& obj)
	{
		Exception::operator = (obj);
		return *this;
	}

};

class NoEnoughMemoryException : public Exception
{
public:
	NoEnoughMemoryException(const char* message) : Exception(message) {}

	NoEnoughMemoryException(const char* file, int line): Exception(file, line) {}

	NoEnoughMemoryException(const char* message, const char* file, int line): Exception(message, file, line) {}

	NoEnoughMemoryException(const NoEnoughMemoryException& obj): Exception(obj) {}

	NoEnoughMemoryException& operator = (const NoEnoughMemoryException& obj)
	{
		Exception::operator = (obj);
		return *this;
	}

};

class InvalidParameterException : public Exception
{
public:
	InvalidParameterException(const char* message) : Exception(message) {}

	InvalidParameterException(const char* file, int line): Exception(file, line) {}

	InvalidParameterException(const char* message, const char* file, int line): Exception(message, file, line) {}

	InvalidParameterException(const InvalidParameterException& obj): Exception(obj) {}

	InvalidParameterException& operator = (const InvalidParameterException& obj)
	{
		Exception::operator = (obj);
		return *this;
	}

};


class NullPointerException : public Exception
{
public:
	NullPointerException(const char* message) : Exception(message) {}

	NullPointerException(const char* file, int line): Exception(file, line) {}

	NullPointerException(const char* message, const char* file, int line): Exception(message, file, line) {}

	NullPointerException(const NullPointerException& obj): Exception(obj) {}

	NullPointerException& operator = (const NullPointerException& obj)
	{
		Exception::operator = (obj);
		return *this;
	}

};

class InvalidOperationException : public Exception
{
public:
    InvalidOperationException(const char* message) : Exception(message) {}

    InvalidOperationException(const char* file, int line): Exception(file, line) {}

    InvalidOperationException(const char* message, const char* file, int line): Exception(message, file, line) {}

    InvalidOperationException(const InvalidOperationException& obj): Exception(obj) {}

    InvalidOperationException& operator = (const InvalidOperationException& obj)
    {
        Exception::operator = (obj);
        return *this;
    }

};

}

#endif // EXCEPTION_H
