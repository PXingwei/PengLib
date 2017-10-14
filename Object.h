#ifndef _OBJECT_H__
#define _OBJECT_H__


namespace PengLib
{
	/**Act as a Superclass, and defines a common behavior for the SubClass*/
	class Object
	{
	public:
		/**Overload the new operator */
        void* operator new(unsigned int size) throw();
		/**Overload the new[] operator */
        void* operator new[](unsigned int size) throw();
		/**Overload the delete operator */
		void operator delete (void* pn);
		/**Overload the delete[] operator */	
		void operator delete[] (void* pn);
		/**Overload the == operator */
        bool operator == (const Object& e);
        /**Overload the != operator */
        bool operator != (const Object& e);

		virtual ~Object();
	};
}

#endif // OBJECT_H

