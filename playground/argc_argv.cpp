#include <numeric>
#include <iostream>
#include <vector>
#include <string_view>
#include <stdlib.h>


int main(int const argc, char const*const* argv) {
  using std::cout;
  cout << "argc: " << argc;
  // auto save_argv = std::span<std::string_view>{argv, argc};
  for(auto idx=0; idx < argc; ++idx) {
    cout << ", argv[" << idx << "]: " << argv[idx];
  }
  cout << "\n";
  std::vector<std::string_view> save_argv{argv, argv+argc};
  int cur_argc = 0;
  std::string args = "argv[0]: ";
  args = std::accumulate(
    std::next(std::begin(save_argv)), std::end(save_argv),
    args += save_argv[cur_argc++],
    [&cur_argc](auto res, auto next){
      res += ", argv[" + std::to_string(cur_argc++) + "]: ";
      res += next;
      return res;}
  );
  cout << "argc: " << argc << ", " << args << "\n";
  return EXIT_SUCCESS;
}
