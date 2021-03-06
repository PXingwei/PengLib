#ifndef _PLSTRING_H__
#define _PLSTRING_H__
#include "Object.h"
#include <stdlib.h>

namespace PengLib
{
    class String : public Object
    {
    protected:
        char* m_str;
        int m_length;

        void init(const char*s);
        bool equal(const char* l, const char* r, int n) const;
        static int* make_pmt(const char* s);
        static int kmp(const char* s, const char* p);
        String& remove(int i, int len);

    public:
         String();
         String(const char* s);
         String(char c);
         String(const String& c);

         int length() const;
         const char* str() const;

         bool operator ==(const String& obj);
         bool operator ==(const char* obj);
         bool operator !=(const String& obj);
         bool operator !=(const char* obj);
         bool operator >(const String& obj);
         bool operator >(const char* obj);
         bool operator <(const String& obj);
         bool operator <(const char* obj);
         bool operator <=(const String& obj);
         bool operator <=(const char* obj);
         bool operator >=(const String& obj);
         bool operator >=(const char* obj);

         String operator +(const char* obj) const;
         String operator +(const String& obj) const;
         String operator +=(const char* obj);
         String operator +=(const String& obj);

         String& operator =(const String& s);
         String& operator =(const char* s);
         String& operator =(char s);

         char& operator [](int i);
         char operator [](int i) const;

         bool startWith(const char* s) const;
         bool startWith(const String& s) const;
         bool endOf(const char* s)const;
         bool endOf(const String& s)const;

         String& insert(int i, const char* s);
         String& insert(int i, const String& s);

         String& trim();

         int indexOf(const char* s);
         int indexOf(const String& s);

         String& remove(const char* s);
         String& remove(const String& s);

         String operator -(const String& s);
         String operator -(const char* s);
         String& operator -=(const String& s);
         String& operator -=(const char* s);

         String& replace(const char* s, const char* l);
         String& replace(const char* s, const String & l);
         String& replace(const String& s, const char* l);
         String& replace(const String& s, const String & l);

         String sub(int i, int len) const;

         ~ String();

    };
}

#endif
