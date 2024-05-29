cmake_minimum_required(VERSION 3.14)
project(ev_stl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test.exe
  test/vector_test.cpp
  test/binary_search_tree_test.cpp
  test/avl_tree_test.cpp
  test/set_test.cpp
)

target_link_libraries(
  test.exe
  GTest::gtest_main
)

target_include_directories(
  test.exe
  PUBLIC
  include
)

include(GoogleTest)
gtest_discover_tests(test.exe)

