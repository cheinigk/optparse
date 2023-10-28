#pragma once

#include <string_view>
#include <boost/spirit/home/x3.hpp>

namespace optparse {

class Modifier {
};

Modifier operator<<(Modifier const& mod, Modifier const& other) {
  return mod;
};

Modifier long_option(std::string_view ) { return {}; }
Modifier short_option(char c) { return {}; }
Modifier help(std::string_view ) { return {}; }

class ParserInfo {
};

ParserInfo switchP(auto const& mod) {
  return {};
};

template<class T>
class Parser {
public:
  explicit Parser<T>(ParserInfo const& /* pi */) {};
  T operator()(std::string_view argv) { return {true}; }
};

}
