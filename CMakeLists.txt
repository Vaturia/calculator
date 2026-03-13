cmake_minimum_required(VERSION 3.10)

project(calculator)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(HEADER_FILES
    include/parser.hpp
    include/compute.hpp
    include/printer.hpp
    include/operation.hpp
    include/logger.hpp
    include/db_conn.hpp
    include/cache.hpp
    include/app.hpp
)
set(SOURCES_FILES
    src/main.cpp
)
include(FetchContent)

FetchContent_Declare(
    math_library
    GIT_REPOSITORY https://github.com/Vaturia/math-operation.git
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(math_library json spdlog)


find_package(PostgreSQL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

add_executable(calculator ${SOURCES_FILES})

target_link_libraries(calculator 
    math_library 
    nlohmann_json::nlohmann_json 
    spdlog::spdlog 
    PostgreSQL::PostgreSQL 
    zmq
)
add_executable(calculator_client client/main.cpp)

target_include_directories(calculator_client PRIVATE
    ${ZMQ_INCLUDE_DIRS}
)

target_link_libraries(calculator_client
    ${ZMQ_LIBRARIES}
)
install(TARGETS calculator DESTINATION bin)

find_program(CLANG_FORMAT "clang-format")

if(CLANG_FORMAT)

    set(ALL_FILES ${SOURCES_FILES} ${HEADER_FILES})

    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_FILES}
        COMMENT "Formattin sources files"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    add_custom_target(check-format
        COMMAND ${CLANG_FORMAT} --dry-run --Werror ${ALL_FILES}
        COMMENT "Check format"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    message(STATUS "Files for formattin: ${ALL_FILES}")
else()
    message(WARNING "clang-format not found.")
endif()
# В корневой CMakeLists.txt добавить опцию
option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)

if(ENABLE_TSAN)
    target_compile_options(calculator PRIVATE -fsanitize=thread -g)
    target_link_options(calculator PRIVATE -fsanitize=thread)
endif()

add_subdirectory(tests)