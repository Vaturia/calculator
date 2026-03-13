include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

add_executable(run_tests test_client.cpp)

target_include_directories(run_tests PRIVATE
    ${ZMQ_INCLUDE_DIRS}
)

target_link_libraries(run_tests
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    ${ZMQ_LIBRARIES}
)

enable_testing()
add_test(NAME CalculatorTests COMMAND run_tests)

message(STATUS "Tests enabled. Use './build/tests/run_tests' to run them.")