cmake_minimum_required(VERSION 3.14)
project(ArithmeticExpr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Основная программа ----
add_executable(main_app src/main.cpp)
target_include_directories(main_app PRIVATE include)

# ---- Тесты ----
enable_testing()

include(FetchContent)

# не собираем gmock и не ставим gtest в систему — меньше поводов для ошибок
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests/test_arithmetic.cpp
    tests/test_stack.cpp
    tests/test_queue.cpp
)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE GTest::gtest_main)

# вместо gtest_discover_tests (POST_BUILD) — обычный add_test
add_test(NAME all_tests COMMAND tests)
