#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>

#include <cstdio>
#include <cstdlib>
#include <assert.h>

class IntFileReader {
public:
        IntFileReader() {}
        ~IntFileReader() {}
        bool get(std::vector<int>* p) {
                const char filename[] = "20-integers-less-than-100.txt";
                if (!p)
                        return false;
                if (ivec_.size() == 0) {
                        std::ifstream infile(filename);
                        if (!infile.is_open()) {
                                perror("failed to open test file.");
                                return false;
                        }

                        std::string line;
                        std::getline(infile, line);
                        assert(line[0] == '#');

                        int num;
                        while (infile >> num)
                                ivec_.push_back(num);

                        infile.close();
                }
                *p = ivec_;
                return true;
        }
private:
        std::vector<int> ivec_;

        // disallow copy constructor and assignment operator
        IntFileReader(const IntFileReader&);
        IntFileReader& operator=(const IntFileReader&);
};

template <typename T>
inline void print_vector_via_copy_to_ostream(const std::vector<T>& x)
{
        std::cout << " |";
        std::copy(x.begin(), x.end(), std::ostream_iterator<T>(std::cout, "|"));
        std::cout << std::endl;
}

template <typename T>
void print_vector_via_index(const std::vector<T>& v)
{
        typedef typename std::vector<T>::size_type SizeType;
        std::cout << "[ ";
        for (SizeType i = 0; i < v.size(); ++i)
                std::cout << v[i] << ' ';
        std::cout << "]\n";
}

template <typename T>
void print_vector_via_iterator(const T& v)
{
        typedef typename T::const_iterator ConstIt;
        std::cout << "< ";
        for (ConstIt it = v.begin(); it != v.end(); ++it)
                std::cout << *it << ' ';
        std::cout << ">\n";
}

