#include <iostream>
#include <cstdint>
#include <vector>
#include <iterator>

using maxt = unsigned __int128;
using data = std::uintmax_t;

std::vector<data> map{0,1,1};
std::vector<data> sum{0,1,2};

data mod;
data c;

data get(data n)
{
    if(sum.size() > n)
        return sum[n];

    ++n;
    map.reserve(n);
    sum.reserve(n);

    for(auto it = map.end(), it2 = sum.end(); map.size() != n; ++it, ++it2)
    {
        map.insert(it, (static_cast<maxt>(c) * it[-1] + it[-2]) % mod );
        sum.insert(it2, (static_cast<maxt>(it2[-1]) + *it) % mod );
    }
    return sum.back();
}

int main()
{
    data t;
    std::cin >> c >> mod >> t;
    for(data i = 0; i < t ; ++i)
        std::cout << get( *std::istream_iterator<data>(std::cin) ) << std::endl;
}

