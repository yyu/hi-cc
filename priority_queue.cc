#include <iostream>
#include <iterator>
#include <queue>
#include <algorithm>
#include <cassert>

#define __________________________________________________ print_iterative

template <typename T>
void print_iterative(T b, T e, bool newline = true)
{
        std::copy(b, e, std::ostream_iterator<int>(std::cout, " "));
        if (newline)
                std::cout << std::endl;
}

void print_banner(const std::string& banner)
{
        const char Pattern = '=';
        const std::string padding = " ";
        const int banner_len_max = 100;

        // int left_pattern_len = (banner_len_max - banner.size()) / 2;
        int left_pattern_len = 10;
        int right_pattern_len = banner_len_max - banner.size() - left_pattern_len - padding.size() * 2;
        assert(left_pattern_len > 0);
        assert(right_pattern_len > 0);
        std::string prefix_str = std::string(left_pattern_len, Pattern);
        std::string suffix_str = std::string(right_pattern_len, Pattern);

        std::cout << prefix_str
                  << padding
                  << banner
                  << padding
                  << suffix_str
                  << "\n";
}

int main(int argc, char* argv[])
{
        print_banner("default priority_queue");
        {
                // the default is equivelent to
                // std::priority_queue< int, std::vector<int>, std::less<int> > pq;
                std::priority_queue<int> pq;

                pq.push(3);
                pq.push(1);
                pq.push(4);

                while (!pq.empty()) {
                        std::cout << pq.top() << " ";
                        pq.pop();
                }
                std::cout << '\n';
                // output: 4 3 1
        }

        print_banner("priority_queue with non-default container and non-default compare function");
        {
                std::priority_queue< int, std::deque<int>, std::greater<int> > pq;

                pq.push(3);
                pq.push(1);
                pq.push(4);

                while (!pq.empty()) {
                        std::cout << pq.top() << ' ';
                        pq.pop();
                }
                std::cout << '\n';
                // output: 1 3 4
        }

        print_banner("priority_queue(begin, end)");
        {
                const int init[] = {3, 1, 4};
                const int len = sizeof(init) / sizeof(init[0]);

                std::priority_queue<int> pq(init, init + len);

                pq.push(1);
                pq.push(6);

                while (!pq.empty()) {
                        std::cout << pq.top() << " ";
                        pq.pop();
                }
                std::cout << '\n';
                // output: 6 4 3 1 1
        }

        print_banner("make_heap(), pop_heap()");
        {
                int A[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
                int N = sizeof(A) / sizeof(A[0]);

                std::make_heap(A, A + N);
                __________________________________________________(A, A + N);

                for (int i = 0; i < N; ++i) {
                        std::cout << A[0] << " <= ";
                        std::pop_heap(A, A + N - i);
                        __________________________________________________(A, A + N - i - 1);
                }
        }

        print_banner("heapsort using make_heap() and pop_heap()");
        {
                int A[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
                int N = sizeof(A) / sizeof(A[0]);

                std::make_heap(A, A + N);
                __________________________________________________(A, A + N);
                for (int i = 0; i < N; ++i)
                        std::pop_heap(A, A + N - i);
                __________________________________________________(A, A + N);
        }

        print_banner("heapsort using make_heap() and sort_heap()");
        {
                int A[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
                int N = sizeof(A) / sizeof(A[0]);

                std::make_heap(A, A + N);
                __________________________________________________(A, A + N);
                std::sort_heap(A, A + N);
                __________________________________________________(A, A + N);
        }

        print_banner("make_heap(), pop_heap() + container.pop_back()");
        {
                int A[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
                int N = sizeof(A) / sizeof(A[0]);

                //std::deque<int> pq(A, A + N);
                std::vector<int> pq(A, A + N);

                std::make_heap(pq.begin(), pq.end());

                for (int i = 0; i < N; ++i) {
                        // the one with the most priority:
                        std::cout << "(" << pq.front() << ") ";
                        __________________________________________________(pq.begin(), pq.end());

                        std::pop_heap(pq.begin(), pq.end());

                        std::cout << "\t\t\tafter pop_heap: ";
                        __________________________________________________(pq.begin(), pq.end(), false);

                        std::cout << "    pq.pop_back() is expected right now\n";
                        pq.pop_back();
                }
        }

        print_banner("make_heap(), pop_heap() + container.pop_back(), push_heap()");
        {
                int A1[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
                int N1 = sizeof(A1) / sizeof(A1[0]);
                int A2[] = {8, 9, 7, 9, 3, 2, 3, 8};
                int N2 = sizeof(A2) / sizeof(A2[0]);
                int k = 0;

                std::vector<int> pq(A1, A1 + N1);

                std::make_heap(pq.begin(), pq.end());

                for (int i = 0; i < N1 + N2; ++i) {
                        // the one with the most priority:
                        std::cout << "(" << pq.front() << ") ";
                        __________________________________________________(pq.begin(), pq.end());

                        std::pop_heap(pq.begin(), pq.end());

                        std::cout << "\t\t\tafter pop_heap: ";
                        __________________________________________________(pq.begin(), pq.end(), false);

                        std::cout << "    pq.pop_back() is expected right now\n";
                        pq.pop_back();

                        if (k < N2) {
                                int new_val = A2[k++];
                                pq.push_back(new_val);
                                std::push_heap(pq.begin(), pq.end());

                                std::cout << "\t\t\tafter push_heap(" << new_val << "): ";
                                __________________________________________________(pq.begin(), pq.end());
                        }
                }
        }

        return 0;
}
