/**
 * @file
 * @brief The main API of the optparse library.
 * @author Christian Heinigk
 */

#pragma once

#include <string_view>
#include <vector>
#include <boost/spirit/home/x3.hpp>

namespace optparse {

/**
 * @class Void
 * @brief An actual type which encodes just one possible value, namely void.
 *
 */
struct Void {};

/**
 * @class Modifier
 * @brief Modifies the CLI Parser to read long and short options or display the corresponding help text.
 *
 * @tparam T The default value's type. In case no type is provided, it is Void meaning no default value.
 */
template <class T = Void>
struct Modifier {
  std::optional<std::string> long = std::nullopt;
  std::optional<char> short = std::nullopt;
  std::optional<std::string> help = std::nullopt;
  std::optional<T> default = std::nullopt;
};

/**
 * @brief Helper to create a Modifier which holds a long option string.
 *
 * @param l The long option string.
 * @return A Modifier.
 */
Modifier long_option(std::string_view l) { return {l, std::nullopt, std::nullopt, std::nullopt}; }

/**
 * @brief Helper to create a Modifier which holds a short option char.
 *
 * @param s The short option char.
 * @return A Modifier.
 */
Modifier short_option(char s) { return {std::nullopt, s, std::nullopt, std::nullopt}; }

/**
 * @brief Helper to create a Modifier which holds a help string.
 *
 * @param h The help string.
 * @return A Modifier.
 */
Modifier help(std::string_view h) { return {std::nullopt, std::nullopt, h, std::nullopt}; }

template <class T>
Modifier default(T && default) { return {std::nullopt, std::nullopt, std::nullopt, std::forward<T>(default)}; }

/**
 * @brief Combines two modifiers.
 *
 * @param mod The base modifier.
 * @param other The modifier which might overwrite the base one.
 * @return The resulting modifier.
 */
Modifier operator<<(Modifier const& mod, Modifier const& other) {
  return {
    other.long.value_or(mod.long.value_or(std::nullopt)),
    other.short.value_or(mod.short.value_or(std::nullopt)),
    other.help.value_or(mod.help.value_or(std::nullopt)),
  };
};

struct ParserInfo {
  Modifier mod;
};

ParserInfo switchP(auto const& mod) {
  return {mod};
};

/**
 * @brief A parser is essentilly a function from string to some value.
 *
 * @tparam T Type of a successfull parse.
 * @return The value of type T on successfull parsing.
 */
template<class T>
struct Parser {
  explicit Parser<T>(ParserInfo const& /* pi */) {};
  T operator()(std::string_view argv) { return {true}; }
  T operator()(std::vector<std::string_view> argv) { return {true}; }
  T operator()(int const argc, char const*const* argv) {
    return (*this)(std::vector<std::string_view>{argv, argv+argc});
  }
  T operator()(int argc, char ** argv) {
    return (*this)(const_cast<int const>(argc), const_cast<char const*const*>(argv));
  }
};

}
