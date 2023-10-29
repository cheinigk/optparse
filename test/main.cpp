#include <catch2/catch_test_macros.hpp>

#include "optparse/optparse.hpp"

TEST_CASE( "initial test", "[dummy]" ) {
  REQUIRE(false);
};

TEST_CASE( "parse a bool into a struct", "[simple_options]" ) {
  //! [Parsing a switch]
  struct Config{
    bool quiet = false;
  };
  using namespace optparse;
  Parser<Config> cli_parser{
    switchP(long_option("quiet") << short_option('q') << help("whether to be quiet"))
  };
  //! [Parsing a switch]
  //! [Parsing a switch long]
  auto parsed_config = cli_parser("--quiet");
  //! [Parsing a switch long]
  REQUIRE(parsed_config == Config{true});
  //! [Parsing a switch short]
  parsed_config = cli_parser("-q");
  //! [Parsing a switch short]
  REQUIRE(parsed_config == Config{true});
  parsed_config = cli_parser("--wrong");
  REQUIRE(false);
  parsed_config = cli_parser("-w");
  REQUIRE(false);
};
