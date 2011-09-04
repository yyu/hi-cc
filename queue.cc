#include <iostream>
#include <queue>
#include <list>

int main(int argc, char * argv[])
{
        std::queue<int> q;
        // std::queue< int, std::list<int> > q; // use list as the containter

        q.push(3);
        q.push(1);
        q.push(4);
        q.push(1);
        q.push(5);
        q.push(9);
        q.push(2);
        q.push(6);
        q.push(5);

        while (!q.empty()) {
                std::cout << q.front() << "\t" << q.back() << "\n";
                q.pop();
        }

        return 0;
}
