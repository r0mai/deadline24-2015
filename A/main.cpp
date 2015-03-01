#include <iostream>
#include <cstdint>
#include <vector>

using maxt = unsigned __int128;

std::vector<maxt> map{0,1,1};
std::vector<maxt> sum{0,1,2};

maxt mod;
maxt c;

maxt get(maxt n)
{
    if(sum.size() < n)
        return sum[n];

    map.reserve(n+1);
    sum.reserve(n+1);

    auto reservedEnd = map.begin() + map.capacity();
    for(auto it = map.end(), it2 = sum.end(); it != reservedEnd; ++it, ++it2)
    {
        map.insert(it, (c * it[-1] + it[-2]) % mod );
        sum.insert(it2, (it2[-1] + *it) % mod );
    }
    return sum.back();
}

int main()
{
    maxt t;
    std::cin >> c >> mod >> t;
    for(maxt i = 0; i < t ; ++i)
        std::cout << get( *std::istream_iterator<maxt>(std::cin) ) << std::endl;
}

