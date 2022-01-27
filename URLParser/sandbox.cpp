#include <iostream>
#include "./Library/URL/url.hpp"


int main()
{
    const auto test = URL("test.com/example.html");
    std::cout << test.Source();

    return 0;
}
