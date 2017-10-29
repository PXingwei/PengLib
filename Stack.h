#ifndef _STACK_H__
#define _STACK_H__
#include "Object.h"

namespace PengLib {
	template <typename T>
	class Stack : public Object
	{
	public:
		virtual void push(const T& e) = 0;
		virtual void pop() = 0;
        virtual T Top() const = 0;
		virtual void clear() = 0;
        virtual int Size() const = 0;
	};
}

#endif
