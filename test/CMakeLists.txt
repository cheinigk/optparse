Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        devel
)

FetchContent_MakeAvailable(Catch2)

set(test_target "${CMAKE_PROJECT_NAME}-test")
add_executable(${test_target} main.cpp)
target_link_libraries(${test_target} PRIVATE ${CMAKE_PROJECT_NAME}::${library_target})

# Enable warnings.
target_compile_options(${test_target} PRIVATE
  $<IF:$<CXX_COMPILER_ID:AppleClang,Clang>,-Weverything,>
  -Wno-c++98-compat -Wno-padded -Wno-c++98-compat-pedantic
  -D_GLIBCXX_DEBUG
  )
target_link_options(${test_target} PRIVATE -D_GLIBCXX_DEBUG)

# Coverage
target_compile_options(${test_target} PRIVATE
  -ftest-coverage
  $<IF:$<CXX_COMPILER_ID:AppleClang,Clang>,-fprofile-instr-generate -fcoverage-mapping -mllvm -runtime-counter-relocation,>
  )
target_link_options(${test_target} PRIVATE
  -ftest-coverage
  $<IF:$<CXX_COMPILER_ID:AppleClang,Clang>,-fprofile-instr-generate -fcoverage-mapping -mllvm -runtime-counter-relocation,>
  )

# Testing
target_link_libraries(${test_target} PRIVATE Catch2::Catch2WithMain)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(${test_target})
