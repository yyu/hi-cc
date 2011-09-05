#include <iostream>
#include <set>
#include <cassert>

template <typename T>
void print_set(std::multiset<T>& ms)
{
        typedef typename std::multiset<T>::iterator SetIt;
        for (SetIt it = ms.begin(); it != ms.end(); ++it)
                std::cout << *it << " ";
        std::cout << "\n";
}
#define ______________________________ print_set

int main(int argc, char* argv[])
{
        const int A[] = {3, 1, 4, 1, 5};
        const int N = sizeof(A) / sizeof(A[0]);

        std::multiset<int> ms(A, A + N);
        ______________________________(ms);

        std::multiset<int>::iterator it = ms.insert(7);
        assert(it != ms.end());
        std::cout << "inserted " << *it << "\n";
        ______________________________(ms);

        it = ms.insert(7);
        assert(it != ms.end());
        std::cout << "inserted " << *it << " again.\n";
        ______________________________(ms);

        const int B[] = {9, 2, 6, 5, 3, 5};
        const int M = sizeof(B) / sizeof(B[0]);
        ms.insert(B, B + M);
        ______________________________(ms);

        assert(ms.count(7) == 2);
        assert(ms.count(8) == 0);
        assert(ms.find(7) != ms.end());
        assert(ms.find(8) == ms.end());

        assert(ms.erase(5) == 3);
        ______________________________(ms);

        return 0;
}
