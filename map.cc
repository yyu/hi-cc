#include <iostream>
#include <string>
#include <map>
#include <cassert>

typedef std::pair<std::string, std::string> CallingcodesAndCallprefix;
typedef std::map<std::string, CallingcodesAndCallprefix> PhonecallMap;

#define country     first
#define callingcode second.first
#define callprefix  second.second

void print_map(PhonecallMap& m)
{
        // When we iterate across an associative container, we are guaranteed that the elements are accessed in key order,
        // irrespective of the order in which the elements were placed in the container
        // -- C++ Primer §10.2 @ p.359
        // 
        // When we use an iterator to traverse a map, the iterators yield elements in ascending key order.
        // -- C++ Primer §10.3.8 @ p.369
        for (PhonecallMap::iterator it = m.begin(); it != m.end(); ++it) {
                std::cout << "\t" << it->country << "\n";
                std::cout << "\t\tcalling code: " << it->callingcode << "\n";
                std::cout << "\t\tcall prefix : " << it->callprefix << "\n";
        }
}

int main(int argc, char * argv[])
{
        PhonecallMap m;

        // See:
        //   http://en.wikipedia.org/wiki/List_of_country_calling_codes
        //   http://en.wikipedia.org/wiki/List_of_international_call_prefixes
        m["US"] = std::make_pair("+1",   "011");   // USA
        m["CN"] = std::make_pair("+86",  "00");    // China
        m["ZH"] = std::make_pair("+86",  "00");    // China (repeated intentionally)
        m["TW"] = std::make_pair("+886", "00");    // Taiwan

        m["AU"] = std::make_pair("+",    "0011");  // Australia
        m["AU"] = std::make_pair("+61",  "0011");  // Australia exists, this line should change the mapped value

        m.insert(PhonecallMap::value_type("JP", std::make_pair("+81",  "010")));   // Japan
        m.insert(PhonecallMap::value_type("CA", std::make_pair("+1",   "011")));   // Canada
        m.insert(PhonecallMap::value_type("CU", std::make_pair("+53",  "119")));   // Cuba

        std::pair<PhonecallMap::iterator, bool> ret =
                m.insert(PhonecallMap::value_type("TH", std::make_pair("+66",  "001")));   // Thailand
        assert(ret.second);
        std::cout << "("
                  << ret.first->country
                  << " => <"
                  << ret.first->callingcode
                  << ", "
                  << ret.first->callprefix
                  << ">) inserted successfully.\n";

        ret = m.insert(PhonecallMap::value_type("TH", std::make_pair("+",    "001")));   // Thailand exists, so this line should do nothing
        assert(!ret.second);
        std::cout << "("
                  << ret.first->country
                  << " => <"
                  << ret.first->callingcode
                  << ", "
                  << ret.first->callprefix
                  << ">) already exists. returning with nothing done.\n";

        std::cout << "traverse:\n";
        print_map(m);

        std::cout << "map::count():\n";
        const char * countries[] = {"CN", "XX"};
        const int num_of_countries = sizeof(countries) / sizeof(countries[0]);
        for (int i = 0; i < num_of_countries; ++i) {
                PhonecallMap::iterator it = m.find(countries[i]);
                std::cout << "\t" << countries[i] << " is";
                if (m.count(countries[i]) == 0) {
                        assert(it == m.end());
                        std::cout << " not";
                } else {
                        assert(it != m.end());
                }
                std::cout << " in the map\n";
        }

        const char thebad[] = "CU";
        std::cout << "map::erase(" << thebad << "):\n";
        m.erase(thebad);
        print_map(m);

        const char thedup[] = "ZH";
        PhonecallMap::iterator it = m.find(thedup);
        assert(it != m.end());
        std::cout << "map::erase(iterator of " << thedup << "):\n";
        m.erase(it);
        print_map(m);

        const char * range_to_del[] = {"JP", "US"};
        PhonecallMap::iterator it_b = m.find(range_to_del[0]);
        PhonecallMap::iterator it_e = m.find(range_to_del[1]);
        assert(it_b != m.end());
        assert(it_e != m.end());
        std::cout << "map::erase([" << range_to_del[0] << ", ..., [" << range_to_del[1] << "):\n";
        m.erase(it_b, it_e);
        print_map(m);

        return 0;
}
