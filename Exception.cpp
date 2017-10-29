#include "Exception.h"
#include <cstdio>
#include <cstring>

using namespace std;

namespace PengLib
{

void Exception::init(const char* message, const char* file, int line)
{

	m_message = (message ? strdup(message) : NULL);
	if(file != NULL)
	{
		char sl[16] = {0};
        sprintf(sl, "%d", line);

		if(sl != NULL)
		{
			char* location = reinterpret_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));

			location = strcpy(location, file);
			location = strcat(location, ":");
			location = strcat(location, sl);
			//location = strcat(location, "\0");

			m_location = location;
		}
	}
	else
	{
		m_location = NULL;
	}

}

Exception::Exception(const char* message)
{
	init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
	init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
	init(message, file, line);
}

Exception::Exception(const Exception& obj)
{
	this->m_message = strdup(obj.m_message);
	this->m_location = strdup(obj.m_location);
}

Exception& Exception::operator = (const Exception& obj)
{
	if(this != &obj)
	{
		free(this->m_message);
		free(this->m_location);
		this->m_message = strdup(obj.m_message);
		this->m_location = strdup(obj.m_location);
	}

	return *this;
}

const char* Exception::message() const
{
	return m_message;
}

const char* Exception::location() const
{
	return m_location;
}

Exception::~Exception()
{
	free(m_location);
	free(m_message);
}

}
