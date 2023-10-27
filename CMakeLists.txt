if(NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.12)

  project(optparse VERSION 0.0.1 LANGUAGES CXX)

  set(library_target "${PROJECT_NAME}")

  add_library(${library_target} INTERFACE)
  add_library(${PROJECT_NAME}::${library_target} ALIAS ${library_target})

  target_include_directories(${library_target} INTERFACE include)

  target_compile_features(boost_hana INTERFACE cxx_std_20)
else()
  cmake_minimum_required(VERSION 3.12)

  project(optparse VERSION 0.0.1 LANGUAGES CXX)

  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

  set(library_target "${CMAKE_PROJECT_NAME}")

  add_library(${library_target} INTERFACE)
  add_library(${PROJECT_NAME}::${library_target} ALIAS ${library_target})
  target_include_directories(${library_target} INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
  target_compile_features(${library_target} INTERFACE cxx_std_20)

  # Export the `optparse` library into a optparseConfig.cmake file
  install(TARGETS ${library_target}
          EXPORT ${CMAKE_PROJECT_NAME}Config
          INCLUDES DESTINATION include)
  install(EXPORT ${CMAKE_PROJECT_NAME}Config
          DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})
  install(DIRECTORY include/${CMAKE_PROJECT_NAME}
          DESTINATION include
          FILES_MATCHING PATTERN "*.hpp")

  enable_testing()
  add_subdirectory(test)
endif()
