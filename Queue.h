#ifndef _QUEUE_H__
#define _QUEUE_H__
#include "Object.h"

namespace PengLib
{	
	template <typename T>
	class Queue : public Object
	{
	protected:
		virtual void add(const T& e) = 0;
		virtual void remove() = 0;
		virtual int size() const = 0;
		virtual void clear() = 0;
		virtual T front() const = 0;
	};
}

#endif
