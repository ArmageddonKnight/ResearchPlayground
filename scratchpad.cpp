#include <iostream>
#include <vector>
#include <functional>

int main()
{
        int a = 0;
        std::vector < std::reference_wrapper < const int > > A;
        A.push_back(a);

        std::cout << A[0];

        return 0;
}