int main(int argc, char * argv[])
{
        typedef std::vector<int> IntVec;
        typedef std::vector<int>::iterator IntVecIt;
        typedef std::vector<int>::const_iterator IntVecConstIt;

        std::cout << "\n======== empty vector ========\n";
        {
                IntVec v;

                std::cout << "v.empty(): " << v.empty() << std::endl;

                print_vector_via_iterator(v);

                // std::cout << v.front(); <-- NO GOOD
                // std::cout << v.back(); <-- NO GOOD
                // std::cout << v[1]; <-- NO GOOD
                try {
                        std::cout << v.at(1);
                } catch (std::out_of_range& e) {
                        std::cout << "! out of range !\n";
                }
        }

        std::cout << "\n======== C c(n); ========\n";
        {
                IntVec::size_type n = 8;
                IntVec v(n);

                print_vector_via_copy_to_ostream(v);
                print_vector_via_index(v);
                print_vector_via_iterator(v);
        }

        std::cout << "\n======== C c(n, t); ========\n";
        {
                IntVec::size_type n = 8;
                int init_val = 1;
                IntVec v(n, init_val);

                print_vector_via_copy_to_ostream(v);
                print_vector_via_index(v);
                print_vector_via_iterator(v);
        }

        IntFileReader ifr;

        std::cout << "\n======== C<T> c; ========\n";
        {
                IntVec v;
                ifr.get(&v);

                print_vector_via_copy_to_ostream(v);
                print_vector_via_index(v);
                print_vector_via_iterator(v);
                std::sort(v.begin(), v.end());
                print_vector_via_copy_to_ostream(v);
        }

        std::cout << "\n======== C c(c2); ========\n";
        {
                IntVec v;
                ifr.get(&v);

                IntVec v2(v);

                print_vector_via_copy_to_ostream(v2);
        }

        std::cout << "\n======== C c(b, e); ========\n";
        {
                IntVec v;
                ifr.get(&v);

                IntVec v2(v.begin(), v.end());

                print_vector_via_copy_to_ostream(v2);
        }

        std::cout << "\n======== pop_back() ========\n";
        {
                IntVec v;
                ifr.get(&v);

                print_vector_via_copy_to_ostream(v);
                v.pop_back();
                print_vector_via_copy_to_ostream(v);
        }

        std::cout << "\n======== reverse iterator ========\n";
        {
                IntVec v;
                ifr.get(&v);

                print_vector_via_copy_to_ostream(v);
                print_vector_via_copy_to_ostream(IntVec(v.rbegin(), v.rend()));
        }

        std::cout << "\n======== empty(), size(), max_size(), capacity() ========\n";
        {
                IntVec v;
                ifr.get(&v);

                print_vector_via_copy_to_ostream(v);

                std::cout << "empty():    " << v.empty() << "\n";
                std::cout << "size():     " << v.size() << "\n";
                std::cout << "max_size(): " << v.max_size() << "\n";
                std::cout << "max_size(): 0x"
                          << std::hex << v.max_size()
                          << std::dec << "\n";
                std::cout << "capacity(): " << v.capacity() << "\n";
        }

        std::cout << "\n======== assign() ========\n";
        {
                IntVec v;
                ifr.get(&v);

                print_vector_via_copy_to_ostream(v);

                IntVec::size_type n = 8;
                int new_val = 200;
                v.assign(n, new_val);

                print_vector_via_copy_to_ostream(v);

                IntVec v2;
                ifr.get(&v);
                v2.assign(v.rbegin(), v.rend());
                print_vector_via_copy_to_ostream(v2);
        }

        // insert()
        //   iterator insert(iterator position, const T& x);
        //   void insert(iterator pos, size_type n, const T& x );
        //   void insert(iterator pos, InputIterator first, InputIterator last );
        std::cout << "\n======== insert() ========\n";
        {
                IntVec v;
                ifr.get(&v);

                print_vector_via_copy_to_ostream(v);

                // Caution! This is no good:
                //     IntVecIt it = std::find(v.begin(), v.end(), 88);
                //     v.insert(it, 200);
                //     v.insert(it, 300);
                // because "it" is no longer valid after the first v.insert,
                // therefor if we wanna insert one more element, we should get
                // a new "it", like this:
                //     v.insert(it, 200);
                //     it = std::find(v.begin(), v.end(), some_number);
                //     v.insert(it, 300);
                // or we can renew "it" with the return value of v.insert:
                IntVecIt it = std::find(v.begin(), v.end(), 88);
                it = v.insert(it, 200); // renew "it" with the return value
                print_vector_via_copy_to_ostream(v);
                v.insert(it, 300); // we give up the return value,
                                   // which means "it" is no more valid
                print_vector_via_copy_to_ostream(v);

                IntVec::size_type howmany = 5;
                v.insert(std::find(v.begin(), v.end(), 7), howmany, 123);
                print_vector_via_copy_to_ostream(v);

                IntVec v2(3, 789);
                print_vector_via_copy_to_ostream(v2);
                v2.insert(v2.begin() + 1, v.begin(), v.end());
                print_vector_via_copy_to_ostream(v2);
        }

        // erase()
        //   iterator erase ( iterator position );
        //   iterator erase ( iterator first, iterator last );
        std::cout << "\n======== erase() ========\n";
        {
                IntVec v;
                ifr.get(&v);

                print_vector_via_copy_to_ostream(v);

                IntVecIt it = v.erase(std::find(v.begin(), v.end(), 76));
                print_vector_via_copy_to_ostream(v);
                std::cout << *it << "\n";

                it = v.erase(std::find(v.begin(), v.end(), 65),
                             std::find(v.begin(), v.end(), 37));
                print_vector_via_copy_to_ostream(v);
                std::cout << *it << "\n";
        }

        std::cout << "\n======== clear() ========\n";
        {
                IntVec v;
                ifr.get(&v);

                print_vector_via_copy_to_ostream(v);
                v.clear();
                print_vector_via_copy_to_ostream(v);
        }

        return EXIT_SUCCESS;
}
