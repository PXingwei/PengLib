#include <cstdlib>
#include <cstring>
#include "PLString.h"
#include "Exception.h"

using namespace std;

namespace PengLib
{
    String& String::remove(int i, int len)
    {
        if((0 <= i) && (i < m_length))
        {
            int n = i + len;

            while((i < n) && (n < m_length))
            {
                m_str[i++] = m_str[n++];
            }

            m_str[i] = '\0';
            m_length = i;
        }

        return *this;
    }

    int* String::make_pmt(const char* s)
    {
        int ll = 0;
        int* pmt = static_cast<int*>(malloc(sizeof(int) * strlen(s)));

        if(pmt != NULL)
        {
            pmt[0] = 0;
            for(unsigned int i=1; i<strlen(s); i++)
            {
                while((s[ll] != s[i]) && (ll > 0))
                {
                    ll = pmt[ll-1];
                }

                if(s[ll] == s[i])
                {
                    ll++;
                }
                pmt[i] = ll;
            }
        }

        return pmt;
    }

    int String::kmp(const char* s, const char* p)
    {
        int ret = -1;
        int sl = strlen(s);
        int pl = strlen(p);
        int* pmt = make_pmt(p);

        if(pmt != NULL)
        {
            for(int i=0, j=0; i<sl; i++)
            {
                while((j>0)&&(s[i]!=p[j]))
                {
                    j = pmt[j];
                }

                if(s[i] == p[j])
                {
                    j++;
                }
                if(j == pl)
                {
                    ret = i+1-pl;
                    break;
                }
            }
        }
        free(pmt);
        return ret;
    }

    void String::init(const char*s)
    {
        m_str = strdup(s);

        if(m_str != NULL)
        {
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create a string object");
        }
    }

    bool String::equal(const char* l, const char* r, int n) const
        {
            bool ret = true;

            for(int i=0; (i<n) && ret; i++)
            {
                ret = ret && (l[i] == r[i]);
            }

            return ret;
        }

    String::String()
    {
        init("");
    }

    String::String(const char* s)
    {
        init((s==NULL) ? "" : s);
    }

    String::String(char c)
    {
        char str[] = {c, '\0'};

        init(str);
    }

    String::String(const String& c)
    {
        init(c.m_str);
    }

    int String::length() const
    {
        return m_length;
    }

    const char* String::str() const
    {
        return m_str;
    }

    bool String::operator ==(const String& obj)
    {
        return (strcmp(this->m_str, obj.m_str) == 0);
    }

    bool String::operator ==(const char* obj)
    {
        return (strcmp(m_str, (obj != NULL ? obj : "")) == 0);
    }

    bool String::operator !=(const String& obj)
    {
        return !(*this == obj);
    }

    bool String::operator !=(const char* obj)
    {
        return !(*this == obj);
    }

    bool String::operator >(const String& obj)
    {
        return(strcmp(this->m_str, obj.m_str) > 0);
    }

    bool String::operator >(const char* obj)
    {
        return(strcmp(this->m_str, (obj != NULL ? obj : "")) > 0);
    }

    bool String::operator <(const String& obj)
    {
        return(strcmp(this->m_str, obj.m_str) < 0);
    }

    bool String::operator <(const char* obj)
    {
        return(strcmp(this->m_str, (obj != NULL ? obj : "")) < 0);
    }

    bool String::operator <=(const String& obj)
    {
        return(strcmp(this->m_str, obj.m_str) <= 0);
    }

    bool String::operator <=(const char* obj)
    {
        return(strcmp(this->m_str, (obj != NULL ? obj : "")) <= 0);
    }

    bool String::operator >=(const String& obj)
    {
        return(strcmp(this->m_str, obj.m_str) <= 0);
    }

    bool String::operator >=(const char* obj)
    {
        return(strcmp(this->m_str, (obj != NULL ? obj : "")) >= 0);
    }

    String String::operator +(const char* obj) const
    {
        String ret;

        int len = m_length + strlen((obj != NULL) ? obj : "");
        char* str = reinterpret_cast<char*>(malloc(len+1));

        if(str != NULL)
        {
            strcpy(str, m_str);
            strcat(str, (obj != NULL) ? obj : "");
            // strcat(str, '\0');

            free(ret.m_str);
            ret.m_str = str;
            ret.m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to add a string object");
        }

        return ret;
    }

    String String::operator +(const String& obj) const
    {
        return (*this + obj.m_str);
    }

    String String::operator +=(const char* obj)
    {
        return (*this = *this + obj);
    }

    String String::operator +=(const String& obj)
    {
        return (*this = *this + obj.m_str);
    }

