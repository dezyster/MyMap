cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  rbtree_tests rbtree_tests.cc map_tests.cc mutual_tests.cc
)

target_link_libraries(
  rbtree_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(rbtree_tests)
