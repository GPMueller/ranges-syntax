#include <range/v3/all.hpp>

#include <iostream>
#include <string>

// Main
int main(int argc, char ** argv)
{
    using namespace ranges;

    std::vector<int> v = view::ints(0,20);
    ranges::for_each( v, [](int c){ std::cout << c << " "; });

    auto v2 = v | copy | action::slice(10,20);

    return 0;
}