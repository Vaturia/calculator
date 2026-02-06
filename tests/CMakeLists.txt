# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Опция для включения/отключения тестов
option(ENABLE_TESTS "Enable tests" ON)

if(ENABLE_TESTS)
    # Подключаем GoogleTest только для тестов
    include(FetchContent)
    
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    )
    
    FetchContent_MakeAvailable(googletest)
    
    # Получаем зависимости из основного проекта
    # Они уже должны быть доступны, так как основной CMakeLists.txt загрузил их раньше
    
    # Создаём исполняемый файл для тестов
    add_executable(run_tests
        # Точка входа для тестов
        main.cpp
        
        # Тестовые файлы
        compute_test.cpp
        parser_test.cpp
        printer_test.cpp
    )
    
    # Подключаем заголовочные файлы
    target_include_directories(run_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )
    
    # Линкуем с теми же библиотеками, что и основное приложение
    target_link_libraries(run_tests PRIVATE
        math_library
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        gtest  # Только gtest, без gtest_main (у нас свой main)
        # НЕ добавляем gtest_main!
    )
    
    # Добавляем в CTest для удобства запуска
    include(GoogleTest)
    gtest_discover_tests(run_tests)
    
    # Сообщаем о создании тестов
    message(STATUS "Tests enabled. Use './tests/run_tests' to run them.")
else()
    message(STATUS "Tests disabled.")
endif()