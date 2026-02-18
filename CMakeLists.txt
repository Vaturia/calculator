cmake_minimum_required(VERSION 3.10)

project(calculator)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
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

add_executable(calculator ${SOURCES_FILES})
target_link_libraries(calculator math_library nlohmann_json::nlohmann_json spdlog::spdlog PostgreSQL::PostgreSQL)

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

add_subdirectory(tests)