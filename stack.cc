#include <iostream>
#include <stack>
#include <vector>

int main(int argc, char * argv[])
{
        std::stack<int> s;
        // std::stack< int, std::vector<int> > s; // use vector as the container

        s.push(3);
        s.push(1);
        s.push(4);
        s.push(1);
        s.push(5);
        s.push(9);
        s.push(2);
        s.push(6);
        s.push(5);

        while (!s.empty()) {
                std::cout << s.top() << "\n";
                s.pop();
        }

        return 0;
}