    String& String::operator =(const String& s)
    {
        return (*this = s.m_str);
    }

    String& String::operator =(const char* s)
    {
        if(m_str != s)
        {
            char* str = strdup(s != NULL ? s : "");

            if(str)
            {
                free(m_str);

                m_str = str;
                m_length = strlen(str);
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to assign a new string object");
            }
        }
        return *this;
    }

    String& String::operator =(char s)
    {
        char str[] = {s, '\0'};
        return (*this = str);
    }

    char& String::operator [](int i)
    {
        if((0 <= i) && (i < m_length))
        {
            return m_str[i];
        }
        else
        {
            THROW_EXCEPTION(indexOutOfBoundsException, "Parameter is invalid");
        }
    }

    char String::operator [](int i) const
    {
        return const_cast<String&>(*this)[i];
    }

    bool String::startWith(const char* s) const
    {
        bool ret = (s != NULL);

        if(ret)
        {
            int len = strlen(s);
            ret = (len < m_length) && equal(m_str, s, len);
        }

        return ret;
    }

    bool String::startWith(const String& s) const
    {
        return startWith(s.m_str);
    }

    bool String::endOf(const char* s)const
    {
        bool ret = (s != NULL);

        if(ret)
        {
            int len = strlen(s);
            ret = (len < m_length) && equal(m_str+m_length-len, s, len);
        }

        return ret;
    }

    bool String::endOf(const String& s)const
    {
        return endOf(s.m_str);
    }

    String& String::insert(int i, const char* s)
    {
        if((0 <= i) && (i <= m_length))
        {
            if((s != NULL) && (s[0] != '\0'))
            {
                int len = strlen(s);
                char* str = reinterpret_cast<char*>(malloc(m_length + len +1));

                if(str != NULL)
                {
                    strncpy(str, m_str, i);
                    strncpy(str+i, s, len);
                    strncpy(str+i+len, m_str+i, m_length-i);
                    str[m_length + len] = '\0';

                    free(m_str);
                    m_str = str;
                    m_length = m_length + len;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to insert a string");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(indexOutOfBoundsException, "Parameter is invalid");
        }

        return *this;
    }

    String& String::insert(int i, const String& s)
    {
        return insert(i, s.m_str);
    }

    String& String::trim()
    {
        int b = 0;
        int e = m_length-1;

        while(m_str[b] == ' ')
        {
            b++;
        }

        while(m_str[e] == ' ')
        {
            e--;
        }

        if(b == 0)
        {
            m_str[e+1] = '\0';
            m_length = e+1;
        }
        else
        {
            for(int i=0, j=b; j<=e; i++, j++)
            {
                m_str[i] = m_str[j];
            }
            m_str[e-b+1] = '\0';
            m_length = e-b+1;
        }

        return *this;
    }

    int String::indexOf(const char* s)
    {
        return kmp(m_str, (s != NULL ? s: ""));
    }

    int String::indexOf(const String& s)
    {
        return kmp(this->m_str, s.m_str);
    }

    String& String::remove(const char* s)
    {
        return remove(indexOf(s), strlen(s != NULL ? s : ""));
    }

    String& String::remove(const String& s)
    {
        return remove(s.m_str);
    }

    String String::operator -(const String& s)
    {
        return String(*this).remove(s);
    }

    String String::operator -(const char* s)
    {
        return String(*this).remove(s);
    }

    String& String::operator -=(const String& s)
    {
        return remove(s);
    }

    String& String::operator -=(const char* s)
    {
        return remove(s);
    }

    String& String::replace(const char* s, const char* l)
    {
        int index = indexOf(s);

        if(index >= 0)
        {
            remove(s);

            insert(index, l);
        }

        return *this;
    }

    String& String::replace(const String& s, const String & l)
    {
        return replace(s.m_str, l.m_str);
    }

    String& String::replace(const char* s, const String & l)
    {
        return replace(s, l.m_str);
    }

    String& String::replace(const String& s, const char* l)
    {
        return replace(s.m_str, l);
    }

    String String::sub(int i, int len) const
    {
        String ret;

        if((0 <= i) && (i < m_length))
        {
            if(len < 0)
            {
                len = 0;
            }
            else if(len + i > m_length)
            {
                len = m_length - i;
            }

            char* str = static_cast<char*>(malloc(len + 1));

            if(str != NULL)
            {
                strncpy(str, this->m_str+i, len);
                str[len] = '\0';

                free(ret.m_str);
                ret.m_str = str;
                ret.m_length = len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "There is no enough memory to create a substring");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "the Parameter is invalid");
        }

        return ret;
    }

    String::~String()
    {
        free(m_str);
    }
}
