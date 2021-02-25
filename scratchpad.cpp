#include <iostream>
#include <vector>
#include <functional>


template < typename T1, typename T2 >
struct A
{
        void foo()
        {
                std::cout << "A generic" << std::endl;
        }
};

template < typename T2 >
struct A < int, T2 > : A < float, T2 >
{
        void boo()
        {
                std::cout << "Happy!" << std::endl;
        }
};


int main()
{
        A < int, float > a;
        a.foo();

        return 0;
}
