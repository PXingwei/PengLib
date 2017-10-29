#include <iostream>
#include "Sort.h"
#include "StaticArray.h"
#include <ctime>

using namespace std;
using namespace PengLib;

//template <int SIZE>
//class QueenSolution : public Object
//{
//private:
//    enum{ N = SIZE + 2 };

//    struct Pos : public Object
//    {
//        int x;
//        int y;

//        Pos(int px=0, int py=0) : x(px), y(py) {}
//    };

//    int ChessBoard[N][N];

//    int count;

//    Pos direction[3];

//    LinkList<Pos> m_solution;

//    void init()
//    {
//        count = 0;

//        for(int i=0; i<N; i+=(N-1))
//        {
//            for(int j=0; j<N; j++)
//            {
//                ChessBoard[i][j] = 2;
//                ChessBoard[j][i] = 2;
//            }
//        }

//        for(int i=1; i<=SIZE; i++)
//        {
//            for(int j=1; j<=SIZE; j++)
//            {
//                ChessBoard[i][j] = 0;
//            }
//        }

//        direction[0].x = -1;
//        direction[0].y = -1;
//        dir
//    };ection[1].x = 0;
//        direction[1].y = -1;
//        direction[2].x = 1;
//        direction[2].y = -1;
//    }

//    void print()
//    {
//        for(m_solution.move(0); !m_solution.end(); m_solution.next())
//        {
//            cout<<"("<<m_solution.current().x<<", "<<m_solution.current().y<<")";
//        }

//        cout<<endl;

//        for(int i=0; i<N; i++)
//        {
//            for(int j=0; j<N; j++)
//            {
//                switch(ChessBoard[j][i])
//                {
//                    case 0:
//                        cout<<i;
//                        break;
//                    case 1:
//                        cout<<"#";
//                        break;
//                    case 2:
//                        cout<<"*";
//                        break;
//                    default:
//                        cout<<"?";
//                }
//            }
//            cout<<endl;
//        }
//        cout<<endl;
//    }

//    bool check(int x, int y, int d)
//    {
//        while(ChessBoard[x][y] == 0)
//        {
//            x += direction[d].x;
//            y += direction[d].y;
//        }

////        return (ChessBoard[x][y] == 2);
////        bool flag = true;
////        do
////        {
////           x += direction[d].x;
////           y += direction[d].y;
////           flag = flag && (ChessBoard[x][y] == 0);
////        } while(flag);

//        return (ChessBoard[x][y] == 2);

//    }

//    void run(int j)
//        {
//            if(j <= SIZE)
//            {
//                for(int i = 1; i<=SIZE; i++)
//                {
//                    if(check(i, j, 0) && check(i, j, 1) && check(i, j, 2))
//                    {
//                        ChessBoard[i][j] = 1;
//                        m_solution.insert(Pos(i, j));
//                        run(j+1);

//                        ChessBoard[i][j] = 0;
//                        m_solution.remove(m_solution.length()-1);
//                    }
//                }
//            }
//            else
//            {
//                count++;
//                print();
//            }
//        }

//public:

//    QueenSolution()
//    {
//        init();
//    }

//    void run()
//    {
//        run(1);
//        cout<<"Total:"<<count<<endl;
//    }

//};

struct Test : public Object
{
    int id;
    int data1[1000];
    double data2[500];

    bool operator < (const Test& obj)
    {
        return id < obj.id;
    }

    bool operator > (const Test& obj)
    {
        return id > obj.id;
    }

    bool operator <= (const Test& obj)
    {
        return id <= obj.id;
    }

    bool operator >= (const Test& obj)
    {
        return id >= obj.id;
    }
};

struct testProxy : public Object
{
protected:
    Test* mPtest;

public:
    int id()
    {
        return mPtest->id;
    }

    int* data1()
    {
        return mPtest->data1;
    }

    double* data2()
    {
        return mPtest->data2;
    }

    Test& test() const
    {
        return *mPtest;
    }

    bool operator > (const testProxy& obj)
    {
        return this->test() > obj.test();
    }

    bool operator < (const testProxy& obj)
    {
        return this->test() < obj.test();
    }

    bool operator >= (const testProxy& obj)
    {
        return this->test() >= obj.test();
    }

    bool operator <= (const testProxy& obj)
    {
        return this->test() <= obj.test();
    }

    Test& operator = (Test& obj)
    {
        mPtest = &obj;

        return obj;
    }
};

Test t[1000];
testProxy tp[1000];

int main()
{
    for(int i=0; i<1000; i++)
    {
        t[i].id = i;
        tp[i] = t[i];
    }

    clock_t begin;
    clock_t end;

    begin = clock();
    Sort::Buble(tp, 1000, false);
    end = clock();

    cout<<end-begin<<endl;

    for(int i=0; i<1000; i++)
    {
        cout<<t[i].id<<"  "<<tp[i].id()<<endl;

    }

    return 0;
}



//class test:public Object
//{
//public:
//    int a;
//    void priny()
//    {
//        cout<<a<<endl;
//    }
//};
/**This function is used to implemnt the josephus problem
  *@param n the number of people
  *@param s the start number
  *@param m each time count how many number
  */
//void josephus(int n, int s, int m)
//{
//    DualCircleList<int> cl;

//    for(int i=1; i<=n; i++)
//    {
//        cl.insert(i);
//    }

//    cl.move(s-1, m-1);

//    while(cl.length() > 0)
//    {
//        cl.next();
//        cout<<cl.current()<<endl;
//        cl.remove(cl.find(cl.current()));
//    }
//}

//void josephus(int n, int s, int m)
//{
//    DualCircleList<int> l;

//    for(int i=1; i<=n; i++)
//    {
//        l.insert(i);
//    }
//    l.move(s-1, m-1);

//    while(!l.end())
//    {
//        l.next();
//        cout<<l.current()<<endl;
//        l.remove(l.find(l.current()));
//    }
//}

//bool is_left(char c)
//{
//    return (c == '<') || (c == '(') || (c == '[') || (c == '{');
//}

//bool is_right(char c)
//{
//    return (c == '>') || (c == ')') || (c == ']') || (c == '}');
//}

//bool is_quote(char c)
//{
//    return (c == '\'') || (c == '\"');
//}

//bool is_match(char l, char r)
//{
//    return ((l == '(') && (r == ')')) ||   \
//           ((l == '<') && (r == '>')) ||   \
//           ((l == '[') && (r == ']')) ||   \
//           ((l == '{') && (r == '}')) ||   \
//           ((l == '\'') && (r == '\'')) ||   \
//           ((l == '\"') && (r == '\"'));
//}

//bool scan(const char* code)
//{
//    bool ret = true;
//    int i=0;
//    LinkStack<char> ls;
//    code = (code == NULL) ? "" : code;

//    while(ret && (code[i] != '\0'))
//    {
//        if(is_left(code[i]))
//        {
//            ls.push(code[i]);
//        }
//        else if(is_right(code[i]))
//        {
//            if((ls.Size() > 0) && is_match(ls.Top(),code[i]))
//            {
//                ls.pop();
//            }
//            else
//            {
//                ret = false;
//            }

//        }
//        else if(is_quote(code[i]))
//        {
//            if((ls.Size() == 0) || (!is_match(ls.Top(),code[i])))
//            {
//                ls.push(code[i]);
//            }
//            else if(is_match(ls.Top(),code[i]))
//            {
//                ls.pop();
//            }
//        }

//        i++;
//    }

//    return (ret && (ls.Size() == 0));
//}


