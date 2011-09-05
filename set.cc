#include <iostream>
#include <set>
#include <cassert>

template <typename T>
void print_set(std::set<T>& s)
{
        typedef typename std::set<T>::iterator SetIt;
        for (SetIt it = s.begin(); it != s.end(); ++it)
                std::cout << *it << " ";
        std::cout << "\n";
}
#define ______________________________ print_set

int main(int argc, char* argv[])
{
        const int A[] = {3, 1, 4, 1, 5};
        const int N = sizeof(A) / sizeof(A[0]);

        std::set<int> s(A, A + N);
        ______________________________(s);

        std::pair<std::set<int>::iterator, bool> ret = s.insert(7);
        assert(ret.second);
        std::cout << "inserted " << *ret.first << "\n";
        ______________________________(s);

        ret = s.insert(7);
        assert(!ret.second);
        std::cout << "failed to insert " << *ret.first << " because it's already there.\n";
        ______________________________(s);

        const int B[] = {9, 2, 6, 5, 3, 5};
        const int M = sizeof(B) / sizeof(B[0]);
        s.insert(B, B + M);
        ______________________________(s);

        assert(s.count(7) == 1);
        assert(s.count(8) == 0);
        assert(s.find(7) != s.end());
        assert(s.find(8) == s.end());

        assert(s.erase(6) == 1);
        ______________________________(s);

        return 0;
}
