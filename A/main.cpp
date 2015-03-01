#include <iostream>
#include <cstdint>
#include <valarray>
#include <iterator>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>

using maxt = unsigned __int128;
using data = std::uintmax_t;

std::deque<data> map{0,1,1};
std::deque<data> sum{0,1,2};

data mod;
data c;
data hol = 0;
data get(data n)
{
    std::cerr << "get:" << n << std::endl;
    while(hol < n)
    {
        if(hol % 1000000000 == 0)
            std::cerr << "itt:"<< hol << std::endl;

        map.pop_front();
        sum.pop_front();
        map.push_back((static_cast<maxt>(c) * map.back() + map.front()) % mod);
        sum.push_back((static_cast<maxt>(sum.back()) + map.back()) % mod);
        ++hol;
    }
    return *sum.begin();
}

int main()
{
    data t;
    std::cin >> c >> mod >> t;

    std::vector< data > nthTcs(t);
    std::map< data, data > tCsRes;
    for(data i = 0; i < t ; ++i)
    {
        data tcs = *std::istream_iterator<data>(std::cin);
        nthTcs[i] = tcs;
        tCsRes[tcs];
    }
    std::cerr << "max: " << tCsRes.rbegin()->first << std::endl;
    std::for_each(tCsRes.begin(), tCsRes.end(), [](decltype(*tCsRes.begin())& elem)
    {
        elem.second = get(elem.first);
    });

    for(data i = 0; i < t ; ++i)
    {
        std::cout << tCsRes[ nthTcs[i] ] << std::endl;
    }
}

