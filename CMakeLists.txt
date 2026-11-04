cmake_minimum_required(VERSION 3.14)
project(ArithmeticExpr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа (пока просто собирает main.cpp, если он нужен)
add_executable(main_app src/main.cpp)
target_include_directories(main_app PRIVATE include)

# --- Тесты ---
enable_testing()

# Подкачиваем GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Исполняемый файл с тестами
add_executable(tests
    tests/test_arithmetic.cpp
    tests/test_stack.cpp
)

# Подключаем include/ (там лежат Stack.h и TArithmeticExpression.h)
target_include_directories(tests PRIVATE include)

# Линкуем GTest
target_link_libraries(tests PRIVATE GTest::gtest_main)

# Автоматическое обнаружение тестов для ctest
include(GoogleTest)
gtest_discover_tests(tests)
