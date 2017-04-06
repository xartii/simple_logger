#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>

std::vector<std::string> explode(std::string haystack, std::string needle) {
    std::vector<std::string> result;
    boost::split(result, haystack, boost::is_any_of(needle));
    return result;
}
