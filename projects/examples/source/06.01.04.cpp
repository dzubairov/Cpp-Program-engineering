#include <cassert>
#include <cstring>
#include <source_location>
#include <string>

using namespace std::literals;

/////////////////////////////////////////////////////////////////////

int main()
{
    constexpr auto location = std::source_location::current();

//  -----------------------------------------------------------------

    std::string file = location.file_name();

    auto path = "06.01.04.cpp";

    assert(file.substr(std::size(file) - std::strlen(path)) == path);

//  -----------------------------------------------------------------

    assert(location.line() == 12);

//  -----------------------------------------------------------------

    assert(location.function_name() == "int main()"s);
}