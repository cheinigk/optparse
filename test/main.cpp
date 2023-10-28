#include <catch2/catch_test_macros.hpp>

#include "optparse/optparse.hpp"

TEST_CASE( "initial test", "[dummy]" ) {
  REQUIRE(false);
};

TEST_CASE( "parse a bool into a struct", "[simple_options]" ) {
  struct Config{
    bool quiet;
  };
  using namespace optparse;
  Parser<Config> cli_parser{
    switchP(long_option("quiet") << short_option('q') << help("whether to be quiet"))
  };
  auto parsed_config = cli_parser("--quiet");
  REQUIRE(false);
  parsed_config = cli_parser("-q");
  REQUIRE(false);
  parsed_config = cli_parser("--wrong");
  REQUIRE(false);
  parsed_config = cli_parser("-w");
  REQUIRE(false);
};
