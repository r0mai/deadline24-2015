#include <iostream>
#include <cstdint>
#include <valarray>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>

using maxt = unsigned __int128;
using data = std::uintmax_t;

std::valarray<data> map{0,1,1};
std::valarray<data> sum{0,1,2};

data mod;
data c;
data hol = 0;
data get(data n)
{
    while(hol < n)
    {
        map = map.shift(1);
        sum = sum.shift(1);
        map[2] = (static_cast<maxt>(c) * map[1] + map[0]) % mod;
        sum[2] = (static_cast<maxt>(sum[1]) + map[2]) % mod;
        ++hol;
    }
    return sum[0];
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

    std::for_each(tCsRes.begin(), tCsRes.end(), [](decltype(*tCsRes.begin())& elem)
    {
        elem.second = get(elem.first);
    });

    for(data i = 0; i < t ; ++i)
    {
        std::cout << tCsRes[ nthTcs[i] ] << std::endl;
    }
}

